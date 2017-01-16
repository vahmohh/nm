QT += network

LIBS += -L ./usr/lib -lpcap

SOURCES += \
    main.cpp \
    core/vcore.cpp \
    session/vsession.cpp \
    objects/vobject.cpp \
    objects/childs/vclientgretting.cpp \
    objects/childs/vservergretting.cpp \
    pcap/vpcap.cpp \
    objects/childs/vclientcapturepackets.cpp \
    slave/vslave.cpp \
    objects/childs/vclientscreenshot.cpp \
    objects/childs/vpacket.cpp \
    sm/vscreenshotmaker.cpp \
    objects/childs/verror.cpp \
    objects/childs/vservercommand.cpp \
    pcap/oitem.cpp \
    pcap/odevice.cpp

HEADERS += \
    core/vcore.h \
    session/vsession.h \
    objects/vobject.h \
    objects/childs/vclientgretting.h \
    objects/childs/vservergretting.h \
    pcap/vpcap.h \
    objects/childs/vclientcapturepackets.h \
    slave/vslave.h \
    objects/childs/vclientscreenshot.h \
    objects/childs/vpacket.h \
    sm/vscreenshotmaker.h \
    objects/childs/verror.h \
    objects/childs/vservercommand.h \
    pcap/oitem.h \
    pcap/odevice.h
