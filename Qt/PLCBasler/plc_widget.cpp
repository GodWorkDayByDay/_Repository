#include "plc_widget.h"
#include <ActUtlType_i.h>
#include <ActProgType_i.h>
#include <ActDefine.h>
#include <ActUtlType_i.c>
#include <ActProgType_i.c>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include <Windows.h>
#include "C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/atlmfc/include/atlstr.h"

PLCWidget::PLCWidget(QFrame *parent) : QFrame(parent)
{
    setMinimumSize(400, 400);
    setFrameStyle(QFrame::Panel | QFrame::Raised);

    m_openPushButton      = new QPushButton(tr(" Open Communication "));
    m_getCpuPushButton    = new QPushButton(tr("Get CPU Type"));
    m_readPushButton      = new QPushButton(tr("Read"));
    m_writePushButton     = new QPushButton(tr("Write"));
    m_deviceNameLabel     = new QLabel(tr("Device Name"));
    m_deviceValueLabel    = new QLabel(tr("Device Value"));
    m_returnCodeLabel     = new QLabel(tr("Return"));
    m_outputLabel         = new QLabel(tr("Output"));
    m_returnCodeLineEdit  = new QLineEdit;
    m_deviceNameLineEdit  = new QLineEdit;
    m_deviceValueLineEdit = new QLineEdit;
    m_outputLineEdit1     = new QLineEdit;
    m_outputLineEdit2     = new QLineEdit;
    m_resultGroupBox      = new QGroupBox(tr("Result"));

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_openPushButton);
    hLayout->addWidget(m_getCpuPushButton);

    QGridLayout *gLayout = new QGridLayout;
    gLayout->addWidget(m_deviceNameLabel, 0, 0, 1, 1);
    gLayout->addWidget(m_deviceNameLineEdit, 0, 1, 1, 1);
    gLayout->addWidget(m_readPushButton, 0, 2, 1, 1);
    gLayout->addWidget(m_deviceValueLabel, 1, 0, 1, 1);
    gLayout->addWidget(m_deviceValueLineEdit, 1, 1, 1, 1);
    gLayout->addWidget(m_writePushButton, 1, 2, 1, 1);

    QGridLayout *gLayout2 = new QGridLayout(m_resultGroupBox);
    gLayout2->addWidget(m_returnCodeLabel, 0, 0, 1, 1);
    gLayout2->addWidget(m_returnCodeLineEdit, 0, 1, 1, 1);
    gLayout2->addWidget(m_outputLabel, 1, 0, 1, 1);
    gLayout2->addWidget(m_outputLineEdit1, 1, 1, 1, 1);
    gLayout2->addWidget(m_outputLineEdit2, 1, 2, 1, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(hLayout);
    mainLayout->addLayout(gLayout);
    mainLayout->addWidget(m_resultGroupBox);
    mainLayout->setMargin(20);
    mainLayout->setSpacing(40);

    connect(m_openPushButton, SIGNAL(clicked(bool)), SLOT(openCommucation()));
    connect(m_getCpuPushButton, SIGNAL(clicked(bool)), SLOT(getCpuType()));
    connect(m_readPushButton, SIGNAL(clicked(bool)), SLOT(read()));
    connect(m_writePushButton, SIGNAL(clicked(bool)), SLOT(write()));

    long hr = CoCreateInstance(CLSID_ActUtlType, NULL, CLSCTX_INPROC_SERVER, IID_IActUtlType, (LPVOID*)&m_IUtlType);
    if (!SUCCEEDED(hr))
        qDebug() << "CoCrateInstance() Failed.";
}

PLCWidget::~PLCWidget()
{
}

void PLCWidget::openCommucation()
{
    long hr;
    long lRet;

    m_outputLineEdit1->clear();
    m_outputLineEdit2->clear();

    hr = m_IUtlType->put_ActLogicalStationNumber(0);
    if (SUCCEEDED(hr))
        hr = m_IUtlType->Open(&lRet);

    m_returnCodeLineEdit->setText(QString::number(hr, 16));
}

void PLCWidget::getCpuType()
{
    BSTR cpuName = NULL;
    long cpuCode;
    long lRet;
    long hr;

    hr = m_IUtlType->GetCpuType(&cpuName, &cpuCode, &lRet);
    if (SUCCEEDED(hr))
    {
        if (lRet == 0x00)
        {
            m_outputLineEdit1->setText(QString::number(cpuCode, 16));
            m_outputLineEdit2->setText(QString::fromWCharArray(cpuName));
        }
    }

    m_returnCodeLineEdit->setText(QString::number(hr, 16));

    //delete cpuName;
}

//void PLCWidget::read()
//{
//    long hr;
//    long lRet;
//    long lValue;

//    QByteArray ba = m_deviceNameLineEdit->text().toLatin1();
//    int len = ba.size();
//    char *device = new char[len + 1];
//    strcpy(device, ba.data());
//    device[len] = '\0';
//    CString s(device);

//    m_outputLineEdit1->clear();
//    m_outputLineEdit2->clear();

//    hr = m_IUtlType->GetDevice(s.AllocSysString(), &lValue, &lRet);

//    if (SUCCEEDED(hr))
//    {
//        if(lRet == 0x00)
//            m_outputLineEdit1->setText(QString::number(lValue, 16));
//    }

//    m_returnCodeLineEdit->setText(QString::number(lRet, 16));
//}

//void PLCWidget::write()
//{
//    long hr;
//    long lRet;
//    long lValue = m_deviceValueLineEdit->text().toLong();

//    QByteArray ba = m_deviceNameLineEdit->text().toLatin1();
//    int len = ba.size();
//    char *device = new char[len + 1];
//    strcpy(device, ba.data());
//    device[len] = '\0';
//    CString s(device);

//    m_outputLineEdit1->clear();
//    m_outputLineEdit2->clear();

//    hr = m_IUtlType->SetDevice(s.AllocSysString(), lValue, &lRet);

//    m_returnCodeLineEdit->setText(QString::number(hr, 16));
//}

void PLCWidget::read()
{
    long hr;
    long lRet;
    long lValue;

    QByteArray ba = m_deviceNameLineEdit->text().toLatin1();
    int len = ba.size();
    char *device = new char[len + 1];
    strcpy(device, ba.data());
    device[len] = '\0';
    CString s(device);

    m_outputLineEdit1->clear();
    m_outputLineEdit2->clear();

    hr = m_IUtlType->GetDevice(s.AllocSysString(), &lValue, &lRet);

    if (SUCCEEDED(hr))
    {
        if(lRet == 0x00)
            m_outputLineEdit1->setText(QString::number(lValue, 16));
    }

    m_returnCodeLineEdit->setText(QString::number(lRet, 16));
}

void PLCWidget::write()
{
    long hr;
    long lRet;
    long lValue = m_deviceValueLineEdit->text().toLong();

    QByteArray ba = m_deviceNameLineEdit->text().toLatin1();
    int len = ba.size();
    char *device = new char[len + 1];
    strcpy(device, ba.data());
    device[len] = '\0';
    CString s(device);

    m_outputLineEdit1->clear();
    m_outputLineEdit2->clear();

    hr = m_IUtlType->SetDevice(s.AllocSysString(), lValue, &lRet);

    m_returnCodeLineEdit->setText(QString::number(hr, 16));
}

