# Contributing to cs2-optimizer

Thanks for wanting to help. This project targets the 2026 CS2 build and
we try to keep the codebase small, honest, and reviewable.

## Ground rules

- Every PR must build with `cmake --build build --config Release` on
  MSVC 19.4x and clang-cl 19+.
- Do not commit offsets, signatures, or netvars directly. They belong
  in `config/offsets.json` and are loaded at runtime.
- Do not commit anything that touches VAC-protected memory in a way
  that isn't already present in `services/`.
- Keep the C# side (`tools/cfgc`) free of native interop unless it's
  behind `cfg_loader.cpp`.

## How to submit offsets

1. Run `cs2-offset-dump.exe --build <build-id>` from the tools folder.
2. Paste the resulting block into `config/offsets.json`.
3. Bump `offsets_revision` and add a changelog line.

## Reporting build breakage

Use the `build-breakage` issue template. Include:
- MSVC version
- CMake version
- Full compile output
- Whether `CS2_OPTIMIZER_USE_VULKAN_LAYER` was enabled

## Style

- 4 spaces, no tabs.
- `snake_case` for files, `PascalCase` for types, `camelCase` for
  locals.
- Prefer `std::optional` over sentinel values.
- Every service method that touches game state takes a
  `frame_context&`.

## Code of conduct

Don't be a jerk. Don't sell builds. Don't repackage someone else's
config as your own.