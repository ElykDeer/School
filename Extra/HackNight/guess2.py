from __future__ import print_function
import socket
import random

#Open 'er up!
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#Guess 1 game hosted on: hn.csaw.io 9003
sock.connect(("hn.csaw.io",9001))


#Keep all our code in here so we can close the connection when we're done
try:
	#Keep guessing!
	token = ""
	GuessCount = 0
	while not "YOU" in token:
		##Reconnect
		sock.shutdown(socket.SHUT_RDWR)		#Wastes one connect cycle
		sock.close()		#Wastes one connect cycle
		#Guess 1 game hosted on: hn.csaw.io 9003
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		sock.connect(("hn.csaw.io",9001))
		
		#Clear buffer
		sock.recv(1024)
		
		#Make and send guess
		guess = random.randrange(101)
		#guess = 5
		sock.send( str(guess)+'\n' )
		GuessCount += 1
		print(str(GuessCount) + ": " + str(guess), end='\b\b\b\b\b\b\b\b\b\b') #Cool Updaty thing
		
		#Check if winner
		token = sock.recv(3) #Echo buffer
		token = sock.recv(4) #Responce
	print("Total Guesses: " + str(GuessCount))
	
finally:
    ##Now Get key!!
    print(sock.recv(1024))
    
    print("")
    print ("Throwing sock away.")
    sock.close()
