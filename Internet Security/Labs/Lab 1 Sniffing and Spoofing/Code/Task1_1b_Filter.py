#!/usr/bin/python3

from scapy.all import *

def print_pkt(pkt):
   pkt.show()

# capture 20 ICMP packets
icmpPackets = sniff(filter='icmp',prn=print_pkt, count=20)

# write the ICMP packets to a PCAP file
wrpcap("IcmpPackets.pcap", icmpPackets)

# capture 20 TCP packets
#tcpPackets = sniff(filter='tcp and (src host 10.0.2.6 and dst port 23)',prn=print_pkt, count=20)

# write the TCP packets to a PCAP file
#wrpcap("TcpPackets.pcap", tcpPackets)

# capture 20 packets using the Subnet
#subnetPackets = sniff(filter='src net 10.0.2.0/24',prn=print_pkt, count=20)

# write the subnet packets to a PCAP file
#wrpcap("SubnetPackets.pcap", subnetPackets)
