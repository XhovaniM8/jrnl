#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QList>
#include <QDir>
#include "journalentry.h"

/**
 * @brief Manages journal entry storage as Markdown files
 * 
 * This class handles reading and writing journal entries to/from
 * Markdown files, ensuring portability and long-term durability.
 */
class FileManager
{
public:
    FileManager();
    explicit FileManager(const QString& journalDirectory);
    
    // Directory management
    QString journalDirectory() const { return m_journalDir.absolutePath(); }
    void setJournalDirectory(const QString& path);
    bool ensureDirectoryExists();
    
    // Entry operations
    bool saveEntry(JournalEntry& entry);  // Non-const to allow updating file path
    JournalEntry loadEntry(const QString& filePath);
    QList<JournalEntry> loadAllEntries();
    bool deleteEntry(const QString& filePath);
    
    // File utilities
    QString generateFileName(const QString& title, const QDateTime& dateTime);
    QStringList listEntryFiles();
    
private:
    QDir m_journalDir;
    
    // Helper functions
    QString sanitizeFileName(const QString& name);
    bool writeMarkdownFile(const QString& filePath, const JournalEntry& entry);
    JournalEntry parseMarkdownFile(const QString& filePath);
};

#endif // FILEMANAGER_H
