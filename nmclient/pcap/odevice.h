#ifndef ODEVICE_H
#define ODEVICE_H

#include <QString>

#include "oitem.h"

class ODevice : public OItem
{
public:
    ODevice();
    ODevice(ulong id, const QString &name, const QString &description);

    void SetName(const QString &name);
    void SetDescription(const QString &description);

    QString GetName() const;
    QString GetDescription() const;

private:
    QString _name, _description;
};

#endif
