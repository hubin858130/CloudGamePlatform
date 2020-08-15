#include "stdafx.h"
#include "Ev_Socket.h"

#if defined(_WINDOWS) || WIN32
# include <stdio.h>
# include <winsock2.h>
#include <time.h>
#include <string>
#include <errno.h>

using std::string;

# define EINPROGRESS	WSAEINPROGRESS
# define EWOULDBLOCK	WSAEWOULDBLOCK
# define ETIMEDOUT	    WSAETIMEDOUT

#pragma comment( lib, "ws2_32.lib" )

static void initWinSock()
{
	static bool wsInit = false;
	if (! wsInit)
	{
		WORD wVersionRequested = MAKEWORD( 2, 0 );
		WSADATA wsaData;
		WSAStartup(wVersionRequested, &wsaData);
		wsInit = true;
	}
}


#else

extern "C" {
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netinet/tcp.h>
# include <netdb.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
#include <string.h>
}

static void initWinSock()
{
	static bool wsInit = false;
	if (! wsInit)
	{
		// 代替系统在对端socket close情况下的处理
		signal(SIGPIPE,SIG_IGN);
		wsInit = true;
	}
}

#endif  // _WINDOWS

static inline bool nonFatalError()
{
	int err = CDayeBasicSocket::getError();
	return (err == EINPROGRESS || err == EAGAIN || err == EWOULDBLOCK || err == EINTR || err == 0);
}

int CDayeBasicSocket::socket()
{
	initWinSock();
#if defined(WIN32)
	SOCKET sock = ::socket(AF_INET, SOCK_STREAM, 0);
#else
	int sock = ::socket(AF_INET, SOCK_STREAM, 0);
#endif
	if (sock >= 0)
	{
		int nrcvbuf = 1024*1024*4;
		setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char *)&nrcvbuf, sizeof(nrcvbuf));
		int nsndbuf = 1024*1024;//524288;	//512KB
		setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char *)&nsndbuf, sizeof(nsndbuf));
	}

	return (int) sock;
}

void CDayeBasicSocket::close(int fd)
{
#if defined(_WINDOWS) || WIN32
	closesocket(fd);
#else
	shutdown(fd, 2);
	::close(fd);
#endif // _WINDOWS
}

bool CDayeBasicSocket::setNonBlocking(int fd)
{
#if defined(_WINDOWS) || WIN32
	unsigned long flag = 1;
	return (ioctlsocket((SOCKET)fd, FIONBIO, &flag) == 1); //huqb
#else
	return (fcntl(fd, F_SETFL, O_NONBLOCK) == 0);
#endif // _WINDOWS
}

bool CDayeBasicSocket::setReuseAddr(int fd)
{
	// 允许socket被重用
	int sflag = 1;
	return (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&sflag, sizeof(sflag)) == 0);
}

// 设置立即关闭
bool CDayeBasicSocket::SetNoLinger(int fd)
{
	linger lge;
	lge.l_onoff = 1;
	lge.l_linger = 0;
	return (setsockopt(fd, SOL_SOCKET, SO_LINGER, (const char *)&lge, sizeof(lge)) == 0);
}

// 设置tcp_nodelay
bool CDayeBasicSocket::SetTcpNodelay(int socket)
{
	int flag = 1;
	return (setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int)) == 0); 
}

// 绑定到指定端口
bool CDayeBasicSocket::bind(int fd, int port)
{
	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons((u_short) port);
	return (::bind(fd, (struct sockaddr *)&saddr, sizeof(saddr)) == 0);
}

// 设置socket为监听模式
bool  CDayeBasicSocket::listen(int fd, int backlog)
{
	return (::listen(fd, backlog) == 0);
}

int CDayeBasicSocket::accept(int fd)
{
	struct sockaddr_in addr;
#if defined(_WINDOWS) || WIN32
	int
#else
	socklen_t
#endif

		addrlen = sizeof(addr);

	return (int) ::accept(fd, (struct sockaddr*)&addr, &addrlen);
}

