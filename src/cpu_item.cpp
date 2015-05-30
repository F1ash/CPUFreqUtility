#include "cpu_item.h"

CPU_Item::CPU_Item(
        QWidget *parent, uint num) :
    QWidget(parent)
{
    cpuN = new QCheckBox(this);
    cpuN->setText(QString("CPU%1").arg(num));
    if ( num==0 ) {
        cpuN->setChecked(true);
        cpuN->setDisabled(true);
    };
    governors = new QComboBox(this);
    governors->setToolTip("Governor");
    minFreq = new QComboBox(this);
    minFreq->setToolTip("Minimal Frequence");
    maxFreq = new QComboBox(this);
    maxFreq->setToolTip("Maximal Frequence");
    baseLayout = new QHBoxLayout(this);
    baseLayout->addWidget(cpuN);
    baseLayout->addWidget(governors);
    baseLayout->addWidget(minFreq);
    baseLayout->addWidget(maxFreq);
    setLayout(baseLayout);
}

