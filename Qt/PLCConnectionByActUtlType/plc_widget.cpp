#include "plc_widget.h"
#include "C:\MELSEC\Act\Include\ActUtlType_i.h"
#include "C:\MELSEC\Act\Include\ActProgType_i.h"
#include "C:\MELSEC\Act\Include\ActDefine.h"
#include "C:\MELSEC\Act\Include\ActUtlType_i.c"
#include "C:\MELSEC\Act\Include\ActProgType_i.c"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDebug>

PLCWidget::PLCWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("PLC Connection by ActUtlType"));
    setFont(QFont("Consolas", 13));

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

    QGridLayout *gLayout = new QGridLayout(m_resultGroupBox);
    gLayout->addWidget(m_returnCodeLabel, 0, 0, 1, 1);
    gLayout->addWidget(m_returnCodeLineEdit, 0, 1, 1, 1);
    gLayout->addWidget(m_outputLabel, 1, 0, 1, 1);
    gLayout->addWidget(m_outputLineEdit1, 1, 1, 1, 1);
    gLayout->addWidget(m_outputLineEdit2, 1, 2, 1, 1);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(m_openPushButton, 0, 0, 1, 1);
    layout->addWidget(m_getCpuPushButton, 1, 0, 1, 1);
    layout->addWidget(m_deviceNameLabel, 2, 0, 1, 1);
    layout->addWidget(m_deviceNameLineEdit, 2, 1, 1, 1);
    layout->addWidget(m_readPushButton, 2, 2, 1, 1);
    layout->addWidget(m_deviceValueLabel, 3, 0, 1, 1);
    layout->addWidget(m_deviceValueLineEdit, 3, 1, 1, 1);
    layout->addWidget(m_writePushButton, 3, 2, 1, 1);
    layout->addWidget(m_resultGroupBox, 4, 0, 1, 3);

    layout->setMargin(20);
    layout->setSpacing(20);

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

    delete cpuName;
}

void PLCWidget::read()
{
    long hr;
    long lRet;
    long lValue;
    //BSTR device;
    wchar_t device[100];

    m_outputLineEdit1->clear();
    m_outputLineEdit2->clear();

    m_deviceNameLineEdit->text().toWCharArray(device);

    hr = m_IUtlType->GetDevice(device, &lValue, &lRet);
    if (SUCCEEDED(hr))
    {
        if(lRet == 0x00)
            m_outputLineEdit1->setText(QString::number(lValue, 16));
    }

    m_returnCodeLineEdit->setText(QString::number(hr, 16));
}

void PLCWidget::write()
{
    long hr;
    long lRet;
    wchar_t device[100];
    long lValue = m_deviceValueLineEdit->text().toLong();

    m_outputLineEdit1->clear();
    m_outputLineEdit2->clear();

    m_deviceNameLineEdit->text().toWCharArray(device);

    hr = m_IUtlType->SetDevice(device, lValue, &lRet);

    m_returnCodeLineEdit->setText(QString::number(hr, 16));
}
