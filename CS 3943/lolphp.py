#This does not work as a solver because the two inputs are === against eachother
 #if they were ==, it would work.  The real answer is to change the URL to end
 #with thing1[]=a&thing2[]=b

import hashlib

thing1 = 0
while hashlib.sha256(hex(thing1)).hexdigest()[:2] != "0e" or "a" in hashlib.sha256(hex(thing1)).hexdigest()[2:] or "b" in hashlib.sha256(hex(thing1)).hexdigest()[2:] or "c" in hashlib.sha256(hex(thing1)).hexdigest()[2:] or "d" in hashlib.sha256(hex(thing1)).hexdigest()[2:] or "e" in hashlib.sha256(hex(thing1)).hexdigest()[2:] or "f" in hashlib.sha256(hex(thing1)).hexdigest()[2:]:
    thing1 += 1

print("thing1 done!")

thing2 = 0
while hashlib.sha256(hex(thing2)).hexdigest()[:2] != "0e" or thing1 == thing2:
    thing2 += 1
    
    
print(hex(thing1))
print(hashlib.sha256(hex(thing1)).hexdigest())

print(hex(thing2))
print(hashlib.sha256(hex(thing2)).hexdigest())
