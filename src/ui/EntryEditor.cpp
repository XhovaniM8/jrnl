#include "EntryEditor.h"
#include <QVBoxLayout>
#include <QFont>

EntryEditor::EntryEditor(QWidget *parent)
    : QWidget(parent)
    , m_hasUnsavedChanges(false)
{
    setupUi();
    
    // Setup autosave timer (save after 2 seconds of inactivity)
    m_autoSaveTimer = new QTimer(this);
    m_autoSaveTimer->setSingleShot(true);
    m_autoSaveTimer->setInterval(2000);
    connect(m_autoSaveTimer, &QTimer::timeout, this, &EntryEditor::onAutoSave);
}

void EntryEditor::setupUi()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(10);

    // Title edit
    m_titleEdit = new QLineEdit(this);
    m_titleEdit->setPlaceholderText("Title");
    QFont titleFont = m_titleEdit->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    m_titleEdit->setFont(titleFont);
    m_titleEdit->setStyleSheet("QLineEdit { border: none; background: transparent; }");
    
    connect(m_titleEdit, &QLineEdit::textChanged, this, &EntryEditor::onTitleChanged);

    // Content edit
    m_contentEdit = new QTextEdit(this);
    m_contentEdit->setPlaceholderText("Start writing...");
    QFont contentFont = m_contentEdit->font();
    contentFont.setPointSize(12);
    m_contentEdit->setFont(contentFont);
    m_contentEdit->setStyleSheet("QTextEdit { border: none; background: transparent; }");
    m_contentEdit->setAcceptRichText(false);
    
    connect(m_contentEdit, &QTextEdit::textChanged, this, &EntryEditor::onContentChanged);

    layout->addWidget(m_titleEdit);
    layout->addWidget(m_contentEdit);
}

void EntryEditor::setEntry(const Entry& entry)
{
    m_currentEntry = entry;
    m_titleEdit->setText(entry.title());
    m_contentEdit->setPlainText(entry.content());
    m_hasUnsavedChanges = false;
}

Entry EntryEditor::getEntry() const
{
    Entry entry = m_currentEntry;
    entry.setTitle(m_titleEdit->text());
    entry.setContent(m_contentEdit->toPlainText());
    return entry;
}

void EntryEditor::clear()
{
    m_currentEntry = Entry();
    m_titleEdit->clear();
    m_contentEdit->clear();
    m_hasUnsavedChanges = false;
}

void EntryEditor::onTitleChanged()
{
    m_hasUnsavedChanges = true;
    m_autoSaveTimer->start();
    emit entryChanged();
}

void EntryEditor::onContentChanged()
{
    m_hasUnsavedChanges = true;
    m_autoSaveTimer->start();
    emit entryChanged();
}

void EntryEditor::onAutoSave()
{
    if (m_hasUnsavedChanges) {
        emit saveRequested();
        m_hasUnsavedChanges = false;
    }
}
