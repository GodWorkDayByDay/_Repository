#include "gallery_widget.h"
#include <QCoreApplication>
#include <QPen>
#include <QDateTime>
#include <qdebug.h>

GalleryWidget::GalleryWidget(QWidget *parent) : QWidget(parent)
{
    //setWindowTitle(QString::fromLocal8Bit("模板裁剪面板"));
    setWindowTitle(QObject::trUtf8("模板裁剪面板"));

    m_saveMode = 0;
    m_screenWidth = 640;
    m_screenHeight = 480;
    setMouseTracking(true);
    setWindowState(Qt::WindowActive);

    m_currentSelectRect   = QRect(0, 0, 0, 0);
    m_currentCaptureState = NotCapture;
    m_stretchRectState    = NotSelect;
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
    m_painter.begin(this);
    m_painter.setPen(QPen(QColor(0, 180, 255), 1, Qt::SolidLine, Qt::FlatCap));
    m_painter.drawPixmap(0, 0, width(), height(), m_savedImage);

    switch (m_currentCaptureState)
    {
    case NotCapture:
        break;
    case BeginCaptureImage:
    case FinishCaptureImage:
    case BeginMoveCapturedImage:
    case FinishMoveCapturedImage:
    case BeginMoveStretchedRect:
    case FinishMoveStretchedRect:
        m_currentSelectRect = getSelectRect();
        m_painter.drawRect(m_currentSelectRect);
        drawStretchRect();
    default:
        break;
    }

    m_painter.end();

    QWidget::paintEvent(event);
}

void GalleryWidget::mousePressEvent(QMouseEvent *event)
{
    m_screenWidth = size().width();
    m_screenHeight = size().height();

    m_stretchRectState = getStretchRectState(event->pos());

    if (event->button() == Qt::LeftButton)
    {
        if (m_currentCaptureState == NotCapture)
        {
            m_currentCaptureState = BeginCaptureImage;
            m_beginPoint = event->pos();
        }
        else if (m_stretchRectState != NotSelect)
        {
            m_currentCaptureState = BeginMoveStretchedRect;
            setStretchCursorStyle(m_stretchRectState);
            m_beginMovePoint = event->pos();
        }
        else if (isPressPointInSelectRect(event->pos()))
        {
            m_currentCaptureState = BeginMoveCapturedImage;
            m_beginMovePoint = event->pos();
        }
    }

    QWidget::mousePressEvent(event);
}

void GalleryWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_currentCaptureState == BeginCaptureImage)
    {
        m_endPoint = event->pos();
        repaint();
    }
    else if (m_currentCaptureState == BeginMoveCapturedImage)
    {
        m_endMovePoint = event->pos();
        repaint();
    }
    else if (m_currentCaptureState == BeginMoveStretchedRect)
    {
        m_endMovePoint = event->pos();
        repaint();
    }

    StretchRectState stretchRectState = getStretchRectState(event->pos());
    if (stretchRectState != NotSelect)
        setStretchCursorStyle(stretchRectState);
    else if (isPressPointInSelectRect(event->pos()))
        setCursor(Qt::SizeAllCursor);
    else if (!isPressPointInSelectRect(event->pos()) && m_currentCaptureState != BeginMoveCapturedImage)
        setCursor(Qt::ArrowCursor);

    QWidget::mouseMoveEvent(event);
}

void GalleryWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_currentCaptureState == BeginCaptureImage)
    {
        m_currentCaptureState = FinishCaptureImage;
        m_endPoint = event->pos();
        repaint();
    }
    else if (m_currentCaptureState == BeginMoveCapturedImage)
    {
        m_currentCaptureState = FinishMoveCapturedImage;
        m_endMovePoint = event->pos();
        repaint();
    }
    else if (m_currentCaptureState == BeginMoveStretchedRect)
    {
        m_currentCaptureState = FinishMoveStretchedRect;
        m_endMovePoint = event->pos();
        repaint();
    }

    QWidget::mousePressEvent(event);
}

void GalleryWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        m_currentCaptureState = NotCapture;
        repaint();
    }

    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        QRect rect = getRect(m_beginPoint, m_endPoint);
        m_savedImage = m_savedImage.copy(widgetToImage(rect));

        if (m_saveMode == 1)
            m_savedImage.save(QCoreApplication::applicationDirPath() + "/model1.jpg");
        else if(m_saveMode == 2)
            m_savedImage.save(QCoreApplication::applicationDirPath() + "/model2.jpg");

        m_currentCaptureState = NotCapture;
        repaint();
    }

    QWidget::keyPressEvent(event);
}

