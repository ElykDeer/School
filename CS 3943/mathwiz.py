#Author: Kyle Martin

from pwn import *

# Connect
sock = connect("offsec-chalbroker.osiris.cyber.nyu.edu", 1236)

# Server Check
sock.recvuntil(":")
sock.sendline("krm504")

# Server Prompt
sock.recvuntil("whiz??\n", timeout = 10)

while (1):
    num1 = sock.recvuntil(" ", drop = True)
    oper = sock.recvuntil(" ", drop = True)
    num2 = sock.recvuntil(" ", drop = True)

    #Check if won
    if num1 == "Woah,":
        print(sock.recvall(timeout = 10))
    else:
        sock.recvuntil("\n")

    #Convert first number
    try:
        num1 = int(num1)
    except:
        try:
            num1 = int(num1, 2)
        except:
            try:
                num1 = int(num1, 16)
            except:
                num1String = num1.split('-')
                num1=0
                for word in num1String:
                    num1*=10
                    if word == "ONE":
                        num1 += 1
                    if word == "TWO":
                        num1 += 2
                    if word == "THREE":
                        num1 += 3
                    if word == "FOUR":
                        num1 += 4
                    if word == "FIVE":
                        num1 += 5
                    if word == "SIX":
                        num1 += 6
                    if word == "SEVEN":
                        num1 += 7
                    if word == "EIGHT":
                        num1 += 8
                    if word == "NINE":
                        num1 += 9

    #convert second number
    try:
        num2 = int(num2)
    except:
        try:
            num2 = int(num2, 2)
        except:
            try:
                num2 = int(num2, 16)
            except:
                num2String = num2.split('-')
                num2=0
                for word in num2String:
                    num2*=10
                    if word == "ONE":
                        num2 += 1
                    if word == "TWO":
                        num2 += 2
                    if word == "THREE":
                        num2 += 3
                    if word == "FOUR":
                        num2 += 4
                    if word == "FIVE":
                        num2 += 5
                    if word == "SIX":
                        num2 += 6
                    if word == "SEVEN":
                        num2 += 7
                    if word == "EIGHT":
                        num2 += 8
                    if word == "NINE":
                        num2 += 9

    # Me Answer
    if oper == "+":
        sock.sendline(str(num1+num2))
    elif oper == "-":
        sock.sendline(str(num1-num2))
    elif oper == "*":
        sock.sendline(str(num1*num2))
    elif oper == "/":
        sock.sendline(str(num1/num2))
    else:
        print(str(num1) + " " + str(oper) + " " + str(num2))

    print(sock.recvline())
