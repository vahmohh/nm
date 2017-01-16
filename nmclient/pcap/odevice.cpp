#include "odevice.h"

ODevice::ODevice()
{
}

ODevice::ODevice(ulong id, const QString &name, const QString &description)
{
    SetID(id);
    SetName(name);
    SetDescription(description);
}

void ODevice::SetName(const QString &name)
{
    _name = name;
}

void ODevice::SetDescription(const QString &description)
{
    _description = description;
}

QString ODevice::GetName() const
{
    return _name;
}

QString ODevice::GetDescription() const
{
    return _description;
}
