#Author: Kyle Martin
#
#Written for HackNight, on 2/8/16

#print better
from __future__ import print_function
#Need to connect to the interwebs:
import socket

def figureOutMoney(cents): #Let's just use the source code to calculate how much money we need of each type
    coins = []
    cents = cents*100
    coins.append(int(round(cents)) // 1000000)
    cents = int(round(cents)) % 1000000
    coins.append(int(round(cents)) // 500000)
    cents = int(round(cents)) % 500000
    coins.append(int(round(cents)) // 100000)
    cents = int(round(cents)) % 100000
    coins.append(int(round(cents)) // 50000)
    cents = int(round(cents)) % 50000
    coins.append(int(round(cents)) // 10000)
    cents = int(round(cents)) % 10000
    coins.append(int(round(cents)) // 5000)
    cents = int(round(cents)) % 5000
    coins.append(int(round(cents)) // 2000)
    cents = int(round(cents)) % 2000
    coins.append(int(round(cents)) // 1000)
    cents = int(round(cents)) % 1000
    coins.append(int(round(cents)) // 500)
    cents = int(round(cents)) % 500
    coins.append(int(round(cents)) // 100)
    cents = int(round(cents)) % 100
    coins.append(int(round(cents)) // 50)
    cents = int(round(cents)) % 50
    coins.append(int(round(cents)) // 25)
    cents = int(round(cents)) % 25
    coins.append(int(round(cents)) // 10)
    cents = int(round(cents)) % 10
    coins.append(int(round(cents)) // 5)
    cents = int(round(cents)) % 5
    coins.append(int(round(cents)))

    return coins

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#Coinslot hosted on: misc.chal.csaw.io 8000
sock.connect(("misc.chal.csaw.io",8000))

#Keep all our code in here so we can close the connection when we're done
try:
    #Start getting data
    while 1:
        intput = '' #Input a new number until the newline
        accumulatedString = '' #String that will build up from accumulating one digit at a time
        while (intput != '\n'):
            accumulatedString += intput
            intput = sock.recv(1)
        money = float(accumulatedString[1:]) #need to convert this to a number
        
        answers = figureOutMoney(money) #figure out the cents needed to submit
        
        print("Amount: " + str(money) + "\tDigested: " + str(answers))
        for amount in answers:
            #Clear Prompts character by character
            
            lastChar = ""
            while not lastChar == ':': #Colin at the end of each line... Nifty
                lastChar = sock.recv(1)
            lastChar = sock.recv(1) #Gotta wipe trailing space
            
            #Send Amount
            sock.send(str(amount)+"\n")
        
        sock.recv(9) #Cleanup Congratulations Message
        
finally:
    ##Now Get key!!
    print(sock.recv(1024))
    
    print("")
    print ("Throwing sock away.")
    sock.close()