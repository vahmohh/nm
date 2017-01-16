#include "vclientssessionmanager.h"

#include <QTcpSocket>

#include "cs/vclientsession.h"

#include "objects/childs/verror.h"

#include "objects/childs/vclientgretting.h"
#include "objects/childs/vclientcapturepackets.h"
#include "objects/childs/vclientscreenshot.h"

VClientsSessionManager::VClientsSessionManager(QObject *parent) : QObject(parent)
{
    _server.setParent(this);
    _clients_up_time_timer.setInterval(1000);

    connect(this, SIGNAL(startSignal()), this, SLOT(startSlot()));
    connect(this, SIGNAL(stopSignal()), this, SLOT(stopSlot()));
    connect(this, SIGNAL(writeToClientSignal(quint64,quint8,QByteArray)), this, SLOT(writeToClientSlot(quint64,quint8,QByteArray)));
    connect(this, SIGNAL(clientUpTimeSignal(quint64)), this, SLOT(connectedClientSlot()));
    connect(&_server, SIGNAL(newConnection()), this, SLOT(connectedClientSlot()));
    connect(&_clients_up_time_timer, SIGNAL(timeout()), this, SLOT(clientsUpTimeSlot()));

    qRegisterMetaType<VError>("VError");
    qRegisterMetaType<VClientGretting>("VClientGretting");
    qRegisterMetaType<VClientCapturePackets>("VClientCapturePackets");
    qRegisterMetaType<VClientScreenshot>("VClientScreenshot");

    moveToThread(&_thread);
    _thread.start();
}

VClientsSessionManager::~VClientsSessionManager()
{
    _thread.quit();
}

void VClientsSessionManager::setPort(quint16 port)
{
    _port = port;
}

quint16 VClientsSessionManager::port() const
{
    return _port;
}

void VClientsSessionManager::start()
{
    emit startSignal();
}

void VClientsSessionManager::stop()
{
    emit stopSignal();
}

void VClientsSessionManager::writeToClient(quint64 id, quint8 type, QByteArray data)
{
    emit writeToClientSignal(id, type, data);
}

void VClientsSessionManager::clientUpTime(quint64 id)
{
    emit clientUpTimeSignal(id);
}

void VClientsSessionManager::startSlot()
{
    VError error;

    if (_server.listen(QHostAddress::Any, port())) {
        _clients_up_time_timer.start();
        error.setNumber(-1);
    } else {
        error.setNumber(_server.serverError());
        error.setText(_server.errorString());
    }

    emit started(error);
}

void VClientsSessionManager::stopSlot()
{
    _server.close();

    emit stoped();
}

void VClientsSessionManager::writeToClientSlot(quint64 id, quint8 type, QByteArray data)
{
    _clients_session_hash.value(id)->write(type, data);

    emit writedClient(id);
}

void VClientsSessionManager::clientUpTimeSlot(quint64 id)
{
    emit readyClientUpTime(_clients_up_time_hash.value(id));
}

void VClientsSessionManager::clientsUpTimeSlot()
{
    foreach (quint64 id, _clients_up_time_hash.keys()) {
        _clients_up_time_hash.insert(id, _clients_up_time_hash.value(id) + 1000);
    }
}

void VClientsSessionManager::connectedClientSlot()
{
    VClientSession *client_session = new VClientSession(_clients_session_hash.count(), _server.nextPendingConnection());

    connect(client_session, SIGNAL(writed(quint64)), this, SIGNAL(writedClient(quint64)));
    connect(client_session, SIGNAL(disconnected(quint64)), this, SIGNAL(disconnectedClient(quint64)));
    connect(client_session, SIGNAL(readyReadClientGretting(quint64,VClientGretting)), this, SIGNAL(readyReadClientGretting(quint64,VClientGretting)));
    connect(client_session, SIGNAL(readyReadClientCapturePackets(quint64,VClientCapturePackets)), this, SIGNAL(readyReadClientCapturePackets(quint64,VClientCapturePackets)));
    connect(client_session, SIGNAL(readyReadClientScreenshot(quint64,VClientScreenshot)), this, SIGNAL(readyReadClientScreenshot(quint64,VClientScreenshot)));

    _clients_session_hash.insert(client_session->id(), client_session);
    _clients_up_time_hash.insert(client_session->id(), 0);

    emit connectedClient(client_session->id());
}

void VClientsSessionManager::disconnectedClientSlot(quint64 id)
{
    delete _clients_session_hash.value(id);

    _clients_session_hash.remove(id);
    _clients_up_time_hash.remove(id);

    emit disconnectedClient(id);
}
