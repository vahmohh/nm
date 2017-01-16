#ifndef VCLIENTWINDOW_H
#define VCLIENTWINDOW_H

#include <QWidget>

class QPushButton;
class QLineEdit;
class QLabel;

class VDiagramWindow;
class VScreenWindow;

class VClientWindow : public QWidget
{
    Q_OBJECT
public:
    enum Themes {
        Blue,
        Red
    };

    VClientWindow(Themes themes, QWidget *parent = 0);

    void update(quint64 send, quint64 receive);

    VScreenWindow *_screen_window;

    quint64 _id;

private:
    quint64 _last_send, _last_receive;
    QPushButton *_screen_button, *_turn_off_button;
    QLineEdit *_limit_edit;
    QLabel *_limit_lable;

    VDiagramWindow *_diagram_window;

    uint _alarm_limit;

    void paintEvent(QPaintEvent *);

private slots:
    void screenButtonClickSlot();
    void turnOffButtonClickSlot();

    void textChangedSlot(QString text);

signals:
    void turnOffButtonClickSignal(quint64 id);
};

#endif // VCLIENTWINDOW_H
