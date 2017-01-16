#include <QApplication>
#include <QDesktopWidget>

#include "windows/login/vloginwindow.h"

int main(int arcv, char *argv[])
{
    QApplication application(arcv, argv);
    VLoginWindow login_window;

    login_window.setGeometry(QApplication::desktop()->width() / 2 - (257 / 2), QApplication::desktop()->height() / 2 - (56), 257, 112);
    login_window.show();

    return application.exec();
}
