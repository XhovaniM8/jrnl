#include "EntryList.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

EntryList::EntryList(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

void EntryList::setupUi()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(5);

    // New entry button
    m_newEntryButton = new QPushButton("+ New Entry", this);
    m_newEntryButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #4CAF50;"
        "   color: white;"
        "   border: none;"
        "   padding: 10px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #45a049;"
        "}"
    );
    connect(m_newEntryButton, &QPushButton::clicked, this, &EntryList::onNewEntryClicked);

    // Search bar
    m_searchEdit = new QLineEdit(this);
    m_searchEdit->setPlaceholderText("Search entries...");
    m_searchEdit->setStyleSheet("QLineEdit { padding: 8px; }");
    connect(m_searchEdit, &QLineEdit::textChanged, this, &EntryList::onSearchTextChanged);

    // Entry list
    m_listWidget = new QListWidget(this);
    m_listWidget->setStyleSheet(
        "QListWidget {"
        "   border: none;"
        "   background: transparent;"
        "}"
        "QListWidget::item {"
        "   padding: 10px;"
        "   border-bottom: 1px solid #e0e0e0;"
        "}"
        "QListWidget::item:selected {"
        "   background-color: #e3f2fd;"
        "}"
    );
    connect(m_listWidget, &QListWidget::itemClicked, this, &EntryList::onItemClicked);

    layout->addWidget(m_newEntryButton);
    layout->addWidget(m_searchEdit);
    layout->addWidget(m_listWidget);
}

void EntryList::setEntries(const QList<Entry>& entries)
{
    m_allEntries = entries;
    refreshList();
}

void EntryList::addEntry(const Entry& entry)
{
    m_allEntries.prepend(entry);
    refreshList();
}

void EntryList::updateEntry(const Entry& entry)
{
    for (int i = 0; i < m_allEntries.size(); ++i) {
        if (m_allEntries[i].id() == entry.id()) {
            m_allEntries[i] = entry;
            
            // Update the list item if it's currently visible
            for (int j = 0; j < m_listWidget->count(); ++j) {
                QListWidgetItem* item = m_listWidget->item(j);
                if (item->data(Qt::UserRole).toString() == entry.id()) {
                    updateListItem(item, entry);
                    break;
                }
            }
            break;
        }
    }
}

void EntryList::removeEntry(const QString& id)
{
    for (int i = 0; i < m_allEntries.size(); ++i) {
        if (m_allEntries[i].id() == id) {
            m_allEntries.removeAt(i);
            break;
        }
    }
    refreshList();
}

void EntryList::clearEntries()
{
    m_allEntries.clear();
    m_listWidget->clear();
}

Entry EntryList::selectedEntry() const
{
    QListWidgetItem* item = m_listWidget->currentItem();
    if (!item) {
        return Entry();
    }
    
    QString id = item->data(Qt::UserRole).toString();
    for (const Entry& entry : m_allEntries) {
        if (entry.id() == id) {
            return entry;
        }
    }
    
    return Entry();
}

QString EntryList::selectedEntryId() const
{
    QListWidgetItem* item = m_listWidget->currentItem();
    if (!item) {
        return QString();
    }
    return item->data(Qt::UserRole).toString();
}

void EntryList::onSearchTextChanged(const QString& text)
{
    refreshList();
}

void EntryList::refreshList()
{
    m_listWidget->clear();
    
    QString searchText = m_searchEdit->text();
    QList<Entry> entriesToShow;
    
    if (searchText.isEmpty()) {
        entriesToShow = m_allEntries;
    } else {
        entriesToShow = m_searchEngine.search(m_allEntries, searchText);
    }
    
    for (const Entry& entry : entriesToShow) {
        QListWidgetItem* item = new QListWidgetItem(m_listWidget);
        item->setData(Qt::UserRole, entry.id());
        updateListItem(item, entry);
        m_listWidget->addItem(item);
    }
}

void EntryList::updateListItem(QListWidgetItem* item, const Entry& entry)
{
    QString displayText = entry.title();
    if (displayText.isEmpty()) {
        displayText = "Untitled";
    }
    
    // Add modified date
    QString dateStr = entry.modified().toString("MMM dd, yyyy");
    displayText += "\n" + dateStr;
    
    // Add preview of content
    QString preview = entry.content().left(50);
    if (entry.content().length() > 50) {
        preview += "...";
    }
    if (!preview.isEmpty()) {
        displayText += "\n" + preview;
    }
    
    item->setText(displayText);
}

void EntryList::onItemClicked(QListWidgetItem* item)
{
    QString id = item->data(Qt::UserRole).toString();
    for (const Entry& entry : m_allEntries) {
        if (entry.id() == id) {
            emit entrySelected(entry);
            break;
        }
    }
}

void EntryList::onNewEntryClicked()
{
    emit newEntryRequested();
}
