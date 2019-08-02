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
    minFreq->setToolTip("Minimal Frequence (MGz)");
    minFreq->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    maxFreq = new QComboBox(this);
    maxFreq->setToolTip("Maximal Frequence (MGz)");
    maxFreq->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    baseLayout = new QHBoxLayout(this);
    baseLayout->addWidget(cpuN);
    baseLayout->addWidget(governors);
    baseLayout->addWidget(minFreq);
    baseLayout->addWidget(maxFreq);
    setLayout(baseLayout);
    setItemData_I();
    if ( cpuNumber=="0" ) {
        connect(governors, SIGNAL(currentTextChanged(QString)),
                this, SLOT(emitCurrentGovernor(QString)));
        connect(maxFreq, SIGNAL(currentTextChanged(QString)),
                this, SLOT(emitCurrentMaxFreq(QString)));
        connect(minFreq, SIGNAL(currentTextChanged(QString)),
                this, SLOT(emitCurrentMinFreq(QString)));
    };
    connect(maxFreq, SIGNAL(currentTextChanged(QString)),
            this, SLOT(maxFreqChanged(QString)));
    connect(minFreq, SIGNAL(currentTextChanged(QString)),
            this, SLOT(minFreqChanged(QString)));
}

/* private slots */
void CPU_Item::setParametersEnabled(bool state)
{
    governors->setEnabled(state);
    maxFreq->setEnabled(state);
    minFreq->setEnabled(state);
}

void CPU_Item::setItemData_I()
{
    QStringList keys;
    keys.append("online");
    keys.append("scaling_available_governors");
    keys.append("scaling_available_frequencies");
    keys.append("scaling_governor");
    foreach (QString key, keys) {
        if (cpuNumber=="0" && key=="online" ) {
            // cpu0 always present and online
        } else {
            readProcData(key);
        };
    };
}

void CPU_Item::setItemData_II()
{
    QStringList keys;
    keys.append("scaling_max_freq");
    keys.append("scaling_min_freq");
    //keys.append("cur_freq");
    foreach (QString key, keys) {
        readProcData(key);
    };
}

void CPU_Item::setItemData_III()
{
    QStringList keys;
    keys.append("cpuinfo_max_freq");
    keys.append("cpuinfo_min_freq");
    //keys.append("cur_freq");
    foreach (QString key, keys) {
        readProcData(key);
    };
}

