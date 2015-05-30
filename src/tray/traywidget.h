#ifndef TRAYWIDGET_H
#define TRAYWIDGET_H

#include <QSystemTrayIcon>
#include <QMenu>

class TrayIcon : public QSystemTrayIcon
{
  Q_OBJECT
public :
  explicit TrayIcon(QWidget *parent = NULL);

  QAction   *hideAction;
  QAction   *closeAction;

private :
  QMenu     *trayIconMenu;

public slots:
};

#endif
