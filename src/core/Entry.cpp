#include "Entry.h"

Entry::Entry()
    : m_id(QUuid::createUuid().toString(QUuid::WithoutBraces))
    , m_title("Untitled")
    , m_content("")
    , m_created(QDateTime::currentDateTime())
    , m_modified(QDateTime::currentDateTime())
{
}

Entry::Entry(const QString& title, const QString& content)
    : m_id(QUuid::createUuid().toString(QUuid::WithoutBraces))
    , m_title(title)
    , m_content(content)
    , m_created(QDateTime::currentDateTime())
    , m_modified(QDateTime::currentDateTime())
{
}

Entry::Entry(const QString& id, const QString& title, const QString& content,
             const QDateTime& created, const QDateTime& modified)
    : m_id(id)
    , m_title(title)
    , m_content(content)
    , m_created(created)
    , m_modified(modified)
{
}

void Entry::setTitle(const QString& title)
{
    m_title = title;
    updateModified();
}

void Entry::setContent(const QString& content)
{
    m_content = content;
    updateModified();
}

void Entry::updateModified()
{
    m_modified = QDateTime::currentDateTime();
}

QString Entry::filename() const
{
    return m_id + ".md";
}
