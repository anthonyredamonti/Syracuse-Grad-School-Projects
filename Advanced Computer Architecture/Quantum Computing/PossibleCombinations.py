# Anthony Redamonti
# Advanced Computer Architecture
# 11-4-2021
# Final Paper: Quantum Computing

# The following program returns all possible numbers that
# satisfy the logical expression using a classical computer.
 
import time
import random

possibleCombinations = []

# return the value of the requested bit ('0' or '1')
def getBitValue(integer, bitNumber):
    twoValue = pow(2, bitNumber)
    if(integer & twoValue != 0):
        return 1
    else:
        return 0

# return the number of combinations that satisfy the logical
# expression.
def testAllCases(highestOrderBit):
    greatestBit = highestOrderBit
    maxNumber = pow(2, greatestBit)

    # iterate through each possible answer and test it using the circuit (if-statement).
    for i in range(maxNumber):
        if(((getBitValue(i, 0) & getBitValue(i, 1)) | (getBitValue(i, 2) & getBitValue(i, 3))) & ~(getBitValue(i, 4) & getBitValue(i, 5))):
            possibleCombinations.append(i)
    return

StartTime1 = time.time()
testAllCases(6)  # test all six-bit numbers through logical expression (circuit)
EndTime1 = time.time()

print("The number of combinations that satisfied the logical expression for a 6-bit number: " + str(len(possibleCombinations)))
TotalTime = (EndTime1 - StartTime1)
print("The total time for the 6-bit calculation: {0}".format("{:.{}f}".format(TotalTime, 8)))

for i in range(len(possibleCombinations)):
    print(bin(possibleCombinations[i]))

possibleCombinations.clear()

#StartTime2 = time.time()
#numberOfCombinations20Bits = returnNumberOfPossibleCombinations(20)
#EndTime2 = time.time()

#print("The number of combinations that satisfied the logical expression for a 20-bit number: " + str(numberOfCombinations20Bits))
#TotalTime = (EndTime2 - StartTime2)
#print("The total time for the 20-bit calculation: {0}".format("{:.{}f}".format(TotalTime, 8)))

#StartTime3 = time.time()
#numberOfCombinations22Bits = returnNumberOfPossibleCombinations(22)
#EndTime3 = time.time()

#print("The number of combinations that satisfied the logical expression for a 22-bit number: " + str(numberOfCombinations22Bits))
#TotalTime = (EndTime3 - StartTime3)
#print("The total time for the 22-bit calculation: {0}".format("{:.{}f}".format(TotalTime, 8)))

#for i in range(len(possibleCombinations)):
    #print(possibleCombinations[i])