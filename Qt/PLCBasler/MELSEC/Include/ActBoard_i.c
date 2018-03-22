/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Apr 12 12:29:45 2013
 */
/* Compiler settings for D:\GETMODULE\CommunicationSupport2\SW3D5\ACT\Control\ActBoard\ActBoard.idl:
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

const IID IID_IActMnet2BD = {0x4F766941,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID IID_IActMnet2BD2 = {0xAD2989F0,0xC72E,0x11d4,{0x87,0x43,0x00,0xE0,0x29,0x2A,0x4F,0xB4}};


const IID IID_IActMnet2BD3 = {0x38E1ED21,0x6EA3,0x11d5,{0x93,0x13,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMnet10BD = {0x4F766944,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID IID_IActMnet10BD2 = {0xAD2989F1,0xC72E,0x11d4,{0x87,0x43,0x00,0xE0,0x29,0x2A,0x4F,0xB4}};


const IID IID_IActMnet10BD3 = {0x38E1ED22,0x6EA3,0x11d5,{0x93,0x13,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActCCBD = {0x4F766947,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID IID_IActCCBD2 = {0xAD2989F4,0xC72E,0x11d4,{0x87,0x43,0x00,0xE0,0x29,0x2A,0x4F,0xB4}};


const IID IID_IActCCBD3 = {0x38E1ED23,0x6EA3,0x11d5,{0x93,0x13,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActAnUBD = {0x4F76694A,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID IID_IActAnUBD2 = {0xAD2989F3,0xC72E,0x11d4,{0x87,0x43,0x00,0xE0,0x29,0x2A,0x4F,0xB4}};


const IID IID_IActAnUBD3 = {0x38E1ED24,0x6EA3,0x11d5,{0x93,0x13,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActAFBD = {0x4F76694D,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID IID_IActAFBD2 = {0xAD2989F2,0xC72E,0x11d4,{0x87,0x43,0x00,0xE0,0x29,0x2A,0x4F,0xB4}};


const IID IID_IActAFBD3 = {0x38E1ED25,0x6EA3,0x11d5,{0x93,0x13,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLMnet2BD = {0x6F4E3FE4,0xA994,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLMnet2BD2 = {0x96771A96,0x705A,0x11d5,{0x93,0x17,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLMnet2BD3 = {0x38E1ED26,0x6EA3,0x11d5,{0x93,0x13,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLMnet10BD = {0x6F4E3FE7,0xA994,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLMnet10BD2 = {0x96771A95,0x705A,0x11d5,{0x93,0x17,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLMnet10BD3 = {0x38E1ED27,0x6EA3,0x11d5,{0x93,0x13,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLCCBD = {0x6F4E3FEA,0xA994,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLCCBD2 = {0x96771A94,0x705A,0x11d5,{0x93,0x17,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLCCBD3 = {0x38E1ED28,0x6EA3,0x11d5,{0x93,0x13,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLAnUBD = {0x6F4E3FED,0xA994,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLAnUBD2 = {0x96771A93,0x705A,0x11d5,{0x93,0x17,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLAnUBD3 = {0x38E1ED29,0x6EA3,0x11d5,{0x93,0x13,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLAFBD = {0x6F4E3FF0,0xA994,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLAFBD2 = {0x96771A92,0x705A,0x11d5,{0x93,0x17,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLAFBD3 = {0x38E1ED2A,0x6EA3,0x11d5,{0x93,0x13,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMnetHBD = {0x062B9B43,0xAA34,0x11D4,{0x91,0x0F,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMnetHBD2 = {0x9D9ECFB0,0xCA5A,0x11d4,{0x87,0x46,0x00,0xE0,0x29,0x2A,0x4F,0xB4}};


const IID IID_IActMnetHBD3 = {0x38E1ED2B,0x6EA3,0x11d5,{0x93,0x13,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLMnetHBD = {0x062B9B46,0xAA34,0x11D4,{0x91,0x0F,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLMnetHBD2 = {0x96771A97,0x705A,0x11d5,{0x93,0x17,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMLMnetHBD3 = {0x38E1ED2C,0x6EA3,0x11d5,{0x93,0x13,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID IID_IActMnetGBD = {0xB4E57265,0xF0F3,0x4D67,{0x9E,0x54,0xA1,0x48,0x08,0x2D,0x84,0x66}};


const IID IID_IActMnetGBD2 = {0x8CA137BC,0x352A,0x477f,{0xB5,0x50,0xD9,0xE7,0x59,0xBD,0xC5,0x0E}};


const IID IID_IActMnetGBD3 = {0x3573F9AE,0x0E22,0x4522,{0x94,0x7D,0xB5,0x36,0xC2,0x44,0xE9,0x72}};


const IID IID_IActMLMnetGBD = {0xB4306CD9,0x0405,0x4347,{0x8B,0x04,0x3D,0xD4,0x19,0x60,0xD5,0xD6}};


const IID IID_IActMLMnetGBD2 = {0x721CA8A8,0x5352,0x4dde,{0x97,0x26,0xF8,0x5D,0x09,0x94,0x7A,0x4C}};


const IID IID_IActMLMnetGBD3 = {0x1A012F41,0xBD5F,0x4baa,{0xAA,0xC0,0x66,0x7E,0x86,0xA7,0xF7,0x40}};


const IID LIBID_ACTBOARDLib = {0xA306B18F,0xAE98,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActMnet2BDEvents = {0x4F766943,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const CLSID CLSID_ActMnet2BD = {0x4F766942,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActMnet10BDEvents = {0x4F766946,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const CLSID CLSID_ActMnet10BD = {0x4F766945,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActCCBDEvents = {0x4F766949,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const CLSID CLSID_ActCCBD = {0x4F766948,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActAnUBDEvents = {0x4F76694C,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const CLSID CLSID_ActAnUBD = {0x4F76694B,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActAFBDEvents = {0x4F76694F,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const CLSID CLSID_ActAFBD = {0x4F76694E,0xAE9E,0x11D3,{0x83,0xAE,0x00,0xA0,0x24,0xBD,0xBF,0x2B}};


const IID DIID__IActMLMnet2BDEvents = {0x6F4E3FE6,0xA994,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActMLMnet2BD = {0x6F4E3FE5,0xA994,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActMLMnet10BDEvents = {0x6F4E3FE9,0xA994,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActMLMnet10BD = {0x6F4E3FE8,0xA994,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActMLCCBDEvents = {0x6F4E3FEC,0xA994,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActMLCCBD = {0x6F4E3FEB,0xA994,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActMLAnUBDEvents = {0x6F4E3FEF,0xA994,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActMLAnUBD = {0x6F4E3FEE,0xA994,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActMLAFBDEvents = {0x6F4E3FF2,0xA994,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActMLAFBD = {0x6F4E3FF1,0xA994,0x11D4,{0x91,0x0D,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActMnetHBDEvents = {0x062B9B45,0xAA34,0x11D4,{0x91,0x0F,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActMnetHBD = {0x062B9B44,0xAA34,0x11D4,{0x91,0x0F,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActMLMnetHBDEvents = {0x062B9B48,0xAA34,0x11D4,{0x91,0x0F,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const CLSID CLSID_ActMLMnetHBD = {0x062B9B47,0xAA34,0x11D4,{0x91,0x0F,0x00,0x90,0x99,0x24,0x4E,0xFD}};


const IID DIID__IActMnetGBDEvents = {0xF2EBD806,0x83B3,0x4AE8,{0x8C,0x33,0xEB,0x20,0x11,0xF5,0xB1,0xC6}};


const CLSID CLSID_ActMnetGBD = {0x6B6A8F0E,0xB29E,0x4498,{0xA8,0x0A,0x45,0xC6,0x71,0x8A,0xAD,0xD8}};


const IID DIID__IActMLMnetGBDEvents = {0xCD91503F,0x480A,0x4D26,{0x93,0x0F,0xD2,0xD5,0xAE,0x18,0xF0,0xED}};


const IID IID_IActCCIEFBD = {0xD776BBCB,0xDA91,0x43F3,{0x89,0x2F,0xB0,0xFF,0x43,0xEB,0x30,0xF3}};


const IID IID_IActCCIEFBD2 = {0xE681ABA0,0xB6F4,0x498d,{0xBD,0x1A,0xF3,0xD1,0x52,0x96,0xB0,0xCD}};


const IID IID_IActCCIEFBD3 = {0x214D2DB7,0x8DBC,0x4c91,{0x92,0x06,0xBC,0x62,0x0B,0x9F,0x90,0xF3}};


const CLSID CLSID_ActMLMnetGBD = {0xD9D71187,0x3CA7,0x44BA,{0xB5,0xF7,0x33,0xCE,0xC9,0x4C,0xD9,0x48}};


const IID DIID__IActCCIEFBDEvents = {0x4ABA92FD,0xCEDA,0x4AE4,{0xB7,0x75,0x4D,0xBA,0xD1,0x04,0xF3,0x38}};


const IID IID_IActMLCCIEFBD = {0xE53EC7C3,0xABA6,0x42D2,{0x8D,0xC4,0xB7,0x1B,0x4E,0xAA,0x5C,0x68}};


const IID IID_IActMLCCIEFBD2 = {0x7109E0D7,0xDD39,0x4c25,{0x9E,0x6F,0xD2,0xDF,0xC0,0x96,0x5F,0xC6}};


const IID IID_IActMLCCIEFBD3 = {0x260E60A9,0xD664,0x4ed8,{0x8B,0xAB,0x6D,0x48,0xF5,0xB7,0x74,0x69}};


const CLSID CLSID_ActCCIEFBD = {0x0997E98E,0x7B85,0x4F52,{0x8B,0x82,0x3F,0x9F,0xD4,0x5C,0xDF,0x4F}};


const IID DIID__IActMLCCIEFBDEvents = {0x886CFD76,0x57A2,0x4819,{0xBB,0x51,0x55,0xC7,0xD0,0xA8,0x30,0xE4}};


const CLSID CLSID_ActMLCCIEFBD = {0xB2247CC4,0x56FF,0x449E,{0xAB,0xD2,0xA8,0x22,0x14,0x55,0xA6,0x57}};


#ifdef __cplusplus
}
#endif
