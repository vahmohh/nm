#ifndef VPACKET_H
#define VPACKET_H

#include "../vobject.h"

class VPacket : public VObject
{
public:
    enum Type {
        ServerGretting,
        ServerCommand,
        ClientGretting,
        ClientCapturePackets,
        ClientScreenshot
    };

    VPacket();
    VPacket(const QByteArray &data);

    void setType(quint8 type);
    void setDataBytes(const QByteArray &data);

    quint8 type() const;
    QByteArray dataBytes() const;

    QByteArray toBytes() const;

private:
    quint8 _type;
    QByteArray _data_bytes;
};

#endif // VPACKET_H
