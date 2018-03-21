/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Apr 12 12:31:51 2013
 */
/* Compiler settings for D:\GETMODULE\CommunicationSupport2\SW3D5\ACT\Control\ActLlt\ActLlt.idl:
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

const IID IID_IActLLT = {0x235CFC01,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID IID_IActLLT2 = {0x949316D0,0xC720,0x11d4,{0x87,0x43,0x00,0xE0,0x29,0x2A,0x4F,0xB4}};


const IID IID_IActLLT3 = {0x36BE3030,0x6B93,0x11d5,{0x93,0x11,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLLLT = {0x0742D5C1,0xA98C,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLLLT2 = {0x96771A91,0x705A,0x11d5,{0x93,0x17,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLLLT3 = {0x36BE3031,0x6B93,0x11d5,{0x93,0x11,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActSIM = {0xE43A5066,0xE58F,0x4F29,{0xBA,0x6B,0x49,0x5D,0x5A,0x61,0x10,0x46}};


const IID IID_IActSIM2 = {0xE73F293F,0x896C,0x49db,{0xAC,0xB1,0xE4,0x9B,0xDE,0x35,0xAE,0x19}};


const IID IID_IActSIM3 = {0xE222BE18,0xF1EF,0x4572,{0x87,0x3C,0x8A,0x6D,0xA7,0x33,0x22,0xD1}};


const IID IID_IActMLSIM = {0xFBD0A696,0x9BD0,0x4068,{0x9C,0x9D,0xBD,0xC1,0xD3,0x91,0x16,0x5C}};


const IID IID_IActMLSIM2 = {0x162FD970,0x7CF2,0x4061,{0x97,0x64,0x72,0x05,0x59,0x91,0x0B,0x4B}};


const IID IID_IActMLSIM3 = {0x655554DB,0x37F8,0x4439,{0x89,0xB2,0x0D,0xDB,0x1C,0xC6,0xBC,0x71}};


const IID LIBID_ACTLLTLib = {0xA306B1A9,0xAE98,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActLLTEvents = {0x235CFC03,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const CLSID CLSID_ActLLT = {0x235CFC02,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActMLLLTEvents = {0x0742D5C3,0xA98C,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActMLLLT = {0x0742D5C2,0xA98C,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActSIMEvents = {0xD8D3D4FE,0x2E70,0x4654,{0xBC,0xF8,0x18,0x05,0x74,0x9D,0x05,0x25}};


const CLSID CLSID_ActSIM = {0x89A558D1,0xD377,0x4653,{0xA1,0x9B,0x9D,0x03,0x48,0x19,0x08,0xA0}};


const IID DIID__IActMLSIMEvents = {0xF4DDF11F,0x3914,0x4C9E,{0x9D,0x63,0x86,0x7C,0xA7,0xC1,0x79,0xDA}};


const CLSID CLSID_ActMLSIM = {0xCF317B9B,0x82CF,0x4803,{0x99,0xC0,0x7B,0xB9,0x06,0xE0,0xC7,0x37}};


#ifdef __cplusplus
}
#endif

