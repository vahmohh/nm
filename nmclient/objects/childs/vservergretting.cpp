#include "vservergretting.h"

#include <QDataStream>

VServerGretting::VServerGretting()
{
}

VServerGretting::VServerGretting(const QByteArray &data)
{
    quint64 id;
    QDateTime date_time;
    int interval;

    QDataStream data_stream((QByteArray *) &data, QIODevice::ReadOnly);

    data_stream >> id;
    data_stream >> date_time;
    data_stream >> interval;

    setID(id);
    setDateTime(date_time);
    setInterval(interval);
}

void VServerGretting::setInterval(int msec)
{
    if (msec > 0) {
        _interval = msec;
    }
}

int VServerGretting::interval() const
{
    return _interval;
}

QByteArray VServerGretting::toBytes() const
{
    QByteArray data_bytes;

    QDataStream data_stream(&data_bytes, QIODevice::ReadWrite);

    data_stream << id();
    data_stream << dateTime();
    data_stream << interval();

    return data_bytes;
}
