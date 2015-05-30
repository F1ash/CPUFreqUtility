#include "traywidget.h"

TrayIcon::TrayIcon(QWidget *parent)
  : QSystemTrayIcon(parent)
{
  setIcon(QIcon::fromTheme("performance"));
  hideAction = new QAction(QString("Down"), this);
  hideAction->setIcon (QIcon::fromTheme("down"));
  closeAction = new QAction(QString("Exit"), this);
  closeAction->setIcon (QIcon::fromTheme("exit"));

  trayIconMenu = new QMenu(parent);
  trayIconMenu->addAction(hideAction);
  trayIconMenu->addSeparator();
  trayIconMenu->addAction(closeAction);

  setToolTip(QString("CPU Frequence Utility"));
  setContextMenu(trayIconMenu);
  setVisible(true);
}
