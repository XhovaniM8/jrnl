# Contributing to jrnl

Thank you for your interest in contributing to jrnl! This document provides guidelines for contributing to the project.

## Getting Started

1. Fork the repository
2. Clone your fork: `git clone https://github.com/YOUR_USERNAME/jrnl.git`
3. Create a feature branch: `git checkout -b feature/your-feature-name`
4. Make your changes
5. Test thoroughly on both macOS and Linux
6. Submit a pull request

## Development Setup

### Prerequisites

- Qt6 (6.2 or later)
- CMake (3.16 or later)
- C++17 compatible compiler
- Python 3.x (optional, for analytics)

See [BUILD.md](BUILD.md) for detailed setup instructions.

### Building for Development

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)
```

## Code Style

### C++ Guidelines

- **Standard**: C++17
- **Style**: Follow Qt coding conventions
- **Naming**:
  - Classes: `PascalCase` (e.g., `MainWindow`)
  - Methods: `camelCase` (e.g., `loadEntry`)
  - Member variables: `m_camelCase` (e.g., `m_editor`)
  - Constants: `UPPER_SNAKE_CASE` (e.g., `MAX_ENTRIES`)

### Code Example

```cpp
class ExampleClass
{
public:
    ExampleClass();
    
    void doSomething();
    QString getValue() const { return m_value; }
    
private:
    QString m_value;
    int m_count;
};
```

### Header Documentation

All public APIs should include Doxygen-style comments:

```cpp
/**
 * @brief Brief description
 * 
 * Detailed description of functionality.
 * 
 * @param parameter Description of parameter
 * @return Description of return value
 */
```

### Python Guidelines

- **Style**: PEP 8
- **Docstrings**: Google style
- **Type hints**: Use where appropriate

## Testing

### Manual Testing

Before submitting, test your changes on:

- [ ] Ubuntu Linux (latest LTS)
- [ ] macOS (latest version)
- [ ] Create, read, update, delete entries
- [ ] Distraction-free mode
- [ ] Settings and preferences

### Future: Automated Tests

We plan to add:
- Unit tests with Qt Test framework
- Integration tests
- CI/CD pipeline

## Pull Request Guidelines

### Before Submitting

- [ ] Code compiles without warnings
- [ ] Manual testing completed
- [ ] Code follows style guidelines
- [ ] Documentation updated (if needed)
- [ ] Commit messages are clear

### Commit Messages

Use clear, descriptive commit messages:

```
Add feature: Brief description

Detailed explanation of what changed and why.
Include any relevant context or decisions made.

Fixes #123
```

### PR Description Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Testing
- [ ] Tested on Linux
- [ ] Tested on macOS
- [ ] Manual testing completed

## Screenshots
(if applicable)
```

## Areas for Contribution

### High Priority

- **Search Functionality**: Full-text search across entries
- **Export Features**: PDF, HTML, EPUB export
- **Tags/Categories**: Organize entries with tags
- **Dark Mode**: Complete dark theme
- **Tests**: Unit and integration tests

### Medium Priority

- **Encryption**: Optional entry encryption
- **Templates**: Entry templates
- **Statistics**: Writing statistics dashboard
- **Backup**: Automated backup functionality
- **Plugins**: Plugin architecture

### Documentation

- User guide
- Developer documentation
- Video tutorials
- Translation (i18n)

## Architecture

### Directory Structure

```
jrnl/
├── include/          # Header files
├── src/              # Implementation files
├── resources/        # Icons, themes, etc.
├── examples/         # Example journal entries
├── tests/            # Test files (future)
└── docs/             # Documentation (future)
```

### Core Classes

- **MainWindow**: Primary UI and application logic
- **MarkdownEditor**: Custom text editor with highlighting
- **JournalEntry**: Data model for entries
- **FileManager**: File I/O operations
- **MarkdownHighlighter**: Syntax highlighting

### Adding New Features

1. Create header in `include/`
2. Implement in `src/`
3. Update `CMakeLists.txt`
4. Add tests (when test framework is ready)
5. Update documentation

## Python Integration

If contributing Python analytics:

- Place Python code in project root or `scripts/`
- Follow PEP 8 style
- Include docstrings
- Add type hints
- Ensure compatibility with Python 3.7+

## Questions?

- Open an issue for discussion
- Join community discussions
- Check existing issues and PRs

## Code of Conduct

- Be respectful and inclusive
- Focus on constructive feedback
- Help create a welcoming environment
- Follow project guidelines

## License

By contributing, you agree that your contributions will be licensed under the MIT License.

---

Thank you for contributing to jrnl! Your efforts help make journaling better for everyone.
