#include "vclientscreenshot.h"

VClientScreenshot::VClientScreenshot()
{
}

VClientScreenshot::VClientScreenshot(const QByteArray &data)
{
    quint64 id;
    QDateTime date_time;
    QImage snapshot;

    QDataStream data_stream((QByteArray *) &data, QIODevice::ReadOnly);

    data_stream >> id;
    data_stream >> date_time;
    data_stream >> snapshot;

    setID(id);
    setDateTime(date_time);
    setSnapshotImage(snapshot);
}

void VClientScreenshot::setSnapshotImage(const QImage &snapshot)
{
    _snapshot_image = snapshot;
}

QImage VClientScreenshot::snapshotImage() const
{
    return _snapshot_image;
}

QByteArray VClientScreenshot::toBytes() const
{
    QByteArray data_bytes;

    QDataStream data_stream(&data_bytes, QIODevice::ReadWrite);

    data_stream << id();
    data_stream << dateTime();
    data_stream << snapshotImage();

    return data_bytes;
}
