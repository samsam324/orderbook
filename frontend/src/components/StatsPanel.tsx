/** Owner: ROLE 5 (UI + Backend WS API) */
import type { UiStats } from "../app/types";

export function StatsPanel({ uiStats }: { uiStats: UiStats }) {
  return (
    <div className="panel">
      <div className="panelHeader">
        <div>Stats</div>
        <div className="text-xs font-normal text-neutral-400">backend + ui</div>
      </div>
      <div className="panelBody space-y-2 text-sm">
        <div className="flex items-center justify-between">
          <div className="text-neutral-400">UI msg rate</div>
          <div className="font-mono">{uiStats.msgsPerSec} /s</div>
        </div>
        <div className="flex items-center justify-between">
          <div className="text-neutral-400">Last message</div>
          <div className="font-mono">
            {uiStats.lastMessageAtMs ? new Date(uiStats.lastMessageAtMs).toLocaleTimeString() : "—"}
          </div>
        </div>
        <div className="mt-3 text-xs text-neutral-400">
          Waiting for `stats` schema from backend. This panel will later show rates, latency percentiles, active
          orders, spread, cancels/sec, trades/sec, and backlog warnings.
        </div>
      </div>
    </div>
  );
}

