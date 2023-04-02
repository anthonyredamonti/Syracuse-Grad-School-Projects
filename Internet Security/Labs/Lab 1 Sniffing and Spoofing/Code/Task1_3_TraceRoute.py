#!/usr/bin/python3
from scapy.all import *

ip = IP()
ipDestination = '10.0.2.5'
ip.dst = ipDestination # client IP address
ttlNum = 1
ip.ttl = ttlNum
numberOfHops = 0
icmp = ICMP()
packet = ip/icmp

# send sr1 to send one DNS request
answer = sr1(packet, verbose = False) # verbose = False means do not print data after sending
numberOfHops = numberOfHops + 1

while((answer != None) and (answer.src!=ipDestination)):
   ttlNum = ttlNum + 1 # increment ttl
   numberOfHops = numberOfHops + 1
   print("Router IP: ", answer.src)
   ipNew = IP()
   ipNew.dst = ipDestination # client IP address
   ipNew.ttl = ttlNum

   icmpNew = ICMP()
   packetNew = ipNew/icmpNew

   # send sr1 to send one DNS request
   answer = sr1(packetNew, verbose = False)

print("Destination IP " + ipDestination + " found!")
print("Number of hops: " + str(numberOfHops))
