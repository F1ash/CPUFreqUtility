#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <QSystemTrayIcon>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = NULL);

signals:

private:
    QSystemTrayIcon    *trayIcon;

private slots:
    void                initTrayIcon();
};

#endif // MAINWINDOW_H
