#ifndef VLOGINWINDOW_H
#define VLOGINWINDOW_H

#include <QWidget>

#include "windows/main/vmainwindow.h"

class VCore;
class VError;

namespace Ui {
class VLoginWindow;
}

class VLoginWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit VLoginWindow(QWidget *parent = 0);
    ~VLoginWindow();
    
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void startedSlot(const VError &database, const VError &session);

private:
    Ui::VLoginWindow *ui;

    VCore *_core;
    VMainWindow _main;
};

#endif // VLOGINWINDOW_H
