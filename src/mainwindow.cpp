#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include <QInputDialog>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_editor(nullptr)
    , m_entryList(nullptr)
    , m_splitter(nullptr)
    , m_statusLabel(nullptr)
    , m_fileManager(nullptr)
{
    // Initialize file manager with default directory
    m_fileManager = new FileManager();
    
    setupUi();
    setupMenus();
    setupToolbar();
    setupStatusBar();
    
    // Load existing entries
    loadEntryList();
    
    // Set window properties
    setWindowTitle("jrnl - Journaling Application");
    resize(1200, 800);
}

MainWindow::~MainWindow()
{
    delete m_fileManager;
}

void MainWindow::setupUi()
{
    // Create main widget and layout
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    
    // Create splitter for sidebar and editor
    m_splitter = new QSplitter(Qt::Horizontal, this);
    
    // Create entry list (sidebar)
    m_entryList = new QListWidget(this);
    m_entryList->setMaximumWidth(300);
    m_entryList->setMinimumWidth(200);
    connect(m_entryList, &QListWidget::itemClicked, this, &MainWindow::onEntrySelected);
    
    // Create editor
    m_editor = new MarkdownEditor(this);
    
    // Add to splitter
    m_splitter->addWidget(m_entryList);
    m_splitter->addWidget(m_editor);
    m_splitter->setStretchFactor(0, 0);
    m_splitter->setStretchFactor(1, 1);
    
    // Add splitter to main layout
    mainLayout->addWidget(m_splitter);
    
    setCentralWidget(centralWidget);
}

