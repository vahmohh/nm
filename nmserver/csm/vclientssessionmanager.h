#ifndef VCLIENTSSESSIONMANAGER_H
#define VCLIENTSSESSIONMANAGER_H

#include <QThread>
#include <QTcpServer>
#include <QTimer>
#include <QHash>

class VClientSession;

class VError;

class VClientGretting;
class VClientCapturePackets;
class VClientScreenshot;

class VClientsSessionManager : public QObject
{
    Q_OBJECT
public:
    VClientsSessionManager(QObject *parent = 0);
    ~VClientsSessionManager();

    void setPort(quint16 port);

    quint16 port() const;

    void start();
    void stop();

    void writeToClient(quint64 id, quint8 type, QByteArray data);
    void clientUpTime(quint64 id);

private:
    QThread _thread;
    QTcpServer _server;
    QTimer _clients_up_time_timer;
    QHash<quint64,VClientSession*> _clients_session_hash;
    QHash<quint64,qint64> _clients_up_time_hash;

    quint16 _port;

private slots:
    void startSlot();
    void stopSlot();

    void writeToClientSlot(quint64 id, quint8 type, QByteArray data);
    void clientUpTimeSlot(quint64 id);

    void clientsUpTimeSlot();

    void connectedClientSlot();
    void disconnectedClientSlot(quint64 id);

signals:
    void startSignal();
    void stopSignal();

    void writeToClientSignal(quint64 id, quint8 type, QByteArray data);
    void clientUpTimeSignal(quint64 id);

    void started(const VError &error);
    void stoped();

    void connectedClient(quint64 id);
    void disconnectedClient(quint64 id);
    void writedClient(quint64 id);
    void readyClientUpTime(qint64 id);

    void readyReadClientGretting(quint64 id, const VClientGretting &gretting);
    void readyReadClientCapturePackets(quint64 id, const VClientCapturePackets &packets);
    void readyReadClientScreenshot(quint64 id, const VClientScreenshot &screenshot);
};

#endif // VCLIENTSSESSIONMANAGER_H
