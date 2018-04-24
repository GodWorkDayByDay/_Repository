#include "main_window.h"
#include <QApplication>
//#include <QTextCodec>

typedef unsigned char BYTE;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QTextCodec *codec = QTextCodec::codecForName("GBK");
//    QTextCodec::setCodecForLocale(codec);

    MainWindow w;
    w.setFont(QFont("Consolas", 11));
    w.show();

    return a.exec();
}
