#ifndef GALLERY_WIDGET_H
#define GALLERY_WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QRect>

class GalleryWidget : public QWidget
{
public:
    explicit GalleryWidget(QWidget *parent = 0);
    ~GalleryWidget();
    void setImage(QPixmap &pixmap);

private:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    QRect getRect();

private:
    bool     m_isMousePress;
    QPoint   m_beginPos;
    QPoint   m_endPos;
    QPixmap  m_savedImage;
};

#endif // GALLERY_WIDGET_H
