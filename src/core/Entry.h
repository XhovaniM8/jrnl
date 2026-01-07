#ifndef ENTRY_H
#define ENTRY_H

#include <QString>
#include <QDateTime>
#include <QUuid>

class Entry
{
public:
    Entry();
    Entry(const QString& title, const QString& content);
    Entry(const QString& id, const QString& title, const QString& content, 
          const QDateTime& created, const QDateTime& modified);

    QString id() const { return m_id; }
    QString title() const { return m_title; }
    QString content() const { return m_content; }
    QDateTime created() const { return m_created; }
    QDateTime modified() const { return m_modified; }

    void setTitle(const QString& title);
    void setContent(const QString& content);
    void updateModified();

    QString filename() const;

private:
    QString m_id;
    QString m_title;
    QString m_content;
    QDateTime m_created;
    QDateTime m_modified;
};

#endif // ENTRY_H
