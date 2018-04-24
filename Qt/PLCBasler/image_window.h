#ifndef IMAGE_WINDOW_H
#define IMAGE_WINDOW_H

#include <QWidget>
#include <QPixmap>

class ImageWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWindow(QWidget *parent = 0);
    ~ImageWindow();

protected:
    virtual void paintEvent(QPaintEvent *event);

public:
    QPixmap m_image;
};

#endif // IMAGE_WINDOW_H
