#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString name("CPUFreqUtility");
    a.setOrganizationName(name);
    a.setApplicationName(name);
    QIcon::setThemeName("CPUFreq");
    MainWindow w;
    w.show();

    return a.exec();
}
