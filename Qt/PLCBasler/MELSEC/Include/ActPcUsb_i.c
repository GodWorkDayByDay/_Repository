/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Apr 12 12:32:59 2013
 */
/* Compiler settings for D:\GETMODULE\CommunicationSupport2\SW3D5\ACT\Control\ActPcUsb\ActPcUsb.idl:
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

const IID IID_IActQCPUQUSB = {0xB5BDE861,0xAEA9,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID IID_IActQCPUQUSB2 = {0xA850BB90,0xC820,0x11d4,{0x87,0x44,0x00,0xE0,0x29,0x2A,0x4F,0xB4}};


const IID IID_IActQCPUQUSB3 = {0x115992F1,0x6EC2,0x11d5,{0x93,0x14,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLQCPUQUSB = {0x95969871,0xA954,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLQCPUQUSB2 = {0x87166060,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLQCPUQUSB3 = {0x115992F2,0x6EC2,0x11d5,{0x93,0x14,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActFXCPUUSB = {0x43620827,0xE04D,0x4BDA,{0x9B,0x0C,0xCA,0x6C,0x24,0x2E,0x65,0x46}};


const IID IID_IActFXCPUUSB2 = {0xD481165B,0xFBE4,0x41d1,{0xB1,0xEF,0xB3,0xDA,0x6C,0xB0,0x18,0xD8}};


const IID IID_IActFXCPUUSB3 = {0x524E1D1D,0x995D,0x401a,{0x8C,0x46,0xED,0x79,0xA7,0x01,0xB9,0x97}};


const IID IID_IActMLFXCPUUSB = {0x1315739A,0xC8C5,0x4867,{0xB6,0x2F,0x8A,0x8F,0x20,0x4A,0x28,0x07}};


const IID IID_IActMLFXCPUUSB2 = {0x745C12FF,0x1695,0x4627,{0x90,0x4B,0xFC,0xC9,0x5F,0x22,0x22,0xCF}};


const IID IID_IActMLFXCPUUSB3 = {0xBE960D4D,0x7F78,0x4d6d,{0xAF,0x68,0x6F,0x5E,0x69,0x14,0xF4,0xBF}};


const IID IID_IActLCPUUSB = {0xDAA1019D,0x6474,0x4BC9,{0xB1,0x03,0xF9,0x19,0x3A,0x5D,0x0A,0x20}};


const IID IID_IActLCPUUSB2 = {0xC7BCF733,0x1758,0x46b2,{0x98,0x61,0xD4,0x87,0x53,0xC6,0x1B,0x0E}};


const IID IID_IActLCPUUSB3 = {0x9A9810EA,0xEEF2,0x4cd0,{0x85,0xEF,0x42,0x3D,0x7B,0x7F,0x27,0x80}};


const IID IID_IActMLLCPUUSB = {0xCAD92CF3,0x71D8,0x47F1,{0x83,0x4D,0xCD,0xDD,0x89,0xAD,0x9E,0x3B}};


const IID IID_IActMLLCPUUSB2 = {0x0CE8E83D,0x4926,0x40a3,{0xA2,0x32,0xE6,0x2F,0x05,0x7D,0x04,0x44}};


const IID IID_IActMLLCPUUSB3 = {0x8B65574B,0x1985,0x4366,{0xA5,0xEB,0xB4,0x79,0x0B,0x7C,0x62,0x85}};


const IID LIBID_ACTPCUSBLib = {0xA306B175,0xAE98,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActQCPUQUSBEvents = {0xB5BDE863,0xAEA9,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const CLSID CLSID_ActQCPUQUSB = {0xB5BDE862,0xAEA9,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActMLQCPUQUSBEvents = {0x95969873,0xA954,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActMLQCPUQUSB = {0x95969872,0xA954,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActFXCPUUSBEvents = {0x9656AF89,0xCD33,0x4C7C,{0xA6,0x5D,0xDE,0x68,0xEF,0x4F,0x97,0x17}};


const CLSID CLSID_ActFXCPUUSB = {0x0FE3736A,0x155A,0x492D,{0x92,0x5B,0xB1,0xB1,0x1A,0xC4,0xA2,0x6C}};


const IID DIID__IActMLFXCPUUSBEvents = {0xB30DA6C5,0x8EDC,0x40C0,{0xB3,0xD3,0xF7,0xC9,0x5A,0x16,0x1C,0xDC}};


const CLSID CLSID_ActMLFXCPUUSB = {0x2F977269,0xEF63,0x448E,{0xB4,0x97,0x55,0x9C,0xA3,0x66,0xC1,0xE0}};


const IID DIID__IActLCPUUSBEvents = {0xF8C63632,0x0733,0x49D8,{0x93,0x49,0x5E,0xAA,0x8C,0xCE,0xA0,0xAF}};


const CLSID CLSID_ActLCPUUSB = {0x514DEE9A,0xC6F7,0x46FD,{0xA3,0x59,0x13,0x22,0xDF,0x4D,0x28,0xF3}};


const IID DIID__IActMLLCPUUSBEvents = {0x58B74969,0x0C83,0x4421,{0x9B,0xA8,0x11,0xD1,0x39,0x7B,0x84,0xFD}};


const CLSID CLSID_ActMLLCPUUSB = {0xBAE3FB8D,0x3A50,0x4AFB,{0x91,0x2A,0x00,0x37,0xF4,0x53,0x74,0xFD}};


#ifdef __cplusplus
}
#endif
