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
            QString  num = "0");

signals:

private:
    const QString    cpuNumber;
    QCheckBox       *cpuN;
    QComboBox       *governors,
                    *minFreq,
                    *maxFreq;
    QHBoxLayout     *baseLayout;

private slots:
    void             setItemData();
    void             onResult(ExecuteJob*);
    void             readProcData(const QString&);
    void             writeProcData(QString&, QString&);
    void             startAction(Action&);
};

#endif // CPU_ITEM_H
