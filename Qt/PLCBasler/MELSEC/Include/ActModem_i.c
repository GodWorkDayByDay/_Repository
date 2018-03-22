/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Apr 12 12:33:23 2013
 */
/* Compiler settings for D:\GETMODULE\CommunicationSupport2\SW3D5\ACT\Control\ActModem\ActModem.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IActA6TEL = {0x5713F072,0x6F4A,0x11D5,{0x93,0x15,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActA6TEL2 = {0x87166036,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActA6TEL3 = {0x87166037,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActQ6TEL = {0x5713F075,0x6F4A,0x11D5,{0x93,0x15,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActQ6TEL2 = {0x87166038,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActQ6TEL3 = {0x87166039,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActFXCPUTEL = {0x5713F078,0x6F4A,0x11D5,{0x93,0x15,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActFXCPUTEL2 = {0x8716603A,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActFXCPUTEL3 = {0x8716603B,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActAJ71QC24TEL = {0x5713F07B,0x6F4A,0x11D5,{0x93,0x15,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActAJ71QC24TEL2 = {0x8716603C,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActAJ71QC24TEL3 = {0x8716603D,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActQJ71C24TEL = {0x5713F07E,0x6F4A,0x11D5,{0x93,0x15,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActQJ71C24TEL2 = {0x8716603E,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActQJ71C24TEL3 = {0x8716603F,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActLJ71C24TEL = {0x44012BC6,0x2F69,0x4FB4,{0xB5,0xD9,0xBF,0x8B,0x17,0x92,0x56,0xA7}};


const IID IID_IActLJ71C24TEL2 = {0xE367C39C,0x39BD,0x4df8,{0x8F,0x5E,0x8D,0x56,0x8C,0xEE,0x79,0x17}};


const IID IID_IActLJ71C24TEL3 = {0xBE96010D,0x12AE,0x45be,{0xA2,0xCA,0x9F,0xB2,0x8B,0x4E,0x6D,0x7A}};


const IID LIBID_ACTMODEMLib = {0x5713F064,0x6F4A,0x11D5,{0x93,0x15,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActA6TELEvents = {0x5713F074,0x6F4A,0x11D5,{0x93,0x15,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActA6TEL = {0x5713F073,0x6F4A,0x11D5,{0x93,0x15,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActQ6TELEvents = {0x5713F077,0x6F4A,0x11D5,{0x93,0x15,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActQ6TEL = {0x5713F076,0x6F4A,0x11D5,{0x93,0x15,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActFXCPUTELEvents = {0x5713F07A,0x6F4A,0x11D5,{0x93,0x15,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActFXCPUTEL = {0x5713F079,0x6F4A,0x11D5,{0x93,0x15,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActAJ71QC24TELEvents = {0x5713F07D,0x6F4A,0x11D5,{0x93,0x15,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActAJ71QC24TEL = {0x5713F07C,0x6F4A,0x11D5,{0x93,0x15,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActQJ71C24TELEvents = {0x5713F080,0x6F4A,0x11D5,{0x93,0x15,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActQJ71C24TEL = {0x5713F07F,0x6F4A,0x11D5,{0x93,0x15,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActLJ71C24TELEvents = {0x75C995BC,0xC301,0x4555,{0x99,0x0D,0xD0,0xAD,0x4B,0xE1,0x32,0xBA}};


const CLSID CLSID_ActLJ71C24TEL = {0x53CC3D65,0xFB92,0x4B53,{0xA1,0xE7,0x23,0xC7,0xC2,0x80,0x92,0x65}};


#ifdef __cplusplus
}
#endif
