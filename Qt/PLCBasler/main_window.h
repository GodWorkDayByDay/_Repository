#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <pylon/PylonIncludes.h>
#include <pylon/PylonGUI.h>

#include "gallery_widget.h"
#include "plc_widget.h"
#include <QMainWindow>
#include <QSplitter>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();

private slots:
    void openCamera();
    void closeCamera();
    void saveCurrentImage();

private:
    QSplitter     *m_mainWidget;
    PLCWidget     *m_plcWidget;
    GalleryWidget *m_galleryWidget;
    QFrame        *m_cameraWidget;
    QLabel        *m_statusLabel;

    QPushButton   *m_openPushButton;
    QPushButton   *m_closePushButton;
    QPushButton   *m_savePushButton;

    bool m_isClosed;
    bool m_isSaved;
};

#endif // MAIN_WINDOW_H
