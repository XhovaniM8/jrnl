#include <QApplication>
#include "ui/MainWindow.h"
#include "ui/VaultSelector.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    app.setApplicationName("jrnl");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("jrnl");
    
    // Show vault selector
    VaultSelector selector;
    if (selector.exec() == QDialog::Accepted) {
        QString vaultPath = selector.selectedVaultPath();
        
        if (!vaultPath.isEmpty()) {
            MainWindow window;
            if (window.openVault(vaultPath)) {
                window.show();
                return app.exec();
            } else {
                QMessageBox::critical(nullptr, "Error", "Failed to open vault.");
                return 1;
            }
        }
    }
    
    return 0;
}
