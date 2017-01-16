#include "verror.h"

VError::VError()
{
}

void VError::setNumber(int number)
{
    _number = number;
}

void VError::setText(const QString &text)
{
    _text = text;
}

int VError::number() const
{
    return _number;
}

QString VError::text() const
{
    return _text;
}
