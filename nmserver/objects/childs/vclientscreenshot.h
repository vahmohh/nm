#ifndef VCLIENTSCREENSHOT_H
#define VCLIENTSCREENSHOT_H

#include "../vobject.h"

#include <QImage>

class VClientScreenshot : public VObject
{
public:
    VClientScreenshot();
    VClientScreenshot(const QByteArray &data);

    void setSnapshotImage(const QImage &snapshot);

    QImage snapshotImage() const;

    QByteArray toBytes() const;

private:
    QImage _snapshot_image;
};

#endif // VCLIENTSCREENSHOT_H
