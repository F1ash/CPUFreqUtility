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
    QPushButton      *firstForAll,
                     *reload,
                     *apply;

private:
    QAction          *firstForAllAct,
                     *reloadAct,
                     *applyAct;
};

#endif // TOOLBAR_H
