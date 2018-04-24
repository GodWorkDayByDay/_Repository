#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <pylon/PylonIncludes.h>
#include <pylon/PylonGUI.h>

#include "image_window.h"
#include "gallery_widget.h"
#include "plc.h"
#include "milc.h"
#include <QMainWindow>
#include <QSplitter>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QCloseEvent>
#include <QGroupBox>
#include <QTabWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();
    bool isExist(QString name);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    bool returnData(long & x, long & y);
    void openCamera();
    void closeCamera();
    void calculate();
    void adminBtn();
    void showAdminControl();
    void saveModeToNegative1();
    void saveModeTo0();
    void saveModeTo1();
    void saveModeTo2();
    void test();
    void comboBoxChanged(int id);

private:
    ImageWindow   *m_imageWindow;
    GalleryWidget *m_galleryWidget;

    PLC plc;
    bool isFirst;
    MILC *m_mil;

    QTabWidget    *m_tabWidget;

    QWidget       *m_cameraWidget;
    QPushButton   *m_openPushButton;
    QPushButton   *m_closePushButton;
    QLabel        *m_returnLabel;
    QLabel        *m_returnDataLabel;
    QLabel        *m_statusLabel;
    QLabel        *m_statusDataLabel;
    QPushButton   *m_adminPushButton;

    QWidget       *m_correctionWidget;
    QPushButton   *m_saveModelPushButton;
    QPushButton   *m_saveSourcePushButton;
    QPushButton   *m_calculatePushButton;
    QLabel        *m_hDistanceLabel;
    QLineEdit     *m_unitLineEdit;

    QWidget       *m_settingWidget;
    QLabel        *m_exposureTimeLabel;
    QLabel        *m_gainLabel;
    QSpinBox      *m_exposureTimeSpinBox;
    QSpinBox      *m_gainSpinBox;
    QPushButton   *m_saveModel1PushButton; // save model1.jpg
    QPushButton   *m_saveModel2Pushbutton; // save model2.jpg

    QWidget       *m_manualWidget;
    QComboBox     *m_comboBox;
    QPushButton   *m_savePushButton;
    QPushButton   *m_getPushButton;

    bool m_isClosed;
    int  m_saveMode; // -1 is save model.jpg, 0 is save source.jpg, 1 is save model1.jpg, 2 is save model2.jpg, -2 is do nothing
    int  m_cameraMode; // 0 is nomal or 1 is sortware trigger
};

#endif // MAIN_WINDOW_H
