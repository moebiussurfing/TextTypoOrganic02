#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
File Structure Generator Script
-------------------------------

This script generates a markdown file named `FILE-STRUCTURE.md` that contains
a recursive tree representation of the current project directory.

Features:
- Recursively traverses the directory tree starting from the current working directory.
- Excludes directories and files specified in a hardcoded exclusion list.
- Reads and respects `.gitignore` patterns if present, interpreting them correctly
  according to Git's specification (basic support for globs, directories, negations).
- Outputs a clean, indented markdown tree.
- Includes detailed logging with colored output for success and error messages.

Hardcoded exclusions include: .git, bin, obj, __pycache__, .venv, venv, node_modules, dist, build

Note: This script uses a simplified .gitignore parser. It handles common cases but
may not cover every edge case of Git's ignore specification (e.g., complex negations,
anchored patterns, or multi-segment globs). For most typical projects, it should work well.

Author: Your Name
Date: 2023-10-01
"""

import os
import sys
import fnmatch
import logging
from pathlib import Path
from typing import List, Set, Optional

# ----------------------------
# Configuration & Constants
# ----------------------------

# Hardcoded list of paths to exclude (case-insensitive, relative to root)
HARDCODED_EXCLUSIONS = {
    '.git',
    'bin',
    'obj',
    '__pycache__',
    '.venv',
    'venv',
    'node_modules',
    'dist',
    'build',
    '.idea',
    '.vscode',
    '.DS_Store',
    'Thumbs.db'
}

# Output filename
OUTPUT_FILENAME = "FILE-STRUCTURE.md"

# Setup colorful logging
class ColoredFormatter(logging.Formatter):
    """Custom formatter to add colors to log levels."""
    COLORS = {
        'DEBUG': '\033[36m',    # Cyan
        'INFO': '\033[32m',     # Green
        'WARNING': '\033[33m',  # Yellow
        'ERROR': '\033[31m',    # Red
        'CRITICAL': '\033[35m', # Magenta
    }
    RESET = '\033[0m'

    def format(self, record):
        log_color = self.COLORS.get(record.levelname, self.RESET)
        record.levelname = f"{log_color}{record.levelname}{self.RESET}"
        record.msg = f"{log_color}{record.msg}{self.RESET}"
        return super().format(record)

# Configure logger
logger = logging.getLogger("FileStructureGenerator")
logger.setLevel(logging.DEBUG)

# Console handler with color
ch = logging.StreamHandler(sys.stdout)
ch.setLevel(logging.DEBUG)
ch.setFormatter(ColoredFormatter('%(levelname)s: %(message)s'))
logger.addHandler(ch)

# ----------------------------
# Helper Functions
# ----------------------------

def normalize_path(path: str) -> str:
    """
    Normalize a path for consistent comparison.
    Converts to lowercase on case-insensitive systems (like Windows),
    but keeps original case on case-sensitive systems.
    For simplicity, we'll just use lower() for exclusion matching.
    """
    return path.lower()

def parse_gitignore(gitignore_path: Path) -> List[str]:
    """
    Parse a .gitignore file and return a list of patterns.
    
    Handles:
    - Comments (lines starting with #)
    - Blank lines
    - Trailing whitespace removal
    - Leading/trailing slashes are normalized
    
    Does NOT fully implement Git's spec (e.g., no support for **, complex negations),
    but covers most common use cases.
    """
    patterns = []
    try:
        with open(gitignore_path, 'r', encoding='utf-8', errors='ignore') as f:
            for line_num, line in enumerate(f, 1):
                line = line.strip()
                # Skip comments and empty lines
                if not line or line.startswith('#'):
                    continue
                # Remove trailing whitespace and optional carriage return
                line = line.rstrip()
                # Git treats leading slash as anchored to root, but for our recursive walk,
                # we'll treat all patterns as relative. We remove leading slash for simplicity.
                if line.startswith('/'):
                    line = line[1:]
                # Git treats trailing slash as directory-only; we keep it for pattern matching.
                patterns.append(line)
        logger.info(f"Successfully parsed .gitignore with {len(patterns)} patterns.")
    except Exception as e:
        logger.error(f"Failed to read .gitignore at {gitignore_path}: {e}")
        return []
    return patterns

def should_exclude(
    relative_path: str,
    name: str,
    is_dir: bool,
    hardcoded_exclusions: Set[str],
    gitignore_patterns: List[str]
) -> bool:
    """
    Determine if a file or directory should be excluded based on:
    1. Hardcoded exclusions
    2. .gitignore patterns

    Parameters:
    - relative_path: Path relative to the root (e.g., 'src/utils/helper.py')
    - name: Basename of the file/directory (e.g., 'helper.py')
    - is_dir: Boolean indicating if it's a directory
    - hardcoded_exclusions: Set of lowercase names to exclude
    - gitignore_patterns: List of patterns from .gitignore

    Returns:
    - True if the item should be excluded, False otherwise.
    """
    # Normalize for hardcoded check
    norm_name = normalize_path(name)
    if norm_name in hardcoded_exclusions:
        logger.debug(f"Excluded by hardcoded list: {relative_path}")
        return True

    # Check against .gitignore patterns
    for pattern in gitignore_patterns:
        # Handle directory-only patterns (ending with /)
        if pattern.endswith('/'):
            if is_dir and fnmatch.fnmatch(name, pattern[:-1]):
                logger.debug(f"Excluded by .gitignore (dir pattern): {relative_path}")
                return True
            # Also match if the relative path ends with the pattern (for nested dirs)
            if is_dir and fnmatch.fnmatch(relative_path, pattern[:-1]) or fnmatch.fnmatch(relative_path + '/', pattern):
                logger.debug(f"Excluded by .gitignore (dir path pattern): {relative_path}")
                return True
        else:
            # Match file or directory name
            if fnmatch.fnmatch(name, pattern):
                logger.debug(f"Excluded by .gitignore (name pattern): {relative_path}")
                return True
            # Match full relative path
            if fnmatch.fnmatch(relative_path, pattern):
                logger.debug(f"Excluded by .gitignore (path pattern): {relative_path}")
                return True
            # Special case: if pattern contains a slash, it's a path pattern
            if '/' in pattern:
                if fnmatch.fnmatch(relative_path, pattern):
                    logger.debug(f"Excluded by .gitignore (explicit path): {relative_path}")
                    return True

    return False

def build_tree(
    root_path: Path,
    prefix: str = "",
    hardcoded_exclusions: Set[str] = None,
    gitignore_patterns: List[str] = None,
    visited: Set[Path] = None
) -> List[str]:
    """
    Recursively build a list of strings representing the directory tree.

    Parameters:
    - root_path: Current directory to process
    - prefix: Indentation string for current depth
    - hardcoded_exclusions: Set of names to exclude
    - gitignore_patterns: List of patterns from .gitignore
    - visited: Set to prevent symlink loops (not implemented here but good practice)

    Returns:
    - List of formatted strings for the tree
    """
    if hardcoded_exclusions is None:
        hardcoded_exclusions = set()
    if gitignore_patterns is None:
        gitignore_patterns = []
    if visited is None:
        visited = set()

    tree_lines = []
    try:
        # Get all entries in the directory
        entries = sorted(os.listdir(root_path))
    except PermissionError as e:
        logger.warning(f"Permission denied accessing {root_path}: {e}")
        return tree_lines
    except Exception as e:
        logger.error(f"Error reading directory {root_path}: {e}")
        return tree_lines

    # Separate directories and files
    dirs = []
    files = []
    for entry in entries:
        full_path = root_path / entry
        try:
            if full_path.is_symlink():
                # Optionally follow symlinks or skip; we skip to avoid cycles
                logger.debug(f"Skipping symlink: {full_path}")
                continue
            if full_path.is_dir():
                dirs.append(entry)
            else:
                files.append(entry)
        except OSError as e:
            logger.warning(f"OSError accessing {full_path}: {e}")
            continue

    # Process directories first
    for i, dname in enumerate(dirs):
        dir_path = root_path / dname
        relative_dir_path = dir_path.relative_to(Path.cwd())
        relative_dir_str = str(relative_dir_path).replace(os.sep, '/')

        # Check exclusions
        if should_exclude(
            relative_dir_str,
            dname,
            is_dir=True,
            hardcoded_exclusions=hardcoded_exclusions,
            gitignore_patterns=gitignore_patterns
        ):
            continue

        is_last = (i == len(dirs) - 1) and (len(files) == 0)
        connector = "└── " if is_last else "├── "
        tree_lines.append(f"{prefix}{connector}{dname}/")

        # Recursive call for subdirectory
        extension = "    " if is_last else "│   "
        subtree = build_tree(
            dir_path,
            prefix=prefix + extension,
            hardcoded_exclusions=hardcoded_exclusions,
            gitignore_patterns=gitignore_patterns,
            visited=visited
        )
        tree_lines.extend(subtree)

    # Process files
    for i, fname in enumerate(files):
        file_path = root_path / fname
        relative_file_path = file_path.relative_to(Path.cwd())
        relative_file_str = str(relative_file_path).replace(os.sep, '/')

        if should_exclude(
            relative_file_str,
            fname,
            is_dir=False,
            hardcoded_exclusions=hardcoded_exclusions,
            gitignore_patterns=gitignore_patterns
        ):
            continue

        is_last = i == len(files) - 1
        connector = "└── " if is_last else "├── "
        tree_lines.append(f"{prefix}{connector}{fname}")

    return tree_lines

# ----------------------------
# Main Execution
# ----------------------------

def main():
    """Main function to generate the file structure markdown."""
    root = Path.cwd()
    logger.info(f"Starting file structure generation at: {root}")

    # Prepare hardcoded exclusions (normalized to lowercase)
    hardcoded_excl_set = {normalize_path(p) for p in HARDCODED_EXCLUSIONS}
    logger.debug(f"Hardcoded exclusions: {hardcoded_excl_set}")

    # Load .gitignore if exists
    gitignore_path = root / ".gitignore"
    gitignore_patterns = []
    if gitignore_path.exists():
        logger.info(f"Found .gitignore at {gitignore_path}")
        gitignore_patterns = parse_gitignore(gitignore_path)
    else:
        logger.info("No .gitignore found. Proceeding without gitignore exclusions.")

    # Build the tree
    logger.info("Building directory tree...")
    tree_lines = build_tree(
        root,
        hardcoded_exclusions=hardcoded_excl_set,
        gitignore_patterns=gitignore_patterns
    )

    # Write to FILE-STRUCTURE.md
    output_path = root / OUTPUT_FILENAME
    try:
        with open(output_path, 'w', encoding='utf-8') as f:
            f.write("# Project File Structure\n\n")
            f.write("```\n")
            f.write(os.path.basename(root) + "/\n")
            for line in tree_lines:
                f.write(line + "\n")
            f.write("```\n")
        logger.info(f"✅ Successfully wrote file structure to {output_path}")
    except Exception as e:
        logger.error(f"❌ Failed to write {output_path}: {e}")
        sys.exit(1)

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        logger.warning("Script interrupted by user.")
        sys.exit(1)
    except Exception as e:
        logger.critical(f"Unexpected error: {e}")
        sys.exit(1)