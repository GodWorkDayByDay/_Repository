#ifndef PLC_H
#define PLC_H

#include <QString>
#include <Windows.h>

struct IActUtlType;

class PLC
{
public:
    PLC();
    ~PLC();
    bool openCommucation();
    long read(QString device_name);
    bool write(QString device_name, long value);

public:
    bool m_createSuccess;

private:
    IActUtlType *m_IUtlType;
};

#endif // PLC_H
