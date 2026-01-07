#!/usr/bin/env python3
"""
Example Python script for analyzing jrnl vault entries

This demonstrates the optional Python integration for analytics and
advanced processing of journal entries.
"""

import os
import sys
import re
from datetime import datetime
from collections import Counter
import glob

def parse_entry(filepath):
    """Parse a jrnl Markdown entry file"""
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Parse YAML front matter
    metadata = {}
    front_matter_match = re.search(r'^---\s*\n(.*?)\n---\s*\n', content, re.DOTALL)
    
    if front_matter_match:
        front_matter = front_matter_match.group(1)
        for line in front_matter.split('\n'):
            if ':' in line:
                key, value = line.split(':', 1)
                metadata[key.strip()] = value.strip()
        
        # Get content after front matter
        entry_content = content[front_matter_match.end():]
    else:
        entry_content = content
    
    # Remove title header if present
    entry_content = re.sub(r'^#\s+.*?\n\n', '', entry_content)
    
    return {
        'metadata': metadata,
        'content': entry_content.strip()
    }

def analyze_vault(vault_path):
    """Analyze all entries in a vault"""
    
    if not os.path.exists(vault_path):
        print(f"Error: Vault path '{vault_path}' does not exist")
        return
    
    # Find all markdown files
    entries = []
    for md_file in glob.glob(os.path.join(vault_path, "*.md")):
        try:
            entry = parse_entry(md_file)
            entry['filename'] = os.path.basename(md_file)
            entries.append(entry)
        except Exception as e:
            print(f"Warning: Failed to parse {md_file}: {e}")
    
    if not entries:
        print(f"No entries found in vault: {vault_path}")
        return
    
    print(f"\n{'='*60}")
    print(f"Vault Analysis: {os.path.basename(vault_path)}")
    print(f"{'='*60}\n")
    
    # Basic statistics
    print(f"Total entries: {len(entries)}")
    
    # Word count statistics
    word_counts = []
    for entry in entries:
        words = len(entry['content'].split())
        word_counts.append(words)
    
    if word_counts:
        print(f"Total words: {sum(word_counts)}")
        print(f"Average words per entry: {sum(word_counts) / len(word_counts):.1f}")
        print(f"Longest entry: {max(word_counts)} words")
        print(f"Shortest entry: {min(word_counts)} words")
    
    # Timeline analysis
    dates = []
    for entry in entries:
        created = entry['metadata'].get('created', '')
        if created:
            try:
                date = datetime.fromisoformat(created)
                dates.append(date)
            except:
                pass
    
    if dates:
        dates.sort()
        print(f"\nFirst entry: {dates[0].strftime('%Y-%m-%d')}")
        print(f"Latest entry: {dates[-1].strftime('%Y-%m-%d')}")
        
        # Entries by month
        months = [d.strftime('%Y-%m') for d in dates]
        month_counts = Counter(months)
        print(f"\nEntries by month:")
        for month, count in sorted(month_counts.items()):
            print(f"  {month}: {count} entries")
    
    # Word frequency analysis (top 10 words)
    all_words = []
    for entry in entries:
        words = re.findall(r'\b[a-z]+\b', entry['content'].lower())
        all_words.extend(words)
    
    # Filter out common words
    common_words = {'the', 'a', 'an', 'and', 'or', 'but', 'in', 'on', 'at', 'to', 
                   'for', 'of', 'with', 'by', 'from', 'is', 'was', 'are', 'were',
                   'be', 'been', 'being', 'have', 'has', 'had', 'do', 'does', 'did',
                   'will', 'would', 'should', 'could', 'may', 'might', 'can', 'this',
                   'that', 'these', 'those', 'i', 'you', 'he', 'she', 'it', 'we', 'they'}
    
    meaningful_words = [w for w in all_words if w not in common_words and len(w) > 3]
    word_freq = Counter(meaningful_words)
    
    print(f"\nTop 10 most frequent words:")
    for word, count in word_freq.most_common(10):
        print(f"  {word}: {count} times")
    
    # Entry titles
    print(f"\nRecent entries:")
    for entry in sorted(entries, key=lambda e: e['metadata'].get('modified', ''), reverse=True)[:5]:
        title = entry['metadata'].get('title', 'Untitled')
        modified = entry['metadata'].get('modified', 'Unknown')
        print(f"  - {title} (modified: {modified})")
    
    print(f"\n{'='*60}\n")

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 analyze_vault.py <vault_path>")
        print("\nExample:")
        print("  python3 analyze_vault.py ~/Documents/jrnl-vault")
        sys.exit(1)
    
    vault_path = sys.argv[1]
    analyze_vault(vault_path)

if __name__ == "__main__":
    main()
