/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Apr 12 12:33:36 2013
 */
/* Compiler settings for D:\GETMODULE\CommunicationSupport2\SW3D5\ACT\Control\ActMulti\ActMulti.idl:
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

const IID IID_IActEasyIF = {0x5AF69F11,0xAE9B,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID IID_IActEasyIF2 = {0xAD41D950,0xC773,0x11d4,{0x87,0x43,0x00,0xE0,0x29,0x2A,0x4F,0xB4}};


const IID IID_IActEasyIF3 = {0x8716604E,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLEasyIF = {0x95D00011,0xAB2E,0x11D4,{0x99,0x85,0x00,0x90,0x99,0x17,0x34,0x19}};


const IID IID_IActMLEasyIF2 = {0x8716604F,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLEasyIF3 = {0x87166050,0x710B,0x11d5,{0x93,0x18,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID LIBID_ACTMULTILib = {0xA306B141,0xAE98,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActEasyIFEvents = {0x5AF69F13,0xAE9B,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const CLSID CLSID_ActEasyIF = {0x5AF69F12,0xAE9B,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActMLEasyIFEvents = {0x95D00013,0xAB2E,0x11D4,{0x99,0x85,0x00,0x90,0x99,0x17,0x34,0x19}};


const CLSID CLSID_ActMLEasyIF = {0x95D00012,0xAB2E,0x11D4,{0x99,0x85,0x00,0x90,0x99,0x17,0x34,0x19}};


#ifdef __cplusplus
}
#endif

