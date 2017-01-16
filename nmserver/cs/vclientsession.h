#ifndef VCLIENTSESSION_H
#define VCLIENTSESSION_H

#include <QThread>

class QTcpSocket;

class VClientGretting;
class VClientCapturePackets;
class VClientScreenshot;

class VClientSession : public QObject
{
    Q_OBJECT
public:
    VClientSession(quint64 id, QTcpSocket *socket, QObject *parent = 0);
    ~VClientSession();

    quint64 id() const;
    QTcpSocket *socket() const;

    void write(quint8 type, QByteArray data);

private:
    QThread _thread;

    quint64 _id;
    QTcpSocket *_socket;

    void setID(quint64 id);
    void setSocket(QTcpSocket *socket);

private slots:
    void writeSlot(quint8 type, QByteArray data);

    void disconnectedSlot();
    void readyReadSlot();

signals:
    void writeSignal(quint8 type, QByteArray data);

    void disconnected(quint64 id);
    void writed(quint64 id);

    void readyReadClientGretting(quint64 id, const VClientGretting &gretting);
    void readyReadClientCapturePackets(quint64 id, const VClientCapturePackets &packets);
    void readyReadClientScreenshot(quint64 id, const VClientScreenshot &screenshot);
};

#endif // VCLIENTSESSION_H