// 连接服务器
bool CDayeBasicSocket::connect(int fd, std::string& host, int port)
{
	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;

	struct hostent *hp = gethostbyname(host.c_str());
	if (hp == 0) return false;

	saddr.sin_family = hp->h_addrtype;
	memcpy(&saddr.sin_addr, hp->h_addr, hp->h_length);
	saddr.sin_port = htons((u_short) port);

	// For asynch operation, this will return EWOULDBLOCK (windows) or
	// EINPROGRESS (linux) and we just need to wait for the socket to be writable...

	clock_t timeBegin = clock();
	int result = ::connect(fd, (struct sockaddr *)&saddr, sizeof(saddr));
	clock_t timeEnd = clock();

	if (result == -1)
	{
#if defined(WIN32)
		int nError = WSAGetLastError();		
#else
		int nError = errno;		
#endif

	}

	return result == 0 || nonFatalError();
}

bool CDayeBasicSocket::nbRead(int fd, std::string& s, bool *eof, int& nError, int nTimeout )
{
	static int nLastfd = -1;
	static int nLastError = 0;

	const int READ_SIZE = 4096;
	char readBuf[READ_SIZE] = {0};

	bool wouldBlock = false;
	*eof = false;

	struct timeval timeout;
	timeout.tv_sec = nTimeout;
	timeout.tv_usec = 0;

	fd_set outFd,inFd,excFd;
	FD_ZERO(&inFd);
	FD_ZERO(&outFd);
	FD_ZERO(&excFd);

	FD_SET(fd, &inFd);
	int nEvents = select(fd+1, &inFd, &outFd, &excFd, &timeout);
	if (nEvents<0)
	{
		return false;
	}
	if (nEvents == 0)
	{
		return false;
	}

	while ( ! wouldBlock && ! *eof)
	{
		int n = recv(fd, readBuf, READ_SIZE-1, 0);

		if (n > 0)
		{
			readBuf[n] = 0;
			s.append(readBuf, n);
		}
		else if (n == 0)
		{
			*eof = true;
		}
		else if (nonFatalError())
		{
			wouldBlock = true;
		}
		else
		{
#if defined(WIN32)
			nError = WSAGetLastError();
#else
			nError = errno;
#endif
			return false;
		}
	}
	return true;
}

// 从指定的socket上读取指定长度的数据 返回false失败
bool nbRead(int fd, std::string& s, int nReadLen,bool *eof, int& nError)
{
	static int nLastfd = -1;
	static int nLastError = 0;

	const int READ_SIZE = 4096;
	char readBuf[READ_SIZE];
	int nTotalRecvLen = 0;

	bool wouldBlock = false;
	*eof = false;

	while ( ! wouldBlock && ! *eof)
	{
		int nCurRecvLen = nReadLen - nTotalRecvLen;
		if (nCurRecvLen > READ_SIZE)
		{
			nCurRecvLen = READ_SIZE;
		}
		int n = recv(fd, readBuf, nCurRecvLen-1, 0);

		if (n > 0)
		{
			readBuf[n] = 0;
			s.append(readBuf, n);

			nTotalRecvLen+= n;
			if (nTotalRecvLen == nReadLen)
			{
				*eof = true;
			}
		}
		else if (nonFatalError())
		{
			wouldBlock = true;
		}
		else
		{
#if defined(WIN32)
			nError = WSAGetLastError();
#else
			nError = errno;
#endif
			return false;
		}
	}
	return true;
}

