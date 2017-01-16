#include "vcore.h"

#include "database/vdatabase.h"
#include "csm/vclientssessionmanager.h"

#include "objects/childs/vpacket.h"
#include "objects/childs/vservergretting.h"
#include "objects/childs/vservercommand.h"
#include "objects/childs/vclientgretting.h"
#include "objects/childs/vclientcapturepackets.h"
#include "objects/childs/vclientscreenshot.h"

VCore::VCore(QObject *parent) : QObject(parent)
{
    _database = new VDatabase();
    _clients_session_manager = new VClientsSessionManager();

    connect(this, SIGNAL(startSignal()), this, SLOT(startSlot()));
    connect(this, SIGNAL(stopSignal()), this, SLOT(stopSlot()));
    connect(_database, SIGNAL(opened(VError)), this, SLOT(openedDatabaseSlot(VError)));
    connect(_database, SIGNAL(closed()), this, SLOT(closedDatabaseSlot()));
    connect(_clients_session_manager, SIGNAL(started(VError)), this, SLOT(startedClientsSessionManagerSlot(VError)));
    connect(_clients_session_manager, SIGNAL(stoped()), this, SLOT(stopedClientsSessionManagerSlot()));
    connect(_clients_session_manager, SIGNAL(connectedClient(quint64)), this, SIGNAL(connectedClient(quint64)));
    connect(_clients_session_manager, SIGNAL(disconnectedClient(quint64)), this, SIGNAL(disconnectedClient(quint64)));
    connect(_clients_session_manager, SIGNAL(readyReadClientGretting(quint64,VClientGretting)), this, SLOT(readyReadClientGrettingSlot(quint64,VClientGretting)));
    connect(_clients_session_manager, SIGNAL(readyReadClientCapturePackets(quint64,VClientCapturePackets)), this, SLOT(readyReadClientCapturePacketsSlot(quint64,VClientCapturePackets)));
    connect(_clients_session_manager, SIGNAL(readyReadClientScreenshot(quint64,VClientScreenshot)), this, SLOT(readyReadClientScreenshotSlot(quint64,VClientScreenshot)));

    moveToThread(&_thread);
    _thread.start();
}

VCore::~VCore()
{
    delete _database;
    delete _clients_session_manager;

    _thread.quit();
}

void VCore::start()
{
    emit startSignal();
}

void VCore::stop()
{
    emit stopSignal();
}

void VCore::command(quint64 id, const QString &command)
{
    VServerCommand server_command;

    server_command._command = command;

    _clients_session_manager->writeToClient(id, VPacket::ServerCommand, server_command.toBytes());
}

void VCore::setDatabaseEngine(quint8 engine)
{
    _database->setEngine(engine);
}

void VCore::setDatabaseHostName(const QString &host)
{
    _database->setHostName(host);
}

void VCore::setDatabaseUserName(const QString &name)
{
    _database->setUserName(name);
}

void VCore::setDatabasePassword(const QString &password)
{
    _database->setPassword(password);
}

void VCore::setDatabasePort(int port)
{
    _database->setPort(port);
}

void VCore::setClientsSessionManagerPort(quint16 port)
{
    _clients_session_manager->setPort(port);
}

quint8 VCore::databaseEngine() const
{
    return _database->engine();
}

QString VCore::databaseHostName() const
{
    return _database->hostName();
}

QString VCore::databaseUserName() const
{
    return _database->userName();
}

QString VCore::databasePassword() const
{
    return _database->password();
}

int VCore::databasePort() const
{
    return _database->port();
}

quint16 VCore::clientsSessionManagerPort() const
{
    return _clients_session_manager->port();
}

void VCore::startSlot()
{
    _database->open();
}

void VCore::stopSlot()
{
    _clients_session_manager->stop();
}

void VCore::openedDatabaseSlot(const VError &error)
{
    errors[0] = error;

    _clients_session_manager->start();
}

void VCore::closedDatabaseSlot()
{
    emit stoped();
}

void VCore::startedClientsSessionManagerSlot(const VError &error)
{
    errors[1] = error;

    if (errors[0].number() != -1) {
        _clients_session_manager->stop();
    }
    if (errors[1].number() != -1) {
        _database->close();
    }

    emit started(errors[0], errors[1]);
}

void VCore::stopedClientsSessionManagerSlot()
{
    _database->close();
}

void VCore::readyReadClientGrettingSlot(quint64 id, const VClientGretting &gretting)
{
    VServerGretting server_gretting;

    _database->insertMachine(0, gretting.hostName());

    _host_hash.insert(id, gretting.hostName());

    server_gretting.setInterval(1000);

    _clients_session_manager->writeToClient(id, VPacket::ServerGretting, server_gretting.toBytes());
}

void VCore::readyReadClientCapturePacketsSlot(quint64 id, const VClientCapturePackets &packets)
{
    emit readyReadClientCapturePackets(id, packets.sendBytes(), packets.receiveBytes());

    _database->insertPacketsLog(packets.hostName(), packets.receiveBytes(), packets.sendBytes());
}

void VCore::readyReadClientScreenshotSlot(quint64 id, const VClientScreenshot &screenshot)
{
    emit readyReadClientScreenshot(id, screenshot.snapshotImage());
}
