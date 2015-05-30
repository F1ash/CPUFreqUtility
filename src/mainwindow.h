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
    void                changeVisibility();
    void                trayIconActivated(QSystemTrayIcon::ActivationReason);
};

#endif // MAINWINDOW_H
