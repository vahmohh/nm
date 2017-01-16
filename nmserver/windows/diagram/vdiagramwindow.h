#ifndef VDIAGRAMWINDOW_H
#define VDIAGRAMWINDOW_H

#include <QWidget>
#include <QPen>

class VDiagramWindow : public QWidget
{
    Q_OBJECT
public:
    VDiagramWindow(QWidget *parent = 0);

    void update(quint64 send, quint64 receive);

    void setBorderColor(QColor color);
    void setFillColor(QColor color);
    void setLineColor(QColor color);

    QColor borderColor() const;

    uint _alarm_limit;

private:
    quint32 _horizontal_cell_count, _vertical_cell_count, _data_count;
    quint32 _first_vertical_line_x, _max_data_number;
    QList<quint32> _send_list, _receive_list;
    QPen _pen;
    QColor _border_color, _fill_color, _line_color;

    void paintEvent(QPaintEvent *);

};

#endif // VDIAGRAMWINDOW_H
