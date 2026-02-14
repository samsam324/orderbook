# ITCH 5.0 notes

This is a quick reference for the ITCH messages we plan to support for an L3 order book for one symbol. We will verify details once we pull real sample files, but this is the target scope.

## Implemented message subset
- S: System Event
- R: Stock Directory (stock locate -> symbol mapping)
- A: Add Orde
- F: Add Order with MPID
- E: Order Executed
- C: Order Executed with Price
- X: Order Cancel
- D: Order Delete
- U: Order Replace (cancel/replace with new order id)
- P: Trade (tape only, does not update the book)

## Decoder principles
- Parse by message type using fixed byte offsets (per Nasdaq spec)
- Convert endianness
- Use ITCH timestamp field as event time (nanoseconds since midnight probably)
- Symbol filtering:
  - Build stock locate -> symbol from R messages
  - Only forward events for the configured symbol

## Replace semantics
-Treat U as cancel/replace:
  - remove the old order id (remaining shares removed)
  - add the new order id with new qty and possibly new price
  - side and symbol stay the same
