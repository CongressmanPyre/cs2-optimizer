# Dumps current CS2 build offsets into config/offsets.json.
# Run from the repo root: pwsh -File scripts/dump-offsets.ps1
param(
    [string]$Build = "auto",
    [string]$Out   = "config/offsets.json"
)

$exe = Join-Path $PSScriptRoot "..\build\Release\cs2-offset-dump.exe"
if (-not (Test-Path $exe)) {
    Write-Error "cs2-offset-dump.exe not built. Run cmake --build build --config Release first."
    exit 1
}

& $exe --build $Build --out $Out
if ($LASTEXITCODE -ne 0) {
    Write-Error "offset dump failed with exit code $LASTEXITCODE"
    exit $LASTEXITCODE
}

Write-Host "wrote $Out"