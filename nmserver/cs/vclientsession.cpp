#include "vclientsession.h"

#include <QTcpSocket>

#include "objects/childs/vpacket.h"
#include "objects/childs/vclientgretting.h"
#include "objects/childs/vclientcapturepackets.h"
#include "objects/childs/vclientscreenshot.h"

VClientSession::VClientSession(quint64 id, QTcpSocket *socket, QObject *parent) : QObject(parent)
{
    setID(id);
    setSocket(socket);

    connect(this, SIGNAL(writeSignal(quint8,QByteArray)), this, SLOT(writeSlot(quint8,QByteArray)));
    connect(this->socket(), SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
    connect(this->socket(), SIGNAL(readyRead()), this, SLOT(readyReadSlot()));

    moveToThread(&_thread);
    _thread.start();
}

VClientSession::~VClientSession()
{
    _thread.quit();
}

quint64 VClientSession::id() const
{
    return _id;
}

QTcpSocket *VClientSession::socket() const
{
    return _socket;
}

void VClientSession::write(quint8 type, QByteArray data)
{
    emit writeSignal(type, data);
}

void VClientSession::setID(quint64 id)
{
    _id = id;
}

void VClientSession::setSocket(QTcpSocket *socket)
{
    if (socket != NULL) {
        _socket = socket;
    }
}

void VClientSession::disconnectedSlot()
{
    emit disconnected(id());
}

void VClientSession::writeSlot(quint8 type, QByteArray data)
{
    VPacket packet;

    packet.setType(type);
    packet.setDataBytes(data);

    socket()->write(packet.toBytes());

    emit writed(id());
}

void VClientSession::readyReadSlot()
{
    VPacket packet(socket()->readAll());

    switch (packet.type()) {
    case VPacket::ClientGretting:
        emit readyReadClientGretting(id(), VClientGretting(packet.dataBytes()));
        break;
    case VPacket::ClientCapturePackets:
        emit readyReadClientCapturePackets(id(), VClientCapturePackets(packet.dataBytes()));
        break;
    case VPacket::ClientScreenshot:
        emit readyReadClientScreenshot(id(), VClientScreenshot(packet.dataBytes()));
        break;
    default:
        break;
    }
}
