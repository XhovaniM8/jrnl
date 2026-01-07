# Python Examples

This directory contains example Python scripts that demonstrate the optional Python integration for analyzing and processing jrnl vault entries.

## analyze_vault.py

Analyzes a jrnl vault and provides statistics including:
- Total entries and word counts
- Timeline analysis (first/last entry, entries by month)
- Word frequency analysis
- Recent entries listing

### Usage

```bash
python3 analyze_vault.py <vault_path>
```

### Example

```bash
python3 analyze_vault.py ~/Documents/jrnl-vault
```

This will output statistics like:
- Total entries and average word count
- Timeline of entries
- Most frequently used words
- Recent entries

## Creating Your Own Scripts

Since jrnl stores all entries as Markdown files with YAML front matter, you can easily write your own Python scripts to analyze, process, or export your journal entries.

### Entry Format

Each entry is stored as a `.md` file with this structure:

```markdown
---
id: unique-id
title: Entry Title
created: 2026-01-07T10:00:00
modified: 2026-01-07T10:30:00
---

# Entry Title

Entry content in Markdown format.
```

### Example: Reading All Entries

```python
import glob
import os
import re

vault_path = "/path/to/your/vault"

for md_file in glob.glob(os.path.join(vault_path, "*.md")):
    with open(md_file, 'r') as f:
        content = f.read()
        
        # Parse front matter
        match = re.search(r'^---\s*\n(.*?)\n---\s*\n', content, re.DOTALL)
        if match:
            metadata = match.group(1)
            entry_content = content[match.end():]
            
            # Process entry...
```

## Ideas for Scripts

- **Export to PDF**: Convert entries to PDF format
- **Mood Tracking**: Analyze sentiment in entries over time
- **Tag Cloud**: Generate tag clouds from frequent words
- **Statistics Dashboard**: Create visualizations of writing patterns
- **Backup/Sync**: Automated backup scripts
- **Search**: Advanced search across all entries
- **Export**: Export to different formats (HTML, PDF, etc.)
