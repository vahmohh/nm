#include "vpacket.h"

#include <QDataStream>

VPacket::VPacket()
{
}

VPacket::VPacket(const QByteArray &data)
{
    quint64 id;
    QDateTime date_time;
    quint8 type;
    QByteArray data_bytes;

    QDataStream data_stream((QByteArray *) &data, QIODevice::ReadOnly);

    data_stream >> id;
    data_stream >> date_time;
    data_stream >> type;
    data_stream >> data_bytes;

    setID(id);
    setDateTime(date_time);
    setType(type);
    setDataBytes(data_bytes);
}

void VPacket::setType(quint8 type)
{
    _type = type;
}

void VPacket::setDataBytes(const QByteArray &data)
{
    _data_bytes = data;
}

quint8 VPacket::type() const
{
    return _type;
}

QByteArray VPacket::dataBytes() const
{
    return _data_bytes;
}

QByteArray VPacket::toBytes() const
{
    QByteArray data_bytes;

    QDataStream data_stream(&data_bytes, QIODevice::WriteOnly);

    data_stream << id();
    data_stream << dateTime();
    data_stream << type();
    data_stream << dataBytes();

    return data_bytes;
}
