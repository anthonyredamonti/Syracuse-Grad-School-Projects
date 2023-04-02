#!/usr/bin/env python3
from scapy.all import *

IPpacket = IP(dst = '10.0.2.6')
UDPpacket = UDP(dport = 53)
questionSection = DNSQR(qname = 'www.example.com')
DNSpacket = DNS(id = 100, qr = 0, qdcount = 1, qd = questionSection)
queryPacket = IPpacket/UDPpacket/DNSpacket
replyPacket = sr1(queryPacket)
dnsInfo = replyPacket[DNS]
print(repr(dnsInfo))
