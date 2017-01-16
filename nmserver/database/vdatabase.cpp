#include "vdatabase.h"

#include <QSqlError>
#include <QDebug>

#include "objects/childs/vclientcapturepackets.h"
#include "objects/childs/verror.h"

VDatabase::VDatabase(QObject *parent) : QObject(parent)
{
    _database = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL", "default"));

    _query = QSqlQuery(*_database);

    connect(this, SIGNAL(openSignal()), this, SLOT(openSlot()));
    connect(this, SIGNAL(closeSignal()), this, SLOT(closeSlot()));

    moveToThread(&_thread);
    _thread.start();
}

VDatabase::~VDatabase()
{
    _thread.quit();
}

void VDatabase::setEngine(quint8 engine)
{
    _engine = engine;
}

void VDatabase::setHostName(const QString &host)
{
    _database->setHostName(host);
}

void VDatabase::setUserName(const QString &name)
{
    _database->setUserName(name);
}

void VDatabase::setPassword(const QString &password)
{
    _database->setPassword(password);
}

void VDatabase::setDatabaseName(const QString &name)
{
    _database->setDatabaseName(name);
}

void VDatabase::setPort(int port)
{
    _database->setPort(port);
}

void VDatabase::setConnectOptions(const QString &options)
{
    _database->setConnectOptions(options);
}

quint8 VDatabase::engine() const
{
    return _engine;
}

QString VDatabase::hostName() const
{
    return _database->hostName();
}

QString VDatabase::userName() const
{
    return _database->userName();
}

QString VDatabase::password() const
{
    return _database->password();
}

QString VDatabase::databaseName() const
{
    return _database->databaseName();
}

int VDatabase::port() const
{
    return _database->port();
}

QString VDatabase::connectOptions() const
{
    return _database->connectOptions();
}

void VDatabase::open()
{
    emit openSignal();
}

void VDatabase::close()
{
    emit closeSignal();
}

void VDatabase::insertMachine(quint64 id, QString host)
{
    _query.exec("INSERT INTO machine_table VALUES (?)");

    _query.addBindValue(host);

    _query.exec();
}

//void VDatabase::getMachine()
//{

//}

void VDatabase::insertPacketsLog(QString id, quint32 download, quint32 upload)
{
    _query.prepare("INSERT INTO packets_log_table VALUES (DEFAULT, ?, ?, ?, now())");

    _query.addBindValue(id);
    _query.addBindValue(download);
    _query.addBindValue(upload);

    _query.exec();
}

QList<VClientCapturePackets *> VDatabase::selectReport(QDateTime than, QDateTime until)
{
    QList<VClientCapturePackets *> packets;

    _query.prepare("SELECT "
                   "machine_table.id_pk_field, packets_log_table.download_field, packets_log_table.upload_field, packets_log_table.insert_time_field "
                   "FROM "
                   "packets_log_table "
                   "INNER JOIN "
                   "machine_table "
                   "ON "
                   "packets_log_table.machine_id_fk_field = machine_table.id_pk_field "
                   "WHERE "
                   "packets_log_table.insert_time_field BETWEEN ? AND ?");

    _query.addBindValue(than);
    _query.addBindValue(until);

    _query.exec();

    _query.first();

    if(!_query.value(0).isNull()) {
        do
        {
            VClientCapturePackets *packet = new VClientCapturePackets();

            packet->setHostName(_query.value(0).toString());
            packet->setReceiveBytes(_query.value(1).toUInt());
            packet->setSendBytes(_query.value(2).toUInt());
            packet->setDateTime(_query.value(3).toDateTime());

            packets.append(packet);

        } while(_query.next());
    }

    return packets;
}

void VDatabase::openSlot()
{
    VError error;

    //    _database.removeDatabase("default");

    //    if (!_database->isOpen()) {
    //        switch (engine()) {
    //        case PostgreSQL:
    //            _database = QSqlDatabase(QSqlDatabase::addDatabase("QPSQL", "default"));
    //            break;
    //        case MySQL:
    //            _database = QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL", "default"));
    //            break;
    //        default:
    //            break;
    //        }

//    _database->close();


    _database->setDatabaseName("nm_db");

    error.setNumber(_database->lastError().number());
    error.setText(_database->open() ? " " : "wrong!");

    //    }

    emit opened(error);
}

void VDatabase::closeSlot()
{
    //    if (_database->isOpen()) {
    //        _database->close();
    //    }

    //    emit closed();
}
