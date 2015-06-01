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
    QPushButton      *firstForAll,
                     *restore,
                     *apply;
    QAction          *firstForAllAct,
                     *restoreAct,
                     *applyAct;
};

#endif // TOOLBAR_H
