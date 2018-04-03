#include "main_window.h"
#include <QStatusBar>
#include <QGridLayout>
#include <QDebug>
#include <QElapsedTimer>
#include <QCoreApplication>
#include <SampleImageCreator.h>
#include <HardwareTriggerConfiguration.h>
#include <SoftwareTriggerConfiguration.h>
#include <pylon/gige/BaslerGigEInstantCamera.h>
#include <ConfigurationEventPrinter.h>
#include <ImageEventPrinter.h>

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent)
{
    m_isSoftwareTriggered = m_isClosed = m_isSaved = false;
    m_triggerModeMask = 0; // 0->OFF, 1->SoftwareTrigger ON, 2->HardwareTrigger ON

    m_mainWidget = new QSplitter(Qt::Horizontal);

    m_plcWidget     = new PLCWidget(m_mainWidget);
    m_galleryWidget = new GalleryWidget;
    m_cameraWidget  = new QFrame(m_mainWidget);

    m_cameraWidget->setMinimumSize(350, 400);
    m_cameraWidget->setFrameStyle(QFrame::Panel | QFrame::Raised);

    m_exposureTimeLabel   = new QLabel(tr("Exposure Time"));
    m_gainLabel           = new QLabel(tr("Gain"));
    m_exposureTimeSpinBox = new QSpinBox;
    m_gainSpinBox         = new QSpinBox;
    m_exposureTimeSpinBox->setRange(1, 65535);
    m_gainSpinBox->setRange(1, 255);
    m_exposureTimeSpinBox->setValue(5000);
    m_gainSpinBox->setValue(231);

    m_triggerModeLabel = new QLabel(tr("Trigger Mode"));
    m_triggerModeComboBox = new QComboBox;
    m_triggerModeComboBox->addItem(tr("OFF"));
    m_triggerModeComboBox->addItem(tr("Software Trigger"));
    m_triggerModeComboBox->addItem(tr("Hardware Trigger"));

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
    connect(m_openPushButton, SIGNAL(clicked(bool)), SLOT(openCamera1()));
    connect(m_closePushButton, SIGNAL(clicked(bool)), SLOT(closeCamera()));
    connect(m_savePushButton, SIGNAL(clicked(bool)), SLOT(saveCurrentImage()));
    connect(m_plcWidget, SIGNAL(emitSoftwareTrigger()), SLOT(softwareTrigger()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::triggerModeChanged(int index)
{
    m_triggerModeMask = index;
}

void MainWindow::openCamera1()
{
    m_isClosed = false;
    m_isSaved  = false;

    m_openPushButton->setAttribute(Qt::WA_UnderMouse, false);
    m_openPushButton->setEnabled(false);
    m_closePushButton->setEnabled(true);
    m_savePushButton->setEnabled(true);
    m_exposureTimeSpinBox->setEnabled(false);
    m_gainSpinBox->setEnabled(false);

    m_statusLabel->setText(tr("Start grabbing, please wait......"));

    QElapsedTimer t;
    t.start();
    while (t.elapsed() <= 200)
        QCoreApplication::processEvents();

    using namespace Pylon;
    using namespace Basler_GigECameraParams;

    const uint32_t c_countOfImagesToGrab = 1000;

    PylonInitialize();

    CPylonImageWindow window;
    window.Create(0, 0, 0, 500, 500);
    window.Show();

    CDeviceInfo info;
    info.SetDeviceClass(CBaslerGigEInstantCamera::DeviceClass());

    int num = 0;
    CGrabResultPtr ptrGrabResult;
    try
    {
        while (!m_isClosed)
        {
            switch (m_triggerModeMask)
            {
            case 0:
            {
                CBaslerGigEInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice(info));
                camera.Open();
                camera.GainAuto.SetValue(GainAuto_Off);
                camera.GainRaw.SetValue(m_gainSpinBox->value());
                camera.ExposureAuto.SetValue(ExposureAuto_Off);
                camera.ExposureTimeRaw.SetValue(m_exposureTimeSpinBox->value());
                camera.StartGrabbing(c_countOfImagesToGrab, GrabStrategy_LatestImageOnly);

                while (camera.IsGrabbing() && m_triggerModeMask == 0 && !m_isClosed)
                {
                    camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_Return);

                    if (ptrGrabResult->GrabSucceeded())
                    {
                        num++;

                        m_statusLabel->setText("You are grabbing " + QString::number(num));
                        CPylonImage image;
                        image.AttachGrabResultBuffer(ptrGrabResult);
                        window.SetImage(image);

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

                        QElapsedTimer t;
                        t.start();
                        while (t.elapsed() <= 200)
                            QCoreApplication::processEvents();
                    }
                    else
                        m_statusLabel->setText("Error image grab failed: " + QString(ptrGrabResult->GetErrorDescription().c_str()));
                }

                camera.StopGrabbing();
                camera.Close();

                break;
            }
            case 1:
            {
                CBaslerGigEInstantCamera camera_software(CTlFactory::GetInstance().CreateFirstDevice(info));
                camera_software.RegisterConfiguration(new CSoftwareTriggerConfiguration, RegistrationMode_ReplaceAll, Cleanup_Delete);
                camera_software.Open();
                camera_software.GainAuto.SetValue(GainAuto_Off);
                camera_software.GainRaw.SetValue(m_gainSpinBox->value());
                camera_software.ExposureAuto.SetValue(ExposureAuto_Off);
                camera_software.ExposureTimeRaw.SetValue(m_exposureTimeSpinBox->value());
                camera_software.StartGrabbing(c_countOfImagesToGrab, GrabStrategy_LatestImageOnly);

                while (m_triggerModeMask == 1 && !m_isClosed)
                {
                    QCoreApplication::processEvents();

                    if (m_isSoftwareTriggered)
                    {
                        while(!camera_software.RetrieveResult(0, ptrGrabResult, TimeoutHandling_Return))
                            camera_software.ExecuteSoftwareTrigger();

                        num++;

                        m_statusLabel->setText("You are grabbing " + QString::number(num));
                        CPylonImage image;
                        image.AttachGrabResultBuffer(ptrGrabResult);
                        window.SetImage(image);

                        QString path = QCoreApplication::applicationDirPath() + "/save_software_trigger.png";
                        QByteArray ba = path.toLatin1();
                        CImagePersistence::Save(ImageFileFormat_Png, ba.data(), ptrGrabResult);

                        m_isSoftwareTriggered = false;

                        QPixmap pixmap(QCoreApplication::applicationDirPath() + "/save_software_trigger.png");
                        m_galleryWidget->setImage(pixmap);
                        m_galleryWidget->repaint();
                        m_galleryWidget->show();
                    }
                }

                camera_software.StopGrabbing();
                camera_software.Close();

                break;
            }
            case 2:
            {
                CBaslerGigEInstantCamera camera_hardware(CTlFactory::GetInstance().CreateFirstDevice(info));
                camera_hardware.RegisterConfiguration(new CHardwareTriggerConfiguration, RegistrationMode_ReplaceAll, Cleanup_Delete);
                camera_hardware.Open();
                camera_hardware.GainAuto.SetValue(GainAuto_Off);
                camera_hardware.GainRaw.SetValue(m_gainSpinBox->value());
                camera_hardware.ExposureAuto.SetValue(ExposureAuto_Off);
                camera_hardware.ExposureTimeRaw.SetValue(m_exposureTimeSpinBox->value());
                camera_hardware.StartGrabbing(c_countOfImagesToGrab, GrabStrategy_LatestImageOnly);

                while (m_triggerModeMask == 2 && !m_isClosed)
                {
                    QCoreApplication::processEvents();

                    if (camera_hardware.RetrieveResult(10, ptrGrabResult, TimeoutHandling_Return))
                    {
                        num++;

                        m_statusLabel->setText("You are grabbing " + QString::number(num));
                        CPylonImage image;
                        image.AttachGrabResultBuffer(ptrGrabResult);
                        window.SetImage(image);

                        QString path = QCoreApplication::applicationDirPath() + "/save_hardware_trigger.png";
                        QByteArray ba = path.toLatin1();
                        CImagePersistence::Save(ImageFileFormat_Png, ba.data(), ptrGrabResult);

                        QPixmap pixmap(QCoreApplication::applicationDirPath() + "/save_hardware_trigger.png");
                        m_galleryWidget->setImage(pixmap);
                        m_galleryWidget->repaint();
                        m_galleryWidget->show();
                    }
                }

                camera_hardware.StopGrabbing();
                camera_hardware.Close();

                break;
            }
            }
        }
    }
    catch (const GenericException &e)
    {
        m_statusLabel->setText("An exception occurred." + QString(e.GetDescription()));
        closeCamera();
    }

    m_statusLabel->setText(tr("Camera has been closed!"));

    PylonTerminate();
}

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

    m_statusLabel->setText(tr("Start grabbing, please wait......"));

    QElapsedTimer t;
    t.start();
    while (t.elapsed() <= 200)
        QCoreApplication::processEvents();

    using namespace Pylon;
    using namespace Basler_GigECameraParams;

    const uint32_t c_countOfImagesToGrab = 1000;
    int num = 0;

    PylonInitialize();

    try
    {
        CPylonImageWindow window;
        window.Create(0, 0, 0, 500, 500);
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
            if (m_triggerModeMask == 2)
            {
                camera.StopGrabbing();
                camera.Close();
                camera.RegisterConfiguration(new CHardwareTriggerConfiguration, RegistrationMode_ReplaceAll, Cleanup_Delete);
                camera.Open();
                camera.StartGrabbing(c_countOfImagesToGrab, GrabStrategy_LatestImageOnly);

                while (m_triggerModeMask == 2 && !m_isClosed)
                {
                    QCoreApplication::processEvents();

                    if (camera.RetrieveResult(10, ptrGrabResult, TimeoutHandling_Return))
                    {
                        num++;

                        m_statusLabel->setText("You are grabbing " + QString::number(num));
                        CPylonImage image;
                        image.AttachGrabResultBuffer(ptrGrabResult);
                        window.SetImage(image);

                        QString path = QCoreApplication::applicationDirPath() + "/save_hardware_trigger.png";
                        QByteArray ba = path.toLatin1();
                        CImagePersistence::Save(ImageFileFormat_Png, ba.data(), ptrGrabResult);

                        QPixmap pixmap(QCoreApplication::applicationDirPath() + "/save_hardware_trigger.png");
                        m_galleryWidget->setImage(pixmap);
                        m_galleryWidget->repaint();
                        m_galleryWidget->show();
                    }
                }
            }

            if (m_triggerModeMask == 1)
            {
                camera.StopGrabbing();
                camera.Close();
                CSoftwareTriggerConfiguration* p = new CSoftwareTriggerConfiguration;
                camera.RegisterConfiguration(p, RegistrationMode_ReplaceAll, Cleanup_Delete);
                camera.Open();
                camera.StartGrabbing(c_countOfImagesToGrab, GrabStrategy_LatestImageOnly);

                while (m_triggerModeMask == 1 && !m_isClosed)
                {
                    QCoreApplication::processEvents();

                    if (m_isSoftwareTriggered)
                    {

                        while(!camera.RetrieveResult(0, ptrGrabResult, TimeoutHandling_Return))
                            camera.ExecuteSoftwareTrigger();

                        num++;

                        m_statusLabel->setText("You are grabbing " + QString::number(num));
                        CPylonImage image;
                        image.AttachGrabResultBuffer(ptrGrabResult);
                        window.SetImage(image);

                        QString path = QCoreApplication::applicationDirPath() + "/save_software_trigger.png";
                        QByteArray ba = path.toLatin1();
                        CImagePersistence::Save(ImageFileFormat_Png, ba.data(), ptrGrabResult);

                        m_isSoftwareTriggered = false;

                        QPixmap pixmap(QCoreApplication::applicationDirPath() + "/save_software_trigger.png");
                        m_galleryWidget->setImage(pixmap);
                        m_galleryWidget->repaint();
                        m_galleryWidget->show();
                    }
                }

//                camera.StopGrabbing();
//                camera.Close();
//                camera.DeregisterConfiguration(p);
//                camera.Open();
//                camera.StartGrabbing(c_countOfImagesToGrab, GrabStrategy_LatestImageOnly);
            }

            if (m_isClosed)
            {
                camera.StopGrabbing();
                camera.Close();
                m_statusLabel->setText(tr("Camera has been closed!"));
            }
            else
            {

                //camera.StartGrabbing(c_countOfImagesToGrab, GrabStrategy_LatestImageOnly);
                camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_Return);

                if (ptrGrabResult->GrabSucceeded())
                {
                    num++;

                    m_statusLabel->setText("You are grabbing " + QString::number(num));
                    CPylonImage image;
                    image.AttachGrabResultBuffer(ptrGrabResult);
                    window.SetImage(image);

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

                    QElapsedTimer t;
                    t.start();
                    while (t.elapsed() <= 200)
                        QCoreApplication::processEvents();
                }
                else
                    m_statusLabel->setText("Error image grab failed: " + QString(ptrGrabResult->GetErrorDescription().c_str()));
            }
        }
    }
    catch (const GenericException &e)
    {
        m_statusLabel->setText("An exception occurred." + QString(e.GetDescription()));
        closeCamera();
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
}

void MainWindow::saveCurrentImage()
{
    m_isSaved = true;
}

void MainWindow::softwareTrigger()
{
    m_isSoftwareTriggered = true;
}
