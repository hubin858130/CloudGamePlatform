/***************************************************************************
*
* (C) Copyright 1998-1999 Rainbow Technologies, Inc. All rights reserved.
*
* Description:  iKey interface and definitions
*
* Environment:  User mode
*
* Revision History:
*
*   08/10/99: Mehdi - created
* 
****************************************************************************/

#ifndef _IKEYAPI_H_
#define _IKEYAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef IKEY_STATUS
#define IKEY_STATUS                 unsigned long
#define IKEY_API                    __stdcall
typedef void *                      IKEY_HANDLE;
#endif

#define IKEY_API_VERSION            0x200

//
// Status return values
//

#define RB_SUCCESS                  0x00
#define RB_CANNOT_OPEN_DRIVER       0x01
#define RB_INVALID_DRVR_VERSION     0x02
#define RB_INVALID_COMMAND          0x03
#define RB_ACCESS_DENIED            0x04
#define RB_ALREADY_ZERO             0x05
#define RB_UNIT_NOT_FOUND           0x06
#define RB_DEVICE_REMOVED           0x07
#define RB_COMMUNICATIONS_ERROR     0x08
#define RB_DIR_NOT_FOUND            0x09
#define RB_FILE_NOT_FOUND           0x0A
#define RB_MEM_CORRUPT              0x0B
#define RB_INTERNAL_HW_ERROR        0x0C
#define RB_INVALID_RESP_SIZE        0x0D
#define RB_PIN_EXPIRED              0x0E
#define RB_ALREADY_EXISTS           0x0F
#define RB_NOT_ENOUGH_MEMORY        0x10
#define RB_INVALID_PARAMETER        0x11
#define RB_ALIGNMENT_ERROR          0x12
#define RB_INPUT_TOO_LONG           0x13
#define RB_INVALID_FILE_SELECTED    0x14
#define RB_DEVICE_IN_USE            0x15
#define RB_INVALID_API_VERSION      0x16
#define RB_TIME_OUT_ERROR           0x17
#define RB_ITEM_NOT_FOUND           0x18
#define RB_COMMAND_ABORTED          0x19
#define RB_INVALID_STATUS           0xff

// Reserved ID's

#define IKEY_ROOT_DIR               0x0000
#define IKEY_7816_ROOT_DIR          0x3F00
#define IKEY_AUTO_ID_BASE           0xF000
#define IKEY_INDEX_FILE             0xFFFF
#define IKEY_TOKEN_NAME_FILE        0xFFFE

// iKey System Types

#define IKEY_SYS_TYPE1              1

// Maximum size of names and labels

#define IKEY_APP_NAME_SIZE          32
#define IKEY_FRIENDLY_NAME_SIZE     32

// Flags used for directory type

#define IKEY_DIR_BY_ID              0x00000100
#define IKEY_DIR_BY_LONG_ID         0x00000200
#define IKEY_DIR_BY_NAME            0x00000300
#define IKEY_DIR_BY_GUID            0x00000400
#define IKEY_DIR_BY_GUID_STR        0x00000500

#define IKEY_DIR_BY_MASK            0x00000f00

typedef struct
{
    unsigned char   MaxPinRetries;
    unsigned char   CurPinCounter;
    unsigned char   Flags;
    unsigned char   Reserved1;
    unsigned char   CreateAccess;
    unsigned char   DeleteAccess;
    unsigned char   Reserved2[10];

} IKEY_ACCESSINFO, *PIKEY_ACCESSINFO;

// IKEY_ACCESSINFO.Flags is reserved for future use and must be 0.

typedef struct
{
    unsigned long   DriverVersion;

    // Hardware information

    unsigned char   FwVersionMajor;
    unsigned char   FwVersionMinor;
    unsigned char   ProductCode;
    unsigned char   Configuration;

} IKEY_VERSIONINFO, *PIKEY_VERSIONINFO;

