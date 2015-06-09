#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QSettings>
#include <QCloseEvent>
#include <QTimer>
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
    uint                CPU_COUNT;
    QSettings           settings;
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

    void                closeEvent(QCloseEvent*);
    void                readSettings();
    void                saveSettings();
};

#endif // MAINWINDOW_H
