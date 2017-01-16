#include "vreportwindow.h"
#include "ui_vreportwindow.h"

#include <objects/childs/vclientcapturepackets.h>
#include <QDebug>

VReportWindow::VReportWindow(QString u, QString p, VDatabase *db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VReportWindow)
{
    ui->setupUi(this);

    _database =db;

//    _database->setHostName("127.0.0.1");
//    _database->setUserName(u);
//    _database->setPassword(p);
//    _database->setDatabaseName("nm_db");
//    _database->open();

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

VReportWindow::~VReportWindow()
{
    delete ui;
}

QDateTime VReportWindow::ShamsiToMiladi(int intYear, int bytMonth, int bytDay)
{
    QDate temp;
    QDateTime outputDate;
    char bytGreLeap, bytSolLeap;
    bytGreLeap = 0;
    bytSolLeap = 0;

    intYear += bytMonth < 11 ? 621 : 622;

    if (!(intYear % 4)) bytGreLeap = 1;
    if (!((intYear - 1) % 4)) bytSolLeap = 1;

    switch(bytMonth)
    {
    case 1:
        bytMonth = bytDay < (12 - bytGreLeap) ? 3 : 4;
        bytDay = bytDay < (12 + bytGreLeap) ? (bytDay - bytGreLeap + 20) : (bytDay - bytGreLeap - 11);
        break;
    case 2:
        bytMonth = bytDay < (11 + bytGreLeap) ? 4 : 5;
        bytDay = bytDay < (11 + bytGreLeap) ? (bytDay - bytGreLeap + 20) : (bytDay - bytGreLeap - 10);
        break;
    case 3:
        bytMonth = bytDay < (11 + bytGreLeap) ? 5 : 6;
        bytDay = bytDay < (11 + bytGreLeap) ? (bytDay - bytGreLeap + 21) : (bytDay - bytGreLeap - 10);
        break;
    case 4:
        bytMonth = bytDay < (10 + bytGreLeap) ? 6 : 7;
        bytDay = bytDay < (10 + bytGreLeap) ? (bytDay - bytGreLeap + 21) : (bytDay - bytGreLeap - 9);
        break;
    case 5:
        bytMonth = bytDay < (10 + bytGreLeap) ? 7 : 8;
        bytDay = bytDay < (10 + bytGreLeap) ? (bytDay - bytGreLeap + 22) : (bytDay - bytGreLeap - 9);
        break;
    case 6:
        bytMonth = bytDay < (10 + bytGreLeap) ? 8 : 9;
        bytDay = bytDay < (10 + bytGreLeap) ? (bytDay - bytGreLeap + 22) : (bytDay - bytGreLeap - 9);
        break;
    case 7:
        bytMonth = bytDay < (9 + bytGreLeap) ? 9 : 10;
        bytDay = bytDay < (9 + bytGreLeap) ? (bytDay - bytGreLeap + 22) : (bytDay - bytGreLeap - 8);
        break;
    case 8:
        bytMonth = bytDay < (10 + bytGreLeap) ? 10 : 11;
        bytDay = bytDay < (10 + bytGreLeap) ? (bytDay - bytGreLeap + 22) : (bytDay - bytGreLeap - 9);
        break;
    case 9:
        bytMonth = bytDay < (10 + bytGreLeap) ? 11 : 12;
        bytDay = bytDay < (10 + bytGreLeap)? (bytDay - bytGreLeap + 21) : (bytDay - bytGreLeap - 9);
        break;
    case 10:
        if (!(bytDay < (11 + bytGreLeap))) intYear = intYear + 1;
        if (!((intYear - 1) % 4))
            bytSolLeap = 1;
        else
            bytSolLeap = 0;

        bytMonth = bytDay < (11 + bytGreLeap) ? 12 : 1;
        bytDay = bytDay < (11 + bytGreLeap) ? (bytDay - bytGreLeap + 21) : (bytDay - bytSolLeap - 10);
        break;
    case 11:
        bytMonth = bytDay < (12 + bytSolLeap) ? 1 : 2;
        bytDay = bytDay < (12 + bytSolLeap) ? (bytDay - bytSolLeap + 20) : (bytDay - bytSolLeap - 11);
        break;
    case 12:
        bytMonth = bytDay < (10 + bytSolLeap) ? 2 : 3;
        bytDay = bytDay < (10 + bytSolLeap) ? (bytDay - bytSolLeap + 19) : (bytDay - bytGreLeap - bytSolLeap - 9);
        break;
    }

    temp.setYMD(intYear, bytMonth, bytDay);
    outputDate.setDate(temp);

    return outputDate;
}

QString VReportWindow::gregorian2Jalali(int g_y, int g_m, int g_d)
{
    int g_days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int j_days_in_month[] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};

    int gy = g_y-1600;
    int gm = g_m-1;
    int gd = g_d-1;

    int i;

    int g_day_no = (365 * gy) + ((gy + 3)/4) - ((gy + 99) / 100) + ((gy + 399) / 400);

    for (i=0; i < gm; ++i)
        g_day_no += g_days_in_month[i];

    if (gm>1 && (((gy % 4 == 0) && (gy % 100 != 0)) || ((gy % 400) == 0)))
        /* leap and after Feb */
        ++g_day_no;
    g_day_no += gd;

    int j_day_no = g_day_no-79;

    int j_np = j_day_no / 12053;
    j_day_no %= 12053;

    int jy = 979 + (33 * j_np) + (4 * (j_day_no / 1461));

    j_day_no %= 1461;

    if (j_day_no >= 366) {
        jy += (j_day_no-1) / 365;
        j_day_no = (j_day_no - 1) % 365;
    }

    for (i = 0; i < 11 && j_day_no >= j_days_in_month[i]; ++i)
    {
        j_day_no -= j_days_in_month[i];
    }

    int jm = i + 1;
    int jd = j_day_no + 1;


    // year/month/day
    return  QString::number(jy) + "/" +
            QString::number(jm) + "/" +
            QString::number(jd);

}

