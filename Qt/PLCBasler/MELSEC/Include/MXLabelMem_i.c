

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Mon Dec 05 13:02:27 2016
 */
/* Compiler settings for .\MXLabelMem.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

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

MIDL_DEFINE_GUID(IID, IID_IMXLabelMemControl,0x8FFE1A45,0x8A1E,0x4DD8,0xAB,0x34,0xE2,0xEB,0x3A,0xEC,0x90,0x49);


MIDL_DEFINE_GUID(IID, LIBID_MXLabelMemLib,0xB0840F52,0xD713,0x4A9D,0xB0,0x39,0x43,0x58,0x9F,0x4C,0xEB,0xA2);


MIDL_DEFINE_GUID(IID, DIID__IMXLabelMemControlEvents,0x78EFB36D,0x1CE2,0x458B,0xA4,0xEB,0x84,0x4B,0x13,0x00,0xC6,0x28);


MIDL_DEFINE_GUID(CLSID, CLSID_MXLabelMemControl,0x18B34EAC,0x5D01,0x4F57,0xA9,0x6F,0xED,0xB0,0x0A,0xF3,0x5C,0x1F);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



