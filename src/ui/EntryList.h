#ifndef ENTRYLIST_H
#define ENTRYLIST_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QList>
#include "core/Entry.h"
#include "core/SearchEngine.h"

class EntryList : public QWidget
{
    Q_OBJECT

public:
    explicit EntryList(QWidget *parent = nullptr);

    void setEntries(const QList<Entry>& entries);
    void addEntry(const Entry& entry);
    void updateEntry(const Entry& entry);
    void removeEntry(const QString& id);
    void clearEntries();
    
    Entry selectedEntry() const;
    QString selectedEntryId() const;

signals:
    void entrySelected(const Entry& entry);
    void newEntryRequested();
    void deleteEntryRequested(const QString& id);

private slots:
    void onSearchTextChanged(const QString& text);
    void onItemClicked(QListWidgetItem* item);
    void onNewEntryClicked();

private:
    QLineEdit* m_searchEdit;
    QListWidget* m_listWidget;
    QPushButton* m_newEntryButton;
    
    QList<Entry> m_allEntries;
    SearchEngine m_searchEngine;
    
    void setupUi();
    void refreshList();
    void updateListItem(QListWidgetItem* item, const Entry& entry);
};

#endif // ENTRYLIST_H
