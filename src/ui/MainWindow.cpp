#include "MainWindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_vault(nullptr)
{
    setupUi();
    setupMenuBar();
    
    setWindowTitle("jrnl - Journaling App");
    resize(1200, 800);
}

MainWindow::~MainWindow()
{
    if (m_vault) {
        m_vault->close();
        delete m_vault;
    }
}

void MainWindow::setupUi()
{
    // Create main splitter
    m_splitter = new QSplitter(Qt::Horizontal, this);
    
    // Create entry list (left side)
    m_entryList = new EntryList(this);
    m_entryList->setMinimumWidth(250);
    m_entryList->setMaximumWidth(400);
    
    connect(m_entryList, &EntryList::entrySelected, this, &MainWindow::onEntrySelected);
    connect(m_entryList, &EntryList::newEntryRequested, this, &MainWindow::onNewEntry);
    
    // Create entry editor (right side)
    m_entryEditor = new EntryEditor(this);
    connect(m_entryEditor, &EntryEditor::saveRequested, this, &MainWindow::onSaveEntry);
    
    m_splitter->addWidget(m_entryList);
    m_splitter->addWidget(m_entryEditor);
    m_splitter->setStretchFactor(0, 0);
    m_splitter->setStretchFactor(1, 1);
    
    setCentralWidget(m_splitter);
    
    // Status bar
    statusBar()->showMessage("Ready");
}

void MainWindow::setupMenuBar()
{
    // File menu
    QMenu* fileMenu = menuBar()->addMenu("&File");
    
    QAction* newEntryAction = new QAction("&New Entry", this);
    newEntryAction->setShortcut(QKeySequence::New);
    connect(newEntryAction, &QAction::triggered, this, &MainWindow::onNewEntry);
    fileMenu->addAction(newEntryAction);
    
    QAction* saveAction = new QAction("&Save", this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MainWindow::onSaveEntry);
    fileMenu->addAction(saveAction);
    
    fileMenu->addSeparator();
    
    QAction* deleteAction = new QAction("&Delete Entry", this);
    deleteAction->setShortcut(QKeySequence::Delete);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::onDeleteEntry);
    fileMenu->addAction(deleteAction);
    
    fileMenu->addSeparator();
    
    QAction* quitAction = new QAction("&Quit", this);
    quitAction->setShortcut(QKeySequence::Quit);
    connect(quitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(quitAction);
    
    // Help menu
    QMenu* helpMenu = menuBar()->addMenu("&Help");
    
    QAction* aboutAction = new QAction("&About", this);
    connect(aboutAction, &QAction::triggered, [this]() {
        QMessageBox::about(this, "About jrnl",
            "jrnl - A Journaling App\n\n"
            "Version 1.0.0\n\n"
            "A clean, distraction-free journaling application\n"
            "inspired by Obsidian, OneNote, and Scrivener.");
    });
    helpMenu->addAction(aboutAction);
}

bool MainWindow::openVault(const QString& path)
{
    if (m_vault) {
        m_vault->close();
        delete m_vault;
    }
    
    m_vault = new Vault(path);
    
    if (!m_vault->isOpen()) {
        QMessageBox::critical(this, "Error", "Failed to open vault.");
        delete m_vault;
        m_vault = nullptr;
        return false;
    }
    
    setWindowTitle(QString("jrnl - %1").arg(m_vault->name()));
    loadEntries();
    statusBar()->showMessage(QString("Opened vault: %1").arg(m_vault->name()));
    
    return true;
}

void MainWindow::loadEntries()
{
    if (!m_vault || !m_vault->isOpen()) {
        return;
    }
    
    QList<Entry> entries = m_vault->storage()->loadAllEntries();
    m_entryList->setEntries(entries);
    
    statusBar()->showMessage(QString("Loaded %1 entries").arg(entries.size()), 3000);
}

void MainWindow::onNewEntry()
{
    if (!m_vault || !m_vault->isOpen()) {
        QMessageBox::warning(this, "No Vault", "Please open a vault first.");
        return;
    }
    
    // Save current entry if needed
    if (m_entryEditor->hasUnsavedChanges()) {
        saveCurrentEntry();
    }
    
    // Create new entry
    Entry newEntry("New Entry", "");
    m_currentEntry = newEntry;
    m_entryEditor->setEntry(newEntry);
    
    // Save immediately to create the file
    saveCurrentEntry();
    
    // Add to list
    m_entryList->addEntry(newEntry);
    
    statusBar()->showMessage("Created new entry", 2000);
}

void MainWindow::onEntrySelected(const Entry& entry)
{
    // Save current entry if needed
    if (m_entryEditor->hasUnsavedChanges()) {
        saveCurrentEntry();
    }
    
    m_currentEntry = entry;
    m_entryEditor->setEntry(entry);
    
    statusBar()->showMessage(QString("Opened: %1").arg(entry.title()), 2000);
}

void MainWindow::onSaveEntry()
{
    saveCurrentEntry();
}

void MainWindow::saveCurrentEntry()
{
    if (!m_vault || !m_vault->isOpen()) {
        return;
    }
    
    Entry entry = m_entryEditor->getEntry();
    
    if (m_vault->storage()->saveEntry(entry)) {
        m_currentEntry = entry;
        m_entryList->updateEntry(entry);
        m_entryEditor->markSaved();
        statusBar()->showMessage("Entry saved", 2000);
    } else {
        statusBar()->showMessage("Failed to save entry", 3000);
    }
}

void MainWindow::onDeleteEntry()
{
    if (!m_vault || !m_vault->isOpen()) {
        return;
    }
    
    QString id = m_entryList->selectedEntryId();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "No Selection", "Please select an entry to delete.");
        return;
    }
    
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Delete Entry", 
        "Are you sure you want to delete this entry?",
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        if (m_vault->storage()->deleteEntry(id)) {
            m_entryList->removeEntry(id);
            m_entryEditor->clear();
            statusBar()->showMessage("Entry deleted", 2000);
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete entry.");
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Save current entry if needed
    if (m_entryEditor->hasUnsavedChanges()) {
        saveCurrentEntry();
    }
    
    event->accept();
}
