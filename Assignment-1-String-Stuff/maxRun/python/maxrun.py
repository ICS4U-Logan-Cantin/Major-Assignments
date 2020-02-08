# MAXRUN
# Created by: Logan Cantin
# Created on: 07-Feb-2019
# Created for: ICS4U
# Assignment 1 (String Stuff) - Max Run
# This program finds and prints the size of the largest run of identical characters

# Getting user input
inputString = input()

# Setting variables
maxRun = 0
pivot = 0
inputLength = len(inputString)

# Making sure to stay inside the bounds of the string
while pivot < inputLength:

    # Getting the first character of this run and setting the initial size
    tempChar = inputString[pivot]
    tempRun = 1

    # Incrementing the size of the run for each adjacent and identical character (making sure not to go off the screen)
    while (pivot + tempRun) < inputLength and inputString[pivot + tempRun] == tempChar:
        tempRun += 1

    # If current run is larger than largest run, replace it
    if tempRun > maxRun:
        maxRun = tempRun

    # Increase pivot
    pivot += tempRun

# Print answer
print(maxRun)