void CPU_Item::onResult(ExecuteJob *job)
{
    if (Q_NULLPTR==job) {
        KNotification::event(
                    KNotification::Notification,
                    "CPUFreqUtility",
                    QString("Processing with CPU data failed."),
                    this);
        return;
    };
    if (job->error()) {
        KNotification::event(
                    KNotification::Notification,
                    "CPUFreqUtility",
                    QString("ERROR: %1\n%2")
                    .arg(job->error()).arg(job->errorText()),
                    this);
    } else if ( job->data().keys().contains("filename") ) {
        if ( job->data().value("filename")=="online" ) {
            online = (job->data().value("contents")
                           .toString().replace("\n", "")
                           .toInt()==1);
            cpuN->setChecked(online);
            setParametersEnabled(online);
        } else if ( job->data().value("filename")=="scaling_available_governors" ) {
            QStringList avail_gov = job->data().value("contents")
                    .toString().replace("\n", "").split(" ");
            avail_gov.removeAll("");
            avail_gov.prepend("undefined");
            governors->addItems(avail_gov);
            for (int i=0; i<governors->count(); i++) {
                QString gov_Icon = governors->itemText(i);
                if (gov_Icon=="undefined") gov_Icon="dialog-error";
                else if (gov_Icon=="userspace") gov_Icon = "user-idle";
                governors->setItemIcon(
                            i,
                            QIcon::fromTheme(
                                gov_Icon,
                                QIcon(QString(":/%1.png")
                                      .arg(gov_Icon))));
            };
        } else if ( job->data().value("filename")=="scaling_available_frequencies" ) {
            if ( "failed"==job->data().value("contents") ) {
                // available_frequencies not exist
                setItemData_III();
            } else {
                QStringList avail_freq = job->data().value("contents")
                        .toString().replace("\n", "").split(" ");
                avail_freq.removeAll("");
                avail_freq.prepend("undefined");
                foreach (QString freq, avail_freq) {
                    QString text = freq.leftJustified(freq.count()-3, '.', true);
                    minFreq->addItem(text, freq);
                    maxFreq->addItem(text, freq);
                };
                setItemData_II();
            };
        } else if ( job->data().value("filename")=="scaling_governor" ) {
            QString cur_gov = job->data().value("contents")
                    .toString().replace("\n", "");
            int idx = governors->findText(cur_gov);
            if (idx<0) idx=0;
            governors->setCurrentIndex(idx);
        } else if ( job->data().value("filename")=="scaling_max_freq" ) {
            QString freq = job->data().value("contents")
                    .toString().replace("\n", "");
            QString text = freq.leftJustified(freq.count()-3, '.', true);
            setCurrMaxFreq(text);
        } else if ( job->data().value("filename")=="scaling_min_freq" ) {
            QString freq = job->data().value("contents")
                    .toString().replace("\n", "");
            QString text = freq.leftJustified(freq.count()-3, '.', true);
            setCurrMinFreq(text);
        } else if ( job->data().value("filename")=="cpuinfo_max_freq" ) {
            QString freq = job->data().value("contents")
                    .toString().replace("\n", "");
            QString text = freq.leftJustified(freq.count()-3, '.', true);
            maxFreq->addItem(text, freq);
        } else if ( job->data().value("filename")=="cpuinfo_min_freq" ) {
            QString freq = job->data().value("contents")
                    .toString().replace("\n", "");
            //QString text = freq.leftJustified(freq.count()-3, '.', true);
            //minFreq->addItem(text, freq);
            int _Freq = freq.toInt();
            int _maxFreq = maxFreq->itemData(0, Qt::UserRole).toInt();
            while ( _Freq<=_maxFreq ) {
                freq = QString::number(_Freq);
                QString text = freq.leftJustified(freq.count()-3, '.', true);
                minFreq->addItem(text, freq);
                if ( _Freq!=_maxFreq )
                    maxFreq->insertItem(maxFreq->count()-1, text, freq);
                _Freq+=100000;
            };
            setItemData_II();
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
        KNotification::event(
                    KNotification::Notification,
                    "CPUFreqUtility",
                    QString("ERROR: %1\n%2")
                    .arg(job->error()).arg(job->errorText()),
                    this);
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

void CPU_Item::maxFreqChanged(QString _freq)
{
    if ( _freq.toInt()<minFreq->currentText().toInt() )
        setCurrMinFreq(_freq);
}

void CPU_Item::minFreqChanged(QString _freq)
{
    if ( _freq.toInt()>maxFreq->currentText().toInt() )
        setCurrMaxFreq(_freq);
}

/* public slots */
void CPU_Item::setFirstForAllState(bool state)
{
    bool changed = ( firstForAll!=state );
    firstForAll = state;
    if (cpuNumber=="0" && changed) emitCurrentParameters();
    else if (changed) setParametersEnabled(!state);
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
                arg = maxFreq->currentData(Qt::UserRole)
                        .toString();
            } else if ( key=="min_freq" ) {
                arg = minFreq->currentData(Qt::UserRole)
                        .toString();
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

bool CPU_Item::getOnlineState() const
{
    return cpuN->isChecked();
}

QString CPU_Item::getGovernor() const
{
    return governors->currentText();
}

QString CPU_Item::getMaxFreq() const
{
    return maxFreq->currentText();
}

QString CPU_Item::getMinFreq() const
{
    return minFreq->currentText();
}

QString CPU_Item::getCPUNumber() const
{
    return cpuNumber;
}
