#include "vcore.h"

#include <QHostInfo>

#include "session/vsession.h"
#include "sm/vscreenshotmaker.h"
#include "slave/vslave.h"

#include "objects/childs/vpacket.h"
#include "objects/childs/vservergretting.h"
#include "objects/childs/vservercommand.h"
#include "objects/childs/vclientgretting.h"
#include "objects/childs/vclientcapturepackets.h"
#include "objects/childs/vclientscreenshot.h"

VCore::VCore(QObject *parent) : QObject(parent)
{
    _session = new VSession();
    _pcap = new VPCap();
    _screenshot_maker = new VScreenshotMaker();
    _slave = new VSlave();

    _screenshot_maker->setInterval(2000);

    connect(&_connect_to_server_timer, SIGNAL(timeout()), this, SLOT(startSlot()));
    connect(_session, SIGNAL(connected()), this, SLOT(connectedSlot()));
    connect(_session, SIGNAL(readyReadServerGretting(VServerGretting)), this, SLOT(readyReadServerGrettingSlot(VServerGretting)));
    connect(_session, SIGNAL(readyReadServerCommand(VServerCommand)), this, SLOT(readyReadServerCommandSlot(VServerCommand)));
    connect(&_pcap_timer, SIGNAL(timeout()), this, SLOT(readyReadClientCapturePacketsSlot()));
    connect(_screenshot_maker, SIGNAL(readyRead(QImage)), this, SLOT(readyReadScreenshotSlot(QImage)));

    qRegisterMetaType<VServerGretting>("VServerGretting");
    qRegisterMetaType<VServerCommand>("VServerCommand");
    qRegisterMetaType<VClientCapturePackets>("VClientCapturePackets");
    qRegisterMetaType<VClientScreenshot>("VClientScreenshot");

    moveToThread(&_thread);
    _thread.start();
}

VCore::~VCore()
{
    delete _session;
    delete _pcap;
    delete _slave;

    _thread.quit();
}

void VCore::start()
{
    _connect_to_server_timer.start(1000);
    _screenshot_maker->start();
}

void VCore::startSlot()
{
    _session->connectToServer();
}

void VCore::connectedSlot()
{
    VClientGretting client_gretting;

    client_gretting.setHostName(QHostInfo::localHostName());

    _connect_to_server_timer.stop();

    _session->write(VPacket::ClientGretting, client_gretting.toBytes());
}

void VCore::readyReadServerGrettingSlot(const VServerGretting &sg)
{
//    _pcap->setInterval(sg.interval());

    _pcap_timer.start(1000);
    _pcap->start();
}

void VCore::readyReadServerCommandSlot(const VServerCommand &command)
{
    _slave->execute(command._command);
}

void VCore::readyReadClientCapturePacketsSlot()
{
    VClientCapturePackets client_packets;

    if(_pcap->_upload == 0)
        _pcap->_upload = 1;
    if(_pcap->_download == 0)
        _pcap->_download = 1;

    client_packets.setSendBytes(_pcap->_upload);
    client_packets.setReceiveBytes(_pcap->_download);
    client_packets.setHostName(QHostInfo::localHostName());

    _pcap->_upload = _pcap->_download = 0;

    qDebug() << _pcap->_upload;
    qDebug() << _pcap->_download;

    _session->write(VPacket::ClientCapturePackets, client_packets.toBytes());
}

void VCore::readyReadScreenshotSlot(const QImage &snapshot)
{
    VClientScreenshot screenshot;

    screenshot.setSnapshotImage(snapshot);

    _session->write(VPacket::ClientScreenshot, screenshot.toBytes());
}
