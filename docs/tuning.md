# Tuning notes

The defaults in `config/optimizer.json` are conservative. On a 7800X3D
+ 4070 Ti system, these are the values that produced the lowest
1% frametime in our testing:

| Setting              | Default | Aggressive |
| -------------------- | ------- | ---------- |
| `forced_fps_cap`     | 240     | 400        |
| `target_latency_ms`  | 8       | 5          |
| `enable_netgraph_tweak` | false | true      |

## Per-map FPS

Some maps (notably `de_ancient`) have heavier geometry and benefit
from a lower cap to keep frametimes flat. See `config/map_profiles.json`.

## What this tool does not do

- It does not modify weapon behaviour, movement, or hit registration.
- It does not read enemy positions.
- It does not spoof HWID, and it will not help you evade VAC.

If you were looking for the other kind of "optimizer", this isn't it.
Use this in offline / community servers only.