typedef struct
{
    unsigned long   Flags;
    unsigned long   FreeSpace;
    unsigned long   Reserved1[2];
    unsigned char   FileSysType;
    unsigned char   MaxDirLevels;
    unsigned char   Reserved2[14];

} IKEY_SYSINFO, *PIKEY_SYSINFO;

typedef struct
{
    unsigned long   Id;
    unsigned long   Flags;
    unsigned long   MaxSize;
    unsigned long   MaxEntries;
    unsigned char   Reserved[32];

} IKEY_DIRINFO, *PIKEY_DIRINFO;

// IKEY_DIRINFO.Flags is reserved for future use and must be 0.

typedef struct
{
    unsigned long   Id;
    unsigned long   Flags;
    unsigned long   FileSize;
    unsigned char   FileType;
    unsigned char   ReadAccess;
    unsigned char   WriteAccess;
    unsigned char   CryptAccess;
    unsigned char   Reserved1[12];

    unsigned char   GrantedAccess;
    unsigned char   Reserved2[15];

} IKEY_FILEINFO, *PIKEY_FILEINFO;

// IKEY_FILEINFO.Flags is reserved for future use and must be 0.

// IKEY_FILEINFO.Type

#define IKEY_FILETYPE_UNUSED        0x00
#define IKEY_FILETYPE_DIR           0x01
#define IKEY_FILETYPE_DATA          0x02
#define IKEY_FILETYPE_COUNTER       0x03
#define IKEY_FILETYPE_KEY           0x04
#define IKEY_FILETYPE_UNKNOWN       0xFF

// IKEY_FILEINFO access types

#define IKEY_ACCESS_ANYONE          0x00
#define IKEY_ACCESS_USER            0x01
#define IKEY_ACCESS_OFFICER         0x02
#define IKEY_ACCESS_NONE            0x07

// IKEY_FILEINFO.GrantedAccess definition

#define IKEY_ACCESS_READ            0x01
#define IKEY_ACCESS_WRITE           0x02
#define IKEY_ACCESS_CRYPT           0x04

// ikey capabilities definitions

#define IKEY_CAPS_MD5HMAC           0x00000001
#define IKEY_CAPS_MD5XOR            0x00000002
#define IKEY_CAPS_MD5CHAP           0x00000004
#define IKEY_CAPS_DES               0x00000008

/////////////////////////////////////////////////////////////////////////////
//
// Device access services
//
/////////////////////////////////////////////////////////////////////////////

IKEY_STATUS IKEY_API ikey_CreateContext(
    IKEY_HANDLE   * PtrContextHandle,           // [out]
    unsigned long   Flags,                      // [in]
    unsigned long   ApiVersion );               // [in]

// Flags is reserved for future use and must be 0.

IKEY_STATUS IKEY_API ikey_DeleteContext(
    IKEY_HANDLE     ContextHandle );            // [in]

IKEY_STATUS IKEY_API ikey_OpenDevice(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    void          * pAppId );                   // [in]

// Flags used by ikey_OpenDevice()

#define IKEY_OPEN_NEXT              0x00000000
#define IKEY_OPEN_FIRST             0x00000001
#define IKEY_OPEN_CURRENT           0x00000002
#define IKEY_OPEN_SPECIFIC          0x00000003
#define IKEY_OPEN_SC_HANDLE         0x00000004

#define IKEY_OPEN_MASK              0x00000007

#define IKEY_OPEN_BY_NAME           0x00000100
#define IKEY_OPEN_BY_GUID           0x00000200
#define IKEY_OPEN_BY_GUID_STR       0x00000300

#define IKEY_OPEN_BY_MASK           0x00000f00

IKEY_STATUS IKEY_API ikey_CloseDevice( 
    IKEY_HANDLE     ContextHandle );            // [in]

/////////////////////////////////////////////////////////////////////////////
//
// File access services
//
/////////////////////////////////////////////////////////////////////////////

IKEY_STATUS IKEY_API ikey_ChangeDir(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    unsigned long   DirId,                      // [in]
    unsigned char * Name );                     // [in]

