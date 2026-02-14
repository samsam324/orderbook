# Runbook (skeleton demo)

This runbook gives exact commands to build and run.
Later it will include real dataset replay and PCAP conversion steps.

## 1) Install dependencies (Ubuntu / WSL2)

```bash
sudo apt update
sudo apt install -y build-essential cmake pkg-config libboost-all-dev libpcap-dev
```

Node:

```bash
sudo apt install -y nodejs npm
```

## 2) Build backend

```bash
cd backend
mkdir -p build && cd build
cmake .. && cmake --build .
ctest --output-on-failure
```

## 3) Run backend (skeleton)

```bash
./md_engine --input sim_udp --symbol AAPL --queue ring --threads single_thread --ws_port 8787 --duration_ms 30000
```

## 4) Run frontend

```bash
cd ../../frontend
npm i
npm run dev
```

Open the printed local URL. You should see a connected indicator and raw JSON messages in the tape.

## Dataset + conversion example

These commands are placeholders until itchbin_to_pcap is fully implemented:

```bash
./tools/itchbin_to_pcap --in 07302019.NASDAQ_ITCH50 --out sample.pcap --symbol AAPL --msgs_per_pkt 30
./backend/md_engine --input pcap_replay --pcap sample.pcap --symbol AAPL --queue ring --ws_port 8787 --speed 10
```

