# Role ownership

We split the repo so 5 people can work in parallel with minimal merge conflicts.

## Rules

- Every file starts with a comment like: // Owner: ROLE X
- Anything in backend/include/core/ is shared, but I’ll call out a primary owner when it matters.

## ROLE 1: IO / Networking / PCAP

Owns:
- backend/include/io/**
- backend/src/io/**
- backend/cmake/FindPCAP.cmake
- tools/itchbin_to_pcap/** (shared with Role 2)

To do:
- PCAP reader + writer stubs compile
- UDP recv/send stubs compile
- ITCH binfile reader stub compiles
- itchbin_to_pcap builds and the CLI runs (--help, args parse, etc.)

## ROLE 2: Protocols (MoldUDP64 + ITCH)

Owns:

- backend/include/protocols/**
- backend/src/protocols/**
- Primary owner of backend/include/core/types.hpp

To do:
- MoldUDP64 decoder API exists + compiles
- ITCH 5.0 subset decoder API exists + compiles
- Symbol registry + filtering plumbing exists (even if it’s stubbed)

## ROLE 3: Pipeline / Concurrency / Modes / Metrics plumbing

Owns:
- backend/include/transport/**
- backend/src/transport/**
- backend/include/metrics/**
- backend/src/metrics/**
- backend/include/app/**
- backend/src/app/**

Primary owner of:
- backend/include/core/config.hpp
- backend/include/core/time.hpp
- backend/include/core/logging.hpp
- backend/include/core/errors.hpp

To do:
- Queue interface + mutex queue + ring buffer APIs exist
- Engine wiring + CLI skeleton exists (flags parse, mode selection works)
- Metrics counters/latency/reporter stubs exist

## ROLE 4: L3 Order Book + Analytics

Owns:
- backend/include/book/**
- backend/src/book/**

To do:
- L3 book data structures exist + apply() stubs are in place
- Snapshot + analytics placeholder types exist
- Invariants are written down clearly in code comments

## ROLE 5: UI + Backend WebSocket API

Owns:
- backend/include/api/**
- backend/src/api/**
- frontend/**

To do:
- Message bus stub exists
- WebSocket server skeleton (Boost.Beast) runs at /ws
- React + Tailwind UI scaffold connects and consumes WS messages (even if it’s placeholder data)