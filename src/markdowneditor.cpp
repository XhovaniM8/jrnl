#include "markdowneditor.h"
#include <QKeyEvent>
#include <QFont>
#include <QRegularExpression>

MarkdownEditor::MarkdownEditor(QWidget *parent)
    : QPlainTextEdit(parent)
    , m_distractionFreeMode(false)
{
    setupEditor();
    new MarkdownHighlighter(document());
}

void MarkdownEditor::setupEditor()
{
    // Set a clean, readable font
    QFont font;
    font.setFamily("Courier");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(12);
    setFont(font);
    
    // Enable word wrap
    setWordWrapMode(QTextOption::WordWrap);
    setLineWrapMode(QPlainTextEdit::WidgetWidth);
    
    // Set reasonable margins
    setViewportMargins(20, 20, 20, 20);
    
    // Tab width
    const int tabStop = 4;
    QFontMetrics metrics(font);
    setTabStopDistance(tabStop * metrics.horizontalAdvance(' '));
}

void MarkdownEditor::setDistractionFreeMode(bool enabled)
{
    m_distractionFreeMode = enabled;
    
    if (enabled) {
        // Increase margins for centered text
        setViewportMargins(100, 50, 100, 50);
    } else {
        setViewportMargins(20, 20, 20, 20);
    }
}

void MarkdownEditor::keyPressEvent(QKeyEvent *event)
{
    // Handle tab key to insert spaces
    if (event->key() == Qt::Key_Tab) {
        insertPlainText("    ");
        return;
    }
    
    QPlainTextEdit::keyPressEvent(event);
}

// MarkdownHighlighter implementation
MarkdownHighlighter::MarkdownHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    setupHighlightRules();
}

void MarkdownHighlighter::setupHighlightRules()
{
    HighlightRule rule;
    
    // Headers
    QTextCharFormat headerFormat;
    headerFormat.setForeground(Qt::darkBlue);
    headerFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("^#{1,6}\\s+.*$");
    rule.format = headerFormat;
    m_rules.append(rule);
    
    // Bold
    QTextCharFormat boldFormat;
    boldFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("\\*\\*[^\\*]+\\*\\*");
    rule.format = boldFormat;
    m_rules.append(rule);
    rule.pattern = QRegularExpression("__[^_]+__");
    rule.format = boldFormat;
    m_rules.append(rule);
    
    // Italic
    QTextCharFormat italicFormat;
    italicFormat.setFontItalic(true);
    rule.pattern = QRegularExpression("\\*[^\\*]+\\*");
    rule.format = italicFormat;
    m_rules.append(rule);
    rule.pattern = QRegularExpression("_[^_]+_");
    rule.format = italicFormat;
    m_rules.append(rule);
    
    // Code blocks
    QTextCharFormat codeFormat;
    codeFormat.setForeground(Qt::darkGreen);
    codeFormat.setFontFamily("Courier");
    rule.pattern = QRegularExpression("`[^`]+`");
    rule.format = codeFormat;
    m_rules.append(rule);
    
    // Links
    QTextCharFormat linkFormat;
    linkFormat.setForeground(Qt::blue);
    linkFormat.setFontUnderline(true);
    rule.pattern = QRegularExpression("\\[([^\\]]+)\\]\\(([^\\)]+)\\)");
    rule.format = linkFormat;
    m_rules.append(rule);
    
    // Lists
    QTextCharFormat listFormat;
    listFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression("^\\s*[-*+]\\s+");
    rule.format = listFormat;
    m_rules.append(rule);
    rule.pattern = QRegularExpression("^\\s*\\d+\\.\\s+");
    rule.format = listFormat;
    m_rules.append(rule);
}

void MarkdownHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightRule &rule : m_rules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