QRect GalleryWidget::widgetToImage(QRect rect)
{
    QSizeF imageSize  = m_savedImage.size();

    qreal scaleWidth = m_screenWidth / imageSize.width();
    qreal scaleHeight = m_screenHeight / imageSize.height();

    QRect realRect;
    realRect.setX(rect.x() / scaleWidth);
    realRect.setY(rect.y() / scaleHeight);
    realRect.setWidth(rect.width() / scaleWidth);
    realRect.setHeight(rect.height() / scaleHeight);

    return realRect;
}

QRect GalleryWidget::getRect(QPoint beginPoint, QPoint endPoint)
{
    int width  = qAbs(beginPoint.x() - endPoint.x());
    int height = qAbs(beginPoint.y() - endPoint.y());
    int x      = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
    int y      = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();

    QRect rect(x, y, width, height);

    if (rect.width() == 0)
        rect.setWidth(2);

    if (rect.height() == 0)
        rect.setHeight(2);

    return rect;
}

QRect GalleryWidget::getMoveRect()
{
    QPoint movePoint  = getMovePoint();
    QPoint beginPoint = m_beginPoint + movePoint;
    QPoint endPoint   = m_endPoint + movePoint;
    if (m_currentCaptureState == FinishMoveCapturedImage)
    {
        m_beginPoint = beginPoint;
        m_endPoint   = endPoint;
    }

    return getRect(beginPoint, endPoint);
}

QRect GalleryWidget::getStretchRect()
{
    QRect stretchRect;
    QRect currentRect = getRect(m_beginPoint, m_endPoint);

    if (m_endMovePoint.x() > m_screenWidth - 1)
        m_endMovePoint.setX(m_screenWidth - 1);
    else if (m_endMovePoint.x() < 1)
        m_endMovePoint.setX(1);

    if (m_endMovePoint.y() > m_screenHeight - 1)
        m_endMovePoint.setY(m_screenHeight - 1);
    else if (m_endMovePoint.y() < 1)
        m_endMovePoint.setY(1);

    switch (m_stretchRectState)
    {
    case NotSelect:
        stretchRect = getRect(m_beginPoint, m_endPoint);
        break;
    case TopLeft:
        stretchRect = getRect(currentRect.bottomRight(), m_endMovePoint);
        break;
    case TopRight:
    {
        QPoint beginPoint = QPoint(currentRect.topLeft().x(), m_endMovePoint.y());
        QPoint endPoint = QPoint(m_endMovePoint.x(), currentRect.bottomRight().y());
        stretchRect = getRect(beginPoint, endPoint);
        break;
    }
    case BottomLeft:
    {
        QPoint beginPoint = QPoint(m_endMovePoint.x() , currentRect.topLeft().y());
        QPoint endPoint = QPoint(currentRect.bottomRight().x(), m_endMovePoint.y());
        stretchRect = getRect(beginPoint, endPoint);
        break;
    }
    case BottomRight:
        stretchRect = getRect(currentRect.topLeft(), m_endMovePoint);
        break;
    case LeftCenter:
    {
        QPoint beginPoint = QPoint(m_endMovePoint.x(), currentRect.topLeft().y());
        stretchRect = getRect(beginPoint, currentRect.bottomRight());
        break;
    }
    case TopCenter:
    {
        QPoint beginPoint = QPoint(currentRect.topLeft().x(), m_endMovePoint.y());
        stretchRect = getRect(beginPoint, currentRect.bottomRight());
        break;
    }
    case RightCenter:
    {
        QPoint endPoint = QPoint(m_endMovePoint.x(), currentRect.bottomRight().y());
        stretchRect = getRect(currentRect.topLeft(), endPoint);
        break;
    }
    case BottomCenter:
    {
        QPoint endPoint = QPoint(currentRect.bottomRight().x(), m_endMovePoint.y());
        stretchRect = getRect(currentRect.topLeft(), endPoint);
        break;
    }
    }

    if (m_currentCaptureState == FinishMoveStretchedRect)
    {
        m_beginPoint = stretchRect.topLeft();
        m_endPoint = stretchRect.bottomRight();
    }

    return stretchRect;
}

bool GalleryWidget::isPressPointInSelectRect(QPoint point)
{
    if (m_currentSelectRect.contains(point))
        return true;

    return false;
}

QRect GalleryWidget::getSelectRect()
{
    if (m_currentCaptureState == BeginCaptureImage || m_currentCaptureState == FinishCaptureImage)
        return getRect(m_beginPoint, m_endPoint);
    else if (m_currentCaptureState == BeginMoveCapturedImage || m_currentCaptureState == FinishMoveCapturedImage)
        return getMoveRect();
    else if (m_currentCaptureState == BeginMoveStretchedRect || m_currentCaptureState == FinishMoveStretchedRect)
        return getStretchRect();

    return QRect(0, 0, 0, 0);
}

