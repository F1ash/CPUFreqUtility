#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    setMinimumSize(100, 100);
    setContentsMargins(0, 0, 0, 5);
    setWindowTitle("CPU Frequence Utility");
    setCentralWidget(new QWidget());
    initTrayIcon();
}
void MainWindow::initTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon::fromTheme("performance"));
    trayIcon->setToolTip("CPU Frequence Utility");
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    trayIcon->show();
}
