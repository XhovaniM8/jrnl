#include "Vault.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>

Vault::Vault()
    : m_isOpen(false)
    , m_storage(nullptr)
{
}

Vault::Vault(const QString& path)
    : m_path(path)
    , m_isOpen(false)
    , m_storage(nullptr)
{
    open(path);
}

bool Vault::createVault(const QString& path)
{
    QDir dir;
    if (dir.exists(path)) {
        qDebug() << "Vault directory already exists:" << path;
        return true;
    }
    
    if (!dir.mkpath(path)) {
        qWarning() << "Failed to create vault directory:" << path;
        return false;
    }
    
    // Create a .jrnl marker file
    QString markerPath = path + "/.jrnl";
    QFile marker(markerPath);
    if (!marker.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to create vault marker file:" << markerPath;
        return false;
    }
    QTextStream out(&marker);
    out << "jrnl vault v1.0\n";
    marker.close();
    
    qDebug() << "Created vault at:" << path;
    return true;
}

bool Vault::open(const QString& path)
{
    QDir dir(path);
    if (!dir.exists()) {
        qWarning() << "Vault directory does not exist:" << path;
        return false;
    }

    // Check for .jrnl marker
    QString markerPath = path + "/.jrnl";
    if (!QFile::exists(markerPath)) {
        qWarning() << "Not a valid jrnl vault (missing .jrnl marker):" << path;
        return false;
    }

    m_path = path;
    m_isOpen = true;
    
    if (m_storage) {
        delete m_storage;
    }
    m_storage = new Storage(path);
    
    qDebug() << "Opened vault:" << path;
    return true;
}

void Vault::close()
{
    if (m_storage) {
        delete m_storage;
        m_storage = nullptr;
    }
    m_isOpen = false;
    m_path.clear();
}

QString Vault::name() const
{
    if (m_path.isEmpty()) {
        return QString();
    }
    return QDir(m_path).dirName();
}
