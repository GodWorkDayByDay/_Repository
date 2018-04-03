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
#include <QSpinBox>
#include <QComboBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();

private slots:
    void triggerModeChanged(int index);
    void openCamera();
    void closeCamera();
    void saveCurrentImage();
    void softwareTrigger();
    void openCamera1();

private:
    QSplitter     *m_mainWidget;
    PLCWidget     *m_plcWidget;
    GalleryWidget *m_galleryWidget;
    QFrame        *m_cameraWidget;
    QLabel        *m_statusLabel;
    QLabel        *m_exposureTimeLabel;
    QLabel        *m_gainLabel;
    QLabel        *m_triggerModeLabel;
    QSpinBox      *m_exposureTimeSpinBox;
    QSpinBox      *m_gainSpinBox;
    QComboBox     *m_triggerModeComboBox;

    QPushButton   *m_openPushButton;
    QPushButton   *m_closePushButton;
    QPushButton   *m_savePushButton;

    bool m_isClosed;
    bool m_isSaved;
    bool m_isSoftwareTriggered;
    int  m_triggerModeMask;
};

#endif // MAIN_WINDOW_H
