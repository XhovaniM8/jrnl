#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <QString>
#include <QList>
#include "Entry.h"

class SearchEngine
{
public:
    SearchEngine();

    QList<Entry> search(const QList<Entry>& entries, const QString& query) const;
    
private:
    bool matches(const Entry& entry, const QString& query) const;
    int calculateScore(const Entry& entry, const QString& query) const;
};

#endif // SEARCHENGINE_H
