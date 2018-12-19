// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "bcrypt.h"

char *argv[] = { "sh", 0 };


int
input_password(char *buf, int nbuf)
{
  memset(buf, 0, nbuf);
  gets(buf, nbuf);
  if(buf[0] == 0)
    return -1;
  return 0;
}


int
login(void)
{
  int fd;
  int i = 0;
  int r = 0;
  char salt[16];
  char hash[BCRYPT_HASHLEN];
  char* generated_hash;
  char password[32];
  char input_1[32];
  char input_2[32];

  if ((fd = open(".password", O_RDONLY)) < 0)
  {
    // File doesn't exist, create it and save hash/salt
    if ((fd = open(".password", O_CREATE|O_WRONLY)) < 0)
    {
      printf(1, "init: failed to create password file\n");
      exit();
    }

    while(i == 0)
    {
      printf(1, "Input password: ");
      if (input_password(input_1, sizeof(input_1)) < 0)
      {
        printf(1, "init: failed to input password\n");
        exit();
      }

      printf(1, "Confirm password: ");
      if (input_password(input_2, sizeof(input_2)) < 0)
      {
        printf(1, "init: failed to input password\n");
        exit();
      }

      if (strcmp(input_1, input_2))  // Not equal
        printf(1, "Passwords not the same. Try again.\n");
      else
        i = 1;
    }

    // Write salted password hash and salt
    for (i=0; i<(16/sizeof(i)); ++i)
    {
      r = random();

      memset(salt + i*4 - 0, r, 1);
      r >>= 8;
      memset(salt + i*4 - 1, r, 1);
      r >>= 8;
      memset(salt + i*4 - 2, r, 1);
      r >>= 8;
      memset(salt + i*4 - 3, r, 1);
    }

    generated_hash = (char*)bcrypt(input_1, (uchar*)salt);

    write(fd, salt, sizeof(salt));
    write(fd, generated_hash, sizeof(password));
  }
  else
  {
    // Password file exists
    // Load file into two strings, salt and password
    if (read(fd, salt, sizeof(salt)) <= 0)
    {
      printf(1, "init: read salt error\n");
      exit();
    }

    if (read(fd, hash, sizeof(hash)) <= 0)
    {
      printf(1, "init: read saved hash error\n");
      exit();
    }

    // Input password, add salt, calculate hash
    for (i = 0; i < 2; ++i)
    {
      printf(1, "Input password: ");
      if (input_password(password, sizeof(password)) < 0)
      {
        printf(1, "init: failed to input password\n");
        exit();
      }

      if (bcrypt_checkpass(password, (uchar*)salt, (uchar*)hash) == 0)
        break;
      else
        printf(1, "Wrong password, try again\n");
    }

    if (i == 2)
    {
      close(fd);
      return -1;
    }
  }

  close(fd);
  return 0;
}


int
main(void)
{
  int pid, wpid;

  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr

  for(;;){
    printf(1, "init: starting sh\n");
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      if (login() == 0)
        exec("sh", argv);

      printf(1, "init: exec sh failed\n");
      exit();
    }
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
  }
}
