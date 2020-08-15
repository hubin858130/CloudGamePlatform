

#ifndef _EV_SOCKET_H
#define _EV_SOCKET_H
# include <string>
using namespace std;


#define BASIC_RECEIVE_SICHUANG		(1024*1024*2)

class CDayeBasicSocket
{
public:

	// 创建TCP socket， 返回-1失败
	static int socket();

	// 关闭socket
	static void close(int socket);

	// 设置socket为非阻塞式 错误时返回false失败
	static bool setNonBlocking(int socket);

	// 从指定的socket上读取数据 返回false失败
	static bool nbRead(int socket, std::string& s, bool *eof, int& nError,int nTimeout = 20 );

	// 从指定的socket上读取指定长度的数据 返回false失败
	static bool nbRead(int socket, std::string& s, int nReadLen,bool *eof, int& nError);

	// 写入数据到指定的socket上 返回false失败
	//static bool nbWrite(int socket, std::string& s, int *bytesSoFar);
	static bool nbWrite(int socket, char *pSendBuffer, int nSendSize, int *bytesSoFar );

	// 以下函数使用于服务器

	// 设置网络重用
	static bool setReuseAddr(int socket);

	// 设置立即关闭
	static bool SetNoLinger(int socket);

	// 设置tcp_nodelay
	static bool SetTcpNodelay(int socket);

	// 绑定到指定端口
	static bool bind(int socket, int port);

	// 在端口上监听
	static bool listen(int socket, int backlog);

	// 接受连接
	static int accept(int socket);

	// 以下函数适用于客户端

	// 连接到服务器
	static bool connect(int socket, std::string& host, int port);

	// 返回最后一个错误
	static int getError();

	// 返回最后错误描述
	static std::string getErrorMsg();

#if defined(WIN32)
	// 根据错误号返回描述
	static std::string getErrorMsg(int error);
#endif

public:
	// 数据接收buf
	static char m_pcRev[BASIC_RECEIVE_SICHUANG];

};
#endif