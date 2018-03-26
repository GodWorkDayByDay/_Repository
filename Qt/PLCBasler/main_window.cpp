#include "main_window.h"
#include <QStatusBar>
#include <QGridLayout>
#include <QDebug>
#include <QTest>
#include <SampleImageCreator.h> // 这里边是函数定义，不是声明
#include <pylon/gige/BaslerGigEInstantCamera.h>

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent)
{
    m_isClosed = m_isSaved = false;
    m_triggerModeIsON = false;

    m_mainWidget = new QSplitter(Qt::Horizontal);

    m_plcWidget     = new PLCWidget(m_mainWidget);
    m_galleryWidget = new GalleryWidget;
    m_cameraWidget  = new QFrame(m_mainWidget);

    m_cameraWidget->setMinimumSize(250, 400);
    m_cameraWidget->setFrameStyle(QFrame::Panel | QFrame::Raised);

    m_exposureTimeLabel   = new QLabel(tr("Exposure Time"));
    m_gainLabel           = new QLabel(tr("Gain"));
    m_exposureTimeSpinBox = new QSpinBox;
    m_gainSpinBox         = new QSpinBox;
    m_exposureTimeSpinBox->setRange(1, 65535);
    m_gainSpinBox->setRange(1, 255);
    m_exposureTimeSpinBox->setValue(5000);
    m_gainSpinBox->setValue(136);

    m_triggerModeLabel = new QLabel(tr("Trigger Mode"));
    m_triggerModeComboBox = new QComboBox;
    m_triggerModeComboBox->addItem(tr("OFF"));
    m_triggerModeComboBox->addItem(tr("ON"));
    m_triggerModeComboBox->setEnabled(false);

    m_openPushButton  = new QPushButton(tr("Open Camera"));
    m_closePushButton = new QPushButton(tr("Close Camera"));
    m_savePushButton  = new QPushButton(tr("Save Image"));
    m_openPushButton->setEnabled(true);
    m_closePushButton->setEnabled(false);
    m_savePushButton->setEnabled(false);

    QGridLayout *gLayout = new QGridLayout(m_cameraWidget);
    gLayout->addWidget(m_exposureTimeLabel, 0, 0, 1, 1);
    gLayout->addWidget(m_exposureTimeSpinBox, 0, 1, 1, 1);
    gLayout->addWidget(m_gainLabel, 1, 0, 1, 1);
    gLayout->addWidget(m_gainSpinBox, 1, 1, 1, 1);
    gLayout->addWidget(m_triggerModeLabel, 2, 0, 1, 1);
    gLayout->addWidget(m_triggerModeComboBox, 2, 1, 1, 1);
    gLayout->addWidget(m_openPushButton, 3, 0, 1, 2);
    gLayout->addWidget(m_closePushButton, 4, 0, 1, 2);
    gLayout->addWidget(m_savePushButton, 5, 0, 1, 2);

    m_mainWidget->setStretchFactor(0, 6);
    m_mainWidget->setStretchFactor(1, 4);

    setCentralWidget(m_mainWidget);

    m_statusLabel = new QLabel(tr("Welcome......"));
    statusBar()->addWidget(m_statusLabel);

    connect(m_triggerModeComboBox, SIGNAL(currentIndexChanged(int)), SLOT(triggerModeChanged(int)));
    connect(m_openPushButton, SIGNAL(clicked(bool)), SLOT(openCamera()));
    connect(m_closePushButton, SIGNAL(clicked(bool)), SLOT(closeCamera()));
    connect(m_savePushButton, SIGNAL(clicked(bool)), SLOT(saveCurrentImage()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::grabOne()
{
//    using namespace Pylon;
//    CGrabResultPtr ptrGrabResult;
//    CInstantCamera Camera( CTlFactory::GetInstance().CreateFirstDevice());

//    if ( Camera.GrabOne( 1000, ptrGrabResult))
//    {
//        // The pylon grab result smart pointer classes provide a cast operator to the IImage
//        // interface. This makes it possible to pass a grab result directly to the
//        // function that saves an image to disk.
//        CImagePersistence::Save( ImageFileFormat_Png, "GrabbedImage.png", ptrGrabResult);
//    }
}

void MainWindow::triggerModeChanged(int index)
{
    if (index == 0)
        m_triggerModeIsON = false;
    else
        m_triggerModeIsON = true;
}
/*
void MainWindow::openCamera()
{
    m_isClosed = false;
    m_isSaved  = false;

    m_openPushButton->setAttribute(Qt::WA_UnderMouse, false);
    m_openPushButton->setEnabled(false);
    m_closePushButton->setEnabled(true);
    m_savePushButton->setEnabled(true);
    m_exposureTimeSpinBox->setEnabled(false);
    m_gainSpinBox->setEnabled(false);
    m_triggerModeComboBox->setEnabled(true);

    m_statusLabel->setText(tr("Start grabbing, please wait......"));
    QTest::qWait(200);

    using namespace Pylon;
    using namespace Basler_GigECameraParams;

    const uint32_t c_countOfImagesToGrab = 1000;
    int num = 0;

    PylonInitialize();

    try
    {
        CDeviceInfo info;
        info.SetDeviceClass(CBaslerGigEInstantCamera::DeviceClass());
        CBaslerGigEInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice(info));

        camera.Open();

        camera.GainAuto.SetValue(GainAuto_Off);
        camera.GainRaw.SetValue(m_gainSpinBox->value());
        camera.ExposureAuto.SetValue(ExposureAuto_Off);
        camera.ExposureTimeRaw.SetValue(m_exposureTimeSpinBox->value());

        camera.StartGrabbing(c_countOfImagesToGrab, GrabStrategy_LatestImageOnly);

        CGrabResultPtr ptrGrabResult;
        while (camera.IsGrabbing())
        {
            camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);

            if (ptrGrabResult->GrabSucceeded())
            {
                num++;

                m_statusLabel->setText("You are grabbing " + QString::number(num));
                CPylonImage image;
                image.AttachGrabResultBuffer(ptrGrabResult);

                do
                {
                    if (m_isSaved)
                    {
                        QString path = QCoreApplication::applicationDirPath() + "/save.png";
                        QByteArray ba = path.toLatin1();
                        CImagePersistence::Save(ImageFileFormat_Png, ba.data(), ptrGrabResult);

                        m_isSaved = false;

                        QPixmap pixmap(QCoreApplication::applicationDirPath() + "/save.png");
                        m_galleryWidget->setImage(pixmap);
                        m_galleryWidget->repaint();
                        m_galleryWidget->show();
                    }

                    QTest::qWait(200);
                }while (m_triggerModeIsON);
            }
            else
                m_statusLabel->setText("Error image grab failed: " + QString(ptrGrabResult->GetErrorDescription().c_str()));

            if (m_isClosed)
            {
                camera.Close();
                camera.StopGrabbing();
                m_statusLabel->setText(tr("Camera has been closed!"));
            }
        }
    }
    catch (const GenericException &e)
    {
        m_statusLabel->setText("An exception occurred." + QString(e.GetDescription()));
    }

    PylonTerminate();
}
*/
void MainWindow::openCamera()
{
    m_isClosed = false;
    m_isSaved  = false;

    m_openPushButton->setAttribute(Qt::WA_UnderMouse, false);
    m_openPushButton->setEnabled(false);
    m_closePushButton->setEnabled(true);
    m_savePushButton->setEnabled(true);
    m_exposureTimeSpinBox->setEnabled(false);
    m_gainSpinBox->setEnabled(false);
    m_triggerModeComboBox->setEnabled(true);

    m_statusLabel->setText(tr("Start grabbing, please wait......"));
    QTest::qWait(200);

    using namespace Pylon;
    using namespace Basler_GigECameraParams;

    const uint32_t c_countOfImagesToGrab = 1000;
    int num = 0;

    PylonInitialize();

    try
    {
        CPylonImageWindow window;
        window.Create(0, 200, 200, 500, 500);
        window.Show();

        CDeviceInfo info;
        info.SetDeviceClass(CBaslerGigEInstantCamera::DeviceClass());
        CBaslerGigEInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice(info));

        camera.Open();

        camera.GainAuto.SetValue(GainAuto_Off);
        camera.GainRaw.SetValue(m_gainSpinBox->value());
        camera.ExposureAuto.SetValue(ExposureAuto_Off);
        camera.ExposureTimeRaw.SetValue(m_exposureTimeSpinBox->value());

        camera.StartGrabbing(c_countOfImagesToGrab, GrabStrategy_LatestImageOnly);

        CGrabResultPtr ptrGrabResult;
        while (camera.IsGrabbing())
        {
            camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);

            if (ptrGrabResult->GrabSucceeded())
            {
                num++;

                m_statusLabel->setText("You are grabbing " + QString::number(num));
                CPylonImage image;
                image.AttachGrabResultBuffer(ptrGrabResult);
                window.SetImage(image);

                do
                {
                    if (m_isSaved)
                    {
                        QString path = QCoreApplication::applicationDirPath() + "/save.png";
                        QByteArray ba = path.toLatin1();
                        CImagePersistence::Save(ImageFileFormat_Png, ba.data(), ptrGrabResult);

                        m_isSaved = false;

                        QPixmap pixmap(QCoreApplication::applicationDirPath() + "/save.png");
                        m_galleryWidget->setImage(pixmap);
                        m_galleryWidget->repaint();
                        m_galleryWidget->show();
                    }

                    QTest::qWait(200);
                }while (m_triggerModeIsON);
            }
            else
                m_statusLabel->setText("Error image grab failed: " + QString(ptrGrabResult->GetErrorDescription().c_str()));

            if (m_isClosed)
            {
                camera.Close();
                camera.StopGrabbing();
                m_statusLabel->setText(tr("Camera has been closed!"));
            }
        }
    }
    catch (const GenericException &e)
    {
        m_statusLabel->setText("An exception occurred." + QString(e.GetDescription()));
    }

    PylonTerminate();
}

void MainWindow::closeCamera()
{
    m_isClosed = true;
    m_openPushButton->setEnabled(true);
    m_closePushButton->setAttribute(Qt::WA_UnderMouse, false);
    m_closePushButton->setEnabled(false);
    m_savePushButton->setEnabled(false);
    m_exposureTimeSpinBox->setEnabled(true);
    m_gainSpinBox->setEnabled(true);
    m_triggerModeComboBox->setEnabled(false);
}

void MainWindow::saveCurrentImage()
{
    m_isSaved = true;
}
