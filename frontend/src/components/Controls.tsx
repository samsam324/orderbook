/** Owner: ROLE 5 (UI + Backend WS API) */

export function Controls() {
  // TODO(ROLE5): Wire play/pause, speed factor, queue mode, and symbol selector
  // For skeleton, controls are visual only
  return (
    <div className="panel">
      <div className="panelHeader">
        <div>Controls</div>
        <div className="text-xs font-normal text-neutral-400">skeleton</div>
      </div>
      <div className="panelBody space-y-3 text-sm">
        <div className="flex items-center gap-2">
          <button className="rounded bg-neutral-800 px-3 py-2 text-sm hover:bg-neutral-700">Play</button>
          <button className="rounded bg-neutral-800 px-3 py-2 text-sm hover:bg-neutral-700">Pause</button>
        </div>
        <div className="grid grid-cols-2 gap-2 text-xs">
          <div className="rounded border border-neutral-800 p-2">
            <div className="text-neutral-400">Speed</div>
            <div className="mt-1 font-mono">10x</div>
          </div>
          <div className="rounded border border-neutral-800 p-2">
            <div className="text-neutral-400">Queue</div>
            <div className="mt-1 font-mono">ring</div>
          </div>
          <div className="col-span-2 rounded border border-neutral-800 p-2">
            <div className="text-neutral-400">Symbol</div>
            <div className="mt-1 font-mono">AAPL</div>
          </div>
        </div>
        <div className="text-xs text-neutral-400">
          Later: these controls will send commands to backend (pause/resume, seek, speed, mode changes).
        </div>
      </div>
    </div>
  );
}

