#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QIcon::setThemeName("CPUFreq");
    MainWindow w;
    w.show();

    return a.exec();
}
