#include "toolbar.h"

ToolBar::ToolBar(QWidget *parent) :
    QToolBar(parent)
{
    firstForAll  = addWidget(
                new QPushButton(QIcon::fromTheme("all"), "", this));
    restore      = addWidget(
                new QPushButton(QIcon::fromTheme("refresh-document"), "", this));
    apply        = addWidget(
                new QPushButton(QIcon::fromTheme("apply"), "", this));
}

