# Example Journal Entries

This directory contains example journal entries to demonstrate the Markdown format used by jrnl.

## Entry Format

Each entry is a Markdown file with YAML frontmatter containing metadata.

### Example 1: Basic Entry

```markdown
---
title: First Day
created: 2026-01-07T09:00:00
modified: 2026-01-07T09:30:00
---

# First Day

Today I started using jrnl, a new cross-platform journaling application.
The distraction-free mode is perfect for focused writing.

I appreciate that all entries are stored as Markdown files - this ensures
my writing will always be accessible, even decades from now.
```

### Example 2: Technical Entry

```markdown
---
title: Learning Qt6
created: 2026-01-07T14:00:00
modified: 2026-01-07T16:45:00
---

# Learning Qt6

## Key Concepts

Today I explored several Qt6 concepts:

- Signal and slot mechanism
- Model-View architecture
- QPlainTextEdit customization

### Code Example

```cpp
connect(button, &QPushButton::clicked, this, &MainWindow::handleClick);
```

The syntax is elegant and type-safe!

## Resources

- [Qt Documentation](https://doc.qt.io/)
- *C++ GUI Programming with Qt*
```

### Example 3: Creative Writing

```markdown
---
title: Story Ideas
created: 2026-01-07T20:00:00
modified: 2026-01-07T21:30:00
---

# Story Ideas

## The Digital Archive

*A short story concept*

In 2086, an archivist discovers journal entries from the 2020s, perfectly
preserved as Markdown files. Unlike proprietary formats that became obsolete,
these plain text files tell the story of...

**Characters:**
- Elena: The archivist
- Marcus: A tech historian
- The Voice: AI curator of the archives

**Themes:**
- Digital preservation
- Human connection across time
- The value of open formats
```

## Features Demonstrated

These examples showcase:

1. **YAML Frontmatter**: Structured metadata
2. **Markdown Syntax**: Headers, lists, emphasis
3. **Code Blocks**: For technical content
4. **Links**: Internal and external references
5. **Mixed Content**: Technical and creative writing

## Using These Examples

To use these examples:

1. Copy any example to a `.md` file
2. Save it in your journal directory (default: `~/.jrnl/`)
3. Open jrnl and the entry will appear in your list

## Creating Your Own Templates

You can create templates for different types of entries:

- Daily journal
- Meeting notes
- Technical documentation
- Creative writing
- Dream journal
- Gratitude log
- Project planning

Simply create a Markdown file with your preferred structure and copy it when creating new entries.
