#include "main_window.h"
#include <QStatusBar>
#include <QGridLayout>
#include <QDebug>
#include <QTest>
#include <SampleImageCreator.h> // 这里边是函数定义，不是声明

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent)
{
    m_isClosed = m_isSaved = false;

    m_mainWidget = new QSplitter(Qt::Horizontal);

    m_plcWidget     = new PLCWidget(m_mainWidget);
    m_galleryWidget = new GalleryWidget;
    m_cameraWidget  = new QFrame(m_mainWidget);

    m_cameraWidget->setMinimumSize(200, 400);
    m_cameraWidget->setFrameStyle(QFrame::Panel | QFrame::Raised);

    m_openPushButton  = new QPushButton(tr("Open Camera"));
    m_closePushButton = new QPushButton(tr("Close Camera"));
    m_savePushButton  = new QPushButton(tr("Save Image"));
    m_openPushButton->setEnabled(true);
    m_closePushButton->setEnabled(false);
    m_savePushButton->setEnabled(false);

    QVBoxLayout *vLayout = new QVBoxLayout(m_cameraWidget);
    vLayout->addWidget(m_openPushButton);
    vLayout->addWidget(m_closePushButton);
    vLayout->addWidget(m_savePushButton);
    vLayout->addStretch();
    vLayout->setSpacing(20);

    m_mainWidget->setStretchFactor(0, 4);
    m_mainWidget->setStretchFactor(1, 4);
    m_mainWidget->setStretchFactor(2, 2);

    setCentralWidget(m_mainWidget);

    m_statusLabel = new QLabel(tr("Welcome......"));
    statusBar()->addWidget(m_statusLabel);

    connect(m_openPushButton, SIGNAL(clicked(bool)), SLOT(openCamera()));
    connect(m_closePushButton, SIGNAL(clicked(bool)), SLOT(closeCamera()));
    connect(m_savePushButton, SIGNAL(clicked(bool)), SLOT(saveCurrentImage()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::openCamera()
{
    m_isClosed = false;
    m_isSaved  = false;

    m_openPushButton->setEnabled(false);
    m_closePushButton->setEnabled(true);
    m_savePushButton->setEnabled(true);

    m_statusLabel->setText(tr("Start grabbing, please wait......"));
    QTest::qWait(200);

    using namespace Pylon;

    const uint32_t c_countOfImagesToGrab = 1000;
    int num = 0;

    PylonInitialize();

    try
    {
        CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());

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

                if (m_isSaved)
                {
                    QString path = QCoreApplication::applicationDirPath()+ "/save.png";
                    QByteArray ba = path.toLatin1();
                    CImagePersistence::Save(ImageFileFormat_Png, ba.data(), ptrGrabResult);

                    m_isSaved = false;

                    m_galleryWidget->repaint();
                    m_galleryWidget->show();
                }

                QTest::qWait(200);
            }
            else
                m_statusLabel->setText("Error image grab failed: " + QString(ptrGrabResult->GetErrorDescription().c_str()));

            if (m_isClosed)
            {
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
    m_closePushButton->setEnabled(false);
    m_savePushButton->setEnabled(false);
}

void MainWindow::saveCurrentImage()
{
    m_isSaved = true;
}
