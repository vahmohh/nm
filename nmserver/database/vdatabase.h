#ifndef VDATABASE_H
#define VDATABASE_H

#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>

class VError;
class VClientCapturePackets;

class VDatabase : public QObject
{
    Q_OBJECT
public:
    enum Engine {
        PostgreSQL,
        MySQL
    };

    VDatabase(QObject *parent = 0);
    ~VDatabase();

    void setEngine(quint8 engine);
    void setHostName(const QString &host);
    void setUserName(const QString &name);
    void setPassword(const QString &password);
    void setDatabaseName(const QString &name);
    void setPort(int port);
    void setConnectOptions(const QString &options);

    quint8 engine() const;
    QString hostName() const;
    QString userName() const;
    QString password() const;
    QString databaseName() const;
    int port() const;
    QString connectOptions() const;

    void open();
    void close();

    void insertUser(QString name, QString password, quint8 access);
    void updateUser(QString id, QString name, QString password, quint8 access);
    void removeUser(QString id);
    void getUser();

    void insertMachine(quint64 id, QString host);
    void getMachine();

    void insertPacketsLog(QString id, quint32 download, quint32 upload);

    QList<VClientCapturePackets *> selectReport(QDateTime than, QDateTime until);

private:
    QThread _thread;
    QSqlDatabase *_database;
    QSqlQuery _query;

    quint8 _engine;

private slots:
    void openSlot();
    void closeSlot();

signals:
    void openSignal();
    void closeSignal();

    void opened(const VError &error);
    void closed();
};

#endif // VDATABASE_H
