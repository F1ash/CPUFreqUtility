#ifndef CPU_ITEM_H
#define CPU_ITEM_H

#include <QWidget>
#include <QIcon>
#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QDebug>
#include <kauth.h>
#include <knotification.h>
using namespace KAuth;

class CPU_Item : public QWidget
{
    Q_OBJECT
public:
    explicit CPU_Item(
            QWidget *parent = 0,
            QString  num = "0");

signals:
    void             curr_gov(QString&);
    void             max_freq(QString&);
    void             min_freq(QString&);

private:
    bool             online, firstForAll;
    const QString    cpuNumber;
    QCheckBox       *cpuN;
    QComboBox       *governors,
                    *minFreq,
                    *maxFreq;
    QHBoxLayout     *baseLayout;

private slots:
    void             setParametersEnabled(bool);
    void             setItemData_I();
    void             setItemData_II();
    void             setItemData_III();
    void             onResult(ExecuteJob*);
    void             readProcData(const QString&);
    void             writeProcData(QString&, QString&);
    void             startAction(Action&);
    void             emitCurrentParameters();
    void             emitCurrentGovernor(QString);
    void             emitCurrentMaxFreq(QString);
    void             emitCurrentMinFreq(QString);
    void             minFreqChanged(QString);
    void             maxFreqChanged(QString);

public slots:
    void             setFirstForAllState(bool);
    void             applyNewSettings();
    void             setCurrGovernor(QString&);
    void             setCurrMaxFreq(QString&);
    void             setCurrMinFreq(QString&);
    bool             getOnlineState() const;
    QString          getGovernor() const;
    QString          getMaxFreq() const;
    QString          getMinFreq() const;
    QString          getCPUNumber() const;
};

#endif // CPU_ITEM_H
