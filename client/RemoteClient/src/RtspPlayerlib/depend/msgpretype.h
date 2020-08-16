#ifndef _MSGPRETYPE_H_
#define _MSGPRETYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef char			MIO_INT8;
typedef unsigned char	MIO_UINT8;
typedef short			MIO_INT16;
typedef unsigned short	MIO_UINT16;
typedef int				MIO_INT32;
typedef unsigned int	MIO_UINT32;

typedef double			MIO_DOUBLE;

typedef MIO_INT8		MIO_CHAR;
typedef MIO_UINT8		MIO_BYTE;

typedef MIO_INT32		MIO_BOOL;

#ifdef WIN32
	typedef __int64				MIO_INT64;
	typedef unsigned __int64	MIO_UINT64;
#else
	typedef long long			MIO_INT64;
	typedef unsigned long long	MIO_UINT64;
#endif


#define MIO_TRUE		1
#define MIO_FALSE		0

typedef void			MIO_VOID;
typedef MIO_VOID*		MIO_HANDLE;

#define MIO_CONST		const

#ifdef __cplusplus
	#define MIO_NULL		0
#else
	#define MIO_NULL		(MIO_VOID*)0
#endif

#define MIO_IPADDR_TYPE_V4		1
#define MIO_IPADDR_TYPE_V6		2

#define MIO_IPADDR_MAXBYTES		16

typedef struct MIO_IPADDR{
	MIO_UINT8		type;
	MIO_BYTE		addr[MIO_IPADDR_MAXBYTES];
}MIO_IPADDR;


typedef MIO_UINT64		MIO_TIME;

#define MIO_PTR_TO_INT(ptr)		(((MIO_BYTE*)(ptr))-((MIO_BYTE*)0))
#define MIO_INT_TO_PTR(i)		((MIO_VOID*)(((MIO_BYTE*)0)+(i)))


extern MIO_UINT32 g_encoder_es_flag;
extern MIO_UINT32 g_decoder_es_flag;


#ifdef WIN32
	#if ( defined( LIBMSGIO_EXPORTS ) || defined ( MEDIASIPDLL_EXPORTS ) )
		#define MIO_API		__declspec( dllexport )
	#elif defined ( USE_OUTSIDE_OSIPSTACK )
		#define MIO_API
	#else
		#define MIO_API		__declspec( dllimport )
	#endif
#else
	#define MIO_API
#endif


#ifdef __cplusplus
}
#endif


#endif

