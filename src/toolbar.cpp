#include "toolbar.h"

ToolBar::ToolBar(QWidget *parent) :
    QToolBar(parent)
{
    firstForAll =
            new QPushButton(QIcon::fromTheme("go-top"), "", this);
    firstForAll->setToolTip("First for all");
    firstForAll->setCheckable(true);
    firstForAllAct  = addWidget(firstForAll);
    reload     =
            new QPushButton(QIcon::fromTheme("view-refresh"), "", this);
    reload->setToolTip("Reload");
    reloadAct      = addWidget(reload);
    apply       =
            new QPushButton(QIcon::fromTheme("dialog-ok-apply"), "", this);
    apply->setToolTip("Apply settings");
    applyAct        = addWidget(apply);
}

