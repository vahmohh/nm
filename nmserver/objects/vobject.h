#ifndef VOBJECT_H
#define VOBJECT_H

#include <QDateTime>

class VObject
{
public:
    VObject();

    void setID(quint64 id);
    void setDateTime(const QDateTime &date);

    quint64 id() const;
    QDateTime dateTime() const;

    virtual QByteArray toBytes() const = 0;

protected:
    quint64 _id;
    QDateTime _date_time;
};

#endif // VOBJECT_H
