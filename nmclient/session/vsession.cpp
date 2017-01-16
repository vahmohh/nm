#include "vsession.h"

#include <QNetworkInterface>
#include <QStringList>

#include "objects/childs/vpacket.h"
#include "objects/childs/vservergretting.h"
#include "objects/childs/vservercommand.h"

VSession::VSession(QObject *parent) : QObject(parent)
{
    _socket.setParent(this);

    connect(this, SIGNAL(connectToServerSignal()), this, SLOT(connectToServerSlot()));
    connect(this, SIGNAL(disconnectFromServerSignal()), this, SLOT(disconnectFromServerSlot()));
    connect(this, SIGNAL(writeSignal(quint8,QByteArray)), this, SLOT(writeSlot(quint8,QByteArray)));
    connect(&_socket, SIGNAL(connected()), this, SIGNAL(connected()));
    connect(&_socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(readyReadSlot()));

    moveToThread(&_thread);
    _thread.start();
}

VSession::~VSession()
{
    _thread.quit();
}

void VSession::connectToServer()
{
    emit connectToServerSignal();
}

void VSession::disconnectFromServer()
{
    emit disconnectFromServerSignal();
}

void VSession::write(quint8 type, QByteArray bytes)
{
    emit writeSignal(type, bytes);
}

void VSession::connectToServerSlot()
{
    foreach(QHostAddress ip, QNetworkInterface::allAddresses())
        if(!ip.toString().contains(":") && ip.toString() != "127.0.0.1") {
            QStringList ip_parts = ip.toString().split(".");

            for(quint8 i = 0; i < 255; i++) {
                _socket.connectToHost(ip_parts.at(0) + "." + ip_parts.at(1) + "." + ip_parts.at(2) + "." + QString::number(i), 9998);

                if(_socket.waitForConnected(30))
                    return;
            }
        }

}

void VSession::disconnectFromServerSlot()
{
    _socket.disconnectFromHost();
}

void VSession::writeSlot(quint8 type, QByteArray bytes)
{
    VPacket packet;

    packet.setType(type);
    packet.setDataBytes(bytes);

    _socket.write(packet.toBytes());
}

void VSession::readyReadSlot()
{
    VPacket packet(_socket.readAll());

    switch (packet.type()) {
    case VPacket::ServerGretting:
        emit readyReadServerGretting(VServerGretting(packet.dataBytes()));
        break;
    case VPacket::ServerCommand:
        emit readyReadServerCommand(VServerCommand(packet.dataBytes()));
        break;
    default:
        break;
    }
}
