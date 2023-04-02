#!/usr/bin/python3
from scapy.all import *

# create a TCP message with destination port number # 23
tcp = TCP(dport=23)

# destination IP address is 10.0.2.5
ip = IP(dst='10.0.2.5')

# wrap the IP and TCP packet
packet = ip/tcp

# send it 20 times
send(packet, count = 20)

#packet.show()

