<#
.SYNOPSIS
    Clean C/C++ build artifacts (exe/obj/pdb) before pushing to Github.
.DESCRIPTION
    Recursively scans the repository root and removes *.exe, *.obj, *.pdb files
    left behind by compilation. Safe to run multiple times. Source files (.c, .py)
    and project files (.slnx, .vcxproj, .gitignore, etc.) are never touched.
.EXAMPLE
    .\scripts\clean.ps1
#>

[CmdletBinding()]
param()

$ErrorActionPreference = 'SilentlyContinue'

$repoRoot = (& git rev-parse --show-toplevel).Trim()
Set-Location -LiteralPath $repoRoot

$patterns = @('*.exe', '*.obj', '*.pdb')
$count = 0

foreach ($p in $patterns) {
    Get-ChildItem -Path $repoRoot -Recurse -File -Filter $p |
        ForEach-Object {
            $rel = $_.FullName.Substring($repoRoot.Length).TrimStart('\', '/')
            Remove-Item -LiteralPath $_.FullName -Force -ErrorAction SilentlyContinue
            if ($?) {
                Write-Host "  [DEL] $rel"
                $count++
            }
        }
}

Write-Host "Cleaned $count build artifact(s)."