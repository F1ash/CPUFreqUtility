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
    baseLayout = NULL;
    baseWdg = NULL;
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
    if (baseLayout!=NULL) {
        for (uint i=0; i<baseLayout->count(); i++) {
            CPU_Item *wdg = static_cast<CPU_Item*>(
                        baseLayout->itemAt(i)->widget());
            if ( NULL!=wdg && i==0 ) {
                disconnect(wdg, SIGNAL(curr_gov(QString&)),
                           this, SLOT(receiveCurrGovernor(QString&)));
                disconnect(wdg, SIGNAL(max_freq(QString&)),
                           this, SLOT(receiveCurrMaxFreq(QString&)));
                disconnect(wdg, SIGNAL(min_freq(QString&)),
                           this, SLOT(receiveCurrMinFreq(QString&)));
            };
        };
        delete baseLayout;
        baseLayout = NULL;
    };
    if (baseWdg!=NULL) {
        delete baseWdg;
        baseWdg = NULL;
    };
    baseLayout = new QVBoxLayout();
    baseWdg = new QWidget(this);
    foreach (QString cpuNum, cpus) {
        CPU_Item *wdg = new CPU_Item(this, cpuNum);
        baseLayout->addWidget(wdg);
        if ( cpuNum=="0" ) {
            connect(wdg, SIGNAL(curr_gov(QString&)),
                    this, SLOT(receiveCurrGovernor(QString&)));
            connect(wdg, SIGNAL(max_freq(QString&)),
                    this, SLOT(receiveCurrMaxFreq(QString&)));
            connect(wdg, SIGNAL(min_freq(QString&)),
                    this, SLOT(receiveCurrMinFreq(QString&)));
        };
    };
    baseWdg->setLayout(baseLayout);
    setCentralWidget(baseWdg);
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
                    QString("ExecuteJob don't started.\n%1 : %2")
                    .arg(job->error()).arg(job->errorText()));
    };
}

void MainWindow::setFirstForAll(bool state)
{
    for (uint i=0; i<baseLayout->count(); i++) {
        CPU_Item *wdg = static_cast<CPU_Item*>(
                    baseLayout->itemAt(i)->widget());
        if ( NULL!=wdg )
            wdg->setFirstForAllState(state);
    };
}

void MainWindow::reloadCPUItems()
{
    toolBar->setEnabled(false);
    readCPUCount();
    toolBar->setEnabled(true);
}

void MainWindow::applyChanges()
{
    toolBar->setEnabled(false);
    baseWdg->setEnabled(false);
    for (uint i=0; i<baseLayout->count(); i++) {
        CPU_Item *wdg = static_cast<CPU_Item*>(
                    baseLayout->itemAt(i)->widget());
        if ( NULL!=wdg )
            wdg->applyNewSettings();
    };
    baseWdg->setEnabled(true);
    reloadCPUItems();
    toolBar->setEnabled(true);
}

void MainWindow::receiveCurrGovernor(QString &arg)
{
    for (uint i=0; i<baseLayout->count(); i++) {
        CPU_Item *wdg = static_cast<CPU_Item*>(
                    baseLayout->itemAt(i)->widget());
        if ( NULL!=wdg )
            wdg->setCurrGovernor(arg);
    };
}

void MainWindow::receiveCurrMaxFreq(QString &arg)
{
    for (uint i=0; i<baseLayout->count(); i++) {
        CPU_Item *wdg = static_cast<CPU_Item*>(
                    baseLayout->itemAt(i)->widget());
        if ( NULL!=wdg )
            wdg->setCurrMaxFreq(arg);
    };
}

void MainWindow::receiveCurrMinFreq(QString &arg)
{
    for (uint i=0; i<baseLayout->count(); i++) {
        CPU_Item *wdg = static_cast<CPU_Item*>(
                    baseLayout->itemAt(i)->widget());
        if ( NULL!=wdg )
            wdg->setCurrMinFreq(arg);
    };
}
