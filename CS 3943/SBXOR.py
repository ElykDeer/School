#!/usr/bin/python

f = open("ciphertext.txt")
f = "".join(f.readlines())

# Repeating key string xor
def sxor(m, k):
    k *= (len(m)/len(k)) + 1
    return ''.join(chr(ord(mc) ^ ord(kc)) for mc, kc in zip(m, k))

for key in range(256):
    test = sxor(f, chr(key))

    # Check for known plaintext
    if test[:5] == "flag{":
        print(sxor(f, chr(key)))
