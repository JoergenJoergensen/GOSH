#include <QApplication>
#include "home.h"
#include "threads.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Home w;

    //GoshThreadInitSpeedControl();
    //GoshThreadInitCAN();

    w.setWindowState(Qt::WindowFullScreen);
    w.show();

    return a.exec();
}
