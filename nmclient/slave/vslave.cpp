#include "vslave.h"

VSlave::VSlave(QObject *parent) : QObject(parent)
{
    connect(this, SIGNAL(executeSignal(QString)), this, SLOT(executeSlot(QString)));

    moveToThread(&_thread);
    _thread.start();
}

VSlave::~VSlave()
{
    _thread.quit();
}

void VSlave::execute(const QString &command)
{
    emit executeSignal(command);
}

void VSlave::executeSlot(const QString &command)
{
    _process.execute(command);
}
