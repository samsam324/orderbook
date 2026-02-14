/** Owner: ROLE 5 (UI + Backend WS API) */

export type WsEnvelope =
  | { type: "event"; [k: string]: unknown }
  | { type: "snapshot"; [k: string]: unknown }
  | { type: "stats"; [k: string]: unknown };

export type ConnectionState = "disconnected" | "connecting" | "connected";

export type UiStats = {
  msgsPerSec: number;
  lastMessageAtMs: number | null;
};

