#ifndef VSERVERCOMMAND_H
#define VSERVERCOMMAND_H

#include "objects/vobject.h"

class VServerCommand : public VObject
{
public:
    VServerCommand();
    VServerCommand(const QByteArray &data);

    QString _command;

    QByteArray toBytes() const;
};

#endif // VSERVERCOMMAND_H
