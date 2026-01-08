#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QSplitter>
#include <QLabel>
#include "markdowneditor.h"
#include "filemanager.h"
#include "journalentry.h"

/**
 * @brief Main application window
 * 
 * Provides the primary UI for the journaling application with
 * a distraction-free editor and entry list.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    // File operations
    void newEntry();
    void saveEntry();
    void deleteEntry();
    
    // Entry selection
    void onEntrySelected(QListWidgetItem *item);
    
    // Settings
    void showSettings();
    void toggleDistractionFree();
    
    // Application
    void about();

private:
    // UI Components
    MarkdownEditor *m_editor;
    QListWidget *m_entryList;
    QSplitter *m_splitter;
    QLabel *m_statusLabel;
    
    // Data
    FileManager *m_fileManager;
    JournalEntry m_currentEntry;
    
    // UI Setup
    void setupUi();
    void setupMenus();
    void setupToolbar();
    void setupStatusBar();
    
    // Helper functions
    void loadEntryList();
    void displayEntry(const JournalEntry& entry);
    bool maybeSave();
    void setCurrentEntry(const JournalEntry& entry);
};

#endif // MAINWINDOW_H
