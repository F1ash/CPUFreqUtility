#include "cpu_item.h"

CPU_Item::CPU_Item(QWidget *parent, QString num) :
    QWidget(parent), cpuNumber(num)
{
    firstForAll = false;
    online = false;
    cpuN = new QCheckBox(this);
    cpuN->setText(QString("CPU%1").arg(cpuNumber));
    if ( cpuNumber=="0" ) {
        cpuN->setChecked(true);
        cpuN->setDisabled(true);
    };
    governors = new QComboBox(this);
    governors->setToolTip("Governor");
    governors->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    minFreq = new QComboBox(this);
    minFreq->setToolTip("Minimal Frequence");
    minFreq->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    maxFreq = new QComboBox(this);
    maxFreq->setToolTip("Maximal Frequence");
    maxFreq->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    baseLayout = new QHBoxLayout(this);
    baseLayout->addWidget(cpuN);
    baseLayout->addWidget(governors);
    baseLayout->addWidget(minFreq);
    baseLayout->addWidget(maxFreq);
    setLayout(baseLayout);
    setItemData();
    if ( cpuNumber=="0" ) {
        connect(governors, SIGNAL(currentTextChanged(QString)),
                this, SLOT(emitCurrentGovernor(QString)));
        connect(maxFreq, SIGNAL(currentTextChanged(QString)),
                this, SLOT(emitCurrentMaxFreq(QString)));
        connect(minFreq, SIGNAL(currentTextChanged(QString)),
                this, SLOT(emitCurrentMinFreq(QString)));
    };
}

/* private slots */
void CPU_Item::setParametersEnabled(bool state)
{
    governors->setEnabled(state);
    maxFreq->setEnabled(state);
    minFreq->setEnabled(state);
}

void CPU_Item::setItemData()
{
    QStringList keys;
    keys.append("online");
    keys.append("available_governors");
    keys.append("available_frequencies");
    keys.append("governor");
    keys.append("max_freq");
    keys.append("min_freq");
    keys.append("cur_freq");
    foreach (QString key, keys) {
        if (cpuNumber=="0" && key=="online" ) {
            // cpu0 always present and online
        } else {
            readProcData(key);
        };
    };
}

void CPU_Item::onResult(ExecuteJob *job)
{
    if (NULL==job) return;
    if (job->error()) {
        QMessageBox::information(this, "Error", \
                    QString("KAuth returned an error code: %1 \n %2")
                    .arg(job->error()).arg(job->errorText()));
    } else if ( job->data().keys().contains("filename") ) {
        if ( job->data().value("filename")=="online" ) {
            online = (job->data().value("contents")
                           .toString().replace("\n", "")
                           .toInt()==1);
            cpuN->setChecked(online);
            setParametersEnabled(online);
        } else if ( job->data().value("filename")=="available_governors" ) {
            QStringList avail_gov = job->data().value("contents")
                    .toString().replace("\n", "").split(" ");
            avail_gov.removeAll("");
            governors->addItems(avail_gov);
            for (uint i=0; i<governors->count(); i++) {
                governors->setItemIcon(
                            i, QIcon::fromTheme(governors->currentText()));
            };
        } else if ( job->data().value("filename")=="available_frequencies" ) {
            QStringList avail_freq = job->data().value("contents")
                    .toString().replace("\n", "").split(" ");
            avail_freq.removeAll("");
            minFreq->addItems(avail_freq);
            maxFreq->addItems(avail_freq);
        } else if ( job->data().value("filename")=="governor" ) {
            QString cur_gov = job->data().value("contents")
                    .toString().replace("\n", "");
            int idx = governors->findText(cur_gov);
            if (idx<0) idx=0;
            governors->setCurrentIndex(idx);
        } else if ( job->data().value("filename")=="max_freq" ) {
            QString _freq = job->data().value("contents")
                    .toString().replace("\n", "");
            int idx = maxFreq->findText(_freq);
            if (idx<0) idx=0;
            maxFreq->setCurrentIndex(idx);
        } else if ( job->data().value("filename")=="min_freq" ) {
            QString _freq = job->data().value("contents")
                    .toString().replace("\n", "");
            int idx = minFreq->findText(_freq);
            if (idx<0) idx=0;
            minFreq->setCurrentIndex(idx);
        };
    };
}

void CPU_Item::readProcData(const QString &fileName)
{
    QVariantMap args;
    args["procnumb"] = cpuNumber;
    args["filename"] = fileName;

    Action act("org.freedesktop.auth.cpufrequtility.read");
    act.setArguments(args);
    startAction(act);
}

void CPU_Item::writeProcData(QString &fileName, QString &arg)
{
    QVariantMap args;
    args["procnumb"] = cpuNumber;
    args["filename"] = fileName;
    args["parametr"] = arg;

    Action act("org.freedesktop.auth.cpufrequtility.write");
    act.setArguments(args);
    startAction(act);
}

void CPU_Item::startAction(Action &act)
{
    act.setHelperId("org.freedesktop.auth.cpufrequtility");
    ExecuteJob *job = act.execute();
    job->setAutoDelete(true);
    if (job->exec()) {
        onResult(job);
    } else {
        QMessageBox::information(this, "Error", \
                    QString("ExecuteJob don't started.\n%1 : %2")
                    .arg(job->error()).arg(job->errorText()));
    };
}

void CPU_Item::emitCurrentParameters()
{
    emitCurrentGovernor(governors->currentText());
    emitCurrentMaxFreq(maxFreq->currentText());
    emitCurrentMinFreq(minFreq->currentText());
}

void CPU_Item::emitCurrentGovernor(QString s)
{
    if (firstForAll) emit curr_gov(s);
}

void CPU_Item::emitCurrentMaxFreq(QString s)
{
    if (firstForAll) emit max_freq(s);
}

void CPU_Item::emitCurrentMinFreq(QString s)
{
    if (firstForAll) emit min_freq(s);
}

/* public slots */
void CPU_Item::setFirstForAllState(bool state)
{
    bool changed = ( firstForAll!=state );
    firstForAll = state;
    if (cpuNumber=="0" && changed) emitCurrentParameters();
}

void CPU_Item::applyNewSettings()
{
    QStringList keys;
    keys.append("governor");
    keys.append("max_freq");
    keys.append("min_freq");
    if ( online != cpuN->isChecked() ) {
        if (!online) keys.prepend("online");
        else keys.append("online");
    } else if (!online) return;
    foreach (QString key, keys) {
        if (cpuNumber=="0" && key=="online" ) {
            // cpu0 always present and online
        } else {
            QString arg;
            if ( key=="online" ) {
                arg = QString::number(cpuN->isChecked()? 1:0);
            } else if ( key=="governor" ) {
                arg = governors->currentText();
            } else if ( key=="max_freq" ) {
                arg = maxFreq->currentText();
            } else if ( key=="min_freq" ) {
                arg = minFreq->currentText();
            } else continue;
            writeProcData(key, arg);
        };
    };
}

void CPU_Item::setCurrGovernor(QString &arg)
{
    int idx = governors->findText(arg);
    if (!(idx<0)) governors->setCurrentIndex(idx);
}

void CPU_Item::setCurrMaxFreq(QString &arg)
{
    int idx = maxFreq->findText(arg);
    if (!(idx<0)) maxFreq->setCurrentIndex(idx);
}

void CPU_Item::setCurrMinFreq(QString &arg)
{
    int idx = minFreq->findText(arg);
    if (!(idx<0)) minFreq->setCurrentIndex(idx);
}
