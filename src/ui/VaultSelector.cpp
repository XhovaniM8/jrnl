#include "VaultSelector.h"
#include "core/Vault.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>

VaultSelector::VaultSelector(QWidget *parent)
    : QDialog(parent)
{
    setupUi();
    setWindowTitle("Select or Create Vault");
    resize(500, 200);
}

void VaultSelector::setupUi()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);

    // Title
    QLabel* titleLabel = new QLabel("Welcome to jrnl", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    // Description
    QLabel* descLabel = new QLabel(
        "Create a new vault or open an existing one to get started.", this);
    descLabel->setWordWrap(true);
    descLabel->setAlignment(Qt::AlignCenter);

    // Path input
    QHBoxLayout* pathLayout = new QHBoxLayout();
    QLabel* pathLabel = new QLabel("Vault path:", this);
    m_pathEdit = new QLineEdit(this);
    
    // Default path
    QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    defaultPath += "/jrnl-vault";
    m_pathEdit->setText(defaultPath);
    
    m_browseButton = new QPushButton("Browse...", this);
    connect(m_browseButton, &QPushButton::clicked, this, &VaultSelector::onBrowse);
    
    pathLayout->addWidget(pathLabel);
    pathLayout->addWidget(m_pathEdit);
    pathLayout->addWidget(m_browseButton);

    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    m_createButton = new QPushButton("Create New Vault", this);
    m_createButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #4CAF50;"
        "   color: white;"
        "   border: none;"
        "   padding: 10px 20px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #45a049;"
        "}"
    );
    connect(m_createButton, &QPushButton::clicked, this, &VaultSelector::onCreateVault);
    
    m_openButton = new QPushButton("Open Existing Vault", this);
    m_openButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #2196F3;"
        "   color: white;"
        "   border: none;"
        "   padding: 10px 20px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #0b7dda;"
        "}"
    );
    connect(m_openButton, &QPushButton::clicked, this, &VaultSelector::onOpenVault);
    
    buttonLayout->addWidget(m_createButton);
    buttonLayout->addWidget(m_openButton);

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(descLabel);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(pathLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
}

void VaultSelector::onCreateVault()
{
    QString path = m_pathEdit->text().trimmed();
    if (path.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a vault path.");
        return;
    }

    if (Vault::createVault(path)) {
        m_selectedPath = path;
        accept();
    } else {
        QMessageBox::critical(this, "Error", "Failed to create vault.");
    }
}

void VaultSelector::onOpenVault()
{
    QString path = m_pathEdit->text().trimmed();
    if (path.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a vault path.");
        return;
    }

    Vault testVault;
    if (testVault.open(path)) {
        m_selectedPath = path;
        accept();
    } else {
        QMessageBox::critical(this, "Error", 
            "Failed to open vault. Make sure the directory exists and contains a .jrnl marker file.");
    }
}

void VaultSelector::onBrowse()
{
    QString dir = QFileDialog::getExistingDirectory(
        this, "Select Vault Directory",
        m_pathEdit->text(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    
    if (!dir.isEmpty()) {
        m_pathEdit->setText(dir);
    }
}
