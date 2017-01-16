QT += network sql

SOURCES += \
    main.cpp \
    core/vcore.cpp \
    objects/vobject.cpp \
    objects/childs/vservergretting.cpp \
    objects/childs/vclientgretting.cpp \
    objects/childs/vclientcapturepackets.cpp \
    cs/vclientsession.cpp \
    csm/vclientssessionmanager.cpp \
    windows/main/vmainwindow.cpp \
    database/vdatabase.cpp \
    windows/screen/vscreenwindow.cpp \
    objects/childs/vclientscreenshot.cpp \
    objects/childs/vpacket.cpp \
    objects/childs/verror.cpp \
    windows/client/vclientwindow.cpp \
    windows/diagram/vdiagramwindow.cpp \
    objects/childs/vservercommand.cpp \
    windows/report/vreportwindow.cpp \
    windows/login/vloginwindow.cpp

HEADERS += \
    core/vcore.h \
    objects/vobject.h \
    objects/childs/vservergretting.h \
    objects/childs/vclientgretting.h \
    objects/childs/vclientcapturepackets.h \
    cs/vclientsession.h \
    csm/vclientssessionmanager.h \
    windows/main/vmainwindow.h \
    database/vdatabase.h \
    windows/screen/vscreenwindow.h \
    objects/childs/vclientscreenshot.h \
    objects/childs/vpacket.h \
    objects/childs/verror.h \
    windows/client/vclientwindow.h \
    windows/diagram/vdiagramwindow.h \
    windows/screen/vscreenwindow.h \
    objects/childs/vservercommand.h \
    windows/report/vreportwindow.h \
    windows/login/vloginwindow.h

FORMS += \
    windows/main/vmainwindow.ui \
    windows/report/vreportwindow.ui \
    windows/login/vloginwindow.ui

RESOURCES += \
    icons.qrc
