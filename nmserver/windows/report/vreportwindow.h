#ifndef VREPORTWINDOW_H
#define VREPORTWINDOW_H

#include <QWidget>
#include <QString>

#include "database/vdatabase.h"

namespace Ui {
class VReportWindow;
}

class VReportWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit VReportWindow(QString u, QString p, VDatabase *db, QWidget *parent = 0);
    ~VReportWindow();

    QDateTime ShamsiToMiladi(int intYear, int bytMonth, int bytDay);
    QString gregorian2Jalali(int g_y, int g_m, int g_d);

    QString _u, _p;
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::VReportWindow *ui;

    VDatabase *_database;
};

#endif // VREPORTWINDOW_H
