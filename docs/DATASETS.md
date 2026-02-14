# Datasets

## Nasdaq TotalView-ITCH historical files

Nasdaq historical ITCH files. These are not PCAP by default and instead they are a binary stream format.

This repo supports two paths:

- Direct binfile replay: parse the length prefixed ITCH stream directly
- Convert to PCAP (tools/itchbin_to_pcap): produce a standard .pcap with synthetic Ethernet/IP/UDP and MoldUDP64 payloads so you can replay via libpcap and inspect in Wireshark

## Notes

- You may need to decompress the file first:
  - `gunzip -k file.NASDAQ_ITCH50.gz`
