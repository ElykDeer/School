#Data taken out of the hex editor..this data is copied to executable mem
crypt = "974623344d8ac47e7c7c7c737997472234f5bbc6837c7c7cc47c7c7c7c7379c37d7c7c7cc6837c7c7cc47d7c7c7c7379c37c7c7c7cc4407c7c7c737994bd8383831a101d1b520804087c94bc83838300"

#Then that mem is xored with a one byte value
for i in range(256):
    print(i, end=": ")
    for (a,b) in zip(crypt[0::2], crypt[1::2]):
        byte = a + b
        print(chr(int(byte, 16)^i), end='')
    print("")
    
# Pipe this to a file, CTRL-f it for flag... It happenes to be 124