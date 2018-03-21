

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon Dec 05 13:01:31 2016
 */
/* Compiler settings for ActSupportMsg.idl:
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

MIDL_DEFINE_GUID(IID, IID_IActSupportMsg,0x13D4BA2D,0x26B4,0x4194,0xA9,0x65,0x9B,0x14,0x84,0x2D,0xAB,0xC8);


MIDL_DEFINE_GUID(IID, IID_IActMLSupportMsg,0xA1D87A6D,0xE020,0x4CB7,0xBC,0x38,0xBD,0xE4,0xDD,0x84,0xB7,0x7B);


MIDL_DEFINE_GUID(IID, LIBID_ActSupportMsgLib,0x1D04DB40,0xF956,0x4DC0,0xA3,0x34,0xE7,0xFA,0x2E,0x4F,0xEF,0x5A);


MIDL_DEFINE_GUID(IID, DIID__IActSupportMsgEvents,0x226E9B0B,0xE9FB,0x46EB,0x9F,0xDD,0x0B,0x20,0xC8,0x87,0xF4,0x5C);


MIDL_DEFINE_GUID(CLSID, CLSID_ActSupportMsg,0x15C5A7A2,0x53A5,0x445C,0xB2,0x94,0xF3,0x83,0xF9,0x51,0xAC,0x92);


MIDL_DEFINE_GUID(IID, DIID__IActMLSupportMsgEvents,0xD3779B1B,0x1D42,0x47DA,0x8D,0xC9,0x32,0xE9,0xEE,0x60,0x15,0x9A);


MIDL_DEFINE_GUID(CLSID, CLSID_ActMLSupportMsg,0xAE77FCC7,0xA9DC,0x4A11,0xA2,0x5C,0x04,0xB7,0xC4,0x4E,0x32,0xE6);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



