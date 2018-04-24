#include "image_window.h"
#include <QPainter>
#include <QDebug>

ImageWindow::ImageWindow(QWidget *parent) : QWidget(parent)
{
    //setWindowTitle(QString::fromLocal8Bit("相机"));
    setWindowTitle(trUtf8("相机"));
}

ImageWindow::~ImageWindow()
{

}

void ImageWindow::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.drawPixmap(0, 0, width(), height(), m_image);
    paint.setPen(QPen(QColor(0, 180, 255), 1, Qt::SolidLine, Qt::FlatCap));
    paint.drawLine(0, height() / 2, width(), height() / 2);
    paint.drawLine(width() / 2, 0, width() / 2, height());
}
