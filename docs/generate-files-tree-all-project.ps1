# ======================================================================
# generate-files-tree-all-project.ps1
#
# Generates a Markdown file with a tree structure of files and directories.
# Features:
# - Scans recursively from the project root
# - Creates a .md file with pattern: [folder-name]-all-project-tree.md
# - Uses pretty box drawing characters for the tree structure
# - Excludes common system and build folders
# - Sorts directories first, then files
# ======================================================================

# --- Setup paths and initialize logging ---
$root = Get-Location
$folderName = Split-Path $root -Leaf
$outputFile = Join-Path $root "$folderName-all-project-tree.md"

Write-Host "🔍 Starting project file tree generation..."
Write-Host "📂 Project root: $root"
Write-Host "📝 Output will be saved to: $outputFile"

# --- Box drawing characters for pretty tree structure ---
$VERT = '│'   # Vertical line
$HORI = '─'   # Horizontal line
$BRANCH = '├'  # Branch connection
$LAST = '└'    # Last item connection

# --- Items to exclude from the tree ---
$exclude = @(
    ".git",      # Git repository
    ".vs",       # Visual Studio files
    ".vscode",   # VS Code files
    "bin",       # Binary output
    "obj",       # Object files
    "node_modules", # NPM packages
    ".DS_Store"  # macOS system files
)

Write-Host "🚫 Excluding: $($exclude -join ', ')"

# --- Global lines buffer for tree content ---
$lines = [System.Collections.Generic.List[string]]::new()
$lines.Add("# Complete Project Tree for '$folderName'")
$lines.Add("Generated on $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')")
$lines.Add('```text')
$lines.Add($folderName)

# --- Process items (directories and files) recursively ---
function Process-Items {
    param(
        [array]$Items,
        [string]$Prefix
    )

    # Separate directories and files for sorted processing
    $directories = $Items | Where-Object { $_.PSIsContainer }
    $files = $Items | Where-Object { -not $_.PSIsContainer }

    Write-Host "  📁 Processing directory with $($directories.Count) subdirectories and $($files.Count) files"

    # Process directories first
    for ($i = 0; $i -lt $directories.Count; $i++) {
        $dir = $directories[$i]
        $isLastDir = ($i -eq $directories.Count - 1) -and ($files.Count -eq 0)
        
        if ($isLastDir) {
            $lines.Add($Prefix + $LAST + $HORI + $HORI + ' ' + $dir.Name)
            $newPrefix = $Prefix + '    '
        } else {
            $lines.Add($Prefix + $BRANCH + $HORI + $HORI + ' ' + $dir.Name)
            $newPrefix = $Prefix + $VERT + '   '
        }

        # Process subdirectory contents recursively
        $children = Get-ChildItem -LiteralPath $dir.FullName -Force -Exclude $exclude -ErrorAction SilentlyContinue |
            Sort-Object @{Expression = { $_.PSIsContainer }; Descending = $true}, Name
        
        if ($children) {
            Process-Items -Items $children -Prefix $newPrefix
        }
    }

    # Then process files
    for ($i = 0; $i -lt $files.Count; $i++) {
        $file = $files[$i]
        $isLastFile = ($i -eq $files.Count - 1)
        
        if ($isLastFile) {
            $lines.Add($Prefix + $LAST + $HORI + $HORI + ' ' + $file.Name)
        } else {
            $lines.Add($Prefix + $BRANCH + $HORI + $HORI + ' ' + $file.Name)
        }
    }
}

# --- Start processing ---
try {
    Write-Host "🔄 Processing project files and directories..."
    
    # Get and sort items from project root
    $rootItems = Get-ChildItem -LiteralPath $root -Force -Exclude $exclude -ErrorAction SilentlyContinue |
        Sort-Object @{Expression = { $_.PSIsContainer }; Descending = $true}, Name

    if ($rootItems) {
        Process-Items -Items $rootItems -Prefix ''
    } else {
        Write-Host "⚠️ No items found in project directory"
    }

    $lines.Add('```')

    # --- Save result ---
    $lines | Out-File -FilePath $outputFile -Encoding utf8
    Write-Host "✅ Tree successfully saved to: $outputFile"
    
    # --- Display the generated tree ---
    Write-Host "`n📋 Generated Tree Content:"
    Write-Host "------------------------"
    Get-Content $outputFile | ForEach-Object { Write-Host $_ }
    Write-Host "------------------------"

} catch {
    Write-Host "❌ Error: $_"
    Write-Host "Stack Trace: $($_.ScriptStackTrace)"
}
