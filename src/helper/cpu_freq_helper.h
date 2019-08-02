#include <kauth.h>
using namespace KAuth;

class CPUFreqHelper : public QObject
{
    Q_OBJECT
public:
    explicit CPUFreqHelper(QObject *parent = Q_NULLPTR);

public slots:
    ActionReply read(QVariantMap args);
    ActionReply write(QVariantMap args);

private:
    QString get_key_varmap(const QVariantMap &args, const QString& key);
};
