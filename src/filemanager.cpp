#include "filemanager.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QRegularExpression>
#include <QDebug>

FileManager::FileManager()
    : m_journalDir(QDir::homePath() + "/.jrnl")
{
    ensureDirectoryExists();
}

FileManager::FileManager(const QString& journalDirectory)
    : m_journalDir(journalDirectory)
{
    ensureDirectoryExists();
}

void FileManager::setJournalDirectory(const QString& path)
{
    m_journalDir.setPath(path);
    ensureDirectoryExists();
}

bool FileManager::ensureDirectoryExists()
{
    if (!m_journalDir.exists()) {
        return m_journalDir.mkpath(m_journalDir.absolutePath());
    }
    return true;
}

bool FileManager::saveEntry(JournalEntry& entry)
{
    QString filePath = entry.filePath();
    
    // Generate filename if not set
    if (filePath.isEmpty()) {
        QString fileName = generateFileName(entry.title(), entry.createdAt());
        filePath = m_journalDir.absoluteFilePath(fileName);
    }
    
    bool success = writeMarkdownFile(filePath, entry);
    
    // Update entry's file path after successful save
    if (success) {
        entry.setFilePath(filePath);
    }
    
    return success;
}

JournalEntry FileManager::loadEntry(const QString& filePath)
{
    return parseMarkdownFile(filePath);
}

QList<JournalEntry> FileManager::loadAllEntries()
{
    QList<JournalEntry> entries;
    QStringList files = listEntryFiles();
    
    for (const QString& fileName : files) {
        QString fullPath = m_journalDir.absoluteFilePath(fileName);
        JournalEntry entry = loadEntry(fullPath);
        if (!entry.isEmpty()) {
            entries.append(entry);
        }
    }
    
    return entries;
}

bool FileManager::deleteEntry(const QString& filePath)
{
    QFile file(filePath);
    return file.remove();
}

QString FileManager::generateFileName(const QString& title, const QDateTime& dateTime)
{
    QString dateStr = dateTime.toString("yyyy-MM-dd");
    QString sanitizedTitle = sanitizeFileName(title);
    
    if (sanitizedTitle.isEmpty()) {
        sanitizedTitle = "untitled";
    }
    
    // Limit length to avoid filesystem issues
    if (sanitizedTitle.length() > 50) {
        sanitizedTitle = sanitizedTitle.left(50);
    }
    
    return QString("%1_%2.md").arg(dateStr, sanitizedTitle);
}

QStringList FileManager::listEntryFiles()
{
    QStringList nameFilters;
    nameFilters << "*.md";
    return m_journalDir.entryList(nameFilters, QDir::Files, QDir::Time | QDir::Reversed);
}

QString FileManager::sanitizeFileName(const QString& name)
{
    // Use simple string replace for better performance
    QString sanitized = name.toLower();
    
    // Replace non-alphanumeric characters with hyphens
    for (int i = 0; i < sanitized.length(); ++i) {
        QChar c = sanitized[i];
        if (!c.isLetterOrNumber()) {
            sanitized[i] = '-';
        }
    }
    
    // Remove leading/trailing hyphens and collapse multiple hyphens
    sanitized = sanitized.trimmed();
    while (sanitized.contains("--")) {
        sanitized.replace("--", "-");
    }
    if (sanitized.startsWith('-')) {
        sanitized = sanitized.mid(1);
    }
    if (sanitized.endsWith('-')) {
        sanitized.chop(1);
    }
    
    return sanitized;
}

bool FileManager::writeMarkdownFile(const QString& filePath, const JournalEntry& entry)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for writing:" << filePath;
        return false;
    }
    
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    
    // Write metadata as YAML frontmatter
    out << "---\n";
    out << "title: " << entry.title() << "\n";
    out << "created: " << entry.createdAt().toString(Qt::ISODate) << "\n";
    out << "modified: " << entry.modifiedAt().toString(Qt::ISODate) << "\n";
    out << "---\n\n";
    
    // Write title as H1 if present
    if (!entry.title().isEmpty()) {
        out << "# " << entry.title() << "\n\n";
    }
    
    // Write content
    out << entry.content();
    
    file.close();
    return true;
}

JournalEntry FileManager::parseMarkdownFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for reading:" << filePath;
        return JournalEntry();
    }
    
    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);
    QString content = in.readAll();
    file.close();
    
    JournalEntry entry;
    entry.setFilePath(filePath);
    
    // Parse YAML frontmatter if present
    if (content.startsWith("---\n")) {
        int endPos = content.indexOf("\n---\n", 4);
        if (endPos != -1) {
            QString frontmatter = content.mid(4, endPos - 4);
            QString mainContent = content.mid(endPos + 5).trimmed();
            
            // Parse frontmatter fields
            QStringList lines = frontmatter.split('\n');
            for (const QString& line : lines) {
                if (line.startsWith("title: ")) {
                    entry.setTitle(line.mid(7).trimmed());
                } else if (line.startsWith("created: ")) {
                    entry.setCreatedAt(QDateTime::fromString(line.mid(9).trimmed(), Qt::ISODate));
                } else if (line.startsWith("modified: ")) {
                    entry.setModifiedAt(QDateTime::fromString(line.mid(10).trimmed(), Qt::ISODate));
                }
            }
            
            // Remove H1 title if it matches the frontmatter title exactly
            if (!entry.title().isEmpty() && 
                mainContent.startsWith("# " + entry.title() + "\n")) {
                // Find the end of the title line
                int newlinePos = mainContent.indexOf('\n');
                if (newlinePos != -1) {
                    mainContent = mainContent.mid(newlinePos + 1).trimmed();
                }
            }
            
            entry.setContent(mainContent);
        }
    } else {
        // No frontmatter, try to extract title from H1
        if (content.startsWith("# ")) {
            int newlinePos = content.indexOf('\n');
            if (newlinePos != -1) {
                entry.setTitle(content.mid(2, newlinePos - 2).trimmed());
                entry.setContent(content.mid(newlinePos + 1).trimmed());
            }
        } else {
            entry.setContent(content);
        }
        
        // Use file metadata for dates
        QFileInfo fileInfo(filePath);
        // birthTime() may not work on all filesystems, use lastModified() as fallback
        QDateTime created = fileInfo.birthTime();
        if (!created.isValid()) {
            created = fileInfo.lastModified();
        }
        entry.setCreatedAt(created);
        entry.setModifiedAt(fileInfo.lastModified());
    }
    
    return entry;
}
