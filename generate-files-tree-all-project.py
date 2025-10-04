#!/usr/bin/env python3
# generate-files-tree-all-project.py

import os
import fnmatch
from datetime import datetime
from pathlib import Path

def read_gitignore_patterns(gitignore_path):
    """Lee los patrones de exclusión del archivo .gitignore"""
    patterns = []
    if os.path.exists(gitignore_path):
        print("📄 Reading .gitignore file...")
        with open(gitignore_path, 'r', encoding='utf-8') as f:
            for line in f:
                line = line.strip()
                if line and not line.startswith('#') and not line.startswith('!'):
                    patterns.append(line)
    return patterns

def should_exclude(path, name, patterns, base_path):
    """Verifica si un archivo o directorio debería ser excluido"""
    for pattern in patterns:
        if fnmatch.fnmatch(name, pattern):
            return True
        # Verificar rutas relativas también
        rel_path = os.path.relpath(path, base_path)
        if fnmatch.fnmatch(rel_path, pattern) or fnmatch.fnmatch(name, pattern):
            return True
    return False

def get_tree_structure(current_dir, exclude_patterns):
    """Genera la estructura de árbol de archivos"""
    tree_lines = []
    
    # Caracteres para el árbol
    VERT = '│'
    HORI = '─'
    BRANCH = '├'
    LAST = '└'
    
    def process_items(path, prefix="", current_path=""):
        items = []
        try:
            for item in os.listdir(path):
                item_path = os.path.join(path, item)
                if not should_exclude(item_path, item, exclude_patterns, current_dir):
                    items.append((item, item_path, os.path.isdir(item_path)))
        except PermissionError:
            pass
        
        # Separar directorios y archivos
        dirs = [(name, path, is_dir) for name, path, is_dir in items if is_dir]
        files = [(name, path, is_dir) for name, path, is_dir in items if not is_dir]
        
        # Combinar: directorios primero, luego archivos
        all_items = dirs + files
        
        for i, (name, item_path, is_dir) in enumerate(all_items):
            is_last = (i == len(all_items) - 1)
            
            if is_last:
                tree_lines.append(f"{prefix}{LAST}{HORI}{HORI} {name}")
                new_prefix = prefix + "    "
            else:
                tree_lines.append(f"{prefix}{BRANCH}{HORI}{HORI} {name}")
                new_prefix = prefix + VERT + "   "
            
            if is_dir:
                process_items(item_path, new_prefix, os.path.join(current_path, name))
    
    return tree_lines

def main():
    # Obtener directorio actual
    current_dir = os.getcwd()
    project_name = os.path.basename(current_dir)
    output_file = os.path.join(current_dir, f"{project_name}-all-project-tree.md")
    
    print(f"🔍 Starting project file tree generation...")
    print(f"📂 Project root: {current_dir}")
    print(f"📝 Output will be saved to: {output_file}")
    
    # Patrones de exclusión optimizados para openFrameworks
    exclude_hardcoded = [
        ".git", "node_modules",
        ".vs", ".vscode", "obj", "bin", "__pycache__",
        "*.log", ".DS_Store", "coverage", "tmp", "temp",
        ".idea", ".gradle", "vendor", "Pods", ".svn",
        "yarn.lock", "package-lock.json", "*.tmp", "*.temp",
        "*.dll", "*.exe", "*.so", "*.dylib", "*.o", "*.obj",
        "*.pyc", "*.pyo", "*.jar", "*.war", "*.zip", "*.tar",
        "*.gz", "*.7z", "*.rar", "*.bin", "*.out", "*.app",
        "*.dmg", "*.iso", "logs/", "log/", "Thumbs.db",
        "*.user", "*.userosscache", "*.suo", "*.pidb", "*.svclog",
        "*.rsp", "*.rsp.user", "*.VC.db", "*.VC.VC.opendb",
        "ipch/", ".metadata", "BenchmarkDotNet.Artifacts/",
        "publish/", "AppPackages/", "BundleArtifacts/",
        "*.opendb", "*.opensdf", "*.sdf", "*.ncb", "*.opt",
        "*.vbw", "*.gpState", "*.dotCover", "nCrunchTemp_*",
        ".*crunch*.local.xml", "FakesAssemblies/", "MigrationBackup/",
        "*.binlog", "*.nvuser", ".mfractor/", ".localhistory/",
        "healthchecksdb", "OpenCover/", "ASALocalRun/"
    ]
    
    # Leer patrones del .gitignore
    gitignore_path = os.path.join(current_dir, ".gitignore")
    gitignore_patterns = read_gitignore_patterns(gitignore_path)
    
    # Combinar exclusiones
    all_exclusions = exclude_hardcoded + gitignore_patterns
    print(f"🚫 Excluding: {', '.join(all_exclusions)}")
    
    # Generar árbol
    print("🔄 Processing project files and directories...")
    
    # DEBUG: Mostrar qué elementos se encuentran y cuáles están excluidos
    print(f"DEBUG: Found {len(os.listdir(current_dir))} items in directory")
    allowed_items = []
    for item in os.listdir(current_dir):
        item_path = os.path.join(current_dir, item)
        excluded = should_exclude(item_path, item, all_exclusions, current_dir)
        status = '❌' if excluded else '✅'
        print(f"  {status} {item} (dir: {os.path.isdir(item_path)})")
        if not excluded:
            allowed_items.append((item, item_path, os.path.isdir(item_path)))
    
    tree_lines = get_tree_structure(current_dir, all_exclusions)
    
    # Crear contenido del archivo
    content = [
        f"# Project Tree for '{project_name}'",
        f"Generated on {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}",
        "```text",
        project_name
    ]
    
    content.extend(tree_lines)
    content.append("```")
    
    # Guardar archivo
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write('\n'.join(content))
    
    print(f"✅ Tree successfully saved to: {output_file}")
    
    # Mostrar contenido generado
    print("\n📋 Generated Tree Content:")
    print("------------------------")
    for line in content:
        print(line)
    print("------------------------")

if __name__ == "__main__":
    main()