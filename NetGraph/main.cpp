#include "netgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetGUI w;
    w.show();

    return a.exec();
}
