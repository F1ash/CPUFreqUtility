#ifndef CPU_ITEM_H
#define CPU_ITEM_H

#include <QWidget>
#include <QIcon>
#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>

class CPU_Item : public QWidget
{
    Q_OBJECT
public:
    explicit CPU_Item(
            QWidget *parent = 0,
            uint        num = 0);

signals:

private:
    QCheckBox       *cpuN;
    QComboBox       *governors,
                    *minFreq,
                    *maxFreq;
    QHBoxLayout     *baseLayout;

public slots:
};

#endif // CPU_ITEM_H
