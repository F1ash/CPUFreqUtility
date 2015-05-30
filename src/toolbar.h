#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QAction>
#include <QPushButton>

class ToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit ToolBar(QWidget *parent = NULL);

private:
    QAction          *firstForAll,
                     *restore,
                     *apply;
};

#endif // TOOLBAR_H
