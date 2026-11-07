#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setOrganizationName("Rig");
    QApplication::setApplicationName("DeekTranslator");

    MainWindow w;
    w.show();
    return app.exec();
}