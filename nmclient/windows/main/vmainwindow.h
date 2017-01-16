#ifndef VMAINWINDOW_H
#define VMAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>

#include <QHash>

#include "windows/report/vreportwindow.h"

class VCore;
class VClientWindow;

namespace Ui {
class VMainWindow;
}

class VMainWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit VMainWindow(QWidget *parent = 0);
    ~VMainWindow();
    
private:
    Ui::VMainWindow *ui;

    QVBoxLayout *_layout;

    VCore *_core;
    QHash<quint64,VClientWindow*> _clients_hash;
    VReportWindow _report;

private slots:
    void newConnectionSlot(quint64 id);

    void disconnectedSlot(quint64 id);

    void turnOffButtonClickSlot(quint64 id);

    void readyReadClientCapturePacketsSlot(quint64 id, const uint &sd, const uint &rd);
    void readyReadClientScreenshotSlot(quint64 id, const QImage &snapshot);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // VMAINWINDOW_H
