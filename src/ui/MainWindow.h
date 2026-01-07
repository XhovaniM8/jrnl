#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include "EntryEditor.h"
#include "EntryList.h"
#include "core/Vault.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool openVault(const QString& path);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onNewEntry();
    void onEntrySelected(const Entry& entry);
    void onSaveEntry();
    void onDeleteEntry();

private:
    EntryList* m_entryList;
    EntryEditor* m_entryEditor;
    QSplitter* m_splitter;
    
    Vault* m_vault;
    Entry m_currentEntry;
    
    void setupUi();
    void setupMenuBar();
    void loadEntries();
    void saveCurrentEntry();
};

#endif // MAINWINDOW_H
