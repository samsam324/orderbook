# MoldUDP64 notes
MoldUDP64 is a lightweight UDP wrapper some exchanges use to pack multiple messages into one UDP datagram. It does not define the message format itself, it just frames the bytes.

## Packet layout
- Session: 10 bytes ASCII
- Sequence number: 8 bytes ASCII digits (sequence of the first message in this packet)
- Message count: 2 bytes unsigned big endian
- Then message_count blocks:
  - Length: 2 bytes unsigned big endian
  - Message bytes: length bytes (an ITCH message in this project)

## Sequence handling
- Each packet carries a base sequence.
- The per message sequence is base_seq + i
- For offline replay, detect gaps and increment counters (no retransmit)
