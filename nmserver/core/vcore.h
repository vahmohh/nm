#ifndef VCORE_H
#define VCORE_H

#include <QThread>

#include "objects/childs/verror.h"

#include <QHash>

class QImage;

class VDatabase;
class VClientsSessionManager;

class VClientGretting;
class VClientCapturePackets;
class VClientScreenshot;

class VCore : public QObject
{
    Q_OBJECT
public:
    VCore(QObject *parent = 0);
    ~VCore();

    void start();
    void stop();

    void command(quint64 id, const QString &command);

    void setDatabaseEngine(quint8 engine);
    void setDatabaseHostName(const QString &host);
    void setDatabaseUserName(const QString &name);
    void setDatabasePassword(const QString &password);
    void setDatabasePort(int port);
    void setClientsSessionManagerPort(quint16 port);

    quint8 databaseEngine() const;
    QString databaseHostName() const;
    QString databaseUserName() const;
    QString databasePassword() const;
    int databasePort() const;
    quint16 clientsSessionManagerPort() const;

    VDatabase *_database;

    QHash<uint,QString> _host_hash;

private:
    QThread _thread;

    VClientsSessionManager *_clients_session_manager;

    VError errors[2];

private slots:
    void startSlot();
    void stopSlot();

    void openedDatabaseSlot(const VError &error);
    void closedDatabaseSlot();

    void startedClientsSessionManagerSlot(const VError &error);
    void stopedClientsSessionManagerSlot();

    void readyReadClientGrettingSlot(quint64 id, const VClientGretting &gretting);
    void readyReadClientCapturePacketsSlot(quint64 id, const VClientCapturePackets &packets);
    void readyReadClientScreenshotSlot(quint64 id, const VClientScreenshot &screenshot);

signals:
    void startSignal();
    void stopSignal();

    void started(const VError &database, const VError &session);
    void stoped();

    void connectedClient(quint64 id);
    void disconnectedClient(quint64 id);

    void readyReadClientCapturePackets(quint64 id, uint send, uint receive);
    void readyReadClientScreenshot(quint64 id, const QImage &screenshot);
};

#endif // VCORE_H
