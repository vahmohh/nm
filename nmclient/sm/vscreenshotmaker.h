#ifndef VSCREENSHOTMAKER_H
#define VSCREENSHOTMAKER_H

#include <QTimer>

class QImage;

class VClientScreenshot;

class VScreenshotMaker : public QObject
{
    Q_OBJECT
public:
    VScreenshotMaker(QObject *parent = 0);

    void setInterval(int msec);

    int interval() const;

    void start();
    void stop();

private:
    QTimer _timer;

    int _interval;

private slots:
    void startSlot();
    void stopSlot();

    void VScreenshotMakerSlot();

signals:
    void startSignal();
    void stopSignal();

    void readyRead(const QImage &snapshot);
};

#endif // VSCREENSHOTMAKER_H
