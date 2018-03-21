

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon Dec 05 13:00:28 2016
 */
/* Compiler settings for ActProgType.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

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

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IActProgType,0xC63A7DDA,0x64FD,0x4B97,0xB1,0x67,0xD3,0x1C,0x3C,0xC0,0x4E,0x3E);


MIDL_DEFINE_GUID(IID, IID_IActMLProgType,0x84181939,0xA078,0x42CB,0x9B,0x07,0x10,0xE2,0x88,0x9D,0x54,0xAE);


MIDL_DEFINE_GUID(IID, LIBID_ActProgTypeLib,0xCD7846DF,0x1C99,0x4BC0,0x8A,0x8D,0xFB,0xFB,0x7F,0xC2,0x6A,0xCB);


MIDL_DEFINE_GUID(IID, DIID__IActProgTypeEvents,0x1DA9A278,0x2C46,0x4EDE,0x8D,0x65,0x7D,0x3B,0xC9,0x59,0x28,0x16);


MIDL_DEFINE_GUID(CLSID, CLSID_ActProgType,0x78703D55,0x4042,0x4046,0x84,0x5D,0x7B,0xBE,0x83,0xFB,0x2F,0x44);


MIDL_DEFINE_GUID(IID, DIID__IActMLProgTypeEvents,0x8CA3FFF9,0xD42E,0x4782,0x8F,0x74,0x6A,0xEA,0xE7,0xF3,0x53,0xEC);


MIDL_DEFINE_GUID(CLSID, CLSID_ActMLProgType,0xD10D1FE3,0x1D76,0x4B8B,0xAD,0xFC,0xCE,0x03,0xF9,0x33,0x7C,0xD3);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



