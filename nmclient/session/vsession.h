#ifndef VSESSION_H
#define VSESSION_H

#include <QThread>
#include <QTcpSocket>

class VServerGretting;
class VServerCommand;

class VSession : public QObject
{
    Q_OBJECT
public:
    VSession(QObject *parent = 0);
    ~VSession();

    void connectToServer();
    void disconnectFromServer();

    void write(quint8 type, QByteArray bytes);

private:
    QThread _thread;
    QTcpSocket _socket;

private slots:
    void connectToServerSlot();
    void disconnectFromServerSlot();

    void writeSlot(quint8 type, QByteArray bytes);

    void readyReadSlot();

signals:
    void connectToServerSignal();
    void disconnectFromServerSignal();

    void writeSignal(quint8 type, QByteArray bytes);

    void connected();
    void disconnected();

    void readyReadServerGretting(const VServerGretting &gretting);
    void readyReadServerCommand(const VServerCommand &command);
};

#endif // VSESSION_H
