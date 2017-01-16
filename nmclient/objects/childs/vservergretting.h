#ifndef VSERVERGRETTING_H
#define VSERVERGRETTING_H

#include "../vobject.h"

class VServerGretting : public VObject
{
public:
    VServerGretting();
    VServerGretting(const QByteArray &data);

    void setInterval(int msec);

    int interval() const;

    QByteArray toBytes() const;

private:
    int _interval;
};

#endif // VSERVERGRETTING_H
