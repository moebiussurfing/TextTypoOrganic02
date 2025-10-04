# ======================================================================
# generate-files-tree.ps1
#
# Genera un árbol de archivos y directorios en formato Markdown.
# - Se ejecuta desde la carpeta raíz que se desea escanear.
# - Crea un archivo .md con el mismo nombre que la carpeta raíz.
# - Utiliza caracteres de línea para una estética "bonita".
# ======================================================================

# --- Setup paths ---
$root = Get-Location
$folderName = Split-Path $root -Leaf
$outputFile = Join-Path $root "$folderName.md"

# --- Box drawing characters ---
$VERT = '│'
$HORI = '─'
$BRANCH = '├'
$LAST = '└'

# --- Items to exclude from the tree ---
$exclude = @(
    ".git",
    ".vs",
    ".vscode",
    "bin",
    "obj",
    "node_modules",
    ".DS_Store",
    "*.md"
)

# --- Global lines buffer ---
$lines = [System.Collections.Generic.List[string]]::new()
$lines.Add("# File Tree for '$folderName'")
$lines.Add('```text')
$lines.Add($folderName)

function Process-Items {
    param(
        [array]$Items,
        [string]$Prefix
    )

    for ($i = 0; $i -lt $Items.Count; $i++) {
        $item = $Items[$i]
        $isLastItem = ($i -eq $Items.Count - 1)
        
        # Construir el prefijo para este ítem
        if ($isLastItem) {
            $lines.Add($Prefix + $LAST + $HORI + $HORI + ' ' + $item.Name)
            $newPrefix = $Prefix + '    '
        } else {
            $lines.Add($Prefix + $BRANCH + $HORI + $HORI + ' ' + $item.Name)
            $newPrefix = $Prefix + $VERT + '   '
        }

        # Procesar subdirectorios
        if ($item.PSIsContainer) {
            $children = Get-ChildItem -LiteralPath $item.FullName -Force -Exclude $exclude -ErrorAction SilentlyContinue |
                Sort-Object @{Expression = { $_.PSIsContainer }; Descending = $true}, Name
            
            if ($children) {
                Process-Items -Items $children -Prefix $newPrefix
            }
        }
    }
}

# --- Start processing ---
try {
    $rootItems = Get-ChildItem -LiteralPath $root -Force -Exclude $exclude -ErrorAction SilentlyContinue |
        Sort-Object @{Expression = { $_.PSIsContainer }; Descending = $true}, Name

    if ($rootItems) {
        Process-Items -Items $rootItems -Prefix ''
    }

    $lines.Add('```')

    # --- Save result ---
    $lines | Out-File -FilePath $outputFile -Encoding utf8
    Write-Host "✅ Tree saved to: $outputFile"
} catch {
    Write-Host "❌ Error: $_"
}
