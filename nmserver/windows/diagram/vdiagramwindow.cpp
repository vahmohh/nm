#include "vdiagramwindow.h"

#include <QPainter>
#include <QDebug>

VDiagramWindow::VDiagramWindow(QWidget *parent) : QWidget(parent)
{
    _first_vertical_line_x = _alarm_limit = 0;

    _horizontal_cell_count = 10;
    _vertical_cell_count = 6;
    _data_count = 40;
}

void VDiagramWindow::update(quint64 send, quint64 receive)
{
    _send_list.insert(0, send);
    _receive_list.insert(0, receive);

    if (_send_list.count() == _data_count + 1) {
        _send_list.removeLast();
        _receive_list.removeLast();
    }

    _max_data_number = _send_list.at(0);

    for (quint8 i = 1; i < _send_list.count(); ++i) {
        if (_max_data_number < _send_list.at(i)) {
            _max_data_number = _send_list.at(i);
        }
        if (_max_data_number < _receive_list.at(i)) {
            _max_data_number = _receive_list.at(i);
        }
    }

    if (_max_data_number < _alarm_limit) {
        _max_data_number = _alarm_limit;
    }

    parentWidget()->update();

    _first_vertical_line_x += (width() / (_data_count - 1));

    if (_first_vertical_line_x > width()) {
        _first_vertical_line_x = _first_vertical_line_x - width();
    }

    if(_max_data_number > _alarm_limit & _alarm_limit != 0) {
        setBorderColor(QColor(168, 79, 1));
        setFillColor(QColor(252, 243, 235, 120));
        setLineColor(QColor(238, 222, 207));
    }
    else
    {
        setBorderColor(QColor(17, 125, 187));
        setFillColor(QColor(241, 246, 250, 120));
        setLineColor(QColor(217, 234, 244));
    }

    parentWidget()->update();
}

void VDiagramWindow::setBorderColor(QColor color)
{
    _border_color = color;
}

void VDiagramWindow::setFillColor(QColor color)
{
    _fill_color = color;
}

void VDiagramWindow::setLineColor(QColor color)
{
    _line_color = color;
}

QColor VDiagramWindow::borderColor() const
{
    return _border_color;
}

void VDiagramWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);

    painter.drawRect(0, 0, width(), height());

    painter.setRenderHints(QPainter::Antialiasing);

    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);

    painter.drawRect(0, 0, width(), height());

    _pen.setStyle(Qt::SolidLine);
    _pen.setColor(_line_color);
    _pen.setWidthF(0.5);

    painter.setPen(_pen);
    painter.setBrush(painter.pen().color());

    for (quint8 i = 0; i < _vertical_cell_count - 1; ++i) {
        painter.drawLine(0, (height() / _vertical_cell_count) + (height() / _vertical_cell_count) * i, width(), (height() / _vertical_cell_count) + (height() / _vertical_cell_count) * i);
    }

    for (quint8 i = 0; i < _horizontal_cell_count; ++i) {
        quint16 tmp_x = _first_vertical_line_x + (width() / _horizontal_cell_count) * i;

        if (tmp_x > width()) {
            tmp_x = tmp_x - width();
        }

        painter.drawLine(width() - tmp_x, 0, width() - tmp_x, height());
    }

    painter.setPen(_border_color);
    painter.setBrush(QBrush());

    painter.drawRect(0, 0, width(), height());

    if (_send_list.count() > 0) {
        QPoint send_data_points[_send_list.count() + 2], receive_data_points[_send_list.count() + 2];

        send_data_points[0] = QPoint(width(), height());
        receive_data_points[0] = send_data_points[0];

        for (quint8 i = 0; i < _send_list.count(); ++i) {
            send_data_points[i + 1] = QPoint(width() - ((float) (((float) width() / (_data_count - 1)) * i)), height() - (_send_list.at(i) * height() / _max_data_number));
            receive_data_points[i + 1] = QPoint(width() - ((float) (((float) width() / (_data_count - 1)) * i)), height() - (_receive_list.at(i) * height() / _max_data_number));
        }

        send_data_points[_send_list.count() + 1] = QPoint(send_data_points[_send_list.count()].x(), height());
        receive_data_points[_send_list.count() + 1] = send_data_points[_send_list.count() + 1];

        QPen _tmp_pen;

        _tmp_pen.setColor(_border_color);
        _tmp_pen.setStyle(Qt::DashLine);

        painter.setPen(_tmp_pen);
        painter.setBrush(_fill_color);

        painter.drawPolygon(send_data_points, _send_list.count() + 2);

        _pen.setColor(_border_color);
        _pen.setWidth(1);

        painter.setPen(_pen);
        painter.setBrush(QBrush());

        painter.drawPolygon(receive_data_points, _send_list.count() + 2);
    }

    if(_alarm_limit != 0) {
        _pen.setColor(QColor(168, 79, 1));
        painter.setPen(_pen);
        painter.drawLine(0, height() - (_alarm_limit * height() / _max_data_number), width(), height() - (_alarm_limit * height() / _max_data_number));

    }
}
