#ifndef VAULT_H
#define VAULT_H

#include <QString>
#include <QDir>
#include "Storage.h"

class Vault
{
public:
    Vault();
    explicit Vault(const QString& path);

    static bool createVault(const QString& path);
    bool open(const QString& path);
    void close();

    bool isOpen() const { return m_isOpen; }
    QString path() const { return m_path; }
    QString name() const;
    
    Storage* storage() { return m_storage; }

private:
    QString m_path;
    bool m_isOpen;
    Storage* m_storage;
};

#endif // VAULT_H
