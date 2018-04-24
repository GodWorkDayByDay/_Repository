#include "main_window.h"
#include "admin_dialog.h"
#include <QStatusBar>
#include <QGridLayout>
#include <QElapsedTimer>
#include <QMessageBox>
#include <QCoreApplication>
#include <QDebug>
#include <SampleImageCreator.h>
#include <HardwareTriggerConfiguration.h>
#include <SoftwareTriggerConfiguration.h>
#include <pylon/gige/BaslerGigEInstantCamera.h>
#include <ConfigurationEventPrinter.h>
#include <ImageEventPrinter.h>
#include <QTime>
#include <QSizePolicy>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent)
{
    setWindowTitle(QString::fromLocal8Bit("龙骨校正"));

    isFirst = true;

    m_mil = new MILC;
    m_cameraWidget  = new QWidget;
    m_cameraWidget->setFixedSize(420, 135);
    m_correctionWidget = new QWidget;
    m_settingWidget = new QWidget;
    m_manualWidget = new QWidget;

    m_imageWindow = new ImageWindow; //m_imageWindow->show();
    m_galleryWidget = new GalleryWidget; //m_galleryWidget->show();
    m_isClosed = false;
    m_saveMode = -2;
    m_cameraMode = 1;

    m_openPushButton = new QPushButton(QString::fromLocal8Bit("打开相机"));
    connect(m_openPushButton, SIGNAL(clicked(bool)), SLOT(openCamera()));
    m_closePushButton = new QPushButton(QString::fromLocal8Bit("关闭相机"));
    m_closePushButton->setEnabled(false);
    connect(m_closePushButton, SIGNAL(clicked(bool)), SLOT(closeCamera()));
    m_returnLabel = new QLabel(QString::fromLocal8Bit("返回值:"));
    m_returnDataLabel = new QLabel;
    m_returnDataLabel->setStyleSheet("border-width: 1px;border-style: dashed;border-color: rgb(0, 0, 0);");
    m_statusLabel = new QLabel(QString::fromLocal8Bit("状态:"));
    m_statusDataLabel = new QLabel;
    m_statusDataLabel->setStyleSheet("border-width: 1px;border-style: dashed;border-color: rgb(0, 0, 0);");
    m_adminPushButton = new QPushButton(QString::fromLocal8Bit("开发者模式"));
    connect(m_adminPushButton, SIGNAL(clicked(bool)), SLOT(adminBtn()));
    QGridLayout *gLayout1 = new QGridLayout(m_cameraWidget);
    gLayout1->addWidget(m_openPushButton, 0, 0, 1, 1);
    gLayout1->addWidget(m_closePushButton, 0, 1, 1, 1);
    gLayout1->addWidget(m_returnLabel, 1, 0, 1, 1);
    gLayout1->addWidget(m_returnDataLabel, 1, 1, 1, 1);
    gLayout1->addWidget(m_statusLabel, 2, 0, 1, 1);
    gLayout1->addWidget(m_statusDataLabel, 2, 1, 1, 1);
    gLayout1->addWidget(m_adminPushButton, 3, 1, 1, 1);

    m_saveModelPushButton = new QPushButton(QString::fromLocal8Bit("保存模板图片"));
    connect(m_saveModelPushButton, SIGNAL(clicked(bool)), SLOT(saveModeToNegative1()));
    m_saveSourcePushButton = new QPushButton(QString::fromLocal8Bit("保存源图片"));
    connect(m_saveSourcePushButton, SIGNAL(clicked(bool)), SLOT(saveModeTo0()));
    m_hDistanceLabel = new QLabel(QString::fromLocal8Bit("水平移量(微米)"));
    m_unitLineEdit = new QLineEdit;
    m_calculatePushButton = new QPushButton(QString::fromLocal8Bit("计算单元值"));
    connect(m_calculatePushButton, SIGNAL(clicked(bool)), SLOT(calculate()));
    QGridLayout *gLayout2 = new QGridLayout(m_correctionWidget);
    gLayout2->addWidget(m_saveModelPushButton, 0, 0, 1, 1);
    gLayout2->addWidget(m_saveSourcePushButton, 0, 1, 1, 1);
    gLayout2->addWidget(m_hDistanceLabel, 2, 0, 1, 1);
    gLayout2->addWidget(m_unitLineEdit, 2, 1, 1 ,1);
    gLayout2->addWidget(m_calculatePushButton, 3, 0, 1, 2);

    m_exposureTimeLabel   = new QLabel(QString::fromLocal8Bit("曝光时间"));
    m_gainLabel           = new QLabel(QString::fromLocal8Bit("增益"));
    m_exposureTimeSpinBox = new QSpinBox;
    m_gainSpinBox         = new QSpinBox;
    m_exposureTimeSpinBox->setRange(1, 65535);
    m_gainSpinBox->setRange(1, 255);
    m_exposureTimeSpinBox->setValue(600);
    m_gainSpinBox->setValue(231);
    m_saveModel1PushButton = new QPushButton(QString::fromLocal8Bit("保存模板一"));
    connect(m_saveModel1PushButton, SIGNAL(clicked(bool)), SLOT(saveModeTo1()));
    m_saveModel2Pushbutton = new QPushButton(QString::fromLocal8Bit("保存模板二"));
    connect(m_saveModel2Pushbutton, SIGNAL(clicked(bool)), SLOT(saveModeTo2()));
    QGridLayout *gLayout3 = new QGridLayout(m_settingWidget);
    gLayout3->addWidget(m_exposureTimeLabel, 0, 0, 1, 1);
    gLayout3->addWidget(m_exposureTimeSpinBox, 0, 1, 1, 1);
    gLayout3->addWidget(m_gainLabel, 1, 0, 1, 1);
    gLayout3->addWidget(m_gainSpinBox, 1, 1, 1, 1);
    gLayout3->addWidget(m_saveModel1PushButton, 2, 0, 1, 1);
    gLayout3->addWidget(m_saveModel2Pushbutton, 2, 1, 1, 1);

    m_comboBox = new QComboBox;
    m_comboBox->addItem(QString::fromLocal8Bit("模板一"));
    m_comboBox->addItem(QString::fromLocal8Bit("模板二"));
    connect(m_comboBox, SIGNAL(currentIndexChanged(int)), SLOT(comboBoxChanged(int)));
    m_savePushButton = new QPushButton(QString::fromLocal8Bit("保存源图片"));
    connect(m_savePushButton, SIGNAL(clicked(bool)), SLOT(saveModeTo0()));
    m_getPushButton = new QPushButton(QString::fromLocal8Bit("测量"));
    connect(m_getPushButton, SIGNAL(clicked(bool)), SLOT(test()));
    QGridLayout *gLayout4 = new QGridLayout(m_manualWidget);
    gLayout4->addWidget(m_comboBox, 0, 0, 1, 1);
    gLayout4->addWidget(m_savePushButton, 0, 1, 1, 1);
    gLayout4->addWidget(m_getPushButton, 1, 1, 1, 1);

    m_tabWidget = new QTabWidget;
    m_tabWidget->addTab(m_correctionWidget, QString::fromLocal8Bit("单元设置"));
    m_tabWidget->addTab(m_settingWidget, QString::fromLocal8Bit("模板取样"));
    m_tabWidget->addTab(m_manualWidget, QString::fromLocal8Bit("手动测量"));
    m_tabWidget->hide();

    QWidget *mainWidget = new QWidget;
    QVBoxLayout *vBoxLayout = new QVBoxLayout(mainWidget);
    vBoxLayout->addWidget(m_cameraWidget);
    vBoxLayout->addWidget(m_tabWidget);
    vBoxLayout->setSizeConstraint(QLayout::SetFixedSize);

    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{
}

bool MainWindow::isExist(QString name)
{
    QFileInfo file(QCoreApplication::applicationDirPath() + name);

    if (file.isFile())
        return true;

    return false;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    delete m_mil;
    delete m_imageWindow;
    delete m_galleryWidget;
}

bool MainWindow::returnData(long & x, long & y)
{
    double find_x;
    double find_y;

    QFile file;
    QTextStream stream;
    file.setFileName("./log_return/log.txt");
    file.open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Append);
    stream.setDevice(&file);

    if (m_mil->MilSearch(find_x, find_y))
    {
        x = find_x;
        y = find_y;

        m_returnDataLabel->setText("x = " + QString::number(x) + ", y = " + QString::number(y));

        stream << "x = " << QString::number(x) << ", y = " << QString::number(y) << "\n";
        file.close();

        return true;
    }
    else
    {
        stream << "x = " << QString::number(-1.0) << ", y = " << QString::number(-1.0) << "\n";
        file.close();

        m_returnDataLabel->setText(QString::fromLocal8Bit("模板查找失败!"));
    }

    return false;
}

