#include "toolbar.h"

ToolBar::ToolBar(QWidget *parent) :
    QToolBar(parent)
{
    firstForAll =
            new QPushButton(QIcon::fromTheme("go-top"), "", this);
    firstForAll->setToolTip("First for all");
    firstForAll->setCheckable(true);
    firstForAllAct  = addWidget(firstForAll);
    addSeparator();
    reload      =
            new QPushButton(QIcon::fromTheme("view-refresh"), "", this);
    reload->setToolTip("Reload CPU Settings");
    reloadAct       = addWidget(reload);
    restore     =
            new QPushButton(QIcon::fromTheme("document-save"), "", this);
    restore->setToolTip("Restore CPU Settings at start");
    restore->setCheckable(true);
    restoreAct      = addWidget(restore);
    apply       =
            new QPushButton(QIcon::fromTheme("dialog-ok-apply"), "", this);
    apply->setToolTip("Apply new Settings");
    applyAct        = addWidget(apply);
    addSeparator();
    resize      =
            new QPushButton(QIcon::fromTheme("zoom-fit-best"), "", this);
    resize->setToolTip("Resize");
    resize->setCheckable(true);
    resizeAct       = addWidget(resize);
    addSeparator();
    exit        =
            new QPushButton(QIcon::fromTheme("application-exit"), "", this);
    exit->setToolTip("Exit");
    exitAct         = addWidget(exit);
}

bool ToolBar::getFirstForAllState() const
{
    return firstForAll->isChecked();
}

bool ToolBar::getRestoreState() const
{
    return restore->isChecked();
}

void ToolBar::setFirstForAllState(bool state)
{
    firstForAll->setChecked(state);
}

void ToolBar::setRestoreState(bool state)
{
    restore->setChecked(state);
}

void ToolBar::setResizingState(bool state)
{
    firstForAll->setEnabled(state);
    reload->setEnabled(state);
    restore->setEnabled(state);
    apply->setEnabled(state);
    exit->setEnabled(state);
}
