# Architecture

`cs2-optimizer` is service-oriented: the entry point wires a
`ProcessAdapter` to an `OptimizerService` and pumps frames through a
thin `FrameHandler`.

```
main.cpp
  └─ bootstrap::EntryPoint
       ├─ platform::ProcessAdapter   (windows/process_adapter_win.cpp)
       ├─ platform::OverlayAdapter   (windows/overlay_adapter_dx11.cpp)
       └─ services::OptimizerService
            ├─ services::FrameProfiler
            └─ services::SkinPreloadService
```

## Layers

- **bootstrap** — process attach, loop, shutdown. No game logic.
- **handlers** — one per input source (frame, config). Translate
  events into service calls.
- **services** — business logic. FPS tuning, map profiles, skin
  preload, netgraph tweaks.
- **models** — plain data. `OptimizerConfig`, `FrameContext`.
- **platform** — the only place that touches Win32 / DXGI / D3D11.
- **utils** — logging, config loading, offset resolution.

## Why services don't take raw handles

Every service receives a `ProcessAdapter&`. This keeps tests able to
sub a fake adapter without spawning a real CS2 process.

## Offsets

Offsets live in `config/offsets.json` and are loaded at startup.
`offsets_revision` must match the client build ID reported by
`ProcessAdapter::read_build_id()` or the service refuses to write.