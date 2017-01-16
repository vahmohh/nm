#include "vscreenshotmaker.h"

#include <QThread>
#include <QApplication>
#include <QDesktopWidget>
#include <QPixmap>

#include "objects/childs/vclientscreenshot.h"

VScreenshotMaker::VScreenshotMaker(QObject *parent) : QObject(parent)
{
    connect(this, SIGNAL(startSignal()), this, SLOT(startSlot()));
    connect(this, SIGNAL(stopSignal()), this, SLOT(stopSlot()));
    connect(&_timer, SIGNAL(timeout()), this, SLOT(VScreenshotMakerSlot()));

    thread()->setPriority(QThread::HighestPriority);
}

void VScreenshotMaker::setInterval(int msec)
{
    if (msec > 0) {
        _interval = msec;
    }
}

int VScreenshotMaker::interval() const
{
    return _interval;
}

void VScreenshotMaker::start()
{
    emit startSignal();
}

void VScreenshotMaker::stop()
{
    emit stopSignal();
}

void VScreenshotMaker::startSlot()
{
    _timer.start(_interval);
}

void VScreenshotMaker::stopSlot()
{
    _timer.stop();
}

void VScreenshotMaker::VScreenshotMakerSlot()
{
    emit readyRead(QPixmap::grabWindow(QApplication::desktop()->winId()).toImage().scaled(80, 60));
}
