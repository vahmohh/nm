#ifndef VSLAVE_H
#define VSLAVE_H

#include <QThread>
#include <QProcess>

class VSlave : public QObject
{
    Q_OBJECT
public:
    VSlave(QObject *parent = 0);
    ~VSlave();

    void execute(const QString &command);

private:
    QThread _thread;
    QProcess _process;

private slots:
    void executeSlot(const QString &command);

signals:
    void executeSignal(const QString &command);
};

#endif // VSLAVE_H
