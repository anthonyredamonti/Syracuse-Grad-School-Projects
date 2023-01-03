import time
import random

def algorithm(array1, array2, n):
   number_of_zeroes = 0
   for i in range(0, n):
      for j in range(0, n):
         if(array1[i] == array2[j]):
            array2[j] = 0
            number_of_zeroes += 1
   return number_of_zeroes

N = 10
while (N <= 10000):
   print('N = ', N)
   array1 = [N]
   array2 = [N]
   for i in range(N):
      array1.append(random.randint(1, N))
      array2.append(random.randint(1, N))

   StartTime = time.time()
   zeroes = algorithm(array1, array2, N)
   EndTime = time.time()
   TotalTime = (EndTime - StartTime)
   print('number of zeroes ', zeroes)
   print("Total Time: {0}".format("{:.{}f}".format(TotalTime, 8)))
   N*=10
