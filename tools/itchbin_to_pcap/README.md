# itchbin_to_pcap
Owner: ROLE 1 (IO/Networking/PCAP) + ROLE 2 (Protocols)

This tool will convert Nasdaq historical ITCH 5.0 binfiles into a standard .pcap that contains synthetic Ethernet/IP/UDP frames carrying MoldUDP64 payloads.

## Status
ALOT to do lol. we got this tho

## Intended CLI

- `--in <path>` input ITCH binfile (decompressed stream)
- `--out <path>` output .pcap
- `--symbol <SYM>` applied at decode stage later
- `--msgs_per_pkt <N>` how many ITCH messages to pack into a MoldUDP64 datagram

## Implementation notes

- Read length prefixed ITCH messages
- Group into MoldUDP64 packets:
  - Mold header: session + seq + msg_count
  - Blocks: [u16 len][msg bytes]...
- Write PCAP:
  - global header: DLT_EN10MB
  - per record header timestamps derived from ITCH timestamp (ns since midnight)
  - synthetic L2/L3 headers (dummy MAC/IP ok)