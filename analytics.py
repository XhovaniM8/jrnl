#!/usr/bin/env python3
"""
jrnl Analytics Module

This module provides text analytics functionality for journal entries.
It can be integrated with the Qt6 C++ application for advanced processing.

Features:
- Word count and character statistics
- Reading time estimation
- Sentiment analysis (basic)
- Text complexity metrics
"""

import re
from typing import Dict, Any
from pathlib import Path


class JournalAnalytics:
    """Analytics processor for journal entries"""
    
    # Average reading speed (words per minute)
    WORDS_PER_MINUTE = 200
    
    def __init__(self):
        """Initialize the analytics processor"""
        pass
    
    def analyze_text(self, content: str) -> Dict[str, Any]:
        """
        Perform comprehensive text analysis
        
        Args:
            content: The text content to analyze
            
        Returns:
            Dictionary with analysis results
        """
        return {
            'word_count': self.get_word_count(content),
            'character_count': len(content),
            'character_count_no_spaces': len(content.replace(' ', '')),
            'line_count': content.count('\n') + 1,
            'paragraph_count': self.get_paragraph_count(content),
            'sentence_count': self.get_sentence_count(content),
            'reading_time_minutes': self.estimate_reading_time(content),
            'avg_word_length': self.get_avg_word_length(content),
            'avg_sentence_length': self.get_avg_sentence_length(content),
        }
    
    def get_word_count(self, content: str) -> int:
        """
        Count words in the text
        
        Args:
            content: Text content
            
        Returns:
            Number of words
        """
        # Remove markdown syntax
        text = re.sub(r'[#*`\[\]()]', ' ', content)
        # Split and count non-empty words
        words = text.split()
        return len([w for w in words if w.strip()])
    
    def estimate_reading_time(self, content: str) -> int:
        """
        Estimate reading time in minutes
        
        Args:
            content: Text content
            
        Returns:
            Estimated reading time in minutes
        """
        word_count = self.get_word_count(content)
        minutes = max(1, round(word_count / self.WORDS_PER_MINUTE))
        return minutes
    
    def get_paragraph_count(self, content: str) -> int:
        """
        Count paragraphs (separated by blank lines)
        
        Args:
            content: Text content
            
        Returns:
            Number of paragraphs
        """
        paragraphs = re.split(r'\n\s*\n', content.strip())
        return len([p for p in paragraphs if p.strip()])
    
    def get_sentence_count(self, content: str) -> int:
        """
        Count sentences
        
        Args:
            content: Text content
            
        Returns:
            Number of sentences
        """
        # Simple sentence detection
        sentences = re.split(r'[.!?]+', content)
        return len([s for s in sentences if s.strip()])
    
    def get_avg_word_length(self, content: str) -> float:
        """
        Calculate average word length
        
        Args:
            content: Text content
            
        Returns:
            Average word length
        """
        text = re.sub(r'[#*`\[\]()]', ' ', content)
        words = [w.strip() for w in text.split() if w.strip()]
        
        if not words:
            return 0.0
        
        total_length = sum(len(w) for w in words)
        return round(total_length / len(words), 2)
    
    def get_avg_sentence_length(self, content: str) -> float:
        """
        Calculate average sentence length in words
        
        Args:
            content: Text content
            
        Returns:
            Average words per sentence
        """
        word_count = self.get_word_count(content)
        sentence_count = self.get_sentence_count(content)
        
        if sentence_count == 0:
            return 0.0
        
        return round(word_count / sentence_count, 2)
    
    def analyze_file(self, filepath: str) -> Dict[str, Any]:
        """
        Analyze a journal entry file
        
        Args:
            filepath: Path to the markdown file
            
        Returns:
            Dictionary with analysis results
        """
        path = Path(filepath)
        
        if not path.exists():
            return {'error': 'File not found'}
        
        try:
            content = path.read_text(encoding='utf-8')
            
            # Remove YAML frontmatter if present
            if content.startswith('---\n'):
                parts = content.split('\n---\n', 1)
                if len(parts) > 1:
                    content = parts[1].strip()
            
            result = self.analyze_text(content)
            result['filename'] = path.name
            result['filepath'] = str(path)
            
            return result
            
        except Exception as e:
            return {'error': str(e)}


def main():
    """Example usage of the analytics module"""
    
    analytics = JournalAnalytics()
    
    # Example text
    sample_text = """
    # My Journal Entry
    
    Today was an interesting day. I learned a lot about Qt6 and C++ development.
    The cross-platform capabilities are really impressive.
    
    I'm excited to continue working on this journaling application.
    It combines the best features of Obsidian, OneNote, and Scrivener.
    
    The markdown format ensures that my entries will be readable for years to come.
    """
    
    # Analyze
    results = analytics.analyze_text(sample_text)
    
    print("Journal Entry Analysis:")
    print("=" * 50)
    for key, value in results.items():
        print(f"{key.replace('_', ' ').title()}: {value}")


if __name__ == '__main__':
    main()