void VReportWindow::on_pushButton_clicked()
{
    QList<VClientCapturePackets *> res;

    QStringList header;

    header << QString::fromUtf8("Machine");
    header << QString::fromUtf8("Send");
    header << QString::fromUtf8("Receive");
    header << QString::fromUtf8("Time");

    int rowCount = ui->tableWidget->rowCount();

    for(int i = 0; i < rowCount; i++)
        ui->tableWidget->removeRow(0);

    ui->tableWidget->clear();

    ui->tableWidget->setHorizontalHeaderLabels(header);

    QDateTime date = QDateTime(ShamsiToMiladi(ui->spbYear->value(), ui->cmbMonth->currentIndex() + 1, ui->spbDay->value()));
    QDateTime date2 = QDateTime(ShamsiToMiladi(ui->spbYear2->value(), ui->cmbMonth2->currentIndex() + 1, ui->spbDay2->value()));

    date.setTime(QTime(ui->spbHour->value(), ui->spbMinute->value(), 0));
    date2.setTime(QTime(ui->spbHour2->value(), ui->spbMinute2->value(), 0));

    res = _database->selectReport(date, date2);

    int row = 0;

    for(uint i = 0; i < res.count(); i++)
    {
        ui->tableWidget->insertRow(row);

        QTableWidgetItem *a = new QTableWidgetItem(res.at(i)->hostName());
        QTableWidgetItem *b = new QTableWidgetItem(QString::number(res.at(i)->sendBytes()));
        QTableWidgetItem *c = new QTableWidgetItem(QString::number(res.at(i)->receiveBytes()));
        QTableWidgetItem *d = new QTableWidgetItem(gregorian2Jalali(res.at(i)->dateTime().date().year(), res.at(i)->dateTime().date().month(), res.at(i)->dateTime().date().day()) + "\n" + res.at(i)->dateTime().time().toString());

        ui->tableWidget->setItem(row, 0, a);
        ui->tableWidget->setItem(row, 1, b);
        ui->tableWidget->setItem(row, 2, c);
        ui->tableWidget->setItem(row, 3, d);

        row++;
    }

}
