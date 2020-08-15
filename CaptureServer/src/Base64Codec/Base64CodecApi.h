#ifndef _BASE64CODECAPI_H
#define _BASE64CODECAPI_H

/************************************************************************/
//函数名称:	base64编码函数
//参数：
//	@data		const char *	输入的待编码数据
//	@nInputLen	int				输入的待编码数据长度
//返回值：
//	@char*	base64编码后的字符串，NULL表示失败，非NULL表示成功
//说明
//	返回的base64编码后的字符串由内部分配空间，需要调用ReleaseDataBuffer释放
/************************************************************************/
char* base64_encode(const char *data,int nInputLen);

/************************************************************************/
//函数名称:	base64解码函数
//参数：
//	@nSize		int				输出参数，为解码后数据长度
//	@bdata		const char *	输入的待解码数据
//返回值：
//	@char*	base64解码后的字符串，NULL表示失败，非NULL表示成功
//说明
//	返回的base64解码后的字符串由内部分配空间，需要调用ReleaseDataBuffer释放
/************************************************************************/
char* base64_decode(int &nSize,const char *bdata);


/************************************************************************/
//函数名称:	释放空间函数
//参数：
//	@data		char **			待释放的数据指针地址
//返回值：
//	无
//说明
//	负责释放编解码函数内部分配的地址空间
/************************************************************************/
void base64_ReleaseDataBuffer(char **data);

#endif