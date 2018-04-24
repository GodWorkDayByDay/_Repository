#include "plc.h"
#include <ActUtlType_i.h>
#include <ActProgType_i.h>
#include <ActDefine.h>
#include <ActUtlType_i.c>
#include <ActProgType_i.c>
#include "C:/Program Files (X86)/Microsoft Visual Studio 14.0/VC/atlmfc/include/atlstr.h"

PLC::PLC()
{
    long hr = CoCreateInstance(CLSID_ActUtlType, NULL, CLSCTX_INPROC_SERVER, IID_IActUtlType, (LPVOID*)&m_IUtlType);

    if (!SUCCEEDED(hr))
        m_createSuccess = false;
    else
        m_createSuccess = true;
}

PLC::~PLC()
{
}

bool PLC::openCommucation()
{
    long hr;
    long lRet;

    hr = m_IUtlType->put_ActLogicalStationNumber(0);
    if (SUCCEEDED(hr))
        hr = m_IUtlType->Open(&lRet);

     return hr == 0 ? true : false;
}

long PLC::read(QString device_name)
{
    long hr;
    long lRet;
    long lValue;

    QByteArray ba = device_name.toLatin1();
    int len = ba.size();
    char *device = new char[len + 1];
    strcpy(device, ba.data());
    device[len] = '\0';
    CString s(device);

    hr = m_IUtlType->GetDevice(s.AllocSysString(), &lValue, &lRet);

    if (SUCCEEDED(hr))
    {
        if(lRet == 0x00)
            return lValue;
    }

    return -1;
}

bool PLC::write(QString device_name, long value)
{
    long hr;
    long lRet;
    long lValue = value;

    QByteArray ba = device_name.toLatin1();
    int len = ba.size();
    char *device = new char[len + 1];
    strcpy(device, ba.data());
    device[len] = '\0';
    CString s(device);

    if (device_name == QString("d250") || device_name == QString("d260"))
    {
        long Svalue[2];

        if (lValue >= 0)
        {
            Svalue[1] = lValue / 65536;
            Svalue[0] = lValue % 65536;
        }
        else
        {
            if (lValue > -65536)
            {
                Svalue[1] = -1;
                Svalue[0] = lValue;
            }
            else
            {
                Svalue[0] = lValue % 65536;
                if (Svalue[0] == 0)
                {
                    Svalue[1] = lValue / 65536;
                }
                else
                {
                    Svalue[1] = (lValue / 65536) - 1;
                }
            }
        }

        hr = m_IUtlType->WriteDeviceBlock(s.AllocSysString(), 2, Svalue, &lRet);
    }
    else
    {
        hr = m_IUtlType->SetDevice(s.AllocSysString(), lValue, &lRet);
    }

    delete []device;

    return hr == 0 ? true : false;
}

