#ifndef CPU_ITEM_H
#define CPU_ITEM_H

#include <QWidget>
#include <QIcon>
#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <kauth.h>
using namespace KAuth;

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

private slots:
    void             onResult(KJob*);
    void             readProcData(uint, QString&);
};

#endif // CPU_ITEM_H
