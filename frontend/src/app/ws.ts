/** Owner: ROLE 5 (UI + Backend WS API) */
import type { WsEnvelope } from "./types";

export type WsHandlers = {
  onState: (state: "disconnected" | "connecting" | "connected") => void;
  onMessage: (msg: WsEnvelope) => void;
  onError?: (err: unknown) => void;
};

export function connectWs(url: string, handlers: WsHandlers) {
  handlers.onState("connecting");

  const ws = new WebSocket(url);

  ws.onopen = () => handlers.onState("connected");
  ws.onclose = () => handlers.onState("disconnected");
  ws.onerror = (e) => handlers.onError?.(e);

  ws.onmessage = (ev) => {
    try {
      const obj = JSON.parse(String(ev.data)) as WsEnvelope;
      if (!obj || typeof obj !== "object" || !("type" in obj)) return;
      handlers.onMessage(obj);
    } catch (e) {
      handlers.onError?.(e);
    }
  };

  return {
    close: () => ws.close()
  };
}

