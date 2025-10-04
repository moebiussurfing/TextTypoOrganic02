# ======================================================================
# generate-files-tree.ps1
# Recursively scans the current folder and writes a pretty tree
# to <current-folder-name>.md in Markdown format.
# Safe Unicode escapes, no emojis, works on Windows PowerShell 5+.
# ======================================================================

# --- Setup paths ---
$root = Get-Location
$folderName = Split-Path $root -Leaf
$outputFile = Join-Path $root ("$folderName.md")

# --- Box drawing characters (Unicode escapes) ---
$VERT       = "`u2502"            # │
$BRANCH     = "`u251C`u2500`u2500 "  # ├──
$LAST       = "`u2514`u2500`u2500 "  # └──
$SPACE      = "    "
$VERT_SPACE = "$VERT   "

# --- Global lines buffer ---
$global:lines = @()
$global:lines += "# File Tree for '$folderName'"
$global:lines += "```"

function Draw-Tree {
    param(
        [string]$Path,
        [string]$Prefix = "",
        [bool]$IsLast = $true
    )

    $name = Split-Path $Path -Leaf
    $connector = if ($IsLast) { $LAST } else { $BRANCH }
    $global:lines += ("$Prefix$connector$name")

    # --- Get children, ignore common system folders ---
    $items = Get-ChildItem -LiteralPath $Path -Force -ErrorAction SilentlyContinue | `
        Where-Object { $_.Name -notin @(".git", ".DS_Store", "node_modules", ".venv") } | `
        Sort-Object @{Expression = { $_.PSIsContainer }; Descending = $true}, Name

    $count = $items.Count

    for ($i = 0; $i -lt $count; $i++) {
        $item = $items[$i]
        $isLastItem = ($i -eq $count - 1)
        $newPrefix = $Prefix + (if ($IsLast) { $SPACE } else { $VERT_SPACE })

        if ($item.PSIsContainer) {
            Draw-Tree -Path $item.FullName -Prefix $newPrefix -IsLast $isLastItem
        } else {
            $fileConnector = if ($isLastItem) { $LAST } else { $BRANCH }
            $global:lines += ("$newPrefix$fileConnector$($item.Name)")
        }
    }
}

# --- Start ---
$global:lines += ($folderName)
Draw-Tree -Path $root -Prefix "" -IsLast $true
$global:lines += "```"

# --- Save result ---
$global:lines | Out-File -FilePath $outputFile -Encoding utf8BOM

Write-Host "✅ Tree saved to: $outputFile"
