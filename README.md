# jrnl - A Cross-Platform Journaling Application

A clean, distraction-free journaling and writing application inspired by Obsidian, OneNote, and Scrivener.

## Features

- **Fast, Minimal Writing Experience**: Clean Qt6 interface with minimal visual noise
- **Markdown-First**: All entries stored as Markdown files for portability and long-term durability
- **File-Based Vault Model**: Your data stays with you in plain text files
- **Autosave**: Automatic saving after 2 seconds of inactivity
- **Search**: Quick search across all entries with relevance scoring
- **Cross-Platform**: Works on macOS and Ubuntu (Linux)

## Architecture

- **C++ Backend**: Fast and efficient core logic for persistence, indexing, and search
- **Qt6 UI**: Modern, responsive desktop interface
- **Clear Separation**: UI, core logic, and storage are clearly separated for maintainability

### Core Components

1. **Vault Management**: Create and manage vaults (collections of journal entries)
2. **Entry Model**: Rich entry objects with metadata (title, content, timestamps)
3. **Storage Layer**: File-based persistence with YAML front matter
4. **Search Engine**: Content-based search with relevance scoring
5. **Qt6 UI**: Clean interface with entry list, editor, and vault selector

## Building

### Prerequisites

- CMake 3.16 or higher
- Qt6 development libraries (Core, Widgets, Gui)
- C++17 compatible compiler

### Ubuntu/Debian

```bash
# Install dependencies
sudo apt-get update
sudo apt-get install build-essential cmake qt6-base-dev

# Build
mkdir build
cd build
cmake ..
make

# Run
./jrnl
```

### macOS

```bash
# Install dependencies using Homebrew
brew install cmake qt@6

# Build
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=/usr/local/opt/qt@6 ..
make

# Run
./jrnl
```

## Usage

### First Launch

1. On first launch, you'll see the Vault Selector dialog
2. Choose "Create New Vault" to create a new vault or "Open Existing Vault" to open one
3. Select or enter a path for your vault
4. Click the appropriate button to proceed

### Creating Entries

- Click "+ New Entry" in the sidebar to create a new entry
- Edit the title and content in the editor
- Changes are automatically saved after 2 seconds of inactivity

### Searching

- Use the search bar in the sidebar to filter entries
- Search looks in both titles and content
- Results are sorted by relevance

### File Format

Entries are stored as Markdown files with YAML front matter:

```markdown
---
id: unique-entry-id
title: My Entry Title
created: 2026-01-07T15:30:00
modified: 2026-01-07T15:35:00
---

# My Entry Title

Entry content goes here in Markdown format.
```

## Optional Python Integration

The application is designed to support optional Python integration for analytics and advanced processing. Python scripts can directly read and process the Markdown files in the vault directory.

Example Python script to analyze your journal:

```python
import os
import glob
import yaml

vault_path = "/path/to/your/vault"

# Load all entries
for md_file in glob.glob(os.path.join(vault_path, "*.md")):
    with open(md_file, 'r') as f:
        content = f.read()
        # Parse YAML front matter and content
        # Perform analysis...
```

## Project Structure

```
jrnl/
├── CMakeLists.txt          # Build configuration
├── src/
│   ├── main.cpp            # Application entry point
│   ├── core/               # C++ backend
│   │   ├── Vault.h/cpp     # Vault management
│   │   ├── Entry.h/cpp     # Entry model
│   │   ├── Storage.h/cpp   # File persistence
│   │   └── SearchEngine.h/cpp  # Search functionality
│   └── ui/                 # Qt6 UI components
│       ├── MainWindow.h/cpp    # Main application window
│       ├── EntryEditor.h/cpp   # Entry editor widget
│       ├── EntryList.h/cpp     # Entry list widget
│       └── VaultSelector.h/cpp # Vault selection dialog
└── README.md              # This file
```

## License

This project is open source and available under the MIT License. 