void MainWindow::setupMenus()
{
    // File menu
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    
    QAction *newAction = fileMenu->addAction(tr("&New Entry"));
    newAction->setShortcut(QKeySequence::New);
    connect(newAction, &QAction::triggered, this, &MainWindow::newEntry);
    
    QAction *saveAction = fileMenu->addAction(tr("&Save"));
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveEntry);
    
    fileMenu->addSeparator();
    
    QAction *deleteAction = fileMenu->addAction(tr("&Delete Entry"));
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteEntry);
    
    fileMenu->addSeparator();
    
    QAction *quitAction = fileMenu->addAction(tr("&Quit"));
    quitAction->setShortcut(QKeySequence::Quit);
    connect(quitAction, &QAction::triggered, this, &MainWindow::close);
    
    // View menu
    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));
    
    QAction *distractionFreeAction = viewMenu->addAction(tr("&Distraction-Free Mode"));
    distractionFreeAction->setCheckable(true);
    distractionFreeAction->setShortcut(Qt::CTRL | Qt::Key_D);
    connect(distractionFreeAction, &QAction::triggered, this, &MainWindow::toggleDistractionFree);
    
    // Settings menu
    QMenu *settingsMenu = menuBar()->addMenu(tr("&Settings"));
    
    QAction *settingsAction = settingsMenu->addAction(tr("&Preferences"));
    connect(settingsAction, &QAction::triggered, this, &MainWindow::showSettings);
    
    // Help menu
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    
    QAction *aboutAction = helpMenu->addAction(tr("&About"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::setupToolbar()
{
    QToolBar *toolbar = addToolBar(tr("Main Toolbar"));
    
    QAction *newAction = toolbar->addAction(tr("New"));
    connect(newAction, &QAction::triggered, this, &MainWindow::newEntry);
    
    QAction *saveAction = toolbar->addAction(tr("Save"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveEntry);
    
    toolbar->addSeparator();
    
    QAction *deleteAction = toolbar->addAction(tr("Delete"));
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteEntry);
}

void MainWindow::setupStatusBar()
{
    m_statusLabel = new QLabel(tr("Ready"), this);
    statusBar()->addWidget(m_statusLabel);
}

void MainWindow::newEntry()
{
    // Check if current entry needs saving
    if (!maybeSave()) {
        return;
    }
    
    // Create new entry (default constructor creates empty file path)
    m_currentEntry = JournalEntry();
    m_editor->clear();
    m_editor->setModified(false);
    m_statusLabel->setText(tr("New entry"));
}

void MainWindow::saveEntry()
{
    // Get title from user if not set
    QString title = m_currentEntry.title();
    if (title.isEmpty()) {
        bool ok;
        title = QInputDialog::getText(this, tr("Entry Title"),
                                      tr("Enter a title for this entry:"),
                                      QLineEdit::Normal, "", &ok);
        if (!ok || title.isEmpty()) {
            return;
        }
    }
    
    // Update entry
    m_currentEntry.setTitle(title);
    m_currentEntry.setContent(m_editor->toPlainText());
    m_currentEntry.updateModifiedTime();
    
    // Save to file
    if (m_fileManager->saveEntry(m_currentEntry)) {
        m_editor->setModified(false);
        m_statusLabel->setText(tr("Entry saved"));
        
        // Reload entry list
        loadEntryList();
    } else {
        QMessageBox::warning(this, tr("Save Error"),
                           tr("Failed to save entry."));
    }
}

void MainWindow::deleteEntry()
{
    if (m_currentEntry.filePath().isEmpty()) {
        QMessageBox::information(this, tr("Delete Entry"),
                               tr("No entry selected to delete."));
        return;
    }
    
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Delete Entry"),
                                  tr("Are you sure you want to delete this entry?"),
                                  QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        if (m_fileManager->deleteEntry(m_currentEntry.filePath())) {
            m_currentEntry = JournalEntry();
            m_editor->clear();
            m_editor->setModified(false);
            loadEntryList();
            m_statusLabel->setText(tr("Entry deleted"));
        } else {
            QMessageBox::warning(this, tr("Delete Error"),
                               tr("Failed to delete entry."));
        }
    }
}

void MainWindow::onEntrySelected(QListWidgetItem *item)
{
    if (!item) {
        return;
    }
    
    // Check if current entry needs saving
    if (!maybeSave()) {
        return;
    }
    
    // Load selected entry
    QString filePath = item->data(Qt::UserRole).toString();
    JournalEntry entry = m_fileManager->loadEntry(filePath);
    
    if (!entry.isEmpty()) {
        displayEntry(entry);
        setCurrentEntry(entry);
    }
}

void MainWindow::displayEntry(const JournalEntry& entry)
{
    m_editor->setPlainText(entry.content());
    m_editor->setModified(false);
    m_statusLabel->setText(tr("Viewing: %1").arg(entry.title()));
}

void MainWindow::setCurrentEntry(const JournalEntry& entry)
{
    m_currentEntry = entry;
}

void MainWindow::loadEntryList()
{
    m_entryList->clear();
    
    QList<JournalEntry> entries = m_fileManager->loadAllEntries();
    
    for (const JournalEntry& entry : entries) {
        QString displayText = entry.title();
        if (displayText.isEmpty()) {
            displayText = tr("Untitled - %1").arg(
                entry.createdAt().toString("yyyy-MM-dd hh:mm"));
        }
        
        QListWidgetItem *item = new QListWidgetItem(displayText);
        item->setData(Qt::UserRole, entry.filePath());
        m_entryList->addItem(item);
    }
    
    m_statusLabel->setText(tr("%1 entries loaded").arg(entries.size()));
}

bool MainWindow::maybeSave()
{
    if (!m_editor->isModified()) {
        return true;
    }
    
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Unsaved Changes"),
                               tr("The current entry has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    
    if (ret == QMessageBox::Save) {
        saveEntry();
        // Check if save was successful by checking if entry still has modifications
        // or if the file path is now set (indicating successful save)
        return !m_editor->isModified() || !m_currentEntry.filePath().isEmpty();
    } else if (ret == QMessageBox::Cancel) {
        return false;
    }
    
    return true;
}

void MainWindow::showSettings()
{
    // Get new journal directory from user
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Journal Directory"),
                                                    m_fileManager->journalDirectory(),
                                                    QFileDialog::ShowDirsOnly);
    
    if (!dir.isEmpty()) {
        m_fileManager->setJournalDirectory(dir);
        loadEntryList();
        m_statusLabel->setText(tr("Journal directory changed to: %1").arg(dir));
    }
}

void MainWindow::toggleDistractionFree()
{
    bool current = m_editor->property("distractionFree").toBool();
    m_editor->setDistractionFreeMode(!current);
    m_editor->setProperty("distractionFree", !current);
    
    // Optionally hide sidebar in distraction-free mode
    if (!current) {
        m_entryList->hide();
        menuBar()->hide();
        statusBar()->hide();
    } else {
        m_entryList->show();
        menuBar()->show();
        statusBar()->show();
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About jrnl"),
                      tr("<h2>jrnl - Journaling Application</h2>"
                         "<p>Version 1.0.0</p>"
                         "<p>A cross-platform journaling application inspired by "
                         "Obsidian, OneNote, and Scrivener.</p>"
                         "<p>Features:</p>"
                         "<ul>"
                         "<li>Clean, distraction-free writing experience</li>"
                         "<li>Markdown-based storage for portability</li>"
                         "<li>Cross-platform support (macOS and Ubuntu)</li>"
                         "<li>Qt6-based modern UI</li>"
                         "</ul>"
                         "<p>All entries are stored as Markdown files for "
                         "long-term durability and transparency.</p>"));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}
