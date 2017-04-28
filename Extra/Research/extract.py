#Author: Kyle Martin

from __future__ import print_function
from binaryninja import *
import sys

#Keep track of what we've scrapped,
  #so we don't recursively scrape recursive functions
scrapedFunctions = []

def scrape(bv, functionPointer):
    #Check if function has already been analyzed
    if functionPointer in scrapedFunctions:
        print(functionPointer + " has already been scrapped, not rescraping.")
        return ""

    #Try to find function
    print("Looking for function at: " + functionPointer, end=' - ')
    sys.stdout.flush()
    try:
        function =  bv.get_functions_at(int(functionPointer, 16))[0]
    except:
        print("Function not found at that address.")
        return ""
    print("Found.")

    #Start Building Stuff Up
    functionInAString = functionPointer[1:] + ":\n" #Function name
    subfunctions = [] #List of subfunctions to also extract
    for block in function:
        #If not the beginning of a function, add block address
        if functionInAString != (functionPointer[1:] + ":\n"):
            functionInAString += " ." + str(hex(block.start))[1:-1] + ":\n"
        for line in block:
            #Catch calls as to digest them later
            if str(line[0][0]) == 'call':
                subfunctions.append(str(line[0][2]))

            #Add opcode
            functionInAString += ' ' + str(line[0][0]) + ' '

            #catch jump statements to localize subfunctions
            if str(line[0][0])[0] == 'j':
                functionInAString += '.' + str(line[0][2])[1:] + '\n'
                continue #Don't re-add return address

            #Add any other operands
            for operand in line[0][2:]:
                functionInAString += str(operand)
            functionInAString += '\n'
        functionInAString += '\n' #Visually Seperate Blocks
    functionInAString += '\n\n' #Viually Seperate Functions

    #Don't rescrape (recursive functions)
    scrapedFunctions.append(functionPointer)

    #Get all functions that I call and put it above me
    programInAString = ""
    for subfunc in subfunctions:
        functionInAString = scrape(bv, subfunc) + functionInAString

    return functionInAString


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print('Usage: {} <file> <functionPointer>'.format(sys.argv[0]))
    else:
        #Try to open file
        print("Opening: " + sys.argv[1], end=' - ')
        sys.stdout.flush()
        try:
            bv = BinaryViewType.get_view_of_file(sys.argv[1]) #Open file
        except:
            print("File could not be opened.")
            quit()
        print("Opened.")

        ### This part should probably be edited by each user,
        ###   if they don't want a new file on their system
        outputFilename = 'digest.asm'
        output = open(outputFilename, 'w')
        #Scrape it
        output.write(scrape(bv, sys.argv[2]))
        output.close()
        print("Done.\nScrapped functions in " + outputFilename + '.')
