#include "vmainwindow.h"
#include "ui_vmainwindow.h"

#include "core/vcore.h"

#include "windows/client/vclientwindow.h"
#include "windows/screen/vscreenwindow.h"

VMainWindow::VMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VMainWindow)
{
    ui->setupUi(this);

    _core = new VCore();

    _core->setClientsSessionManagerPort(7989);

    _layout = new QVBoxLayout(ui->clientsScrollAreaWidgetContents);

    connect(_core, SIGNAL(connectedClient(quint64)), this, SLOT(newConnectionSlot(quint64)));
    connect(_core, SIGNAL(disconnectedClient(quint64)), this, SLOT(disconnectedSlot(quint64)));
    connect(_core, SIGNAL(readyReadClientCapturePackets(quint64,uint,uint)), this, SLOT(readyReadClientCapturePacketsSlot(quint64,uint,uint)));
    connect(_core, SIGNAL(readyReadClientScreenshot(quint64,QImage)), this, SLOT(readyReadClientScreenshotSlot(quint64,QImage)));

    _core->start();
}

VMainWindow::~VMainWindow()
{
    delete ui;
}

void VMainWindow::newConnectionSlot(quint64 id)
{
    VClientWindow *client_window = new VClientWindow(VClientWindow::Blue);

    connect(client_window, SIGNAL(turnOffButtonClickSignal(quint64)), this, SLOT(turnOffButtonClickSlot(quint64)));

    client_window->_id = id;

    client_window->setMinimumHeight(300);
    client_window->setMaximumHeight(300);

    _clients_hash.insert(id, client_window);

    _layout->addWidget(client_window);
}

void VMainWindow::disconnectedSlot(quint64 id)
{
    delete _clients_hash.value(id);

    _clients_hash.remove(id);
}

void VMainWindow::turnOffButtonClickSlot(quint64 id)
{
    _core->command(id, "./systemctl poweroff");
}

void VMainWindow::readyReadClientCapturePacketsSlot(quint64 id, const uint &sd, const uint &rd)
{
    _clients_hash.value(id)->update(sd + (random()/100000), rd+(random()/100000));
}

void VMainWindow::readyReadClientScreenshotSlot(quint64 id, const QImage &snapshot)
{
    if(_clients_hash.value(id)->_screen_window != NULL)
        _clients_hash.value(id)->_screen_window->setImage(snapshot);
}

void VMainWindow::on_pushButton_clicked()
{
    _report.show();
}

void VMainWindow::on_pushButton_2_clicked()
{
    exit(0);
}
