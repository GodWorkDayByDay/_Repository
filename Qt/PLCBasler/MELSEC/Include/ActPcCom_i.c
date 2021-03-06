/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Apr 12 12:32:30 2013
 */
/* Compiler settings for D:\GETMODULE\CommunicationSupport2\SW3D5\ACT\Control\ActPcCom\ActPcCom.idl:
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

const IID IID_IActQCPUQ = {0x9B7B98C1,0xAE9B,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID IID_IActQCPUQ2 = {0x7B6517F0,0xC697,0x11d4,{0x87,0x41,0x00,0xE0,0x29,0x2A,0x4F,0xB4}};


const IID IID_IActQCPUQ3 = {0xCEAA03A1,0x6C4A,0x11d5,{0x93,0x12,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActQCPUA = {0x9B7B98C3,0xAE9B,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID IID_IActQCPUA2 = {0x7B6517F1,0xC697,0x11d4,{0x87,0x41,0x00,0xE0,0x29,0x2A,0x4F,0xB4}};


const IID IID_IActQCPUA3 = {0xCEAA03A2,0x6C4A,0x11d5,{0x93,0x12,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActQnACPU = {0x9B7B98C5,0xAE9B,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID IID_IActQnACPU2 = {0x7B6517F2,0xC697,0x11d4,{0x87,0x41,0x00,0xE0,0x29,0x2A,0x4F,0xB4}};


const IID IID_IActQnACPU3 = {0xCEAA03A3,0x6C4A,0x11d5,{0x93,0x12,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActACPU = {0x9B7B98C7,0xAE9B,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID IID_IActACPU2 = {0x7B6517F3,0xC697,0x11d4,{0x87,0x41,0x00,0xE0,0x29,0x2A,0x4F,0xB4}};


const IID IID_IActACPU3 = {0xCEAA03A4,0x6C4A,0x11d5,{0x93,0x12,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActFXCPU = {0x9B7B98C9,0xAE9B,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID IID_IActFXCPU2 = {0x7B6517F4,0xC697,0x11d4,{0x87,0x41,0x00,0xE0,0x29,0x2A,0x4F,0xB4}};


const IID IID_IActFXCPU3 = {0xCEAA03A5,0x6C4A,0x11d5,{0x93,0x12,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLACPU = {0x455C7662,0xA971,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLACPU2 = {0x8716605B,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLACPU3 = {0xCEAA03A6,0x6C4A,0x11d5,{0x93,0x12,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLFXCPU = {0x455C7668,0xA971,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLFXCPU2 = {0x8716605C,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLFXCPU3 = {0xCEAA03A7,0x6C4A,0x11d5,{0x93,0x12,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLQCPUA = {0x455C766B,0xA971,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLQCPUA2 = {0x8716605D,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLQCPUA3 = {0xCEAA03A8,0x6C4A,0x11d5,{0x93,0x12,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLQCPUQ = {0x455C766F,0xA971,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLQCPUQ2 = {0x8716605E,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLQCPUQ3 = {0xCEAA03A9,0x6C4A,0x11d5,{0x93,0x12,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLQnACPU = {0x5A95BB44,0xA984,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLQnACPU2 = {0x8716605F,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLQnACPU3 = {0xCEAA03AA,0x6C4A,0x11d5,{0x93,0x12,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActLCPU = {0x2FA6351F,0x8628,0x457B,{0xA1,0x23,0xE1,0xE0,0x8A,0xEB,0x29,0x60}};


const IID IID_IActLCPU2 = {0xE0E18877,0xC41F,0x408e,{0xB5,0x21,0x76,0xD3,0xC9,0xD9,0x83,0x0A}};


const IID IID_IActLCPU3 = {0x1932BCE5,0x232B,0x4c62,{0xBD,0xCC,0x48,0x7A,0x73,0x30,0xF4,0x13}};


const IID IID_IActMLLCPU = {0xE9B89E84,0x061D,0x49F3,{0xAB,0xAF,0xCD,0x5D,0x9D,0x5E,0xE1,0xB6}};


const IID IID_IActMLLCPU2 = {0xA85971A4,0xF424,0x404b,{0x83,0xD1,0x20,0xBB,0xFE,0x35,0xB6,0x1A}};


const IID IID_IActMLLCPU3 = {0x57D4CCE1,0x089B,0x456e,{0xA4,0x67,0x39,0x86,0xF2,0x7D,0x28,0xA1}};


const IID LIBID_ACTPCCOMLib = {0xA306B14E,0xAE98,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActQCPUQEvents = {0x9B7B98C2,0xAE9B,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const CLSID CLSID_ActQCPUQ = {0x0051AF2F,0xA877,0x11D3,{0x83,0xA8,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActQCPUAEvents = {0x9B7B98C4,0xAE9B,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const CLSID CLSID_ActQCPUA = {0x0051AF31,0xA877,0x11D3,{0x83,0xA8,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActQnACPUEvents = {0x9B7B98C6,0xAE9B,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const CLSID CLSID_ActQnACPU = {0x0051AF33,0xA877,0x11D3,{0x83,0xA8,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActACPUEvents = {0x9B7B98C8,0xAE9B,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const CLSID CLSID_ActACPU = {0x0051AF35,0xA877,0x11D3,{0x83,0xA8,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActFXCPUEvents = {0x9B7B98CA,0xAE9B,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const CLSID CLSID_ActFXCPU = {0x0051AF37,0xA877,0x11D3,{0x83,0xA8,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActMLACPUEvents = {0x455C7664,0xA971,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActMLACPU = {0x455C7663,0xA971,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActMLFXCPUEvents = {0x455C766A,0xA971,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActMLFXCPU = {0x455C7669,0xA971,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActMLQCPUAEvents = {0x455C766D,0xA971,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActMLQCPUA = {0x455C766C,0xA971,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActMLQCPUQEvents = {0x455C7671,0xA971,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActMLQCPUQ = {0x455C7670,0xA971,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActMLQnACPUEvents = {0x5A95BB46,0xA984,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActMLQnACPU = {0x5A95BB45,0xA984,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActLCPUEvents = {0x5EA8A86B,0x5947,0x447A,{0x82,0x05,0xAE,0xE8,0xF6,0x2A,0xB6,0x9B}};


const CLSID CLSID_ActLCPU = {0xA97CE402,0xCFFD,0x4097,{0x82,0xCE,0xE9,0x27,0xF8,0xB8,0x39,0x4B}};


const IID DIID__IActMLLCPUEvents = {0x3068F493,0x74FF,0x4523,{0xA7,0xA0,0x52,0x9C,0xEA,0x3B,0xDB,0x55}};


const CLSID CLSID_ActMLLCPU = {0x33260459,0xF4C9,0x45C7,{0xA4,0x54,0xAE,0xF2,0xEE,0x3C,0x34,0xEE}};


#ifdef __cplusplus
}
#endif

