# ======================================================================
# generate-files-tree-current-folder.ps1
#
# Genera un árbol de archivos y directorios en formato Markdown.
# - Se ejecuta desde la carpeta actual y escanea recursivamente.
# - Crea un archivo .md con el mismo nombre que la carpeta actual.
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
    ".DS_Store"
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

    # Separar directorios y archivos
    $directories = $Items | Where-Object { $_.PSIsContainer }
    $files = $Items | Where-Object { -not $_.PSIsContainer }

    # Procesar directorios primero
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

        # Procesar contenido del directorio
        $children = Get-ChildItem -LiteralPath $dir.FullName -Force -Exclude $exclude -ErrorAction SilentlyContinue |
            Sort-Object @{Expression = { $_.PSIsContainer }; Descending = $true}, Name
        
        if ($children) {
            Process-Items -Items $children -Prefix $newPrefix
        }
    }

    # Luego procesar archivos
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
    # Obtener items del directorio actual y procesar recursivamente
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
