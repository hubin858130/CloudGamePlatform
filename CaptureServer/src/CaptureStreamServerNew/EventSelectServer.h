/////////////////////////////////////////////////////
// EventSelectServer.h文件

int IoDomain(OnEventUserIOStatus pStatusCb);

//心跳相关
typedef struct _NETHEARTBEATINFO
{
	void*		  pThread;
	//	PSOCKET_OBJ   pSocket;
	long		  lLastTime;//ms
	_NETHEARTBEATINFO()
	{
		pThread = NULL;
		//		pSocket = NULL;
		lLastTime = 0;
	}
}NETHEARTBEATINFO, *PNETHEARTBEATINFO;

// 套节字对象
typedef struct _SOCKET_OBJ
{
	SOCKET s;					// 套节字句柄
	HANDLE event;				// 与此套节字相关联的事件对象句柄
	sockaddr_in addrRemote;		// 客户端地址信息

	bool  bSendTag;				// 能否发送大数据块的标志
	bool  bBeginHeatbeat;       // 开启心跳检查标志
	PNETHEARTBEATINFO  pHeartInfo;//心跳

	_SOCKET_OBJ *pNext;			// 指向下一个SOCKET_OBJ对象，为的是连成一个表
} SOCKET_OBJ, *PSOCKET_OBJ;

// 线程对象
typedef struct _THREAD_OBJ
{
	HANDLE events[WSA_MAXIMUM_WAIT_EVENTS];	// 记录当前线程要等待的事件对象的句柄
	int nSocketCount;						// 记录当前线程处理的套节字的数量 <=  WSA_MAXIMUM_WAIT_EVENTS

	PSOCKET_OBJ pSockHeader;				// 当前线程处理的套节字对象列表，pSockHeader指向表头
	PSOCKET_OBJ pSockTail;					// pSockTail指向表尾

	CRITICAL_SECTION cs;					// 关键代码段变量，为的是同步对本结构的访问
	_THREAD_OBJ *pNext;						// 指向下一个THREAD_OBJ对象，为的是连成一个表

} THREAD_OBJ, *PTHREAD_OBJ;