// Flags uses IKEY_DIR_BY_xxx in addition to:

#define IKEY_DIR_FROM_MF            0x00000000
#define IKEY_DIR_FROM_CUR_DF        0x00000010
#define IKEY_DIR_TO_PARENT          0x00000020

IKEY_STATUS IKEY_API ikey_GetCurrentDir(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    unsigned long * Path,                       // [out]
    unsigned long   MaxLevels,                  // [in]
    unsigned long * RetLevels );                // [out]

IKEY_STATUS IKEY_API ikey_OpenFile(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    unsigned long   FileId,                     // [in]
    PIKEY_FILEINFO  FileInfo,                   // [out]
    unsigned long   SizeOfFileInfo );           // [in]

// Flags uses any combination of:

#define IKEY_FILE_READ              0x00000010
#define IKEY_FILE_WRITE             0x00000020
#define IKEY_FILE_CRYPT             0x00000040

IKEY_STATUS IKEY_API ikey_CloseFile(
    IKEY_HANDLE     ContextHandle );            // [in]

IKEY_STATUS IKEY_API ikey_Directory(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    unsigned long   Index,                      // [in]
    PIKEY_FILEINFO  FileInfo,                   // [out]
    unsigned long   SizeOfFileInfo );           // [in]

// Flags is reserved for future use and must be 0.

IKEY_STATUS IKEY_API ikey_GetFileInfo(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    unsigned long   Id,                         // [in]
    unsigned char * Name,                       // [in]
    PIKEY_FILEINFO  FileInfo,                   // [out]
    unsigned long   FileInfoSize );             // [in]

// Flags uses 0 or one of IKEY_DIR_xxx contants

IKEY_STATUS IKEY_API ikey_Read(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    unsigned long   Offset,                     // [in]
    unsigned char * Buffer,                     // [out]
    unsigned long   BytesToRead,                // [in]
    unsigned long * BytesRead );                // [out]

// Flags is reserved for future use and must be 0.

IKEY_STATUS IKEY_API ikey_Write(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    unsigned long   Offset,                     // [in]
    unsigned char * Buffer,                     // [in]
    unsigned long   BytesToWrite,               // [in]
    unsigned long * BytesWritten );             // [out]

// Flags is reserved for future use and must be 0.

IKEY_STATUS IKEY_API ikey_Decrement(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    unsigned long   Value);                     // [in]

// Flags is reserved for future use and must be 0.

IKEY_STATUS IKEY_API ikey_CreateDir( 
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    unsigned char * Name,                       // [in]
    unsigned char * Guid,                       // [in]
    PIKEY_DIRINFO   DirInfo,                    // [in][out]
    unsigned long   SizeOfDirInfo );            // [in]

// Flags uses 0 or:

#define IKEY_CREATE_AUTO_ID         0x00010000

IKEY_STATUS IKEY_API ikey_DeleteDir( 
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    unsigned long   DirId,                      // [in]
    unsigned char * Name );                     // [in]

// Flags uses one of IKEY_DIR_xxx in addition to:

#define IKEY_DELETE_RECURSIVE       0x00010000

IKEY_STATUS IKEY_API ikey_CreateFile( 
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    PIKEY_FILEINFO  FileInfo,                   // [in]
    unsigned long   SizeOfFileInfo );           // [in]

// Flags is reserved for future use and must be 0.

IKEY_STATUS IKEY_API ikey_DeleteFile( 
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    unsigned long   FileId );                   // [in]

// Flags is reserved for future use and must be 0.


//////////////////////////////////////////////////////////////////
//
// Authentication services
//
//////////////////////////////////////////////////////////////////

IKEY_STATUS IKEY_API ikey_Verify(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    unsigned char * Data,                       // [in]
    unsigned long   Size );                     // [in]

// Flags uses one of:

#define IKEY_VERIFY_USER_PIN        0x00000000
#define IKEY_VERIFY_SO_PIN          0x00000001