void MainWindow::openCamera()
{
    if (isFirst)
    {
        if (!plc.m_createSuccess)
        {
            QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("CoCreateInstance函数失败!"));
        }
        else
        {
            if (!plc.openCommucation())
            {
                QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("PLC连接失败!"));
            }
        }

        isFirst = false;
    }

    long x, y;

    m_isClosed = false;

    m_openPushButton->setAttribute(Qt::WA_UnderMouse, false);
    m_openPushButton->setEnabled(false);
    m_closePushButton->setEnabled(true);
    m_exposureTimeSpinBox->setEnabled(false);
    m_gainSpinBox->setEnabled(false);

    using namespace Pylon;
    using namespace Basler_GigECameraParams;

    const uint32_t c_countOfImagesToGrab = 2000;

    PylonInitialize();

    m_imageWindow->show();

    CDeviceInfo info;
    info.SetDeviceClass(CBaslerGigEInstantCamera::DeviceClass());

    CGrabResultPtr ptrGrabResult;
    try
    {
        while (!m_isClosed)
        {
            switch (m_cameraMode)
            {
            case 0:
            {
                CBaslerGigEInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice(info));
                camera.Open();
                camera.GainAuto.SetValue(GainAuto_Off);
                camera.GainRaw.SetValue(m_gainSpinBox->value());
                camera.ExposureAuto.SetValue(ExposureAuto_Off);
                camera.ExposureTimeRaw.SetValue(m_exposureTimeSpinBox->value());
                camera.StartGrabbing(/*c_countOfImagesToGrab, */GrabStrategy_LatestImageOnly);

                while (camera.IsGrabbing() && m_cameraMode == 0 && !m_isClosed)
                {
                    camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_Return);

                    if (ptrGrabResult->GrabSucceeded())
                    {
                        CPylonImage image;
                        image.AttachGrabResultBuffer(ptrGrabResult);

                        QString path = QCoreApplication::applicationDirPath() + "/buffer.jpg";
                        QByteArray ba = path.toLatin1();
                        CImagePersistence::Save(ImageFileFormat_Jpeg, ba.data(), ptrGrabResult);

                        m_imageWindow->m_image.load(QCoreApplication::applicationDirPath() + "/buffer.jpg");
                        m_imageWindow->repaint();

                        if (m_saveMode == 0)
                        {
                            m_saveMode = -2;
                            m_imageWindow->m_image.save(QCoreApplication::applicationDirPath() + "/source.jpg");

                            if (isExist("/source.jpg"))
                                QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("图片保存成功!"));
                            else
                                QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("图片保存失败，请重新保存!"));
                        }
                        else if (m_saveMode == -1)
                        {
                            m_saveMode = -2;
                            m_imageWindow->m_image.save(QCoreApplication::applicationDirPath() + "/model.jpg");

                            if (isExist("/model.jpg"))
                                QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("图片保存成功!"));
                            else
                                QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("图片保存失败，请重新保存!"));
                        }
                        else if (m_saveMode == 1)
                        {
                            m_saveMode = -2;
                            m_imageWindow->m_image.save(QCoreApplication::applicationDirPath() + "/model1.jpg");

                            if (isExist("/model1.jpg"))
                                QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("图片保存成功!"));
                            else
                                QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("图片保存失败，请重新保存!"));

                            m_galleryWidget->show();
                            m_galleryWidget->m_saveMode = 1;
                            m_galleryWidget->setImage(m_imageWindow->m_image);
                            m_galleryWidget->repaint();                      
                        }
                        else if(m_saveMode == 2)
                        {
                            m_saveMode = -2;
                            m_imageWindow->m_image.save(QCoreApplication::applicationDirPath() + "/model2.jpg");

                            if (isExist("/model2.jpg"))
                                QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("图片保存成功!"));
                            else
                                QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("图片保存失败，请重新保存!"));

                            m_galleryWidget->show();
                            m_galleryWidget->m_saveMode = 2;
                            m_galleryWidget->setImage(m_imageWindow->m_image);
                            m_galleryWidget->repaint();
                        }

                        QElapsedTimer t;
                        t.start();
                        while (t.elapsed() <= 200)
                            QCoreApplication::processEvents();
                    }
                }

                camera.StopGrabbing();
                camera.Close();

                break;
            }
            case 1:
            {
                CBaslerGigEInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice(info));
                camera.Open();
                camera.GainAuto.SetValue(GainAuto_Off);
                camera.GainRaw.SetValue(m_gainSpinBox->value());
                camera.ExposureAuto.SetValue(ExposureAuto_Off);
                camera.ExposureTimeRaw.SetValue(m_exposureTimeSpinBox->value());
                camera.StartGrabbing(/*c_countOfImagesToGrab, */GrabStrategy_LatestImageOnly);

                while (m_cameraMode == 1 && !m_isClosed)
                {
                    long x1, x2;
                    while (m_cameraMode == 1 && !m_isClosed)
                    {
                        QCoreApplication::processEvents();

                        x1 = plc.read("m600");
                        x2 = plc.read("m601");

                        if (x1 == (long)1 && x2 == (long)1)
                        {
                            QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("PLC设备位m600和m601值都为1，无法继续!"));
                            m_isClosed = true;
                            break;
                        }

                        if (x1 == (long)1)
                        {
                            m_mil->modelID = 1;
                            m_statusDataLabel->setText(QString::fromLocal8Bit("正在使用模板一!"));
                            break;
                        }
                        else if (x2 == (long)1)
                        {
                            m_mil->modelID = 2;
                            m_statusDataLabel->setText(QString::fromLocal8Bit("正在使用模板二!"));
                            break;
                        }
                    }

                    if (m_cameraMode != 1)
                        break;

                    if (m_isClosed)
                    {
                        closeCamera();
                        break;
                    }

                    camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_Return);

                    if (ptrGrabResult->GrabSucceeded())
                    {
                        CPylonImage image;
                        image.AttachGrabResultBuffer(ptrGrabResult);

                        QString path = QCoreApplication::applicationDirPath() + "/source.jpg";
                        QByteArray ba = path.toLatin1();
                        CImagePersistence::Save(ImageFileFormat_Jpeg, ba.data(), ptrGrabResult);

                        m_imageWindow->m_image.load(QCoreApplication::applicationDirPath() + "/source.jpg");
                        m_imageWindow->repaint();

                        if (returnData(x, y))
                        {                     
                            if (plc.write("d250", x) && plc.write("d260", y))
                            {
                                m_statusDataLabel->setText(QString::fromLocal8Bit("写入PLC设备位d250和d260成功!"));

                                if (!plc.write("m605", 1))
                                    QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("写入PLC设备位m605失败!"));
                                if (!plc.write("m606", 0))
                                    QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("写入PLC设备位m606失败!"));
                            }
                            else
                                QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("写入PLC设备位d250和d260失败!"));

                            QElapsedTimer t;
                            t.start();
                            while (t.elapsed() <= 850)
                                QCoreApplication::processEvents();
                        }
                        else
                        {
                            if (!plc.write("m605", 0))
                                QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("写入PLC设备位m605失败!"));
                            if (!plc.write("m606", 1))
                                QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("写入PLC设备位m606失败!"));
                        }
                    }

                    QElapsedTimer t;
                    t.start();
                    while (t.elapsed() <= 800)
                        QCoreApplication::processEvents();
                }

                camera.StopGrabbing();
                camera.Close();

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

                while (m_cameraMode == 2 && !m_isClosed)
                {
                    QCoreApplication::processEvents();

                    if (camera_hardware.RetrieveResult(10, ptrGrabResult, TimeoutHandling_Return))
                    {
                        CPylonImage image;
                        image.AttachGrabResultBuffer(ptrGrabResult);

                        QString path = QCoreApplication::applicationDirPath() + "/buffer.jpg";
                        QByteArray ba = path.toLatin1();
                        CImagePersistence::Save(ImageFileFormat_Jpeg, ba.data(), ptrGrabResult);
                        m_imageWindow->m_image.load(QCoreApplication::applicationDirPath() + "/buffer.jpg");
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
        QMessageBox::critical(this, QString::fromLocal8Bit("错误"), "An exception occurred. " + QString(e.GetDescription()));
        closeCamera();
    }

    m_statusDataLabel->setText(QString::fromLocal8Bit("相机关闭中...!"));

    PylonTerminate();

    QElapsedTimer t;
    t.start();
    while (t.elapsed() <= 1000)
        QCoreApplication::processEvents();

    m_statusDataLabel->clear();
}

