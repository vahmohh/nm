#include "vservercommand.h"

#include <QDataStream>

VServerCommand::VServerCommand()
{
}

VServerCommand::VServerCommand(const QByteArray &data)
{
    quint64 id;
    QDateTime date_time;
    QString command;

    QDataStream data_stream((QByteArray *) &data, QIODevice::ReadOnly);

    data_stream >> id;
    data_stream >> date_time;
    data_stream >> command;

    setID(id);
    setDateTime(date_time);
    _command = command;
}

QByteArray VServerCommand::toBytes() const
{
    QByteArray data_bytes;

    QDataStream data_stream(&data_bytes, QIODevice::ReadWrite);

    data_stream << id();
    data_stream << dateTime();
    data_stream << _command;

    return data_bytes;
}
