/** Owner: ROLE 5 (UI + Backend WS API) */
import { useEffect, useMemo, useRef, useState } from "react";
import type { ConnectionState, UiStats, WsEnvelope } from "./types";
import { connectWs } from "./ws";
import { OrderBookL3 } from "../components/OrderBookL3";
import { OrderTape } from "../components/OrderTape";
import { StatsPanel } from "../components/StatsPanel";
import { Controls } from "../components/Controls";

type TapeItem = {
  t: number;
  raw: WsEnvelope;
};

export function App() {
  const wsUrl = useMemo(() => `ws://localhost:8787/ws`, []);
  const [conn, setConn] = useState<ConnectionState>("disconnected");
  const [tape, setTape] = useState<TapeItem[]>([]);
  const [uiStats, setUiStats] = useState<UiStats>({ msgsPerSec: 0, lastMessageAtMs: null });

  const msgCountRef = useRef(0);
  const lastTickRef = useRef<number>(Date.now());

  useEffect(() => {
    const c = connectWs(wsUrl, {
      onState: setConn,
      onMessage: (m) => {
        msgCountRef.current += 1;
        setUiStats((s) => ({ ...s, lastMessageAtMs: Date.now() }));
        setTape((prev) => {
          const next = [{ t: Date.now(), raw: m }, ...prev];
          return next.slice(0, 2000);
        });
      }
    });

    const id = window.setInterval(() => {
      const now = Date.now();
      const dt = (now - lastTickRef.current) / 1000;
      if (dt <= 0) return;
      const rate = msgCountRef.current / dt;
      msgCountRef.current = 0;
      lastTickRef.current = now;
      setUiStats((s) => ({ ...s, msgsPerSec: Math.round(rate) }));
    }, 1000);

    return () => {
      window.clearInterval(id);
      c.close();
    };
  }, [wsUrl]);

  return (
    <div className="min-h-screen">
      <header className="border-b border-neutral-900/80 bg-neutral-950/60 backdrop-blur">
        <div className="mx-auto flex max-w-[1600px] items-center justify-between px-4 py-3">
          <div className="flex items-baseline gap-3">
            <div className="text-lg font-semibold tracking-tight">Orderbook</div>
            <div className="text-xs text-neutral-400">Nasdaq TotalView-ITCH 5.0 (skeleton)</div>
          </div>
          <div className="flex items-center gap-2 text-xs">
            <span
              className={[
                "rounded-full px-2 py-1",
                conn === "connected"
                  ? "bg-emerald-500/15 text-emerald-300"
                  : conn === "connecting"
                    ? "bg-amber-500/15 text-amber-300"
                    : "bg-rose-500/15 text-rose-300"
              ].join(" ")}
            >
              {conn}
            </span>
            <span className="text-neutral-400">{uiStats.msgsPerSec} msg/s</span>
          </div>
        </div>
      </header>

      <main className="mx-auto grid max-w-[1600px] grid-cols-12 gap-3 px-4 py-4">
        <section className="col-span-4">
          <OrderBookL3 />
        </section>
        <section className="col-span-5">
          <OrderTape tape={tape} />
        </section>
        <section className="col-span-3 space-y-3">
          <Controls />
          <StatsPanel uiStats={uiStats} />
        </section>
      </main>
    </div>
  );
}

