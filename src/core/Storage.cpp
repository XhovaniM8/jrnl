#include "Storage.h"
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>

Storage::Storage(const QString& vaultPath)
    : m_vaultPath(vaultPath)
{
}

bool Storage::isValid() const
{
    QDir dir(m_vaultPath);
    return dir.exists();
}

QString Storage::entryPath(const QString& id) const
{
    return m_vaultPath + "/" + id + ".md";
}

bool Storage::saveEntry(const Entry& entry)
{
    QString path = entryPath(entry.id());
    QFile file(path);
    
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for writing:" << path;
        return false;
    }

    QTextStream out(&file);
    
    // Write metadata as YAML front matter
    out << "---\n";
    out << "id: " << entry.id() << "\n";
    out << "title: " << entry.title() << "\n";
    out << "created: " << entry.created().toString(Qt::ISODate) << "\n";
    out << "modified: " << entry.modified().toString(Qt::ISODate) << "\n";
    out << "---\n\n";
    
    // Write content
    out << "# " << entry.title() << "\n\n";
    out << entry.content();
    
    file.close();
    return true;
}

Entry Storage::loadEntry(const QString& id)
{
    QString path = entryPath(id);
    QFile file(path);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for reading:" << path;
        return Entry();
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    // Parse YAML front matter
    QRegularExpression frontMatterRegex("^---\\s*\\n(.*?)\\n---\\s*\\n", 
                                       QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatch match = frontMatterRegex.match(content);
    
    QString entryId = id;
    QString title = "Untitled";
    QDateTime created = QDateTime::currentDateTime();
    QDateTime modified = QDateTime::currentDateTime();
    QString entryContent;

    if (match.hasMatch()) {
        QString metadata = match.captured(1);
        
        // Extract metadata fields
        entryId = metadataFromContent(metadata, "id");
        if (entryId.isEmpty()) entryId = id;
        
        title = metadataFromContent(metadata, "title");
        
        QString createdStr = metadataFromContent(metadata, "created");
        if (!createdStr.isEmpty()) {
            created = QDateTime::fromString(createdStr, Qt::ISODate);
        }
        
        QString modifiedStr = metadataFromContent(metadata, "modified");
        if (!modifiedStr.isEmpty()) {
            modified = QDateTime::fromString(modifiedStr, Qt::ISODate);
        }
        
        // Get content after front matter
        entryContent = content.mid(match.capturedEnd());
        
        // Remove the title header if present
        QRegularExpression titleRegex("^#\\s+.*?\\n\\n");
        entryContent = entryContent.remove(titleRegex);
    } else {
        entryContent = content;
    }

    return Entry(entryId, title, entryContent.trimmed(), created, modified);
}

QString Storage::metadataFromContent(const QString& content, const QString& key) const
{
    QRegularExpression regex(key + ":\\s*(.+)");
    QRegularExpressionMatch match = regex.match(content);
    if (match.hasMatch()) {
        return match.captured(1).trimmed();
    }
    return QString();
}

QList<Entry> Storage::loadAllEntries()
{
    QList<Entry> entries;
    QDir dir(m_vaultPath);
    
    if (!dir.exists()) {
        qWarning() << "Vault directory does not exist:" << m_vaultPath;
        return entries;
    }

    QStringList filters;
    filters << "*.md";
    QFileInfoList files = dir.entryInfoList(filters, QDir::Files, QDir::Time | QDir::Reversed);
    
    for (const QFileInfo& fileInfo : files) {
        QString id = fileInfo.baseName();
        Entry entry = loadEntry(id);
        if (!entry.id().isEmpty()) {
            entries.append(entry);
        }
    }
    
    return entries;
}

bool Storage::deleteEntry(const QString& id)
{
    QString path = entryPath(id);
    return QFile::remove(path);
}

bool Storage::entryExists(const QString& id)
{
    QString path = entryPath(id);
    return QFile::exists(path);
}
