#ifndef _RWCONFINTERFACE_H_
#define _RWCONFINTERFACE_H_


#ifdef __cplusplus
extern "C" {
#endif


typedef char			RWC_INT8;
typedef unsigned char	RWC_UINT8;
typedef short			RWC_INT16;
typedef unsigned short	RWC_UINT16;
typedef int				RWC_INT32;
typedef unsigned int	RWC_UINT32;

typedef RWC_INT8		RWC_CHAR;
typedef RWC_UINT8		RWC_BYTE;

typedef RWC_INT32		RWC_BOOL;

#ifdef WIN32
	typedef __int64				RWC_INT64;
	typedef unsigned __int64	RWC_UINT64;
#else
	typedef long long			RWC_INT64;
	typedef unsigned long long	RWC_UINT64;
#endif


#define RWC_TRUE		1
#define RWC_FALSE		0

typedef void			RWC_VOID;
typedef RWC_VOID*		RWC_HANDLE;

#define RWC_CONST		const

#ifdef __cplusplus
	#define RWC_NULL		0
#else
	#define RWC_NULL		(RWC_VOID*)0
#endif


#ifdef WIN32
	#ifdef LIBRWCONF_EXPORTS
		#define RWC_API		__declspec( dllexport )
	#else
		#define RWC_API		__declspec( dllimport )
	#endif
#else
	#define RWC_API
#endif

typedef struct rwcsConfItem		rwcsConfItem;
struct rwcsConfItem
{
	rwcsConfItem	*next;
	RWC_BYTE		*name;
	RWC_BYTE		*value;
};

typedef struct rwcsConfDir		rwcsConfDir;
struct rwcsConfDir
{
	rwcsConfDir		*next;
	RWC_BYTE		*name;
	rwcsConfItem	*itemList;
};

typedef RWC_INT32 (*RWC_readConfHandler)( RWC_VOID *userData, RWC_BYTE *buf, RWC_INT32 bufLen );
RWC_API rwcsConfDir* RWC_readConf( RWC_VOID *userData, RWC_readConfHandler readConfHandler );
RWC_API rwcsConfDir* RWC_readConfForDir( RWC_VOID *userData,
											RWC_readConfHandler readConfHandler,
											RWC_CONST RWC_BYTE *dirName );
RWC_API RWC_BOOL RWC_readConfForItem( RWC_VOID *userData,
										RWC_readConfHandler readConfHandler,
										RWC_CONST RWC_BYTE *dirName,
										RWC_CONST RWC_BYTE *itemName,
										RWC_BYTE *retItemValueBuf,
										RWC_INT32 retItemValueBufLen );


RWC_API rwcsConfDir* RWC_readConfFromBuf( RWC_CONST RWC_BYTE *buf, RWC_INT32 bufLen );
RWC_API rwcsConfDir* RWC_readConfForDirFromBuf( RWC_CONST RWC_BYTE *buf,
												RWC_INT32 bufLen,
												RWC_CONST RWC_BYTE *dirName );
RWC_API RWC_BOOL RWC_readConfForItemFromBuf( RWC_CONST RWC_BYTE *buf,
												RWC_INT32 bufLen,
												RWC_CONST RWC_BYTE *dirName,
												RWC_CONST RWC_BYTE *itemName,
												RWC_BYTE *retItemValueBuf,
												RWC_INT32 retItemValueBufLen );

RWC_API rwcsConfDir* RWC_readConfFromFile( RWC_CONST RWC_CHAR *filePath );
RWC_API rwcsConfDir* RWC_readConfForDirFromFile( RWC_CONST RWC_CHAR *filePath, RWC_CONST RWC_BYTE *dirName );

RWC_API RWC_BOOL RWC_readConfForItemFromFile( RWC_CONST RWC_CHAR *filePath,
												RWC_CONST RWC_BYTE *dirName,
												RWC_CONST RWC_BYTE *itemName,
												RWC_BYTE *retItemValueBuf,
												RWC_INT32 retItemValueBufLen );
RWC_API RWC_BOOL RWC_readConfForItemFromFileEx( RWC_CONST RWC_CHAR *filePath,
												RWC_CONST RWC_BYTE *dirName,
												RWC_CONST RWC_BYTE *itemName,
												RWC_BYTE *retItemValueBuf,
												RWC_INT32 retItemValueBufLen,
												RWC_CONST RWC_CHAR *defaultItemValue );

RWC_API RWC_BOOL RWC_readConfForIntItemFromFile( RWC_CONST RWC_CHAR *filePath,
													RWC_CONST RWC_BYTE *dirName,
													RWC_CONST RWC_BYTE *itemName,
													RWC_INT32 *retItemValue );
RWC_API RWC_INT32 RWC_readConfForIntItemFromFileEx( RWC_CONST RWC_CHAR *filePath,
													RWC_CONST RWC_BYTE *dirName,
													RWC_CONST RWC_BYTE *itemName,
													RWC_INT32 defaultItemValue );


RWC_API rwcsConfDir* RWC_getDirFromList( rwcsConfDir *confList, RWC_CONST RWC_BYTE *dirName );
RWC_API RWC_BYTE* RWC_getItemValueFromDir( rwcsConfDir *dir, RWC_CONST RWC_BYTE *itemName );
RWC_API RWC_BYTE* RWC_getItemValueFromList( rwcsConfDir *confList,
										   RWC_CONST RWC_BYTE *dirName,
										   RWC_CONST RWC_BYTE *itemName );



RWC_API RWC_BOOL RWC_setConfInDir( rwcsConfDir *dir,
									RWC_CONST RWC_BYTE *itemName,
									RWC_CONST RWC_BYTE *itemValue );

RWC_API RWC_BOOL RWC_setConf( rwcsConfDir **pConfList,
								RWC_CONST RWC_BYTE *dirName,
								RWC_CONST RWC_BYTE *itemName,
								RWC_CONST RWC_BYTE *itemValue );

typedef RWC_BOOL (*RWC_writeConfHandler)( RWC_VOID *userData, RWC_CONST RWC_BYTE *buf, RWC_INT32 bufLen );
RWC_API RWC_BOOL RWC_writeConf( rwcsConfDir *confList,
								RWC_VOID *userData,
								RWC_writeConfHandler writeConfHandler );

RWC_API RWC_BOOL RWC_writeConfToBuf( rwcsConfDir *confList,
										RWC_BYTE *buf,
										RWC_INT32 bufLen );

RWC_API RWC_BOOL RWC_writeConfToFile( rwcsConfDir *confList,
										RWC_CONST RWC_CHAR *filePath );

RWC_API RWC_VOID RWC_freeConf( rwcsConfDir *oldConfList );



RWC_API RWC_BOOL RWC_changeConf( RWC_CONST RWC_BYTE *dirName,
									RWC_CONST RWC_BYTE *itemName,
									RWC_CONST RWC_BYTE *itemValue,
									RWC_VOID *readUserData,
									RWC_readConfHandler readConfHandler,
									RWC_VOID *writeUserData,
									RWC_writeConfHandler writeConfHandler );

#define RWC_deleteConfItem( dirName, itemName, readUserData, readConfHandler, writeUserData, writeConfHandler )	\
							RWC_changeConf( dirName, itemName, RWC_NULL, readUserData, readConfHandler, writeUserData, writeConfHandler )

#define RWC_deleteConfDir( dirName, readUserData, readConfHandler, writeUserData, writeConfHandler )	\
							RWC_changeConf( dirName, RWC_NULL, RWC_NULL, readUserData, readConfHandler, writeUserData, writeConfHandler )


RWC_API RWC_BOOL RWC_changeConfInFile( RWC_CONST RWC_CHAR *filePath,
										RWC_CONST RWC_BYTE *dirName,
										RWC_CONST RWC_BYTE *itemName,
										RWC_CONST RWC_BYTE *itemValue );


#define RWC_deleteConfItemInFile( filePath, dirName, itemName )		\
									RWC_changeConfInFile( filePath, dirName, itemName, RWC_NULL )

#define RWC_deleteConfDirInFile( filePath, dirName )	\
									RWC_changeConfInFile( filePath, dirName, RWC_NULL, RWC_NULL );


RWC_API RWC_BOOL RWC_changeConfInFileForInt( RWC_CONST RWC_CHAR *filePath,
												RWC_CONST RWC_BYTE *dirName,
												RWC_CONST RWC_BYTE *itemName,
												RWC_CONST RWC_INT32 intValue );

#ifdef __cplusplus
}
#endif


#endif

