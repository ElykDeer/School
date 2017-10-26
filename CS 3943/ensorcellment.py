from __future__ import print_function
from pwn import *
import re

def getFlag():
    # Connect and log in
    p = connect("offsec-chalbroker.osiris.cyber.nyu.edu", 1254)
    p.recvuntil("):")
    p.sendline("krm504")

    #Clear prompts
    p.recvuntil('!\n')

    # Get data
    data = p.recvall()

    # No longer need connections
    p.close()

    layers = 0

    # Decrypt Data
    while not "flag{" in data:
        layers += 1
        print("Layer " + str(layers), end='; ')

        # Purge bad characters
        data = re.sub(r'[\'\"/\\]', '', data)

        # Determine base and convert
        base64Regex = re.compile(r'[A-Z]')
        base64Match = base64Regex.search(data)

        if not base64Match == None:
            print("base64")
            data = data.decode("base64")
        else:
            print("Hex")
            data = data.decode("hex")

    print(data)

trying = True
while trying:
    try:
        getFlag()
        trying = False
    except:
        print("I think I got some bad data. Trying again..")
