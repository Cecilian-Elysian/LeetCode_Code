<#
.SYNOPSIS
    One-shot: commit -> push -> refresh README heatmap.

.DESCRIPTION
    Stages all changes, commits with a date-based message (override with
    -Message), regenerates README + heatmap via scripts/gen_readme.py,
    commits any docs delta, then pushes both commits to Github/main.

.EXAMPLE
    .\scripts\sync.ps1
.EXAMPLE
    .\scripts\sync.ps1 -Message "fix: 修正 xx 题边界条件"
#>

[CmdletBinding()]
param(
    [string]$Message
)

$ErrorActionPreference = 'Stop'

function Invoke-Git {
    & git @args
    if ($LASTEXITCODE -ne 0) {
        throw "git $($args -join ' ') failed with exit code $LASTEXITCODE"
    }
}

function Test-StagedChanges {
    & git diff --cached --quiet
    return $LASTEXITCODE -ne 0
}

$repoRoot = (& git rev-parse --show-toplevel).Trim()
Set-Location -LiteralPath $repoRoot

# Clean build artifacts before staging so only source is committed
& "$repoRoot/scripts/clean.ps1"

& git add .
if (Test-StagedChanges) {
    if ([string]::IsNullOrWhiteSpace($Message)) {
        $Message = Get-Date -Format "yyyy.M.d"
    }
    Invoke-Git commit -m $Message
}

$python = Get-Command python -ErrorAction SilentlyContinue
if (-not $python) {
    throw "python not found on PATH. Install Python 3 and ensure 'python' is callable."
}
& python scripts/gen_readme.py
if ($LASTEXITCODE -ne 0) {
    throw "gen_readme.py failed with exit code $LASTEXITCODE"
}

& git add README.md scripts/heatmap.svg
if (Test-StagedChanges) {
    $docsMsg = "docs: 同步 $(Get-Date -Format 'yyyy.M.d') 热力图"
    Invoke-Git commit -m $docsMsg
}

Invoke-Git push Github main

Write-Host 'sync.ps1 - done.'
