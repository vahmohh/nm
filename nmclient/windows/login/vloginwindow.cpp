#include "vloginwindow.h"
#include "ui_vloginwindow.h"

#include <QDesktopWidget>
#include <QMessageBox>

#include "core/vcore.h"
#include "windows/main/vmainwindow.h"
#include "objects/childs/verror.h"

VLoginWindow::VLoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VLoginWindow)
{
    ui->setupUi(this);

    _core = new VCore();

    _core->setClientsSessionManagerPort(7989);

    connect(_core, SIGNAL(started(VError,VError)), this, SLOT(startedSlot(VError,VError)));
}

VLoginWindow::~VLoginWindow()
{
    delete ui;
}

void VLoginWindow::on_pushButton_2_clicked()
{
    exit(0);
}

void VLoginWindow::on_pushButton_clicked()
{
    _core->setDatabaseUserName(ui->lineEdit->text());
    _core->setDatabasePassword(ui->lineEdit_2->text());

    _core->start();
}

void VLoginWindow::startedSlot(const VError &database, const VError &session)
{
    if(database.number() == -1 && session.number() == -1)
    {
        VMainWindow main_window;

        main_window.setGeometry(QApplication::desktop()->width() / 2 - 400, QApplication::desktop()->height() / 2 - 300, 800, 600);
        main_window.show();
    }
    else
    {
        QMessageBox::critical(0, "Error", "Invalid username or password");

        _core->stop();
    }
}


