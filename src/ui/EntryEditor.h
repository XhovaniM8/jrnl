#ifndef ENTRYEDITOR_H
#define ENTRYEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QTimer>
#include "core/Entry.h"

class EntryEditor : public QWidget
{
    Q_OBJECT

public:
    explicit EntryEditor(QWidget *parent = nullptr);

    void setEntry(const Entry& entry);
    Entry getEntry() const;
    void clear();
    void markSaved() { m_hasUnsavedChanges = false; }
    
    bool hasUnsavedChanges() const { return m_hasUnsavedChanges; }

signals:
    void entryChanged();
    void saveRequested();

private slots:
    void onTitleChanged();
    void onContentChanged();
    void onAutoSave();

private:
    QLineEdit* m_titleEdit;
    QTextEdit* m_contentEdit;
    QTimer* m_autoSaveTimer;
    Entry m_currentEntry;
    bool m_hasUnsavedChanges;
    
    void setupUi();
};

#endif // ENTRYEDITOR_H
