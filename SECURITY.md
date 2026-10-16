# Security Policy

## Scope

`cs2-optimizer` runs at the same privilege level as the CS2 client and
reads/writes only memory owned by that process. Anything that escapes
that boundary is a bug and should be reported privately.

## Reporting

Email: `security@cs2-optimizer.dev` (PGP key in `keys/`).
Expected first response: 72 hours.

Please include:
- Build ID of the CS2 client (`version` in the main menu).
- `cs2-optimizer` version (`--version`).
- Crash dump if available.
- Whether the issue reproduces with `--safe-mode`.

## What we consider in scope

- Arbitrary code execution outside the CS2 process.
- Persistence outside `%APPDATA%\cs2-optimizer\`.
- Network egress other than the optional update check.
- Unintended writes to non-game memory regions.

## What we consider out of scope

- VAC detection. Using this tool in matchmaking will get you banned.
  That is expected behaviour, not a vulnerability.
- Performance regressions on unsupported Windows builds.
- Conflicts with other overlays (Discord, MSI Afterburner, RTSS).

## Disclosure

Coordinated 90-day disclosure. If we can't ship a fix in 90 days we'll
publish a mitigation and a timeline.

## Not a security boundary

The config loader trusts local files. Do not load configs from sources
you don't trust.