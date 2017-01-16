#ifndef VSCREENWINDOW_H
#define VSCREENWINDOW_H

#include <QWidget>

class VScreenWindow : public QWidget
{
    Q_OBJECT
public:
    VScreenWindow(QWidget *parent = 0);

    void setImage(const QImage &image);

private:
    void paintEvent(QPaintEvent *);

    QImage _snapshot;

};

#endif // VSCREENWINDOW_H
