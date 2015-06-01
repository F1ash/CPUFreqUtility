#include "toolbar.h"

ToolBar::ToolBar(QWidget *parent) :
    QToolBar(parent)
{
    firstForAll =
            new QPushButton(QIcon::fromTheme("go-top"), "", this);
    firstForAll->setToolTip("First for all");
    firstForAll->setCheckable(true);
    firstForAllAct  = addWidget(firstForAll);
    restore     =
            new QPushButton(QIcon::fromTheme("view-refresh"), "", this);
    restore->setToolTip("Restore");
    restoreAct      = addWidget(restore);
    apply       =
            new QPushButton(QIcon::fromTheme("dialog-ok-apply"), "", this);
    apply->setToolTip("Apply settings");
    applyAct        = addWidget(apply);
}