// 写入数据
bool CDayeBasicSocket::nbWrite(int fd, char *pSendBuffer, int nSendSize, int *bytesSoFar)
{
	struct timeval timeout;
	timeout.tv_sec = 10;
	timeout.tv_usec = 0;

	static int nLastfd = -1;
	static int nLastError = 0;
	
	if ( NULL == pSendBuffer || nSendSize <= 0 )
	{
		return false;
	}
	int nToWrite = nSendSize;//int(s.length()) - *bytesSoFar;
	char *sp = const_cast<char*>(pSendBuffer) + *bytesSoFar;//const_cast<char*>(s.c_str()) + *bytesSoFar;
	bool wouldBlock = false;
	int sendsize = 0;
	char *writep = sp;

	fd_set outFd,inFd,excFd;
	FD_ZERO(&inFd);
	FD_ZERO(&outFd);
	FD_ZERO(&excFd);

	FD_SET(fd, &outFd);
	int nEvents = select(fd+1, &inFd, &outFd, &excFd, &timeout);
	if (nEvents<0)
	{

		return false;
	}
	if (nEvents == 0)
	{
		return false;
	}

	while ( nToWrite > 0 && ! wouldBlock )
	{
		int nCurrentSendSize = nToWrite;
		if (nCurrentSendSize > 64*1024)
		{
			nCurrentSendSize = 64*1024;
		}
		int n = send(fd, sp, nCurrentSendSize, 0);

		if (n > 0)
		{
			sp += n;
			*bytesSoFar += n;
			nToWrite -= n;
			sendsize += n;
		}
		else if (nonFatalError())
		{
			wouldBlock = true;

			// 在发送buf不够时,会出现未发送完数据却收到非致命错误的情况,需要外面调用者继续发送
			if( sendsize != nSendSize )
			{
//				printf("|||| 要发送数据 %d,  实际发送长度:  %d \r\n.", nSendSize, sendsize );
				return true;	
			}
		}
		else
		{
#if defined(WIN32)
			int nError = WSAGetLastError();
#else
			int nError = errno;
#endif
			if ((nError != nLastError) && (nLastfd != fd))
			{
				nLastfd = fd;
				nLastError = nError;
			}
			else
			{
			}

			return false;   // Error
		}
	}

	if ( nSendSize == sendsize )
	{
//		printf("要发送数据 %d,  实际发送长度:  %d.\r\n", nSendSize, sendsize );
	}
	else
	{
		printf("发送数据错误......要发送数据 %d,  实际发送长度:  %d.\r\n", nSendSize, sendsize );
	}
	
	return true;
}

// 返回最后一个错误
int CDayeBasicSocket::getError()
{
#if defined(_WINDOWS)
	return WSAGetLastError();
#else
	return errno;
#endif
}

// 返回最后错误描述
std::string CDayeBasicSocket::getErrorMsg()
{
#if defined(WIN32)
	return getErrorMsg(getError());
#else
	return string(strerror(errno));
#endif
}