void MainWindow::closeCamera()
{
    m_isClosed = true;
    m_openPushButton->setEnabled(true);
    m_closePushButton->setAttribute(Qt::WA_UnderMouse, false);
    m_closePushButton->setEnabled(false);
    m_exposureTimeSpinBox->setEnabled(true);
    m_gainSpinBox->setEnabled(true);

    m_imageWindow->hide();
    m_galleryWidget->hide();
}

void MainWindow::calculate()
{
    if (!isExist("/source.jpg"))
    {
        QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("未找到source.jpg!"));
        return;
    }

    if (!isExist("/model.jpg"))
    {
        QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("未找到model.jpg!"));
        return;
    }

    bool ok;
    double z = m_unitLineEdit->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("请输入正确格式的数值!"));
        return;
    }

    m_mil->modelID = 0;

    double x, y;
    if (m_mil->MilSearch(x, y))
    {
        m_mil->unit = fabs(z) / fabs(x);

        QFile file("./log_unit/log.txt");
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream stream(&file);
        stream << m_mil->unit;
        file.close();

        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("计算成功，单元值已设置!"));
    }
    else
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("模板查找失败，单元值设置失败!"));
    }
}

void MainWindow::adminBtn()
{
    if (m_tabWidget->isHidden())
    {
        AdminDialog *dialog = new AdminDialog(this);
        connect(dialog, SIGNAL(success()), SLOT(showAdminControl()));
        dialog->show();
    }
    else
    {
        m_tabWidget->hide();
        m_cameraMode = 1;
        m_statusDataLabel->clear();
    }
}

