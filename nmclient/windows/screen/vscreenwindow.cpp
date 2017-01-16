#include "vscreenwindow.h"

#include <QPainter>

VScreenWindow::VScreenWindow(QWidget *parent) : QWidget(parent)
{
}

void VScreenWindow::setImage(const QImage &image)
{
    _snapshot = image;

    update();
}

void VScreenWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawImage(0, 0, _snapshot.scaled(width(), height()));
}
