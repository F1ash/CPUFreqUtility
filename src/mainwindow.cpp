#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowFlags(windowFlags() ^ Qt::FramelessWindowHint);
    setSizePolicy(
                QSizePolicy(
                    QSizePolicy::MinimumExpanding,
                    QSizePolicy::MinimumExpanding));
    setMinimumSize(100, 100);
    setContentsMargins(0, 0, 0, 5);
    setWindowTitle("CPU Frequence Utility");
    addToolBar(new ToolBar(this));
    baseLayout = new QVBoxLayout();
    baseWdg = new QWidget(this);
    baseWdg->setLayout(baseLayout);
    setCentralWidget(baseWdg);
    baseLayout->addWidget(new CPU_Item(this));
    //hide();
    initTrayIcon();
}
void MainWindow::initTrayIcon()
{
    trayIcon = new TrayIcon(this);
    trayIcon->setIcon(QIcon::fromTheme("performance"));
    trayIcon->setToolTip("CPU Frequence Utility");
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    trayIcon->show();
}
void MainWindow::changeVisibility()
{
    if (this->isVisible()) {
        this->hide();
        trayIcon->hideAction->setText (QString("Up"));
        trayIcon->hideAction->setIcon (QIcon::fromTheme("go-up"));
    } else {
        this->show();
        //this->move(mapToGlobal(QCursor::pos()));
        trayIcon->hideAction->setText (QString("Down"));
        trayIcon->hideAction->setIcon (QIcon::fromTheme("go-down"));
    };
}
void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason r)
{
  if (r==QSystemTrayIcon::Trigger) changeVisibility();
}
