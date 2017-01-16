#include <QApplication>

#include "core/vcore.h"

int main(int arcv, char *argv[])
{
    QApplication app(arcv, argv);

    VCore *core = new VCore();

    core->start();

    return app.exec();
}
