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

void CPU_Item::onResult(KJob *_job)
{
    ExecuteJob *job = static_cast<ExecuteJob*>(_job);
    if (job->error()) {
        QMessageBox::information(this, "Error", \
                    QString("KAuth returned an error code: %1 \n %2")
                    .arg(job->error()).arg(job->errorText()));
        //reply.setData(QVariant({QString('contents') : 0}).toMap());
        //print [reply.data()]
    } else {
        qDebug()<<job->data();
    };
}
void CPU_Item::readProcData(uint number, QString &fileName)
{
    QVariantMap args;
    args["procnumb"] = QString(number);
    args["filename"] = QString(fileName);

    Action act("org.freedesktop.auth.cpufrequtility.read");
    act.setHelperId("org.freedesktop.auth.cpufrequtility");
    act.setArguments(args);
    ExecuteJob *job = act.execute();
    job->setAutoDelete(true);
    connect(job, SIGNAL(result(KJob*)),
            this, SLOT(onResult(KJob*)));
    job->start();
}

void CPU_Item::writeCpuData(uint number, QString &fileName, QString &parametr)
{
    QVariantMap args;
    args["procnumb"] = number;
    args["filename"] = fileName;
    args["parametr"] = parametr;

    Action act("org.freedesktop.auth.cpufrequtility.write");
    act.setHelperId("org.freedesktop.auth.cpufrequtility");
    act.setArguments(args);
    ExecuteJob *job = act.execute();
    job->setAutoDelete(true);
    connect(job, SIGNAL(result(KJob*)),
            this, SLOT(onResult(KJob*)));
    job->start();
}
