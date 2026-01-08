# Quick Start Guide

Get started with jrnl in 5 minutes!

## Installation

### Ubuntu/Linux

```bash
# Install dependencies
sudo apt-get update
sudo apt-get install qt6-base-dev cmake g++

# Clone and build
git clone https://github.com/XhovaniM8/jrnl.git
cd jrnl
mkdir build && cd build
cmake ..
make

# Run
./jrnl
```

### macOS

```bash
# Install dependencies
brew install qt@6 cmake

# Clone and build
git clone https://github.com/XhovaniM8/jrnl.git
cd jrnl
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qt@6
make

# Run
./jrnl
```

## First Steps

1. **Launch jrnl**
   ```bash
   ./jrnl
   ```

2. **Create Your First Entry**
   - Click "File → New Entry" (or press Ctrl+N / Cmd+N)
   - Start writing in the editor
   - Press Ctrl+S / Cmd+S to save
   - Enter a title when prompted

3. **Try Distraction-Free Mode**
   - Press Ctrl+D / Cmd+D
   - The interface disappears, leaving only your text
   - Press Ctrl+D / Cmd+D again to return

## Keyboard Shortcuts

| Action | Linux/Windows | macOS |
|--------|---------------|-------|
| New Entry | Ctrl+N | Cmd+N |
| Save | Ctrl+S | Cmd+S |
| Distraction-Free | Ctrl+D | Cmd+D |
| Quit | Ctrl+Q | Cmd+Q |

## Markdown Quick Reference

jrnl uses standard Markdown formatting:

```markdown
# Heading 1
## Heading 2
### Heading 3

**bold text**
*italic text*
`code`

- Bullet list
- Another item

1. Numbered list
2. Another item

[Link text](https://example.com)
```

## Your Journal Files

- **Default location**: `~/.jrnl/`
- **Format**: Markdown files (`.md`)
- **Naming**: `YYYY-MM-DD_title.md`

Each entry looks like:

```markdown
---
title: My Entry
created: 2026-01-07T12:00:00
modified: 2026-01-07T14:30:00
---

# My Entry

Your content here...
```

## Tips

### Daily Journaling

- Set aside 10-15 minutes daily
- Morning pages: Write immediately after waking
- Evening reflection: Review your day before bed

### Organization

- Use descriptive titles
- Keep entries focused on one topic
- Use markdown headers for structure

### Backup

Your entries are just files! Back them up:

```bash
# Copy to external drive
cp -r ~/.jrnl /path/to/backup

# Use Git for version control
cd ~/.jrnl
git init
git add .
git commit -m "My journal entries"
```

## Customization

### Change Journal Location

1. Go to "Settings → Preferences"
2. Select your preferred directory
3. All entries will now save there

### Export Entries

Your entries are plain text Markdown files. You can:

- Open them in any text editor
- Convert to PDF using pandoc: `pandoc entry.md -o entry.pdf`
- Convert to HTML: `pandoc entry.md -o entry.html`
- Version control with Git

## Analytics (Optional)

Use the Python analytics module:

```bash
python3 analytics.py
```

Or integrate with your workflow:

```python
from analytics import JournalAnalytics

analytics = JournalAnalytics()
results = analytics.analyze_file("~/.jrnl/2026-01-07_my-entry.md")
print(results['word_count'])
print(results['reading_time_minutes'])
```

## Troubleshooting

### Can't find entries
- Check your journal directory in Settings
- Ensure entries are saved as `.md` files

### Editor not responding
- Try restarting the application
- Check for file permissions in journal directory

### Build errors
- Ensure Qt6 is installed: `qmake6 --version` or `qmake --version`
- Check CMake can find Qt6: `cmake .. -DCMAKE_PREFIX_PATH=/path/to/qt6`

## Next Steps

- Read the full [README.md](README.md)
- Check out [EXAMPLES.md](EXAMPLES.md) for entry inspiration
- Review [BUILD.md](BUILD.md) for advanced build options
- See [CONTRIBUTING.md](CONTRIBUTING.md) to help develop jrnl

## Support

- Report issues on GitHub
- Check existing documentation
- Review example entries

Happy journaling! ✨
