#ifndef VERROR_H
#define VERROR_H

#include <QString>

class VError
{
public:
    VError();

    void setNumber(int number);
    void setText(const QString &text);

    int number() const;
    QString text() const;

private:
    int _number;
    QString _text;
};

#endif // VERROR_H
