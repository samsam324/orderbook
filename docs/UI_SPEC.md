# UI spec

## Layout
- Left: Order book ladder (bids/asks)
- Center: Event tape (latest events; color-coded by type; later virtualized)
- Right: Stats panel and controls

## Behavior
- Connect to `ws://localhost:<port>/ws`
- Render event, snapshot, stats messages
- Keep bounded client-side buffers:
  - Tape: max N rows
  - Snapshots: store latest only

## Visual design
- Dark mode default
- Clean typography, spacing, and subtle borders
