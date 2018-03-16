#include "plc_widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PLCWidget w;
    w.show();

    return a.exec();
}
