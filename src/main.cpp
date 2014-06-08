#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationName("UmlautSoftware");
    app.setApplicationName("SyncConverter");

    MainWindow window;
    window.show();

    return app.exec();
}
