#include "SearchEngine.h"
#include <QRegularExpression>
#include <algorithm>

SearchEngine::SearchEngine()
{
}

QList<Entry> SearchEngine::search(const QList<Entry>& entries, const QString& query) const
{
    if (query.trimmed().isEmpty()) {
        return entries;
    }

    QList<Entry> results;
    
    for (const Entry& entry : entries) {
        if (matches(entry, query)) {
            results.append(entry);
        }
    }
    
    // Sort by relevance score (higher is better)
    std::sort(results.begin(), results.end(), [this, query](const Entry& a, const Entry& b) {
        return calculateScore(a, query) > calculateScore(b, query);
    });
    
    return results;
}

bool SearchEngine::matches(const Entry& entry, const QString& query) const
{
    QString lowerQuery = query.toLower();
    
    // Search in title
    if (entry.title().toLower().contains(lowerQuery)) {
        return true;
    }
    
    // Search in content
    if (entry.content().toLower().contains(lowerQuery)) {
        return true;
    }
    
    return false;
}

int SearchEngine::calculateScore(const Entry& entry, const QString& query) const
{
    int score = 0;
    QString lowerQuery = query.toLower();
    
    // Higher score for title matches
    if (entry.title().toLower().contains(lowerQuery)) {
        score += 100;
        
        // Even higher if it's at the beginning
        if (entry.title().toLower().startsWith(lowerQuery)) {
            score += 50;
        }
    }
    
    // Score for content matches
    QString lowerContent = entry.content().toLower();
    int occurrences = lowerContent.count(lowerQuery);
    score += occurrences * 10;
    
    return score;
}
