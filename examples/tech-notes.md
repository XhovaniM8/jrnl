---
title: Qt6 Development Notes
created: 2026-01-07T15:30:00
modified: 2026-01-07T16:45:00
---

# Qt6 Development Notes

## Project Setup

Today I set up the Qt6 development environment for the jrnl application.

### Key Components

The application uses several Qt6 modules:

- **Qt6::Core** - Core non-GUI functionality
- **Qt6::Widgets** - Widget-based UI components
- **Qt6::Gui** - GUI utilities and abstractions

### Architecture Overview

```
MainWindow (QMainWindow)
├── MarkdownEditor (QPlainTextEdit)
│   └── MarkdownHighlighter (QSyntaxHighlighter)
├── Entry List (QListWidget)
└── FileManager (backend)
    └── JournalEntry (model)
```

## Implementation Details

### Markdown Syntax Highlighting

Implemented a custom `QSyntaxHighlighter` subclass to provide:

- Header highlighting (`#`, `##`, etc.)
- Bold text (`**text**` or `__text__`)
- Italic text (`*text*` or `_text_`)
- Code blocks (`` `code` ``)
- Links (`[text](url)`)
- Lists (`-`, `*`, `1.`)

### File Format

Entries are stored with YAML frontmatter:

```yaml
---
title: Entry Title
created: 2026-01-07T12:00:00
modified: 2026-01-07T12:30:00
---
```

This provides structured metadata while keeping the content in plain Markdown.

## Challenges Solved

### Cross-Platform Font Rendering

Different platforms have different default fonts. Solution:

```cpp
QFont font;
font.setFamily("Courier");
font.setStyleHint(QFont::Monospace);
font.setFixedPitch(true);
```

This ensures consistent appearance across macOS and Linux.

### Auto-Save Logic

Implemented a "dirty flag" pattern:
- Monitor `document()->isModified()`
- Prompt before switching entries
- Save automatically when user expects it

## Next Features

- [ ] Full-text search
- [ ] Tags system
- [ ] Export to PDF
- [ ] Dark mode
- [ ] Cloud sync

## Resources

- [Qt6 Documentation](https://doc.qt.io/qt-6/)
- [CMake Qt6 Guide](https://cmake.org/cmake/help/latest/manual/cmake-qt.7.html)
- [Markdown Specification](https://spec.commonmark.org/)

## Learnings

Building a Qt6 application taught me:

1. **Signal/Slot Mechanism**: Elegant way to connect UI events to logic
2. **Model-View Pattern**: Separation of data and presentation
3. **Cross-Platform Development**: Write once, deploy everywhere
4. **Modern C++**: C++17 features with Qt integration

The combination of C++ performance and Qt's rich UI framework is powerful!
