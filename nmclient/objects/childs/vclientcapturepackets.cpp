#include "vclientcapturepackets.h"

#include <QDataStream>

VClientCapturePackets::VClientCapturePackets()
{
}

VClientCapturePackets::VClientCapturePackets(const QByteArray &data)
{
    quint64 id;
    QDateTime date_time;
    uint send_bytes, receive_bytes;
    QString host_name;

    QDataStream data_stream((QByteArray *) &data, QIODevice::ReadOnly);

    data_stream >> id;
    data_stream >> date_time;
    data_stream >> send_bytes;
    data_stream >> receive_bytes;
    data_stream >> host_name;

    setID(id);
    setDateTime(date_time);
    setSendBytes(send_bytes);
    setReceiveBytes(receive_bytes);
    setHostName(host_name);
}

void VClientCapturePackets::setSendBytes(uint send)
{
    _send_bytes = send;
}

void VClientCapturePackets::setReceiveBytes(uint receive)
{
    _receive_bytes = receive;
}

void VClientCapturePackets::setHostName(const QString &host)
{
    _host_name = host;
}

uint VClientCapturePackets::sendBytes() const
{
    return _send_bytes;
}

uint VClientCapturePackets::receiveBytes() const
{
    return _receive_bytes;
}

QString VClientCapturePackets::hostName() const
{
    return _host_name;
}

QByteArray VClientCapturePackets::toBytes() const
{
    QByteArray data_bytes;

    QDataStream data_stream(&data_bytes, QIODevice::WriteOnly);

    data_stream << id();
    data_stream << dateTime();
    data_stream << sendBytes();
    data_stream << receiveBytes();
    data_stream << hostName();

    return data_bytes;
}
