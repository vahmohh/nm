#include "vclientgretting.h"

#include <QDataStream>

VClientGretting::VClientGretting()
{
}

VClientGretting::VClientGretting(const QByteArray &data)
{
    quint64 id;
    QDateTime date_time;
    QString host_name;

    QDataStream data_stream((QByteArray *) &data, QIODevice::ReadOnly);

    data_stream >> id;
    data_stream >> date_time;
    data_stream >> host_name;

    setID(id);
    setDateTime(date_time);
    setHostName(host_name);
}

void VClientGretting::setHostName(const QString &host)
{
    _host_name = host;
}

QString VClientGretting::hostName() const
{
    return _host_name;
}

QByteArray VClientGretting::toBytes() const
{
    QByteArray data_bytes;

    QDataStream data_stream(&data_bytes, QIODevice::ReadWrite);

    data_stream << id();
    data_stream << dateTime();
    data_stream << hostName();

    return data_bytes;
}
