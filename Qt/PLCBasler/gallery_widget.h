#ifndef GALLERY_WIDGET_H
#define GALLERY_WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QRect>
#include <QPainter>

enum CaptureState { NotCapture = 0,
                    BeginCaptureImage,
                    FinishCaptureImage,
                    BeginMoveCapturedImage,
                    FinishMoveCapturedImage,
                    BeginMoveStretchedRect,
                    FinishMoveStretchedRect };

enum StretchRectState { NotSelect = 0,
                        TopLeft,
                        TopRight,
                        BottomLeft,
                        BottomRight,
                        LeftCenter,
                        TopCenter,
                        RightCenter,
                        BottomCenter };


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
    QRect widgetToImage(QRect rect);
    QRect getRect(QPoint beginPoint, QPoint endPoint);
    QRect getMoveRect();
    QRect getStretchRect();
    bool isPressPointInSelectRect(QPoint Point);
    QRect getSelectRect();
    QPoint getMovePoint();
    StretchRectState getStretchRectState(QPoint point);
    void setStretchCursorStyle(StretchRectState state);
    void drawStretchRect();

public:
    int  m_saveMode; // 0 is save source.jpg, 1 is save model1.jpg, 2 is save model2.jpg

private:
    int      m_screenWidth;
    int      m_screenHeight;
    QPoint   m_beginPoint;
    QPoint   m_endPoint;
    QPoint   m_beginMovePoint;
    QPoint   m_endMovePoint;
    QPixmap  m_savedImage;
    QRect    m_currentSelectRect;
    QPainter m_painter;

    QRect m_topLeftRect;
    QRect m_topRightRect;
    QRect m_bottomLeftRect;
    QRect m_bottomRightRect;
    QRect m_leftCenterRect;
    QRect m_topCenterRect;
    QRect m_rightCenterRect;
    QRect m_bottomCenterRect;

    CaptureState     m_currentCaptureState;
    StretchRectState m_stretchRectState;
};

#endif // GALLERY_WIDGET_H
