#ifndef VCLIENTGRETTING_H
#define VCLIENTGRETTING_H

#include "../vobject.h"

class VClientGretting : public VObject
{
public:
    VClientGretting();
    VClientGretting(const QByteArray &data);

    void setHostName(const QString &host);
    QString hostName() const;

    QByteArray toBytes() const;

private:
    QString _host_name;
};

#endif // VCLIENTGRETTING_H
