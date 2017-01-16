#include "oitem.h"

OItem::OItem()
{
}

void OItem::SetID(quint64 id)
{
    _id = id;
}

quint64 OItem::GetID() const
{
    return _id;
}