// 根据错误号返回描述
std::string CDayeBasicSocket::getErrorMsg(int nError)
{
	switch (nError)
	{
	case WSAEWOULDBLOCK:
		return "无法立即完成一个非阻挡性套接字操作";
		break;
	case WSAEINPROGRESS:
		return "目前正在执行一个阻挡性操作";
		break;
	case WSAEALREADY:
		return "在一个非阻挡套接字上尝试了一个已经在进行的操作";
		break;
	case WSAENOTSOCK:
		return "在一个非套接字上尝试了一个操作";
		break;
	case WSAEDESTADDRREQ:
		return "请求的地址在一个套接字中从操作中忽略";
		break;
	case WSAEMSGSIZE:
		return "一个在数据报套接字上发送的消息大于内部消息缓冲器或其他一些网络限制，或该用户用于接收数据报的缓冲器比数据报小";
		break;
	case WSAEPROTOTYPE:
		return "在套接字函数调用中指定的一个协议不支持请求的套接字类型的语法";
		break;
	case WSAENOPROTOOPT:
		return "在 getsockopt 或 setsockopt 调用中指定的一个未知的、无效的或不受支持的选项或层次";
		break;
	case WSAEPROTONOSUPPORT:
		return "请求的协议还没有在系统中配置，或者没有它存在的迹象";
		break;
	case WSAESOCKTNOSUPPORT:
		return "在这个地址家族中不存在对指定的插槽类型的支持";
		break;
	case WSAEOPNOTSUPP:
		return "参考的对象类型不支持尝试的操作";
		break;
	case WSAEPFNOSUPPORT:
		return "协议家族尚未配置到系统中或没有它的存在迹象";
		break;
	case WSAEAFNOSUPPORT:
		return "使用了与请求的协议不兼容的地址";
		break;
	case WSAEADDRINUSE:
		return "通常每个套接字地址(协议/网络地址/端口)只允许使用一次";
		break;
	case WSAEADDRNOTAVAIL:
		return "在其上下文中，该请求的地址无效";
		break;
	case WSAENETDOWN:
		return "套接字操作遇到了一个已死的网络";
		break;
	case WSAENETUNREACH:
		return "向一个无法连接的网络尝试了一个套接字操作";
		break;
	case WSAENETRESET:
		return "当该操作在进行中，由于保持活动的操作检测到一个故障，该连接中断作";
		break;
	case WSAECONNABORTED:
		return "您的主机中的软件放弃了一个已建立的连接";
		break;
	case WSAECONNRESET:
		return "远程主机强迫关闭了一个现有的连接";
		break;
	case WSAENOBUFS:
		return "由于系统缓冲区空间不足或列队已满，不能执行套接字上的操作";
		break;
	case WSAEISCONN:
		return "在一个已经连接的套接字上做了一个连接请求";
		break;
	case WSAENOTCONN:
		return "由于套接字没有连接并且(当使用一个 sendto 调用发送数据报套接字时)没有提供地址，发送或接收数据的请求没有被接受";
		break;
	case WSAESHUTDOWN:
		return "由于以前的关闭调用，套接字在那个方向已经关闭，发送或接收数据的请求没有被接受";
		break;
	case WSAETOOMANYREFS:
		return "对某个内核对象的引用过多";
		break;
	case WSAETIMEDOUT:
		return "由于连接方在一段时间后没有正确答复或连接的主机没有反应，连接尝试失败";
		break;
	case WSAECONNREFUSED:
		return "由于目标机器积极拒绝，无法连接";
		break;
	case WSAELOOP:
		return "无法转换名称";
		break;
	case WSAENAMETOOLONG:
		return "名称组件或名称太长";
		break;
	case WSAEHOSTDOWN:
		return "由于目标主机坏了，套接字操作失败";
		break;
	case WSAEHOSTUNREACH:
		return "套接字操作尝试一个无法连接的主机";
		break;
	case WSAENOTEMPTY:
		return "不能删除目录，除非它是空的";
		break;
	case WSAEPROCLIM:
		return "一个 Windows 套接字操作可能在可以同时使用的应用程序数目上有限制";
		break;
	case WSAEUSERS:
		return "限额不足";
		break;
	case WSAEDQUOT:
		return "磁盘限额不足";
		break;
	case WSAESTALE:
		return "文件句柄引用不再可用";
		break;
	case WSAEREMOTE:
		return "项目在本地不可用";
		break;

	case WSASYSNOTREADY:
		return "因为它使用提供网络服务的系统目前无效，WSAStartup 目前不能正常工作";
		break;
	case WSAVERNOTSUPPORTED:
		return "不支持请求的 Windows 套接字版本";
		break;
	case WSANOTINITIALISED:
		return "应用程序没有调用 WSAStartup，或者 WSAStartup 失败";
		break;
	case WSAEDISCON:
		return "由 WSARecv 或 WSARecvFrom 返回表示远程方面已经开始了关闭步骤";
		break;
	case WSAENOMORE:
		return "WSALookupServiceNext 不能返回更多的结果";
		break;
	case WSAECANCELLED:
		return "在该调用还处于处理中时，就调用了 WSALookupServiceEnd。该调用被取消";
		break;
	case WSAEINVALIDPROCTABLE:
		return "过程调用无效";
		break;
	case WSAEINVALIDPROVIDER:
		return "请求的服务提供程序无效";
		break;
	case WSAEPROVIDERFAILEDINIT:
		return "无法加载或初始化请求的服务提供程序";
		break;
	case WSASYSCALLFAILURE:
		return "从来不应失败的系统调用失败了";
		break;
	case WSASERVICE_NOT_FOUND:
		return "此服务不存在。在指定的名称空间中找不这个服务";
		break;
	case WSATYPE_NOT_FOUND:
		return "找不到指定的类别";
		break;
	case WSA_E_NO_MORE:
		return "WSALookupServiceNext 不能返回更多的结果";
		break;
	case WSA_E_CANCELLED:
		return "在该调用还处于处理中时，就调用了 WSALookupServiceEnd。该调用被取消";
		break;
	case WSAEREFUSED:
		return "由于被拒绝，数据查询失败";
		break;
	default:
		return "未知错误";
		break;
	}
	return "unknown socket error";
}