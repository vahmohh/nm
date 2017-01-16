#ifndef VCLIENTCAPTUREPACKETS_H
#define VCLIENTCAPTUREPACKETS_H

#include "../vobject.h"

class VClientCapturePackets : public VObject
{
public:
    VClientCapturePackets();
    VClientCapturePackets(const QByteArray &data);

    void setSendBytes(uint send);
    void setReceiveBytes(uint receive);
    void setHostName(const QString &host);

    uint sendBytes() const;
    uint receiveBytes() const;
    QString hostName() const;

    QByteArray toBytes() const;

private:
    uint _send_bytes, _receive_bytes;
    QString _host_name;
};

#endif // VCLIENTCAPTUREPACKETS_H