QPoint GalleryWidget::getMovePoint()
{
    QPoint movePoint = m_endMovePoint - m_beginMovePoint;
    QRect currentRect = getRect(m_beginPoint, m_endPoint);

    if (currentRect.topLeft().x() + movePoint.x() < 0)
        movePoint.setX(0 - currentRect.topLeft().x());

    if (currentRect.topLeft().y() + movePoint.y() < 0)
        movePoint.setY(0 - currentRect.topLeft().y());

    if (currentRect.bottomRight().x() + movePoint.x() > m_screenWidth)
        movePoint.setX(m_screenWidth - currentRect.bottomRight().x());

    if (currentRect.bottomRight().y() + movePoint.y() > m_screenHeight)
        movePoint.setY(m_screenHeight - currentRect.bottomRight().y());

    return movePoint;
}

StretchRectState GalleryWidget::getStretchRectState(QPoint point)
{
    StretchRectState stretchRectState = NotSelect;

    if (m_topLeftRect.contains(point))
        stretchRectState = TopLeft;
    else if (m_topCenterRect.contains(point))
        stretchRectState = TopCenter;
    else if (m_topRightRect.contains(point))
        stretchRectState = TopRight;
    else if (m_rightCenterRect.contains(point))
        stretchRectState = RightCenter;
    else if (m_bottomRightRect.contains(point))
        stretchRectState = BottomRight;
    else if (m_bottomCenterRect.contains(point))
        stretchRectState = BottomCenter;
    else if (m_bottomLeftRect.contains(point))
        stretchRectState = BottomLeft;
    else if (m_leftCenterRect.contains(point))
        stretchRectState = LeftCenter;

    return stretchRectState;
}

void GalleryWidget::setStretchCursorStyle(StretchRectState state)
{
    switch (state)
    {
    case NotSelect:
        setCursor(Qt::ArrowCursor);
        break;
    case TopLeft:
    case BottomRight:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case TopRight:
    case BottomLeft:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case LeftCenter:
    case RightCenter:
        setCursor(Qt::SizeHorCursor);
        break;
    case TopCenter:
    case BottomCenter:
        setCursor(Qt::SizeVerCursor);
        break;
    default:
        break;
    }
}

void GalleryWidget::drawStretchRect()
{
    QColor color = QColor(0, 174, 255);

    QPoint topLeft     = m_currentSelectRect.topLeft();
    QPoint topRight    = m_currentSelectRect.topRight();
    QPoint bottomLeft  = m_currentSelectRect.bottomLeft();
    QPoint bottomRight = m_currentSelectRect.bottomRight();

    QPoint leftCenter   = QPoint(topLeft.x(), (topLeft.y() + bottomLeft.y()) / 2);
    QPoint topCenter    = QPoint((topLeft.x() + topRight.x()) / 2, topLeft.y());
    QPoint rightCenter  = QPoint(topRight.x(), leftCenter.y());
    QPoint bottomCenter = QPoint(topCenter.x(), bottomLeft.y());

    m_topLeftRect     = QRect(topLeft.x() - 6 / 2, topLeft.y() - 6 / 2, 6, 6);
    m_topRightRect    = QRect(topRight.x() - 6 / 2, topRight.y() - 6 / 2, 6, 6);
    m_bottomLeftRect  = QRect(bottomLeft.x() - 6 / 2, bottomLeft.y() - 6 / 2, 6, 6);
    m_bottomRightRect = QRect(bottomRight.x() - 6 / 2, bottomRight.y() - 6 / 2, 6, 6);

    m_leftCenterRect   = QRect(leftCenter.x() - 6 / 2, leftCenter.y() - 6 / 2, 6, 6);
    m_topCenterRect    = QRect(topCenter.x() - 6 / 2, topCenter.y() - 6 / 2, 6, 6);
    m_rightCenterRect  = QRect(rightCenter.x() - 6 / 2, rightCenter.y() - 6 / 2, 6, 6);
    m_bottomCenterRect = QRect(bottomCenter.x() - 6 / 2, bottomCenter.y() - 6 / 2, 6, 6);

    m_painter.fillRect(m_topLeftRect, color);
    m_painter.fillRect(m_topRightRect, color);
    m_painter.fillRect(m_bottomLeftRect, color);
    m_painter.fillRect(m_bottomRightRect, color);
    m_painter.fillRect(m_leftCenterRect, color);
    m_painter.fillRect(m_topCenterRect, color);
    m_painter.fillRect(m_rightCenterRect, color);
    m_painter.fillRect(m_bottomCenterRect, color);
}
