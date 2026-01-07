#ifndef MARKDOWNEDITOR_H
#define MARKDOWNEDITOR_H

#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>

/**
 * @brief Custom text editor optimized for Markdown editing
 * 
 * Provides a distraction-free writing experience with
 * syntax highlighting and formatting support.
 */
class MarkdownEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit MarkdownEditor(QWidget *parent = nullptr);
    
    void setDistractionFreeMode(bool enabled);
    bool isModified() const { return document()->isModified(); }
    void setModified(bool modified) { document()->setModified(modified); }

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    bool m_distractionFreeMode;
    void setupEditor();
};

/**
 * @brief Basic Markdown syntax highlighter
 */
class MarkdownHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit MarkdownHighlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightRule> m_rules;
    
    void setupHighlightRules();
};

#endif // MARKDOWNEDITOR_H
