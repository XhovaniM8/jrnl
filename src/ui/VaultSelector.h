#ifndef VAULTSELECTOR_H
#define VAULTSELECTOR_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>

class VaultSelector : public QDialog
{
    Q_OBJECT

public:
    explicit VaultSelector(QWidget *parent = nullptr);

    QString selectedVaultPath() const { return m_selectedPath; }

private slots:
    void onCreateVault();
    void onOpenVault();
    void onBrowse();

private:
    QLineEdit* m_pathEdit;
    QPushButton* m_createButton;
    QPushButton* m_openButton;
    QPushButton* m_browseButton;
    
    QString m_selectedPath;
    
    void setupUi();
};

#endif // VAULTSELECTOR_H
