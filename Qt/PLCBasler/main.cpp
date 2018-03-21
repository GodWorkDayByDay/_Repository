#include "main_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFont(QFont("Consolas", 12));
    w.show();

    return a.exec();
}
