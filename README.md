# Orderbook (Nasdaq ITCH L3) — skeleton monorepo

Backend (Ubuntu / WSL2):

```bash
cd backend
mkdir -p build && cd build
cmake .. && cmake --build .
./md_engine --input sim_udp --symbol AAPL --queue mutex --threads single_thread --ws_port 8787 --duration_ms 3000
```

Frontend:

```bash
cd frontend
npm i
npm run dev
```

Open the Vite URL and you should see the UI.
The event tape will show placeholder WS messages once the backend is running.

## Docs

See the `docs/` folder for architecture notes, dataset instructions, and role ownership.
