#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_date(void)
{
  struct rtcdate *rtcdate_s;

  if (argptr(0, (void*)&rtcdate_s, sizeof(*rtcdate_s)) < 0)
    return -1;

  cmostime(rtcdate_s);

  // This probably works....completely ignores leap years and dayllight savings and all that nonsense.
  if (rtcdate_s->hour < 5)
  {
    if (rtcdate_s->day == 1)
    {
      if (rtcdate_s->month == 1)
      {
        rtcdate_s->month = 12;
        rtcdate_s->day = 31;
        rtcdate_s->hour += 19;
      }
      else
      {
        if (rtcdate_s->month == 2)
          rtcdate_s->day = 31;
        else if (rtcdate_s->month == 3)
          rtcdate_s->day = 28;
        else if (rtcdate_s->month == 4)
          rtcdate_s->day = 31;
        else if (rtcdate_s->month == 5)
          rtcdate_s->day = 30;
        else if (rtcdate_s->month == 6)
          rtcdate_s->day = 31;
        else if (rtcdate_s->month == 7)
          rtcdate_s->day = 30;
        else if (rtcdate_s->month == 8)
          rtcdate_s->day = 31;
        else if (rtcdate_s->month == 9)
          rtcdate_s->day = 31;
        else if (rtcdate_s->month == 10)
          rtcdate_s->day = 30;
        else if (rtcdate_s->month == 11)
          rtcdate_s->day = 31;
        else if (rtcdate_s->month == 12)
          rtcdate_s->day = 30;
        rtcdate_s->month -= 1;

        rtcdate_s->hour += 19;
      }
    }
    else
    {
      rtcdate_s->day  -= 1;
      rtcdate_s->hour += 19;
    }
  }
  else
  {
    rtcdate_s->hour -= 5;
  }

  return 0;
}