void MainWindow::showAdminControl()
{
    m_tabWidget->show();
    m_cameraMode = 0;
    m_mil->modelID = 1;
}

void MainWindow::saveModeToNegative1()
{
    m_saveMode = -1;
}

void MainWindow::saveModeTo0()
{
    m_saveMode = 0;
}

void MainWindow::saveModeTo1()
{
    m_saveMode = 1;
}

void MainWindow::saveModeTo2()
{
    m_saveMode = 2;
}

void MainWindow::test()
{
    if (!isExist("/source.jpg"))
    {
        QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("未找到source.jpg!"));
        return;
    }

    if (m_comboBox->currentIndex() == 0)
    {
        m_statusDataLabel->setText(QString::fromLocal8Bit("正在使用模板一!"));
        if (!isExist("/model1.jpg"))
        {
            QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("未找到model1.jpg!"));
            return;
        }
    }
    else
    {
        m_statusDataLabel->setText(QString::fromLocal8Bit("正在使用模板二!"));
        if (!isExist("/model2.jpg"))
        {
            QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("未找到model2.jpg!"));
            return;
        }
    }

    double find_x;
    double find_y;

    QFile file;
    QTextStream stream;
    file.setFileName("./log_return/log.txt");
    file.open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Append);
    stream.setDevice(&file);

    if (m_mil->MilSearch(find_x, find_y))
    {
        long x = find_x;
        long y = find_y;

        m_returnDataLabel->setText("x = " + QString::number(x) + ", y = " + QString::number(y));


        stream << "x = " << QString::number(x) << ", y = " << QString::number(y) << "\n";
        file.close();
    }
    else
    {
        stream << "x = " << QString::number(-1.0) << ", y = " << QString::number(-1.0) << "\n";
        file.close();
        m_returnDataLabel->setText(QString::fromLocal8Bit("模板查找失败!"));
    }
}

void MainWindow::comboBoxChanged(int id)
{
    m_mil->modelID = id;
}
