#include "journalentry.h"

JournalEntry::JournalEntry()
    : m_createdAt(QDateTime::currentDateTime())
    , m_modifiedAt(QDateTime::currentDateTime())
{
}

JournalEntry::JournalEntry(const QString& title, const QString& content)
    : m_title(title)
    , m_content(content)
    , m_createdAt(QDateTime::currentDateTime())
    , m_modifiedAt(QDateTime::currentDateTime())
{
}

void JournalEntry::setTitle(const QString& title)
{
    m_title = title;
    updateModifiedTime();
}

void JournalEntry::setContent(const QString& content)
{
    m_content = content;
    updateModifiedTime();
}

bool JournalEntry::isEmpty() const
{
    return m_title.isEmpty() && m_content.isEmpty();
}

void JournalEntry::updateModifiedTime()
{
    m_modifiedAt = QDateTime::currentDateTime();
}
