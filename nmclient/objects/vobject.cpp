#include "vobject.h"

VObject::VObject()
{
}

void VObject::setID(quint64 id)
{
    _id = id;
}

void VObject::setDateTime(const QDateTime &date)
{
    _date_time = date;
}

quint64 VObject::id() const
{
    return _id;
}

QDateTime VObject::dateTime() const
{
    return _date_time;
}
