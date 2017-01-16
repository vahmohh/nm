#include "vclientwindow.h"

#include <QPainter>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include "windows/diagram/vdiagramwindow.h"
#include "windows/screen/vscreenwindow.h"

VClientWindow::VClientWindow(Themes themes, QWidget *parent) : QWidget(parent)
{
    _last_send = _last_receive = 0;

    _alarm_limit = 0;

    _screen_button = new QPushButton(this);
    _turn_off_button = new QPushButton(this);
    _diagram_window = new VDiagramWindow(this);
    _limit_edit = new QLineEdit(this);
    _limit_lable = new QLabel(this);

    _screen_window = new VScreenWindow();

    connect(_screen_button, SIGNAL(clicked()), this, SLOT(screenButtonClickSlot()));
    connect(_turn_off_button, SIGNAL(clicked()), this, SLOT(turnOffButtonClickSlot()));
    connect(_limit_edit, SIGNAL(textChanged(QString)), this, SLOT(textChangedSlot(QString)));

    _screen_button->setIcon(QIcon(":/new/prefix1/icons/screen.png"));
    _turn_off_button->setIcon(QIcon(":/new/prefix1/icons/shutdown.png"));

    _screen_button->setIconSize(QSize(50, 50));
    _turn_off_button->setIconSize(QSize(50, 50));

    _screen_button->setGeometry(15, 10, 50, 50);
    _turn_off_button->setGeometry(15, 70, 50, 50);

    _diagram_window->setGeometry(90, 10, 600, 200);
    _screen_window->setGeometry(100, 100, 300, 200);

    _limit_edit->setGeometry(width() - 10, 250, 100, 20);
    _limit_lable->setGeometry(width() - 50, 250, 50, 20);

    _limit_lable->setText("Limit: ");
    _limit_edit->setText("0");

    switch (themes) {
    case Blue:
        _diagram_window->setBorderColor(QColor(17, 125, 187));
        _diagram_window->setFillColor(QColor(241, 246, 250, 120));
        _diagram_window->setLineColor(QColor(217, 234, 244));

        break;
    case Red:
        _diagram_window->setBorderColor(QColor(168, 79, 1));
        _diagram_window->setFillColor(QColor(252, 243, 235, 120));
        _diagram_window->setLineColor(QColor(238, 222, 207));

        break;
    default:
        break;
    }
}

void VClientWindow::update(quint64 send, quint64 receive)
{
    _last_send = send;
    _last_receive = receive;

    _diagram_window->update(send, receive);

    parentWidget()->update();
}

void VClientWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    QFont font;

    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);

    painter.drawRect(0, 0, width(), height());

    painter.setPen(_diagram_window->borderColor());
    painter.setBrush(QBrush());

    painter.drawRect(0, 0, width() - 1, height() - 1);

    painter.setPen(_diagram_window->borderColor());

    painter.drawLine(_diagram_window->x(), _diagram_window->y() + _diagram_window->height() + 10, _diagram_window->x(), _diagram_window->y() + _diagram_window->height() + 55);

    pen.setColor(_diagram_window->borderColor());
    pen.setStyle(Qt::DashLine);
    pen.setWidth(1);

    painter.setPen(pen);
    painter.setBrush(QBrush());

    painter.drawLine(_diagram_window->x() + 150, _diagram_window->y() + _diagram_window->height() + 10, _diagram_window->x() + 150, _diagram_window->y() + _diagram_window->height() + 55);

    painter.setPen(Qt::lightGray);

    painter.drawText(_diagram_window->x() + 5, _diagram_window->y() + _diagram_window->height() + 20, "Send");
    painter.drawText(_diagram_window->x() + 155, _diagram_window->y() + _diagram_window->height() + 20, "Receive");

    font.setPointSize(15);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.setFont(font);

    painter.drawText(_diagram_window->x() + 5, _diagram_window->y() + _diagram_window->height() + 50, QString::number(_last_receive) + " Kbps");
    painter.drawText(_diagram_window->x() + 155, _diagram_window->y() + _diagram_window->height() + 50, QString::number(_last_send) + " Kbps");
}

void VClientWindow::screenButtonClickSlot()
{
    _screen_window->show();
}

void VClientWindow::turnOffButtonClickSlot()
{
    emit turnOffButtonClickSignal(_id);
}

void VClientWindow::textChangedSlot(QString text)
{
    if(text != "0" && text != "")
        _diagram_window->_alarm_limit = text.toUInt();
    else
        _diagram_window->_alarm_limit = 0;
}
