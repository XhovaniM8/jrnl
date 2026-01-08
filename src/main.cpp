#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application information
    app.setApplicationName("jrnl");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("jrnl");
    app.setOrganizationDomain("jrnl.app");
    
    // Create and show main window
    MainWindow window;
    window.show();
    
    return app.exec();
}
