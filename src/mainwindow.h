#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "tray/traywidget.h"
#include "cpu_item.h"
#include "toolbar.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = NULL);

signals:

private:
    ToolBar            *toolBar;
    TrayIcon           *trayIcon;
    QVBoxLayout        *baseLayout;
    QWidget            *baseWdg;

private slots:
    void                initTrayIcon();
    void                initCPU_Items(QStringList&);
    void                changeVisibility();
    void                trayIconActivated(QSystemTrayIcon::ActivationReason);

    void                onResult(ExecuteJob*);
    void                readCPUCount();

    void                setFirstForAll(bool);
    void                reloadCPUItems();
    void                applyChanges();

    void                receiveCurrGovernor(QString&);
    void                receiveCurrMaxFreq(QString&);
    void                receiveCurrMinFreq(QString&);
};

#endif // MAINWINDOW_H
