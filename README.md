# jrnl - Cross-Platform Journaling Application

A clean, distraction-free journaling and writing application inspired by Obsidian, OneNote, and Scrivener. Built with Qt6 and C++ for maximum performance and cross-platform compatibility.

## Features

- **Distraction-Free Writing**: Clean, focused interface for uninterrupted writing
- **Markdown Storage**: All entries stored as portable Markdown files
- **Cross-Platform**: Native support for macOS and Ubuntu
- **Syntax Highlighting**: Beautiful Markdown syntax highlighting
- **Entry Management**: Easy browsing and organization of journal entries
- **Python Integration**: Optional Python support for analytics and advanced processing

## Requirements

### Build Dependencies

- **Qt6** (6.2 or later)
  - Qt6::Core
  - Qt6::Widgets
  - Qt6::Gui
- **CMake** (3.16 or later)
- **C++ Compiler** with C++17 support
  - GCC 7+ on Linux
  - Clang/Apple Clang on macOS
- **Python 3** (optional, for analytics features)

### Platform-Specific Requirements

#### Ubuntu/Linux
```bash
sudo apt-get update
sudo apt-get install qt6-base-dev cmake g++ python3-dev
```

#### macOS
```bash
brew install qt@6 cmake python3
```

## Building

### Linux (Ubuntu)

```bash
# Clone the repository
git clone https://github.com/XhovaniM8/jrnl.git
cd jrnl

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build
make

# Run
./jrnl
```

### macOS

```bash
# Clone the repository
git clone https://github.com/XhovaniM8/jrnl.git
cd jrnl

# Create build directory
mkdir build
cd build

# Configure with CMake (specify Qt6 path if needed)
cmake .. -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qt@6

# Build
make

# Run
./jrnl
```

### Build with Python Integration

To enable Python integration for analytics:

```bash
cmake .. -DPYTHON_ENABLED=ON
make
```

## Usage

### Starting the Application

Simply run the `jrnl` executable:

```bash
./jrnl
```

### Creating a New Entry

1. Click **File → New Entry** or press `Ctrl+N` (Linux) / `Cmd+N` (macOS)
2. Write your content in the editor
3. Click **File → Save** or press `Ctrl+S` / `Cmd+S`
4. Enter a title when prompted

### Distraction-Free Mode

Toggle distraction-free mode by:
- Pressing `Ctrl+D` (Linux) / `Cmd+D` (macOS)
- Selecting **View → Distraction-Free Mode**

This hides the sidebar, menu, and status bar for an immersive writing experience.

### Journal Storage Location

By default, journal entries are stored in `~/.jrnl/`

To change the journal directory:
1. Go to **Settings → Preferences**
2. Select a new directory

### Markdown Format

Entries are stored as Markdown files with YAML frontmatter:

```markdown
---
title: My Journal Entry
created: 2026-01-07T12:00:00
modified: 2026-01-07T15:30:00
---

# My Journal Entry

This is the content of my journal entry.

## Subheading

- Bullet points work
- **Bold** and *italic* text
- `code blocks`
```

## Architecture

### Core Components

- **JournalEntry**: Model class representing a single journal entry
- **FileManager**: Handles reading/writing Markdown files
- **MarkdownEditor**: Custom text editor with syntax highlighting
- **MainWindow**: Primary application window and UI

### File Structure

```
jrnl/
├── CMakeLists.txt          # Build configuration
├── README.md               # This file
├── include/                # Header files
│   ├── mainwindow.h
│   ├── journalentry.h
│   ├── filemanager.h
│   ├── markdowneditor.h
│   └── pythonintegration.h
├── src/                    # Source files
│   ├── main.cpp
│   ├── mainwindow.cpp
│   ├── journalentry.cpp
│   ├── filemanager.cpp
│   └── markdowneditor.cpp
└── resources/              # Resources (future: icons, themes)
```

## Development

### Code Style

- C++17 standard
- Qt coding conventions
- Comprehensive header documentation

### Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test on both macOS and Ubuntu
5. Submit a pull request

## Why Markdown?

Markdown files ensure:
- **Portability**: Open with any text editor
- **Transparency**: Human-readable format
- **Durability**: Future-proof file format
- **Version Control**: Easy to track changes with Git
- **Export**: Simple conversion to HTML, PDF, etc.

## Future Enhancements

- [ ] Full-text search across all entries
- [ ] Tags and categories
- [ ] Export to PDF/HTML
- [ ] Dark mode theme
- [ ] Encryption support
- [ ] Cloud sync
- [ ] Mobile apps (iOS/Android)
- [ ] Plugin system

## License

This project is licensed under the MIT License.

## Acknowledgments

Inspired by:
- **Obsidian**: For Markdown-first approach
- **OneNote**: For organizational features
- **Scrivener**: For distraction-free writing mode
