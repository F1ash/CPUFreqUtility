#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowFlags(windowFlags() ^ Qt::FramelessWindowHint);
    setSizePolicy(
                QSizePolicy(
                    QSizePolicy::MinimumExpanding,
                    QSizePolicy::MinimumExpanding));
    //setMinimumSize(100, 100);
    setContentsMargins(0, 0, 0, 5);
    setWindowTitle("CPU Frequence Utility");
    toolBar = new ToolBar(this);
    addToolBar(toolBar);
    baseLayout = new QVBoxLayout();
    baseWdg = new QWidget(this);
    baseWdg->setLayout(baseLayout);
    setCentralWidget(baseWdg);
    //hide();
    initTrayIcon();
    readCPUCount();
    connect(toolBar->firstForAll, SIGNAL(toggled(bool)),
            this, SLOT(setFirstForAll(bool)));
    connect(toolBar->reload, SIGNAL(released()),
            this, SLOT(reloadCPUItems()));
    connect(toolBar->apply, SIGNAL(released()),
            this, SLOT(applyChanges()));
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
void MainWindow::initCPU_Items(QStringList &cpus)
{
    foreach (QString cpuNum, cpus) {
        CPU_Item *wdg = new CPU_Item(this, cpuNum);
        baseLayout->addWidget(wdg);
    };
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

void MainWindow::onResult(ExecuteJob *job)
{
    if (NULL==job) return;
    if (job->error()) {
        QMessageBox::information(this, "Error", \
                    QString("KAuth returned an error code: %1 \n %2")
                    .arg(job->error()).arg(job->errorText()));
    } else if ( job->data().keys().contains("filename") ) {
        if ( job->data().value("filename")=="present" ) {
            QStringList cpus = job->data()
                    .value("contents").toString()
                    .replace("\n", "").split("-");
            initCPU_Items(cpus);
        };
    };
}

void MainWindow::readCPUCount()
{
    QVariantMap args;
    args["procnumb"] = "null";
    args["filename"] = "present";

    Action act("org.freedesktop.auth.cpufrequtility.read");
    act.setHelperId("org.freedesktop.auth.cpufrequtility");
    act.setArguments(args);
    ExecuteJob *job = act.execute();
    job->setAutoDelete(true);
    if (job->exec()) {
        onResult(job);
    } else {
        QMessageBox::information(this, "Error", \
                    QString("ExecuteJob don't started."));
    };
}

void MainWindow::setFirstForAll(bool state)
{

}

void MainWindow::reloadCPUItems()
{

}

void MainWindow::applyChanges()
{

}
