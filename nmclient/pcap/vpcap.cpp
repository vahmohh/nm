#include "vpcap.h"

#include <sys/socket.h>
#include <netinet/in.h>

#include "objects/childs/vclientcapturepackets.h"

VPCap::VPCap(QObject *parent) : QObject(parent)
{
    _download = 0;
    _upload = 0;

    connect(this, SIGNAL(startSignal()), this, SLOT(startSlot()));

    moveToThread(&_thread);
    _thread.start();
}

VPCap::~VPCap()
{

}

void VPCap::start()
{
    emit startSignal();
}

void VPCap::startSlot()
{
    GetDevices();
    Open(_network_id);

    _timer.start(1000);

    int res = 0;
    struct pcap_pkthdr *header;
    const u_char *pkt_data;

    while((res = pcap_next_ex(adhandle, &header, &pkt_data)) >= 0)
    {
        if(res == 0)
            continue;

        if(QString::number(((VPCap::ip_header *) (pkt_data + 14))->saddr.byte1) + "." + QString::number(((VPCap::ip_header *) (pkt_data + 14))->saddr.byte2) + "." + QString::number(((VPCap::ip_header *) (pkt_data + 14))->saddr.byte3) + "." + QString::number(((VPCap::ip_header *) (pkt_data + 14))->saddr.byte4) == IPadd)
            _upload += header->len;
        if(QString::number(((VPCap::ip_header *) (pkt_data + 14))->daddr.byte1) + "." + QString::number(((VPCap::ip_header *) (pkt_data + 14))->daddr.byte2) + "." + QString::number(((VPCap::ip_header *) (pkt_data + 14))->daddr.byte3) + "." + QString::number(((VPCap::ip_header *) (pkt_data + 14))->daddr.byte4) == IPadd)
            _download += header->len;
    }

    emit started();
}

QList<ODevice> VPCap::GetDevices()
{
        QList<ODevice> devices;

        char errbuf[PCAP_ERRBUF_SIZE];

        if(pcap_findalldevs(&alldevs, errbuf) != -1)
        {
            pcap_if_t *d;

            int i = 0;

            for(d=alldevs; d; d=d->next)
            {
                i++;

                devices.append(ODevice(i, IPadd, d->description));

                if(d->addresses != 0 && QString(d->name) != "lo")
                    _network_id = i;
            }

            if(i == 0)
                pcap_freealldevs(alldevs);

            delete d;
        }
        else
            pcap_freealldevs(alldevs);

        return devices;
}

int VPCap::Open(uint id)
{
    pcap_if_t *d;

    char errbuf[PCAP_ERRBUF_SIZE];

    getDeviceIP(id);

    int i=0;
    for(d=alldevs, i=0; i< id-1 ;d=d->next, i++);

    adhandle= pcap_open_live(d->name,	// name of the device
                             65536,			// portion of the packet to capture.
                             // 65536 grants that the whole packet will be captured on all the MACs.
                             1,				// promiscuous mode (nonzero means promiscuous)
                             1000,			// read timeout
                             errbuf			// error buffer
                             );

    pcap_freealldevs(alldevs);

    return 0;
}

char *VPCap::iptos(u_long in)
{
    static char output[12][3*4+3+1];
    static short which;
    u_char *p;

    p = (u_char *)&in;
    which = (which + 1 == 12 ? 0 : which + 1);
    sprintf(output[which], "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
    return output[which];
}

QString VPCap::getDeviceIP(int DeviceNo)
{
    QString ip;

    pcap_if_t *Adev;
    int it=0;

    for(Adev=alldevs;Adev;Adev=Adev->next)
    {
        if (it==DeviceNo-1)
            break;

        it++;
    }

    pcap_addr_t *a;

    for(a=Adev->addresses;a;a=a->next)
    {
        switch(a->addr->sa_family)
        {
        case AF_INET:
            if (a->addr)
                ip = iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr);
            break;
        default:
            break;
        }
    }

    IPadd = ip;

    return ip;
}
