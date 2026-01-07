# User Interface Overview

This document describes the jrnl user interface and its components.

## Application Layout

The jrnl application features a clean, two-panel layout designed for distraction-free writing:

```
┌─────────────────────────────────────────────────────────────────┐
│ File   Help                                          jrnl - Vault│
├──────────────┬──────────────────────────────────────────────────┤
│              │                                                    │
│ ┌──────────┐ │  Title                                            │
│ │+ New Entry│ │  ─────────────────────────────────────────────   │
│ └──────────┘ │                                                    │
│              │                                                    │
│ ┌──────────┐ │  Start writing...                                 │
│ │ Search   │ │                                                    │
│ └──────────┘ │                                                    │
│              │                                                    │
│ Entry 1      │                                                    │
│ Jan 05, 2026 │                                                    │
│ Weekend...   │                                                    │
│              │                                                    │
│ Entry 2      │                                                    │
│ Jan 03, 2026 │                                                    │
│ Thoughts...  │                                                    │
│              │                                                    │
│ Entry 3      │                                                    │
│ Jan 01, 2026 │                                                    │
│ My First...  │                                                    │
│              │                                                    │
└──────────────┴──────────────────────────────────────────────────┘
 Entry List     Entry Editor
 (250-400px)    (Flexible width)
```

## Components

### 1. Vault Selector Dialog (First Launch)

When you first launch jrnl, you see a dialog to create or open a vault:

- **Title**: "Welcome to jrnl"
- **Description**: Brief explanation of vaults
- **Path Input**: Text field with default path (~/Documents/jrnl-vault)
- **Browse Button**: Opens file picker to select vault location
- **Create New Vault** button (green): Creates a new vault at specified path
- **Open Existing Vault** button (blue): Opens an existing vault

### 2. Main Window

#### Top Menu Bar
- **File Menu**:
  - New Entry (Cmd/Ctrl+N)
  - Save (Cmd/Ctrl+S)
  - Delete Entry (Delete key)
  - Quit (Cmd/Ctrl+Q)
- **Help Menu**:
  - About

#### Left Panel - Entry List (250-400px wide)

**Top Section:**
- **+ New Entry Button**: Large green button spanning the width
  - Creates a new entry immediately
  - Opens it in the editor

**Search Bar:**
- Text input field with placeholder "Search entries..."
- Real-time filtering of entries as you type
- Searches both titles and content

**Entry List:**
- Scrollable list of all entries
- Each entry shows:
  - Title (bold, larger font)
  - Modified date (smaller, gray text)
  - Content preview (first 50 characters)
- Selected entry highlighted with light blue background
- Entries sorted by modification time (most recent first)

#### Right Panel - Entry Editor (Flexible width)

**Title Input:**
- Large, bold text field (18pt)
- No visible border (seamless)
- Placeholder: "Title"

**Content Editor:**
- Large text area (12pt)
- No visible border (seamless)
- Plain text input (Markdown formatting)
- Placeholder: "Start writing..."
- Supports standard text editing shortcuts
- Auto-save after 2 seconds of inactivity

#### Bottom Status Bar
- Shows status messages:
  - "Entry saved"
  - "Opened: [entry title]"
  - "Loaded X entries"

## Design Philosophy

### Distraction-Free Writing

- **Minimal chrome**: No unnecessary buttons or decorations
- **Clean typography**: Clear, readable fonts
- **Borderless inputs**: Seamless writing experience
- **Subtle colors**: Light backgrounds, minimal contrast
- **Focus on content**: Maximum space for writing

### Color Scheme

- **Background**: White/light gray
- **Text**: Dark gray/black
- **Accents**: 
  - Green for create actions (#4CAF50)
  - Blue for selection/focus (#e3f2fd)
  - Light gray for borders (#e0e0e0)

### Typography

- **Title**: 18pt, bold, sans-serif
- **Content**: 12pt, regular, sans-serif
- **List items**: 10-11pt, mixed weights

## User Workflows

### Creating a New Entry

1. Click "+ New Entry" button or press Cmd/Ctrl+N
2. New entry appears in editor with "Untitled" title
3. Type title in title field
4. Write content in content area
5. Entry auto-saves after 2 seconds
6. Entry appears in list immediately

### Editing an Entry

1. Click an entry in the list
2. Entry loads in editor
3. Make changes to title or content
4. Changes auto-save after 2 seconds
5. Updated entry reflects in list

### Searching Entries

1. Type search query in search box
2. List filters in real-time
3. Results sorted by relevance
4. Click entry to view/edit

### Deleting an Entry

1. Select entry in list
2. Press Delete key or choose File > Delete Entry
3. Confirm deletion in dialog
4. Entry removed from list and disk

## Keyboard Shortcuts

- **Cmd/Ctrl+N**: New entry
- **Cmd/Ctrl+S**: Save entry (usually not needed due to auto-save)
- **Cmd/Ctrl+Q**: Quit application
- **Delete**: Delete selected entry
- **Cmd/Ctrl+F**: Focus search box (future feature)

## Responsive Design

- Entry list has minimum width of 250px and maximum of 400px
- Editor takes remaining horizontal space
- Vertical space fully utilized
- Splitter can be dragged to adjust panel sizes

## Platform Differences

### macOS
- Native menu bar (top of screen)
- Standard macOS keyboard shortcuts (Cmd+)
- System font (San Francisco)

### Ubuntu/Linux
- In-window menu bar
- Standard Linux keyboard shortcuts (Ctrl+)
- System font (Ubuntu/default sans-serif)

## Accessibility

- Clear visual hierarchy
- Keyboard navigation supported
- Standard Qt6 accessibility features
- High contrast readable text
- No reliance on color alone for information
