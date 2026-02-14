/** Owner: ROLE 5 (UI + Backend WS API) */
import type { WsEnvelope } from "../app/types";

type TapeItem = { t: number; raw: WsEnvelope };

export function OrderTape({ tape }: { tape: TapeItem[] }) {
  // TODO(ROLE5): Virtualize this list (react window) for very large tapes
  return (
    <div className="panel">
      <div className="panelHeader">
        <div>Event Tape</div>
        <div className="text-xs font-normal text-neutral-400">{tape.length} buffered</div>
      </div>
      <div className="panelBody">
        <div className="h-[75vh] overflow-auto pr-2">
          {tape.length === 0 ? (
            <div className="text-sm text-neutral-400">Waiting for WS messages…</div>
          ) : (
            <ul className="space-y-2 text-xs">
              {tape.map((it, idx) => (
                <li key={idx} className="rounded border border-neutral-800 bg-neutral-950/40 p-2">
                  <div className="flex items-center justify-between">
                    <div className="font-mono text-neutral-400">{new Date(it.t).toLocaleTimeString()}</div>
                    <div className="rounded bg-neutral-800/60 px-2 py-0.5 text-[11px] text-neutral-200">
                      {it.raw.type}
                    </div>
                  </div>
                  <pre className="mt-2 overflow-x-auto whitespace-pre-wrap break-words text-neutral-200">
                    {JSON.stringify(it.raw, null, 2)}
                  </pre>
                </li>
              ))}
            </ul>
          )}
        </div>
      </div>
    </div>
  );
}

