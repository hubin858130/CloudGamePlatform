#ifndef _MIOTHREAD_H_
#define _MIOTHREAD_H_

#include "msgpretype.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32

	#include <windows.h>

	typedef HANDLE			MIO_THREAD;
	typedef HANDLE			MIO_MUTEX;
	typedef HANDLE			MIO_SEM;
	typedef HANDLE			MIO_PROCESS_MUTEX;

#else

	#include <pthread.h>
	#include <time.h>
	#include <errno.h>
	#include <fcntl.h>
	#include <sys/stat.h>
	#include <string.h>
	#include <semaphore.h>

	typedef pthread_t			MIO_THREAD;
	typedef pthread_mutex_t		MIO_MUTEX;
	typedef sem_t				MIO_SEM;

#define MIO_PROCESS_MUTEX_NAME_MAXLEN		256
	typedef struct{
		sem_t		*sem_named;
		MIO_MUTEX	mutex;
		MIO_CHAR	name[MIO_PROCESS_MUTEX_NAME_MAXLEN + 1];
	}MIO_PROCESS_MUTEX;

#endif


MIO_BOOL mio_thread_create( MIO_THREAD *retThread, MIO_VOID *(*func) (MIO_VOID *), MIO_VOID *arg );
MIO_VOID mio_thread_join( MIO_THREAD *thread );

MIO_BOOL mio_mutex_init( MIO_MUTEX *retMutex );
MIO_VOID mio_mutex_destroy( MIO_MUTEX *mutex );
MIO_BOOL mio_mutex_lock( MIO_MUTEX *mutex );
MIO_BOOL mio_mutex_unlock( MIO_MUTEX *mutex );

MIO_BOOL mio_sem_init( MIO_SEM *retSem );
MIO_VOID mio_sem_destroy( MIO_SEM *sem );
MIO_BOOL mio_sem_post( MIO_SEM *sem );
MIO_BOOL mio_sem_timed_wait( MIO_SEM *sem, MIO_UINT32 timeout );
MIO_BOOL mio_sem_wait( MIO_SEM *sem );

MIO_BOOL mio_process_mutex_init( MIO_PROCESS_MUTEX *retMutex, MIO_CONST MIO_CHAR *name );
MIO_VOID mio_process_mutex_destroy( MIO_PROCESS_MUTEX *mutex );
MIO_BOOL mio_process_mutex_lock( MIO_PROCESS_MUTEX *mutex );
MIO_BOOL mio_process_mutex_unlock( MIO_PROCESS_MUTEX *mutex );


///////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////

MIO_API MIO_BOOL MIO_threadCreate( MIO_THREAD *retThread, MIO_VOID *(*func) (MIO_VOID *), MIO_VOID *arg );
MIO_API MIO_VOID MIO_threadJoin( MIO_THREAD *thread );

MIO_API MIO_BOOL MIO_mutexInit( MIO_MUTEX *retMutex );
MIO_API MIO_VOID MIO_mutexDestroy( MIO_MUTEX *mutex );
MIO_API MIO_BOOL MIO_mutexLock( MIO_MUTEX *mutex );
MIO_API MIO_BOOL MIO_mutexUnlock( MIO_MUTEX *mutex );

MIO_API MIO_BOOL MIO_semInit( MIO_SEM *retSem );
MIO_API MIO_VOID MIO_semDestroy( MIO_SEM *sem );
MIO_API MIO_BOOL MIO_semPost( MIO_SEM *sem );
MIO_API MIO_BOOL MIO_semTimedWait( MIO_SEM *sem, MIO_UINT32 timeout );
MIO_API MIO_BOOL MIO_semWait( MIO_SEM *sem );

MIO_API MIO_BOOL MIO_processMutexInit( MIO_PROCESS_MUTEX *retMutex, MIO_CONST MIO_CHAR *name );
MIO_API MIO_VOID MIO_processMutexDestroy( MIO_PROCESS_MUTEX *mutex );
MIO_API MIO_BOOL MIO_processMutexLock( MIO_PROCESS_MUTEX *mutex );
MIO_API MIO_BOOL MIO_processMutexUnlock( MIO_PROCESS_MUTEX *mutex );


#ifdef __cplusplus
}
#endif

#endif

