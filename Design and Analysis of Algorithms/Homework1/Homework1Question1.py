import time
import random

def algorithm(n):
   count = 0
   for a in range(1, n):
      for b in range(a+1, n):
         print(a,b)
   return

times = []
N = 10
while (N <= 10000):
   StartTime = time.time()
   algorithm(N)
   EndTime = time.time()
   TotalTime = (EndTime - StartTime)
   times.append(TotalTime)
   N*=10

N = 10
for TotalTime in times:
   print('N = ', N)
   N *= 10
   print("Total Time: {0}".format("{:.{}f}".format(TotalTime, 8)))

