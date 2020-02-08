# BLOWUP
# Created by: Logan Cantin
# Created on: 07-Feb-2019
# Created for: ICS4U
# Assignment 1 (String Stuff) - Blowup
# This program blows up a string by using numbers as coefficients, multiplying the letter to the right of it
#

import re

# Getting input from the user
inputString = input()

# Alerting the user if their input is invalid (contains any non-alphanumeric characters)
if re.search("^[A-Za-z0-9]*$", inputString) == None:
    print("Please enter only alphanumeric characters.")
    exit()

#Initializing vairiables
index = 0
outputString = ""

# Keeping index inside of bounds of string
while index < len(inputString):

    #Getting the character at the index
    tempChar = inputString[index]

    #If the character is a digit
    if tempChar.isdigit():

        #If the character is the last in the string, add it to the output and increment the index
        if index == len(inputString) - 1:
            outputString += tempChar
            index += 1
            continue
        
        # Calculate the next character
        nextChar = inputString[index + 1]
        
        #If the next character is a digit, add the current character to the output and increment counter
        if nextChar.isdigit():
            outputString += tempChar
            index += 1
            continue
        
        # Calculate the string to be added and add it to the output string and increment index
        multiplier = int(tempChar)
        outputString += nextChar * multiplier
        index += 1
    else:
        # Character is a letter so add it and increment index
        outputString += tempChar
        index += 1

# Print output
print(outputString)