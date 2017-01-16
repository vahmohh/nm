#ifndef OITEM_H
#define OITEM_H

#include <QtGlobal>

class OItem
{
public:
    OItem();

    void SetID(quint64 id);

    quint64 GetID() const;

private:
    quint64 _id;
};

#endif
