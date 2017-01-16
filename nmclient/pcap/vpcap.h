#ifndef PCAP_H
#define PCAP_H

#include <QThread>
#include <QTimer>

#include "objects/childs/vclientcapturepackets.h"
#include "odevice.h"

#include <pcap.h>

class VPCap : public QObject
{
    Q_OBJECT
public:
    VPCap(QObject *parent = 0);
    ~VPCap();

    void start();

    int Open(uint id);
    QList<ODevice> GetDevices();
    char *iptos(u_long in);
    QString getDeviceIP(int DeviceNo);

    typedef struct ip_address
    {
        u_char byte1;
        u_char byte2;
        u_char byte3;
        u_char byte4;
    } ip_address;

    typedef struct ip_header
    {
        u_char  ver_ihl;        // Version (4 bits) + Internet header length (4 bits)
        u_char  tos;            // Type of service
        u_short tlen;           // Total length
        u_short identification; // Identification
        u_short flags_fo;       // Flags (3 bits) + Fragment offset (13 bits)
        u_char  ttl;            // Time to live
        u_char  proto;          // Protocol
        u_short crc;            // Header checksum
        ip_address  saddr;      // Source address
        ip_address  daddr;      // Destination address
        u_int   op_pad;         // Option + Padding
    } ip_header;

    uint _network_id;
    uint _download, _upload;

private:
    QThread _thread;
    QTimer _timer;


    pcap_t *adhandle;
    QString IPadd;

    pcap_if_t *alldevs;

private slots:
    void startSlot();

signals:
    void startSignal();

    void started();

    void readyReadClientCapturePackets(const VClientCapturePackets &);
};

#endif // PCAP_H
