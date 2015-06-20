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
                     *restore,
                     *apply,
                     *exit,
                     *resize;

private:
    QAction          *firstForAllAct,
                     *reloadAct,
                     *restoreAct,
                     *applyAct,
                     *exitAct,
                     *resizeAct;

public slots:
    bool              getFirstForAllState() const;
    bool              getRestoreState() const;
    void              setFirstForAllState(bool);
    void              setRestoreState(bool);
    void              setResizingState(bool);
};

#endif // TOOLBAR_H
