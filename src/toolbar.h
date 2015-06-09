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
                     *exit;

private:
    QAction          *firstForAllAct,
                     *reloadAct,
                     *restoreAct,
                     *applyAct,
                     *exitAct;

public slots:
    bool              getFirstForAllState() const;
    bool              getRestoreState() const;
    void              setFirstForAllState(bool);
    void              setRestoreState(bool);
};

#endif // TOOLBAR_H
