#ifndef VCORE_H
#define VCORE_H

#include <QThread>
#include <QTimer>

#include "pcap/vpcap.h"

class QImage;

class VSession;
class VScreenshotMaker;
class VSlave;

class VServerGretting;
class VServerCommand;
class VClientCapturePackets;
class VClientScreenshot;

class VCore : public QObject
{
    Q_OBJECT
public:
    VCore(QObject *parent = 0);
    ~VCore();

    void start();

private:
    QThread _thread;
    QTimer _connect_to_server_timer, _pcap_timer;

    VSession *_session;
    VPCap *_pcap;
    VScreenshotMaker *_screenshot_maker;
    VSlave *_slave;

private slots:
    void startSlot();

    void connectedSlot();

    void readyReadServerGrettingSlot(const VServerGretting &sg);
    void readyReadServerCommandSlot(const VServerCommand &command);

    void readyReadClientCapturePacketsSlot();

    void readyReadScreenshotSlot(const QImage &snapshot);


signals:
    void startSignal();
};

#endif // VCORE_H