#define IKEY_VERIFY_NO_HASH         0x00001000

IKEY_STATUS IKEY_API ikey_ChangeCode(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    unsigned char * OldCode,                    // [in]
    unsigned long   OldCodeLen,                 // [in]
    unsigned char * NewCode,                    // [in]
    unsigned long   NewCodeLen );               // [in]

// Flags uses one of:

#define IKEY_CHANGE_USER_PIN        0x00000000
#define IKEY_UNBLOCK_USER_PIN       0x00000001
#define IKEY_CHANGE_SO_PIN          0x00000002

#define IKEY_CHANGE_MASK            0x0000000F

#define IKEY_CHANGE_NO_HASH         0x00001000

IKEY_STATUS IKEY_API ikey_ResetSecurityState(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags );                    // [in]

// Flags uses one of:
#define IKEY_SCOPE_MF               0x00000000

IKEY_STATUS IKEY_API ikey_HashToken(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    unsigned long   RefData,                    // [in]
    unsigned char * Buffer,                     // [in]
    unsigned long   BufferSize,                 // [in]
    unsigned char * Response,                   // [out]
    unsigned long   RespSize,                   // [in]
    unsigned long * ReturnedBytes );            // [out]

// Flags in ikey_HashToken()

#define IKEY_HASH_MD5_XOR           0x00
#define IKEY_HASH_MD5_HMAC          0x01
#define IKEY_HASH_MD5_CHAP          0x02
#define IKEY_HASH_TYPE_MASK         0xFF

IKEY_STATUS IKEY_API ikey_MD5_HMAC(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   FileId1,                    // [in]
    unsigned long   FileId2,                    // [in]
    unsigned char * Text,                       // [in]
    unsigned long   TextSize,                   // [in]
    unsigned char * Digest );                   // [out]

IKEY_STATUS IKEY_API ikey_MD5_CHAP(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   FileId,                     // [in]
    unsigned char   Identifier,                 // [in]
    unsigned char * Text,                       // [in]
    unsigned long   TextSize,                   // [in]
    unsigned char * Digest );                   // [out]

/////////////////////////////////////////////////////////////////////////////
//
// Misc. services
//
/////////////////////////////////////////////////////////////////////////////

unsigned long IKEY_API ikey_GetLibVersion( void );

unsigned long IKEY_API ikey_GetDriverVersion( void );

IKEY_STATUS IKEY_API ikey_GenRandom(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    unsigned char * Buffer,                     // [in][out]
    unsigned long   BufferSize );               // [in]

// Flags is reserved for future use and must be 0.

IKEY_STATUS IKEY_API ikey_Cleanup(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags );                    // [in]

IKEY_STATUS IKEY_API ikey_GetProperty(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    void          * RefData,                    // [in]
    void          * PropData,                   // [in][out]
    unsigned long   PropSize );                 // [in]

IKEY_STATUS IKEY_API ikey_SetProperty(
    IKEY_HANDLE     ContextHandle,              // [in]
    unsigned long   Flags,                      // [in]
    void          * RefData,                    // [in]
    void          * PropData,                   // [in]
    unsigned long   PropSize );                 // [in]

// Flags for ikey_GetProperty() and ikey_SetProperty uses one of:

#define IKEY_PROP_CAPABILITIES      0x00
#define IKEY_PROP_MEM_SIZE          0x01
#define IKEY_PROP_ACCESSINFO        0x03
#define IKEY_PROP_APP_NAME          0x04
#define IKEY_PROP_APP_GUID          0x05
#define IKEY_PROP_VERSIONINFO       0x06
#define IKEY_PROP_SERNUM            0x07
#define IKEY_PROP_LED_ON            0x08
#define IKEY_PROP_LED_OFF           0x09
#define IKEY_PROP_FRIENDLY_NAME     0x0B
#define IKEY_PROP_SYSINFO           0x0C

#ifdef __cplusplus
}
#endif

#endif // _IKEYAPI_H_
