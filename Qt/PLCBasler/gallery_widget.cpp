#include "gallery_widget.h"
#include <QCoreApplication>
#include <QPen>
#include <QPainter>
#include <QDateTime>
#include <qdebug.h>

GalleryWidget::GalleryWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(500, 500);
    setMouseTracking(true);
    setWindowState(Qt::WindowActive);

    m_isMousePress = false;

    m_savedImage.load(QCoreApplication::applicationDirPath() + "/save.png");
}

GalleryWidget::~GalleryWidget()
{
}

void GalleryWidget::setImage(QPixmap &pixmap)
{
    m_savedImage = pixmap;
}

void GalleryWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), m_savedImage);

    if (m_isMousePress)
    {
        painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap));
        painter.drawRect(getRect());
    }

    QWidget::paintEvent(event);
}

void GalleryWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isMousePress = true;
        m_beginPos = event->pos();
    }

    QWidget::mousePressEvent(event);
}

void GalleryWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isMousePress)
    {
        m_endPos = event->pos();
        repaint();
    }

    QWidget::mouseMoveEvent(event);
}

void GalleryWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_endPos = event->pos();
    m_isMousePress = false;

    QWidget::mousePressEvent(event);
}

void GalleryWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        m_isMousePress = false;
        repaint();
    }

    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        m_savedImage = m_savedImage.copy(getRect());
        QString suffix = QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + ".png";
        m_savedImage.save(QCoreApplication::applicationDirPath() + "/save_capture_" + suffix);
        m_isMousePress = false;
        repaint();
    }

    QWidget::keyPressEvent(event);
}

QRect GalleryWidget::getRect()
{
    int width  = qAbs(m_beginPos.x() - m_endPos.x());
    int height = qAbs(m_beginPos.y() - m_endPos.y());
    int x      = m_beginPos.x() < m_endPos.x() ? m_beginPos.x() : m_endPos.x();
    int y      = m_beginPos.y() < m_endPos.y() ? m_beginPos.y() : m_endPos.y();

    QRect rect(x, y, width, height);

    if (rect.width() == 0)
        rect.setWidth(2);

    if (rect.height() == 0)
        rect.setHeight(2);

    return rect;
}
