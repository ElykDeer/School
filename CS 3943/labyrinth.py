#!/usr/bin/python

# So the story with this one is that I thought it was doing something other than what it was, overcomplicated my solver (the middle bits), realized it wasn't doing what I thought it was, and then just used the first bit with z3 to get some working combinations out, and then worked in a cycle of trying to get those outputs to work in the form of the puzzle (certain numbers can only jump to certain other numbers), and fuding the z3 minimums/values until I got a set that worked out nicely.

from pwn import *
# from __future__ import print_function
# from z3 import Ints, Solver, BitVec
# from re import sub
#
# #Solve the problem using Z3:
# a, b, c, d, e, f, g, h, i, j, aVal, bVal, cVal, dVal, eVal, fVal, gVal, hVal, iVal, jVal = Ints('a b c d e f g h i j aVal bVal cVal dVal eVal fVal gVal hVal iVal jVal')
#
# s = Solver()
# s.add(a>0, b>=1, c>=1, d>=1, e>=1, f>=1, g>=1, h==0, i>=1, j>=1)
# # s.add(a>=0, b<=*10, c<=a*10, d<=*10, e<=*10, f<=*10, g<=*10, h<=*10, i<=*10, j<=*10)
# s.add(aVal==0xe3, bVal==0x01f9, cVal==0x0468, dVal==0x0213, eVal==0x0121, fVal==0x03a9, gVal==0x019a, hVal==0x013a, iVal==0x0362, jVal==0x02c6)
# s.add(((((((((((a*aVal)+b*bVal)+c*cVal)+d*dVal)+e*eVal)+f*fVal)+g*gVal)+h*hVal)+i*iVal)+j*jVal) == 0x257b)
# s.add(a + b + c + d + e + f + g + h + i + j <= 0x80)
# print("Getting solutions...", end='')
# if str(s.check()) == "sat":
#     print("done!")
# else:
#     print("failed!")
#     quit()

# Extract data from model
# mod = str(s.model())
# print(mod)
# mod = re.sub(r"(,\n .Val)(.|\n)*\]", ']', mod)
# mod = re.sub(r"[\[\]\,\s=]", '', mod)
# values = {}
# for var,val in zip(mod[::2], mod[1::2]):
#     values[var] = int(val)

# Get data in order:
# position = 'a'
# vals = []
# while position <= 'j':
#     vals.append(values[position])
#     position = chr(ord(position) + 1)

# Build exploit
 #L incs pointer by 0x8
 #R incs pointer by 0x10
 #Other characters do nothing

# fffR ffffL R L fR L ffL L L f
# fffRffffLRLfRLffLLLf
# a = 4
# g = 5
# j = 1
# d = 1
# i = 2
# b = 1
# e = 3
# f = 1
# a = 1
# c = 1

sploit = 'fffRffffLRLfRLffLLLf'

# Open Program
debug = False
if debug:
    p = process("./labyrinth")
    pause()
else:
    # Connect and log in
    p = remote("offsec-chalbroker.osiris.cyber.nyu.edu", 1253)
    p.recvuntil("):")
    p.sendline("krm504")

p.recvuntil("ugh?")
p.sendline(sploit)
p.recvuntil("friend: ")
print(p.recvuntil("}"))
