#ifndef JOURNALENTRY_H
#define JOURNALENTRY_H

#include <QString>
#include <QDateTime>
#include <QMetaType>

/**
 * @brief Represents a single journal entry
 * 
 * This class encapsulates all data for a journal entry including
 * title, content, creation/modification times, and file path.
 */
class JournalEntry
{
public:
    JournalEntry();
    JournalEntry(const QString& title, const QString& content);
    
    // Getters
    QString title() const { return m_title; }
    QString content() const { return m_content; }
    QDateTime createdAt() const { return m_createdAt; }
    QDateTime modifiedAt() const { return m_modifiedAt; }
    QString filePath() const { return m_filePath; }
    
    // Setters
    void setTitle(const QString& title);
    void setContent(const QString& content);
    void setCreatedAt(const QDateTime& dateTime) { m_createdAt = dateTime; }
    void setModifiedAt(const QDateTime& dateTime) { m_modifiedAt = dateTime; }
    void setFilePath(const QString& path) { m_filePath = path; }
    
    // Utility
    bool isEmpty() const;
    void updateModifiedTime();
    
private:
    QString m_title;
    QString m_content;
    QDateTime m_createdAt;
    QDateTime m_modifiedAt;
    QString m_filePath;
};

Q_DECLARE_METATYPE(JournalEntry)

#endif // JOURNALENTRY_H
