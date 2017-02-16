#Author: Kyle Martin
#
#Written for HackNight, on 2/8/16

#print better
from __future__ import print_function
#Need to connect to the interwebs:
import socket

def figureOutMoney(cents): #Let's just use the source code to calculate how much money we need of each type
    coins = []
    cents *= 100.0
    coins.append(int(cents / 1000000.0))
    cents %= 1000000.0
    coins.append(int(cents / 500000.0))
    cents %= 500000.0
    coins.append(int(cents / 100000.0))
    cents %= 100000.0
    coins.append(int(cents / 50000.0))
    cents %= 50000.0
    coins.append(int(cents / 10000.0))
    cents %= 10000.0
    coins.append(int(cents / 5000.0))
    cents %= 5000.0
    coins.append(int(cents / 2000.0))
    cents %= 2000.0
    coins.append(int(cents / 1000.0))
    cents %= 1000.0
    coins.append(int(cents / 500.0))
    cents %= 500.0
    coins.append(int(cents / 100.0))
    cents %= 100.0
    coins.append(int(cents / 50.0))
    cents %= 50.0
    coins.append(int(cents / 25.0))
    cents %= 25.0
    coins.append(int(cents / 10.0))
    cents %= 10.0
    print("COINS LEFT: "+str(cents))
    coins.append(int(cents / 5.0))
    cents %= 5.0
    coins.append(int(round(cents)))

    return coins

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#Coinslot hosted on: misc.chal.csaw.io 8000
sock.connect(("misc.chal.csaw.io",8000))

#Keep all our code in here so we can close the connection when we're done
try:
    #Start getting data
    while 1:
        money = float(sock.recv(6)[1:]) #Get money amount
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
