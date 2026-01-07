#ifndef STORAGE_H
#define STORAGE_H

#include <QString>
#include <QDir>
#include <QList>
#include "Entry.h"

class Storage
{
public:
    explicit Storage(const QString& vaultPath);

    bool saveEntry(const Entry& entry);
    Entry loadEntry(const QString& id);
    QList<Entry> loadAllEntries();
    bool deleteEntry(const QString& id);
    bool entryExists(const QString& id);

    QString vaultPath() const { return m_vaultPath; }
    bool isValid() const;

private:
    QString m_vaultPath;
    QString entryPath(const QString& id) const;
    QString metadataFromContent(const QString& content, const QString& key) const;
};

#endif // STORAGE_H
