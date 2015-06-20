#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QSettings>
#include <QCloseEvent>
#include <QFocusEvent>
#include <QTimerEvent>
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
    Qt::WindowFlags     flags;
    uint                CPU_COUNT;
    int                 timerID;
    QSettings           settings;
    ToolBar            *toolBar;
    TrayIcon           *trayIcon;
    QVBoxLayout        *baseLayout;
    QWidget            *baseWdg;
    QScrollArea        *scrolled;

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
    void                resizeApp(bool);

    void                receiveCurrGovernor(QString&);
    void                receiveCurrMaxFreq(QString&);
    void                receiveCurrMinFreq(QString&);

    void                closeEvent(QCloseEvent*);
    void                readSettings();
    void                saveSettings();
    void                focusInEvent(QFocusEvent*);
    void                focusOutEvent(QFocusEvent*);
    void                timerEvent(QTimerEvent*);
};

#endif // MAINWINDOW_H
