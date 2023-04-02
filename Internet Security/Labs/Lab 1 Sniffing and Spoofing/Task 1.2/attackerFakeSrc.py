#!/usr/bin/python3
from scapy.all import *

ip = IP()
ip.dst = '10.0.2.5' # client IP address
ip.src = '10.0.2.99' # attacker's IP address

icmp = ICMP()
packet = ip/icmp
send(packet, verbose = False) # verbose = False means do not print data after sending
