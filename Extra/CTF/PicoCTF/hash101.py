#Doesn't work!

from pwn import *
import binascii

sock = connect("shell2017.picoctf.com", 34959)

sock.recvuntil("of ")

chal = sock.recvline()[:-1]
part1 = binascii.b2a_uu(chal)[:-1]
print(chal)
print(part1)
sock.sendline(part1)
sock.interactive()
