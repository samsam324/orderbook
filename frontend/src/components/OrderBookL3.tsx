/** Owner: ROLE 5 (UI + Backend WS API) */

export function OrderBookL3() {
  // TODO(ROLE5): Render ladder + expandable L3 at each level
  // UI requirements:
  // - Left panel: bids/asks depth ladder
  // - Expand a price level to show top N orders (FIFO)
  return (
    <div className="panel">
      <div className="panelHeader">
        <div>Order Book</div>
        <div className="text-xs font-normal text-neutral-400">L3 (skeleton)</div>
      </div>
      <div className="panelBody">
        <div className="text-sm text-neutral-300">Not implemented. Awaiting snapshot schema.</div>
        <div className="mt-3 grid grid-cols-3 gap-2 text-xs text-neutral-400">
          <div className="rounded border border-neutral-800 p-2">Bid Qty</div>
          <div className="rounded border border-neutral-800 p-2 text-center">Price</div>
          <div className="rounded border border-neutral-800 p-2 text-right">Ask Qty</div>
        </div>
      </div>
    </div>
  );
}

