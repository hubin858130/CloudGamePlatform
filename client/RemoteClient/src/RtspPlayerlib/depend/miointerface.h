/**
 *  File Name                   :           miointerface.h
 *  Version                     :           1.0
 *  Project Information         :           MegaEye
 *  Copyright                   :
 *  Brief Description           :           header file for MIO interface
 *=================================================================================
 *  Revision History            :
 *
 */

#ifndef _MIOINTERFACE_H_
#define _MIOINTERFACE_H_

#include <stdarg.h>

#include "msgdef.h"
#include "iedef.h"


#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////
//	用户自定义消息相关部分，没有完全完成
///////////////////////////////////////////////////////

/*
 * 用户自定义消息定义结构
 */
typedef struct miosUserMsgDef{
	MIO_CONST MIO_CHAR		*name;		// 消息名
	MIO_INT32				nameLen;	// 消息名的长度
	MIO_UINT32				type;		// 消息编号值
}miosUserMsgDef;

/*
 * 用户自定义IE成员量的数据类型
 */
typedef enum mioeUserIEMemberType{
	MIO_IMT_INT8,			// for char
	MIO_IMT_UINT8,			// for byte
	MIO_IMT_INT16,			// for short
	MIO_IMT_UINT16,			// for word
	MIO_IMT_INT32,			// for int
	MIO_IMT_UINT32,			// for dword
	MIO_IMT_INT64,			// for int64
	MIO_IMT_UINT64,			// for qword

	MIO_IMT_STRING,			// for string
	MIO_IMT_TIME,			// time
	MIO_IMT_UNKNOWN
}mioeUserIEMemberType;

/*
 * 用户自定义IE成员量定义结构
 */
typedef struct miosUserIEMemberDef{
	MIO_CONST MIO_CHAR		*name;				// 成员变量名
	MIO_INT32				nameLen;			// 成员变量名的长度
	MIO_UINT32				offset;				// 成员变量在IE中的内存偏移量
	mioeUserIEMemberType	type;				// 成员变量的值类型
	MIO_UINT32				extraParam;			// 成员变量需要的附加参数
												// 字符串变量使用它来记录最大长度
	MIO_CONST MIO_CHAR		*defaultValue;		// 成员变量的默认值
}miosUserIEMemberDef;

/*
 * 用户自定义IE定义结构
 */
typedef struct miosUserIEDef{
	MIO_CONST MIO_CHAR				*name;			// IE名
	MIO_INT32						nameLen;		// IE名的长度
	MIO_UINT32						type;			// IE的编号值
	MIO_UINT32						size;			// IE结构的大小
	MIO_CONST miosUserIEMemberDef	*memberDefs;	// IE的成员列表
													// 为一个数组，结尾的结构为0
}miosUserIEDef;

/*
 * 用户自定义相关的一些宏定义，详细的参见《控制接口详细设计说明书》
 */
#define MIO_USER_MSG_DEFINE_NAME( suffixName )					g_MIOUserMsgDef_##suffixName
#define MIO_USER_IE_DEFINE_NAME( suffixName )					g_MIOUserIEDef_##suffixName
#define MIO_USER_IE_MEMBER_DEFINE_NAME( ieName )				g_MIOUserIEMemberDef_##ieName
#define MIO_USER_IE_MEMBER_NAME( memberName )					m_##memberName
#define MIO_USER_IE_STRUCT_NAME( ieName )						mios##ieName
#define MIO_STRUCT_MEMBER_OFFSET( structName, memberName )		MIO_PTR_TO_INT(&(((structName*)0)->memberName))
#define MIO_USER_MSG_TYPE_DEFINE_NAME( suffixName )				mioeUserMSGType_##suffixName
#define MIO_USER_IE_TYPE_DEFINE_NAME( suffixName )				mioeUserIEType_##suffixName
#define MIO_USER_MSG_TYPE_NAME( msgName )						MT_##msgName
#define MIO_USER_IE_TYPE_NAME( ieName )							IET_##ieName

#define MIO_BEGIN_USER_MSG_TYPE_DEFINE( suffixName )			typedef enum MIO_USER_MSG_TYPE_DEFINE_NAME( suffixName ){
#define MIO_DEFINE_USER_MSG_TYPE( msgName, type )				MIO_USER_MSG_TYPE_NAME( msgName ) = type,
#define MIO_END_USER_MSG_TYPE_DEFINE( suffixName )				MT_UNKNOW_USER_MSG = 0xffffffff }MIO_USER_MSG_TYPE_DEFINE_NAME( suffixName );

#define MIO_BEGIN_USER_IE_TYPE_DEFINE( suffixName )				typedef enum MIO_USER_IE_TYPE_DEFINE_NAME( suffixName ){
#define MIO_DEFINE_USER_IE_TYPE( ieName, type )					MIO_USER_IE_TYPE_NAME( ieName ) = type,
#define MIO_END_USER_IE_TYPE_DEFINE( suffixName )				IET_UNKNOW_USER_IE = 0xffffffff }MIO_USER_IE_TYPE_DEFINE_NAME( suffixName );

#define MIO_BEGIN_USER_MSG_DEFINE( suffixName )					miosUserMsgDef MIO_USER_MSG_DEFINE_NAME(suffixName)[] = {
#define MIO_DEFINE_USER_MSG( msgName, type )					{ #msgName, sizeof(#msgName)-1, type },
#define MIO_END_USER_MSG_DEFINE( suffixName )					{ MIO_NULL, 0, 0 } };

#define MIO_BEGIN_USER_IE_MEMBER_DEFINE( ieName )				miosUserIEMemberDef MIO_USER_IE_MEMBER_DEFINE_NAME(ieName)[] = {
#define MIO_DEFINE_USER_IE_MEMBER( ieName, memberName, type, extraParam, defaultValue )		\
																{ #memberName, sizeof(#memberName)-1, MIO_STRUCT_MEMBER_OFFSET( MIO_USER_IE_STRUCT_NAME( ieName ), MIO_USER_IE_MEMBER_NAME(memberName) ), MIO_IMT_##type, extraParam, defaultValue },
#define MIO_END_USER_IE_MEMBER_DEFINE( ieName )					{ MIO_NULL, 0, 0, 0, 0, MIO_NULL } };

#define MIO_BEGIN_USER_IE_STRUCT_DEFINE( ieName )							typedef struct MIO_USER_IE_STRUCT_NAME( ieName ){	\
																				MIO_UINT32 type;
#define MIO_DEFINE_USER_IE_STRUCT_MEMBER( ieName, memberName, type )			MIO_##type MIO_USER_IE_MEMBER_NAME(memberName);
#define MIO_DEFINE_USER_IE_STRUCT_MEMBER_STRING( ieName, memberName, len )		MIO_CHAR MIO_USER_IE_MEMBER_NAME(memberName)[len+1];
#define MIO_END_USER_IE_STRUCT_DEFINE( ieName )								}MIO_USER_IE_STRUCT_NAME( ieName );

#define MIO_BEGIN_USER_IE_DEFINE( suffixName )			miosUserIEDef MIO_USER_IE_DEFINE_NAME(suffixName)[] = {
#define MIO_DEFINE_USER_IE( ieName, type )				{ #ieName, sizeof(#ieName)-1, type, sizeof(MIO_USER_IE_STRUCT_NAME( ieName )), MIO_USER_IE_MEMBER_DEFINE_NAME( ieName ) },
#define MIO_END_USER_IE_DEFINE( suffixName )			{ MIO_NULL, 0, 0, 0, MIO_NULL } };


/*
 * 无效的消息ID
 */
#define MIO_INVALID_MSGID		0

/*
 * MIO_NotifyHandler的回调通知类型
 */
typedef enum mioeNotiyCode
{
	MIO_NC_RECV_REQUEST,		// 收到了一个请求数据包
	MIO_NC_RECV_RESPONSE,		// 收到了一个应答数据包
	MIO_NC_SND_REQUEST_FAIL,	// 发送请求数据包失败
	MIO_NC_RECV_REGISTER,		// 收到了一个注册请求包
	MIO_NC_RECV_REGISTER_RESP,	// 收到了一个成功的注册回应包
	MIO_NC_SND_REGISTER_FAIL,	// 发送注册请求失败
	MIO_NC_ACCEPT_REGISTER,		// 接受了一个带认证的注册请求
	MIO_NC_REGISTER_TIMEOUT		// 发送注册消息超时
}mioeNotiyCode;

/*
 * linux下的上层模块实现的回调通知函数
 * 参数及返回值见回调函数原型定义处的说明
 */
extern MIO_VOID MIO_NotifyHandler(MIO_VOID *userData,
									mioeNotiyCode notifyCode,
									MIO_UINT32 msgID,
									miosMSG *msg,
									MIO_CHAR *to,
									MIO_CHAR *from,
									MIO_VOID *notifyExtraParam);

/*
 *	当 notifyCode 为 MIO_NC_RECV_REGISTER 或 MIO_NC_ACCEPT_REGISTER 时
 *	notifyExtraParam 为指向如下结构的指针
 */
typedef struct miosRegisterNotifyExtraParam{
	MIO_CONST MIO_CHAR	*ipAddr;	// 实际接收的 IP 地址
	MIO_UINT16			port;		// 实际接收的端口号
	MIO_CONST MIO_CHAR	*deviceid;	// 注册的设备 ID 号
	MIO_CONST MIO_CHAR	*digestUserName;	// Digest认证中的username参数
	MIO_UINT32			expires;	// 注册持续时长
	MIO_CONST MIO_CHAR	*regCallId;	// 注册消息的Call-ID字段

	// 如下的这些参数用来计算认证信息
	MIO_CONST MIO_CHAR	*digestNonce;		// SIP Authorization 头字段中的 nonce
	MIO_CONST MIO_CHAR	*digestCNonce;		// SIP Authorization 头字段中的 cnonce
	MIO_CONST MIO_CHAR	*digestRealm;		// SIP Authorization 头字段中的 realm
	MIO_CONST MIO_CHAR	*digestAlg;			// SIP Authorization 头字段中的 algorithm
	MIO_CONST MIO_CHAR	*digestNonceCount;	// SIP Authorization 头字段中的 nc
	MIO_CONST MIO_CHAR	*digestMethod;		// SIP 消息的方法名
	MIO_CONST MIO_CHAR	*digestQop;			// SIP Authorization 头字段中的 qop
	MIO_CONST MIO_CHAR	*digestURI;			// SIP Authorization 头字段中的 uri
	MIO_CONST MIO_CHAR	*digestResponse;	// SIP Authorization 头字段中的 response
}miosRegisterNotifyExtraParam;

/*
 * 当 notifyCode 为 MIO_NC_RECV_REQUEST时
 * 收到信令消息的协议类型为如下几种
 */
typedef enum mioeRequestProtocol{
	MIO_RP_SIP,				// SIP 消息
	MIO_RP_HTTP,			// HTTP 消息
	MIO_RP_UNKNOWN			// 不知道的类型
}mioeRequestProtocol;

/*
 * 当 notifyCode 为 MIO_NC_RECV_REQUEST 时
 * notifyExtraParam 为指向如下结构的指针
 */
typedef struct miosRequestNotifyExtraParam{
	MIO_CONST MIO_CHAR	*ipAddr;	// 实际接收的 IP 地址
	MIO_UINT16			port;		// 实际接收的端口号
	mioeRequestProtocol	protocol;	// 接收的协议类型
}miosRequestNotifyExtraParam;

/* 
 * 当 notifyCode 为 MIO_NC_RECV_RESPONSE 或 MIO_NC_SND_REQUEST_FAIL 时
 * notifyExtraParam 为发送消息时的 msgUserData
 */

/*
 * 当 notifyCode 为 MIO_NC_RECV_REGISTER_RESP 或 MIO_NC_SND_REGISTER_FAIL 时
 * notifyExtraParam 为发送注册消息时的 regUserData
 */


/*
 * 消息通知回调函数原型定义
 *
 * 参数定义：
 *  userData: 当通知的是SIP消息时，为创建接口时传入的不透明用户数据
 *            当通知的是HTTP消息时，如果初始化 HTTP 时没有传入回调函数，那么就是创建接口时的不透明用户数据
 *                                  如果初始化 HTTP 时传入了回调函数，那么就是初始化 HTTP 时传入的不透明用户数据
 *  notifyCode: 通知的类型
 *  msgID: 消息ID号
 *  msg: 解析后的 XML 消息
 *  to: SIP消息 To 头中的SIP URL
 *  from: SIP消息 From 头中的SIP URL
 *  notifyExtraParam: 附加的通知参数。详细的参见上面的说明
 *
 * 返回值：
 *  无
 *
 */
typedef MIO_VOID (*MIO_NotifyCB)(MIO_VOID *userData,
									mioeNotiyCode notifyCode,
									MIO_UINT32 msgID,
									miosMSG *msg,
									MIO_CHAR *to,
									MIO_CHAR *from,
									MIO_VOID *notifyExtraParam);

/*
 * 创建接口
 *
 * 参数定义：
 *  listenPort: SIP 的侦听端口号
 *  userData: 调用通知回调时传回的上层模块不透明指针
 *  notifyCB: 消息通知回调函数指针。
 *            如果这个参数为MIO_NULL，那么表示只是为使用XML的编解码功能，此时不会初始化通讯协议栈，任何发送和接收消息的函数都无效。
 *            对于只使用编解码功能的初始化可以调用多次。
 *            但是对于收发数据的初始化目前只能支持一次。
 *
 * 返回值：
 *  接口句柄指针
 *
 */
MIO_API MIO_VOID* MIO_CreateCtxEx( MIO_UINT16 listenPort,
									MIO_VOID *userData,
									MIO_NotifyCB notifyCB);


/*
 * 创建接口，和 MIO_CreateCtxEx 的区别在于少了 notifyCB 参数。
 * 接口库在需要调用回调函数的时候，直接调用 MIO_NotifyHandler 。
 * 这个函数只在linux版本中有效，应当避免使用这个函数，而使用 MIO_CreateCtxEx 来替代。
 *
 * 参数定义：
 *  listenPort: SIP 的侦听端口号
 *  userData: 调用通知回调时传回的上层模块不透明指针
 *
 * 返回值：
 *  接口句柄指针
 *
 */
MIO_API MIO_VOID* MIO_CreateCtx( MIO_UINT16 listenPort,
									MIO_VOID *userData);

/*
 * 销毁接口
 *
 * 参数定义：
 *  mioCtx: 创建接口时返回的接口模块句柄
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_DestroyCtx( MIO_VOID *mioCtx );


/*
 * 用来发送上层需要发送的消息。
 * 目前分为两种情况：
 * 当参数中的msgID有效时（即不为MIO_INVALID_MSGID），那么表示要发送应答数据包。
 * 当参数中的msgID无效时（即为MIO_INVALID_MSGID），那么表示要发送请求数据包。此时参数中的to和from需要填写。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  to: 接收消息方（对应SIP消息 To 头中的SIP URL，对应HTTP消息中的目的URL）（发送请求时使用）
 *  from: 发送消息方（对应SIP消息 From 头中的 SIP URL，HTTP消息没有使用）（发送请求时使用）
 *  msgID: 消息ID号（由消息通知回调函数生成的）（发送应答时使用）
 *  msg: 消息内容
 *  msgUserData: 上层模块的私有消息数据。只在发送请求消息时有效。
 *               用来帮助上层模块记录和本请求消息相关的私有数据。
 *               会在收到对应的应答或发送失败时通过消息通知函数回传给上层模块。
 *               上层模块特别需要注意的是这个私有数据的内存分配和释放问题。
 *               发送消息时，这个私有数据会被记录在收发包模块中，
 *               当收发包模块调用了通知回调以后，这个私有数据就已经从收发包模块的记录中移除，
 *               此时上层模块可能需要在使用完毕以后，释放掉对应的内存。
 *
 * 返回值：
 *  消息ID号（MIO_INVALID_MSGID为无效的消息ID号，当返回这个值时表示函数调用失败）
 *
 */
MIO_API MIO_UINT32 MIO_SendMsg( MIO_VOID *mioCtx,
								MIO_CHAR *to,
								MIO_CHAR *from,
								MIO_UINT32 msgID,
								miosMSG *msg,
								MIO_VOID *msgUserData );

/*
 * 用来发送上层需要发送的消息。
 * 这个函数和 MIO_SendMsg 除了在发送 SIP 消息时使用的是 INFO 命令字，而不是 MESSAGE 命令字之外，完全相同
 * 目前分为两种情况：
 * 当参数中的msgID有效时（即不为MIO_INVALID_MSGID），那么表示要发送应答数据包。
 * 当参数中的msgID无效时（即为MIO_INVALID_MSGID），那么表示要发送请求数据包。此时参数中的to和from需要填写。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  to: 接收消息方（对应SIP消息 To 头中的SIP URL，对应HTTP消息中的目的URL）（发送请求时使用）
 *  from: 发送消息方（对应SIP消息 From 头中的 SIP URL，HTTP消息没有使用）（发送请求时使用）
 *  msgID: 消息ID号（由消息通知回调函数生成的）（发送应答时使用）
 *  msg: 消息内容
 *  msgUserData: 上层模块的私有消息数据。只在发送请求消息时有效。
 *               用来帮助上层模块记录和本请求消息相关的私有数据。
 *               会在收到对应的应答或发送失败时通过消息通知函数回传给上层模块。
 *               上层模块特别需要注意的是这个私有数据的内存分配和释放问题。
 *               发送消息时，这个私有数据会被记录在收发包模块中，
 *               当收发包模块调用了通知回调以后，这个私有数据就已经从收发包模块的记录中移除，
 *               此时上层模块可能需要在使用完毕以后，释放掉对应的内存。
 *
 * 返回值：
 *  消息ID号（MIO_INVALID_MSGID为无效的消息ID号，当返回这个值时表示函数调用失败）
 *
 */MIO_API MIO_UINT32 MIO_SendMsgEs( MIO_VOID *mioCtx,
								MIO_CHAR *to,
								MIO_CHAR *from,
								MIO_UINT32 msgID,
								miosMSG *msg,
								MIO_VOID *msgUserData );

/*
 * 用来发送上层需要发送的消息。
 * 这个函数和 MIO_SendMsg 的区别在于增加了实际的发送地址（ip和port），而不是依赖 to 参数中的解析出来的地址
 * 目前分为两种情况：
 * 当参数中的msgID有效时（即不为MIO_INVALID_MSGID），那么表示要发送应答数据包。
 * 当参数中的msgID无效时（即为MIO_INVALID_MSGID），那么表示要发送请求数据包。此时参数中的to和from需要填写。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  to: 接收消息方（对应SIP消息 To 头中的SIP URL，对应HTTP消息中的目的URL）（发送请求时使用）
 *  from: 发送消息方（对应SIP消息 From 头中的 SIP URL，HTTP消息没有使用）（发送请求时使用）
 *  msgID: 消息ID号（由消息通知回调函数生成的）（发送应答时使用）
 *  msg: 消息内容
 *  msgUserData: 上层模块的私有消息数据。只在发送请求消息时有效。
 *               用来帮助上层模块记录和本请求消息相关的私有数据。
 *               会在收到对应的应答或发送失败时通过消息通知函数回传给上层模块。
 *               上层模块特别需要注意的是这个私有数据的内存分配和释放问题。
 *               发送消息时，这个私有数据会被记录在收发包模块中，
 *               当收发包模块调用了通知回调以后，这个私有数据就已经从收发包模块的记录中移除，
 *               此时上层模块可能需要在使用完毕以后，释放掉对应的内存。
 *  ip: 发送的实际 IP 地址，如果为空，使用 to 中解析出来的地址
 *  port: 发送的实际端口号
 *
 * 返回值：
 *  消息ID号（MIO_INVALID_MSGID为无效的消息ID号，当返回这个值时表示函数调用失败）
 *
 */
MIO_API MIO_UINT32 MIO_SendMsgEx( MIO_VOID *mioCtx,
									MIO_CHAR *to,
									MIO_CHAR *from,
									MIO_UINT32 msgID,
									miosMSG *msg,
									MIO_VOID *msgUserData,
									MIO_CHAR *ip,
									MIO_UINT16 port );


/*
 * 用来发送上层需要发送的消息。
 * 这个函数和 MIO_SendMsgEx 除了在发送 SIP 消息时使用的是 INFO 命令字，而不是 MESSAGE 命令字之外，完全相同
 * 目前分为两种情况：
 * 当参数中的msgID有效时（即不为MIO_INVALID_MSGID），那么表示要发送应答数据包。
 * 当参数中的msgID无效时（即为MIO_INVALID_MSGID），那么表示要发送请求数据包。此时参数中的to和from需要填写。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  to: 接收消息方（对应SIP消息 To 头中的SIP URL，对应HTTP消息中的目的URL）（发送请求时使用）
 *  from: 发送消息方（对应SIP消息 From 头中的 SIP URL，HTTP消息没有使用）（发送请求时使用）
 *  msgID: 消息ID号（由消息通知回调函数生成的）（发送应答时使用）
 *  msg: 消息内容
 *  msgUserData: 上层模块的私有消息数据。只在发送请求消息时有效。
 *               用来帮助上层模块记录和本请求消息相关的私有数据。
 *               会在收到对应的应答或发送失败时通过消息通知函数回传给上层模块。
 *               上层模块特别需要注意的是这个私有数据的内存分配和释放问题。
 *               发送消息时，这个私有数据会被记录在收发包模块中，
 *               当收发包模块调用了通知回调以后，这个私有数据就已经从收发包模块的记录中移除，
 *               此时上层模块可能需要在使用完毕以后，释放掉对应的内存。
 *  ip: 发送的实际 IP 地址，如果为空，使用 to 中解析出来的地址
 *  port: 发送的实际端口号
 *
 * 返回值：
 *  消息ID号（MIO_INVALID_MSGID为无效的消息ID号，当返回这个值时表示函数调用失败）
 *
 */
MIO_API MIO_UINT32 MIO_SendMsgEsEx( MIO_VOID *mioCtx,
									MIO_CHAR *to,
									MIO_CHAR *from,
									MIO_UINT32 msgID,
									miosMSG *msg,
									MIO_VOID *msgUserData,
									MIO_CHAR *ip,
									MIO_UINT16 port );

/*
 * 无效的注册ID
 */
#define MIO_INVALID_REGID		0

/*
 * 这个函数用来发起一个SIP的REGISTER会话，这个会话保持到调用MIO_cancelReg为止，
 * 周期性的发送注册消息。此时上层应用作为一个请求认证的客户端。
 * 发送的注册消息是否成功，通过消息通知回调函数通知上层。
 * notifyCode为MIO_NC_RECV_REGISTER_RESP时，表示一个注册消息已经被服务器接受。
 * notifyCode为MIO_NC_SND_REGISTER_FAIL时，表示一个注册消息没有发送成功，或者注册消息被服务器拒绝了。
 * 发送失败的情况下，默认会继续下一次的注册请求，只有调用MIO_cancelReg才会停止注册的请求。
 * 可以通过调用MIO_enableStopRegWhenFail或MIO_disableStopRegWhenFail来改变这个行为，具体的行为请参见这两个函数的说明。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  to: 注册的目标服务器地址。
 *  from: 要注册的地址（必须包含用户名部分）
 *  userName: 用来计算digest认证时的用户名。
 *  passWord: 用来计算digest认证时的密码。
 *  expires: 注册地址的有效时间，以秒为单位。
 *           接口模块会依据这个值在小于这个值的时间间隔内重发注册，以保持注册的持续有效。
 *           这个值必须大于或等于0，最好大于60秒，因为协议栈会在这个时间减去60秒的时候重发注册，如果这个值小于60，就会导致协议栈不断的重发注册消息。
 *           等于0时有特殊的用途，协议栈只会发送一次注册。
 *  regUserData: 上层模块和本注册相关的私有消息数据。用来帮助上层模块记录和本请求消息相关的私有数据。
 *               接口模块会在收到对应的应答或发送失败时通过消息回调函数回传给上层模块。
 *               上层模块特别需要注意的是这个私有数据的内存分配和释放问题。
 *               发送消息时，这个私有数据会被记录在接口模块中，直到调用MIO_cancelReg时才会被删除掉，
 *               上层模块可能要在这之后，释放掉对应的内存。
 *  ip: 发送的实际 IP 地址，如果为空，那么使用 to 中解析出来的地址。
 *  port: 发送的实际端口号
 *
 * 返回值：
 *  注册ID号（MIO_INVALID_REGID为无效的注册ID号，当返回这个值时时表示函数调用失败）
 *
 */
MIO_API MIO_UINT32 MIO_SendReg( MIO_VOID *mioCtx,
								MIO_CHAR *to,
								MIO_CHAR *from,
								MIO_CHAR *userName,
								MIO_CHAR *passWord,
								MIO_INT32 expires,
								MIO_VOID *regUserData,
								MIO_CHAR *ip,
								MIO_UINT16 port );

/*
 * 这个函数和 MIO_SendReg 的功能相同，只是增加了设置注册时 REGISTER 消息头中的 Call-ID 字段
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  to: 注册的目标服务器地址。
 *  from: 要注册的地址（必须包含用户名部分）
 *  userName: 用来计算digest认证时的用户名。
 *  passWord: 用来计算digest认证时的密码。
 *  expires: 注册地址的有效时间，以秒为单位。
 *           接口模块会依据这个值在小于这个值的时间间隔内重发注册，以保持注册的持续有效。
 *           这个值必须大于或等于0，最好大于60秒，因为协议栈会在这个时间减去60秒的时候重发注册，如果这个值小于60，就会导致协议栈不断的重发注册消息。
 *           等于0时有特殊的用途，协议栈只会发送一次注册。
 *  regUserData: 上层模块和本注册相关的私有消息数据。用来帮助上层模块记录和本请求消息相关的私有数据。
 *               接口模块会在收到对应的应答或发送失败时通过消息回调函数回传给上层模块。
 *               上层模块特别需要注意的是这个私有数据的内存分配和释放问题。
 *               发送消息时，这个私有数据会被记录在接口模块中，直到调用MIO_cancelReg时才会被删除掉，
 *               上层模块可能要在这之后，释放掉对应的内存。
 *  ip: 发送的实际 IP 地址，如果为空，那么使用 to 中解析出来的地址。
 *  port: 发送的实际端口号
 *  regCallId: 由上层填写的Call-ID。在使用这个的时候需要小心，因为按照SIP协议的规定，这个值要在全局上保持唯一性
 *
 * 返回值：
 *  注册ID号（MIO_INVALID_REGID为无效的注册ID号，当返回这个值时时表示函数调用失败）
 *
 */
MIO_API MIO_UINT32 MIO_SendRegEx( MIO_VOID *mioCtx,
									MIO_CHAR *to,
									MIO_CHAR *from,
									MIO_CHAR *userName,
									MIO_CHAR *passWord,
									MIO_INT32 expires,
									MIO_VOID *regUserData,
									MIO_CHAR *ip,
									MIO_UINT16 port,
									MIO_CHAR *regCallId );

/*
 * 这个函数和 MIO_SendRegEx 的功能相同，只是增加了注册时可以携带 XML 消息体
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  to: 注册的目标服务器地址。
 *  from: 要注册的地址（必须包含用户名部分）
 *  userName: 用来计算digest认证时的用户名。
 *  passWord: 用来计算digest认证时的密码。
 *  expires: 注册地址的有效时间，以秒为单位。
 *           接口模块会依据这个值在小于这个值的时间间隔内重发注册，以保持注册的持续有效。
 *           这个值必须大于或等于0，最好大于60秒，因为协议栈会在这个时间减去60秒的时候重发注册，如果这个值小于60，就会导致协议栈不断的重发注册消息。
 *           等于0时有特殊的用途，协议栈只会发送一次注册。
 *  regUserData: 上层模块和本注册相关的私有消息数据。用来帮助上层模块记录和本请求消息相关的私有数据。
 *               接口模块会在收到对应的应答或发送失败时通过消息回调函数回传给上层模块。
 *               上层模块特别需要注意的是这个私有数据的内存分配和释放问题。
 *               发送消息时，这个私有数据会被记录在接口模块中，直到调用MIO_cancelReg时才会被删除掉，
 *               上层模块可能要在这之后，释放掉对应的内存。
 *  ip: 发送的实际 IP 地址，如果为空，那么使用 to 中解析出来的地址。
 *  port: 发送的实际端口号
 *  regCallId: 由上层填写的Call-ID。在使用这个的时候需要小心，因为按照SIP协议的规定，这个值要在全局上保持唯一性
 *  msg: 注册时携带的 XML 消息体
 *
 * 返回值：
 *  注册ID号（MIO_INVALID_REGID为无效的注册ID号，当返回这个值时时表示函数调用失败）
 *
 */
MIO_API MIO_UINT32 MIO_SendRegEx2( MIO_VOID *mioCtx,
									MIO_CHAR *to,
									MIO_CHAR *from,
									MIO_CHAR *userName,
									MIO_CHAR *passWord,
									MIO_INT32 expires,
									MIO_VOID *regUserData,
									MIO_CHAR *ip,
									MIO_UINT16 port,
									MIO_CHAR *regCallId,
									miosMSG *msg );


/*
 * 这个函数用来取消一个由MIO_SendReg，MIO_SendRegEx或MIO_SendRegEx2发起的注册会话。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  regID: 由MIO_SendReg，MIO_SendRegEx或MIO_SendRegEx2返回的注册会话ID。
 *
 * 返回值：
 *  MIO_TRUE 表示取消成功
 *  MIO_FALSE 表示取消失败
 *
 */
MIO_API MIO_BOOL MIO_cancelReg( MIO_VOID *mioCtx,
								MIO_UINT32 regID );

/*
 * 用来发送SIP的REGISTER回应。此时上层应用作为一个认证服务器。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  msgID: 为回调通知notifyCode为MIO_NC_RECV_REGISTER时携带的msgID。
 *  respCode：注册回应的状态码。200表示成功。403表示认证失败。
 *  passWord: 当respCode为200时，并且启用了digest认证，那么收发包模块使用这个密码值来计算digest。
 *            如果这个值为空，那么也不进行认证计算。
 *
 * 返回值：
 *  消息ID号（MIO_INVALID_MSGID为无效的消息ID号，当返回这个值时表示函数调用失败）
 *
 */
MIO_API MIO_UINT32 MIO_SendRegResp( MIO_VOID *mioCtx,
									MIO_UINT32 msgID,
									MIO_INT32 respCode,
									MIO_CHAR *passWord );

/*
 * 这个函数和 MIO_SendRegResp 的功能相同。只是增加了设置SIP回应消息头的回应说明
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  msgID: 为回调通知notifyCode为MIO_NC_RECV_REGISTER时携带的msgID。
 *  respCode：注册回应的状态码。200表示成功。403表示认证失败。
 *  passWord: 当respCode为200时，并且启用了digest认证，那么收发包模块使用这个密码值来计算digest。
 *            如果这个值为空，那么也不进行认证计算。
 *  respReasonPhrase：SIP回应头中的回应说明
 *
 * 返回值：
 *  消息ID号（MIO_INVALID_MSGID为无效的消息ID号，当返回这个值时表示函数调用失败）
 *
 */
MIO_API MIO_UINT32 MIO_SendRegRespEx( MIO_VOID *mioCtx,
										MIO_UINT32 msgID,
										MIO_INT32 respCode,
										MIO_CHAR *passWord,
										MIO_CONST MIO_CHAR *respReasonPhrase );

/*
 * 这个函数和 MIO_SendRegRespEx 的功能相同。只是增加了发送注册回应时可以携带 XML 消息体
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  msgID: 为回调通知notifyCode为MIO_NC_RECV_REGISTER时携带的msgID。
 *  respCode：注册回应的状态码。200表示成功。403表示认证失败。
 *  passWord: 当respCode为200时，并且启用了digest认证，那么收发包模块使用这个密码值来计算digest。
 *            如果这个值为空，那么也不进行认证计算。
 *  respReasonPhrase：SIP回应头中的回应说明
 *  msg: 注册时携带的 XML 消息体
 *
 * 返回值：
 *  消息ID号（MIO_INVALID_MSGID为无效的消息ID号，当返回这个值时表示函数调用失败）
 *
 */
MIO_API MIO_UINT32 MIO_SendRegRespEx2( MIO_VOID *mioCtx,
										MIO_UINT32 msgID,
										MIO_INT32 respCode,
										MIO_CHAR *passWord,
										MIO_CONST MIO_CHAR *respReasonPhrase,
										miosMSG *msg );


/*
 * 用来添加认证信息，可以用来预先添加一些认证信息。这样可以在调用MIO_SendReg时不用提供userName和passWord。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  deviceid: 要注册的设备号（对应于MIO_SendReg的from参数中的SIP地址的username部分）
 *  digestUserName: digest计算中的用户名
 *  password: digest计算中的密码
 *
 * 返回值：
 *  MIO_TRUE 表示添加成功
 *  MIO_FALSE 表示添加失败
 *
 */
MIO_API MIO_BOOL MIO_addAuthInfo( MIO_VOID *mioCtx,
									MIO_CONST MIO_CHAR *deviceid,
									MIO_CONST MIO_CHAR *digestUserName,
									MIO_CONST MIO_CHAR *password );


/*
 * 用来分配消息内容的头结构(miosMSG)，内存没有被清成0，由上层模块来选择处理。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *
 * 返回值：
 *  指向头结构的指针（MIO_NULL表示分配失败）
 *
 */
MIO_API miosMSG* MIO_mallocMsgHeader( MIO_VOID *mioCtx );

/*
 * 用来释放消息内容的头结构(miosMSG)。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  msg: 需要被释放的消息头结构指针
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_freeMsgHeader( MIO_VOID *mioCtx, miosMSG* msg );

/*
 * 用来分配消息内容中的信息元素结构，内存没有被清成0，由上层模块来选择处理。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  size: 需要的IE大小
 *
 * 返回值：
 *  指向信息元素结构的指针（MIO_NULL表示分配失败）
 *
 */
MIO_API MIO_VOID* MIO_mallocIE( MIO_VOID *mioCtx, MIO_UINT32 size );

/*
 * 用来释放消息内容中的信息元素结构。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  ie: 需要被释放的信息元素结构指针
 *  size: 需要被释放的信息元素结构的大小
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_freeIE( MIO_VOID *mioCtx, MIO_VOID *ie, MIO_UINT32 size);

/*
 * 用来分配消息内容中的列表节点，内存没有被清成0，由上层模块来选择处理。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *
 * 返回值：
 *  指向列表节点的指针（MIO_NULL表示分配失败）
 *
 */
MIO_API miosList* MIO_mallocListNode( MIO_VOID *mioCtx );

/*
 * 用来释放消息内容中的列表节点。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  listNode: 需要被释放的列表节点指针
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_freeListNode( MIO_VOID *mioCtx, miosList *listNode );

/*
 * 用来释放消息内容中的IE列表。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  ieList: 需要被释放的IE列表
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_freeIEList( MIO_VOID *mioCtx, miosList *ieList );

/*
 * 用来释放整个消息内容，包括头结构(miosMSG)，所有的列表节点(miosList)和所有的信息元素结构
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  msg: 需要被释放的消息内容指针
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_freeWholeMsg( MIO_VOID *mioCtx, miosMSG* msg );

#define IPV4 0
#define IPV6 1
/*
 * 用来猜测本地的IP地址。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  family: IPV4:0,IPV6:1
 *  ipAddr: 用来存放IP地址的缓存区
 *  len: 可用的缓存区的长度
 *  dest: 数据将要发送的目的地址。这个参数用在主机有多个网络地址时，可以选择到一个最合适的地址。
 *
 * 返回值：
 *  MIO_FALSE表示猜测失败
 *  MIO_TRUE表示成功。
 *
 */
MIO_API MIO_BOOL MIO_guessLocalIP( MIO_VOID *mioCtx, MIO_INT32 family, MIO_CHAR *ipAddr, MIO_INT32 len, MIO_CHAR *dest );

/*
 * 消息体的编码模式，不同的编码格式有不同的形式，举例说明如下：
 * 假使我们现在需要发送一个消息，消息名为"MSG_CMS_REG_REQ"，需要携带如下结构的IE
 *  typedef struct miosIEX_DCS_INFO{
 *      MIO_UINT32 type;
 *
 *      MIO_UINT8 m_PTZmode;
 *      MIO_UINT8 m_Vtdumode;
 *      MIO_UINT16 m_CallNum;
 *  }miosIEX_DCS_INFO;
 *
 * 当类型为 MIOC_CM_TELECOM 时，生成的消息体如下
 *  <?xml version="1.0" encoding="UTF-8" ?><Message Version="1.0">
 *  <IE_HEADER MessageType="MSG_CMS_REG_REQ" SequenceNumber="0" SessionID="3241" SourceID="123456789012345678" DestinationID="123456789012345678" />
 *  <IEX_DCS_INFO PTZmode="0" Vtdumode="1" CallNum="4" />
 *  </Message>
 *
 * 当类型为 MIOC_CM_CNC_REQ 时，生成的消息体如下
 *  <?xml version="1.0" encoding="UTF-8" ?><request command="MSG_CMS_REG_REQ"><parameters>
 *  <IEX_DCS_INFO>
 *      <PTZmode>0</PTZmode>
 *      <Vtdumode>1</Vtdumode>
 *      <CallNum>4</CallNum>
 *  </IEX_DCS_INFO>
 *  </parameters></request>
 *
 * 当类型为 MIOC_CM_CNC_RESP 时，生成的消息体如下
 *  <?xml version="1.0" encoding="UTF-8" ?><response command="MSG_CMS_REG_REQ">
 *  <result code="0"></result>
 *  <parameters>
 *  <IEX_DCS_INFO>
 *      <PTZmode>0</PTZmode>
 *      <Vtdumode>1</Vtdumode>
 *      <CallNum>4</CallNum>
 *  </IEX_DCS_INFO>
 *  </parameters>
 *  </response>
 *
 * 当类型为 MIOC_CM_CNC_URLENCODED 时，生成的消息体如下
 *  MSG_CMS_REG_REQ?IEX_DCS_INFO=0%2c1%2c4
 *
 */
typedef enum mioeCodeMode
{
	MIOC_CM_TELECOM,
	MIOC_CM_CNC_REQ,
	MIOC_CM_CNC_RESP,
	MIOC_CM_CNC_URLENCODED,
	MIOC_CM_UNKNOWN
}mioeCodeMode;

/*
 * 用来将XML消息文本解析成miosMSG的消息结构。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  buf: XML格式的消息文本
 *  len: 消息文本的长度
 *  codeMode: 编码模式。详细参见mioeCodeMode的说明
 *
 * 返回值：
 *  返回解析后生成的消息结构。如果为MIO_NULL，表示解析失败。
 *  需要使用MIO_freeWholeMsg函数释放，或者传递给MIO_SendMsg发送。
 *
 */
MIO_API miosMSG* MIO_decodeMSG( MIO_VOID *mioCtx, MIO_BYTE *buf, MIO_INT32 len, mioeCodeMode codeMode );

/*
 * 用来将miosMSG结构的消息转换成消息文本。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  msg: 需要转换成文本的消息
 *  buf: 输出的缓存。如果为MIO_NULL，表明只是计算需要的输出长度。
 *  len: 输出的缓存长度。
 *  codeMode: 编码模式。详细参见mioeCodeMode的说明
 *
 * 返回值：
 *  返回转换成文本之后的长度。如果buf不为MIO_NULL，并且len小于实际需要的长度，返回值为所需要的长度的相反数。
 *
 */
MIO_API MIO_INT32 MIO_encodeMSG( MIO_VOID *mioCtx, miosMSG *msg, MIO_BYTE *buf, MIO_INT32 len, mioeCodeMode codeMode );

/*
 * 将已有的消息结构完整的复制一份。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  msg: 需要被复制的消息结构
 *
 * 返回值：
 *  复制的消息结构，如果为MIO_NULL表示复制失败。
 *  需要使用MIO_freeWholeMsg函数释放，或者传递给MIO_SendMsg发送。
 *
 */
MIO_API miosMSG* MIO_cloneWholeMsg( MIO_VOID *mioCtx, miosMSG* msg );


/*
 * 用来设置接口模块是否自动从接受到的请求消息中获取真正的IP地址和端口号。
 * 当设置为使能的情况下，接口模块会将收到的请求消息中的SourceID和真正接收到的来源IP地址和端口号添加到一张对应表中。
 * 之后发送请求消息时，如果DestinationID可以在这张对应表中查到，那么就使用表中的地址发送消息，而不用from参数。
 * 默认在创建收发包模块时，这个功能是使能的。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  bEnable: 是否使能ID和地址的映射。
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_selfLearnDeviceIP( MIO_VOID *mioCtx, MIO_BOOL bEnable );

/*
 * MIO_checkLearnDeviceIPCB回调函数的返回值
*/
#define MIO_LEARN_DEVICE_IP_NO			0
#define MIO_LEARN_DEVICE_IP_YES			1
#define MIO_LEARN_DEVICE_IP_DEL			2
#define MIO_LEARN_DEVICE_IP_DEFAULT		3

/*
 * 检查是否要记录ID和IP地址映射的回调函数
 * 当设置了这个函数，接口模块在接收到消息时会调用这个函数，根据返回值来做不同的处理
 *
 * 参数定义：
 *  userData: 创建接口时由上层模块传入的不透明指针。
 *  msg: 接收到的请求消息。
 *
 * 返回值：
 *  MIO_LEARN_DEVICE_IP_NO: 表示不记录。
 *  MIO_LEARN_DEVICE_IP_YES: 表示需要记录。
 *  MIO_LEARN_DEVICE_IP_DEL: 表示要删除已经纪录的地址。
 *  MIO_LEARN_DEVICE_IP_DEFAULT: 表示如同没有设置这个回调函数一样
 *
 */
typedef MIO_INT32 (*MIO_checkLearnDeviceIPCB)( MIO_VOID *userData, miosMSG *msg );

/*
 * 因为 MIO_selfLearnDeviceIP 是针对所有的消息来设置是否需要自动获取并记录接收到的真正IP地址和端口号。
 * 不能满足可选择性的获取。所以设计这个函数，用来由上层使用模块设置一个用来判断是否需要获取的回调函数。
 * 当设置了这个判断回调时，接口模块首先获调用这个回调，然后根据回调的返回值来做不同的动作。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  checkLearnDeviceIPCB: 用来做判断的回调函数。
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_setCheckLearnDeviceIPCallBack( MIO_VOID *mioCtx, MIO_checkLearnDeviceIPCB checkLearnDeviceIPCB );

/*
 * 用于在ID和地址的映射表中添加一条记录。
 * 如果自动获取的功能被使能时，那么这条记录可能会被后续自动获取到的地址所覆盖。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  deviceID: ID号
 *  ip: IP地址
 *  port: 端口号
 *
 * 返回值：
 *  MIO_FALSE 表示添加失败。
 *  MIO_TRUE 表示添加成功。
 *
 */
MIO_API MIO_BOOL MIO_addDeviceAddr( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *deviceID, MIO_CONST MIO_CHAR *ip, MIO_UINT16 port );

/*
 * 用于在ID和地址的映射表中删除一条记录。
 *
 * 参数定义：
 *  mioCtx: 接口模块句柄
 *  deviceID: ID号
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_removeDeviceAddr( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *deviceID );

/*
 * 用来设置收发包模块LOG文件的大小限制。收发包模块的LOG采用多个文件的方式。
 * 每个LOG文件默认最大为大约 16M，默认的总大小限制为1G。
 * 一个文件的大小达到限制以后就生成一个新的文件，这些文件的前缀保持一致以便查看。
 * 如果总LOG信息大小达到了最大的限制。那么采用循环覆盖的方式。覆盖掉最早的那个文件。
 * 可以使用这个函数来修改默认值。
 *
 * 参数定义：
 *  totalBytes: 总的LOG大小限制。如果这个值小于 bytesPerFile，那么就取消了总大小的限制。默认值为1G。
 *  bytesPerFile: 单个LOG文件的大小限制。小于512K的值就被当作 512K。默认值为16M。
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_setLogLimit( MIO_UINT32 totalBytes, MIO_UINT32 bytesPerFile );

/*
 * 用来取消正在发送的消息。本函数只是将消息从协议栈中删除，并且不再将这个消息的回应传递给应用层。
 * 对于已经发送出去的数据包，以及由这些数据包导致的接收方动作不能产生影响。
 *
 * 参数定义：
 *  mioCtx: 收发包模块上下文指针
 *  msgID: 要取消的消息ID号
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_cancelSendingMsg( MIO_VOID *mioCtx, MIO_UINT32 msgID );

/*
 * 用来设置上层自定义的消息和IE。详细的请参见《控制接口详细设计说明书》中的自定义发送消息和IE。
 *
 * 参数定义：
 *  userMsgList: 上层自定义的消息定义列表。为一个数组，结尾的结构内容为0
 *  userIEList: 上层自定义的IE定义列表。为一个数组，结尾的结构内容为0
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_setUserMsgAndIE( MIO_CONST miosUserMsgDef *userMsgList, MIO_CONST miosUserIEDef *userIEList );


/*
 * 用来获得接口模块的版本号。
 *
 * 参数定义：
 *  无
 *
 * 返回值：
 *  返回一个标志接口模块版本的字符串。
 *
 */
MIO_API MIO_CONST MIO_CHAR* MIO_getVersionStr( MIO_VOID );

/*
 * 将miosMSG消息以二进制的形式填写到一段缓存中。
 * 填写到缓存中的数据，可以使用在同一类架构CPU的机器上使用MIO_deserializeMsg还原成miosMSG消息。
 *
 * 参数定义：
 *  mioCtx: 收发包模块上下文指针
 *  msg: 要转化的消息
 *  buf: 输出缓存
 *  len: 输出缓存的长度
 *
 * 返回值：
 *  如果buf不为MIO_NULL，返回填写的长度，len小于需要的长度，返回值小于零，表示填写失败。
 *  如果buf为MIO_NULL，返回需要的长度。
 *
 */
MIO_API MIO_INT32 MIO_serializeMsg( MIO_VOID *mioCtx, miosMSG* msg, MIO_BYTE *buf, MIO_INT32 len );

/*
 * 用来将MIO_serializeMsg函数二进制化的数据还原为miosMSG消息。
 *
 * 参数定义：
 *  mioCtx: 收发包模块上下文指针
 *  buf: 二进制数据
 *  len: 二进制数据长度
 *
 * 返回值：
 *  还原的消息。需要用MIO_freeWholeMsg释放。
 *
 */
MIO_API miosMSG* MIO_deserializeMsg( MIO_VOID *mioCtx, MIO_BYTE *buf, MIO_INT32 len );



/*
 * 用来初始化HTTP消息协议栈。
 *
 * 参数定义：
 *  mioCtx: 收发包模块上下文指针
 *  listenIpFamily: AF_INET;AF_INET6
 *  listenPort: 侦听的端口号
 *  userData: 上层用户的不透明指针，在调用回调的时候回传给上层
 *  notifyCB: 接收到消息的通知回调，和MIO_CreateCtxEx函数的回调相同。
 *            如果这个参数为空，那么就使用创建收发包模块时的userData和notifyCB
 *
 * 返回值：
 *  MIO_TRUE表示初始化成功。
 *  MIO_FALSE表示初始化失败。
 *
 */
MIO_API MIO_BOOL MIO_initHTTPCtx( MIO_VOID *mioCtx,
									MIO_INT32 listenIpFamily,
									MIO_UINT16 listenPort,
									MIO_VOID *userData,
									MIO_NotifyCB notifyCB );

/*
 * 用来关闭HTTP协议栈的一个连接。
 * HTTP协议栈的工作模式是不主动关闭对方发来的连接。
 * 上层模块可以根据需要选择性的关闭某一个连接。
 * 连接的远端地址，可以从接收到请求消息的回调通知参数中获得。
 *
 * 参数定义：
 *  mioCtx: 收发包模块上下文指针
 *  ip: 连接的远端ip地址
 *  port: 连接的远端端口号
 *
 * 返回值：
 *  MIO_TRUE表示关闭连接成功
 *  MIO_FALSE表示关闭连接失败
 *
 */
MIO_API MIO_BOOL MIO_closeHTTPConnection( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *ip, MIO_UINT16 port );

/*
 * 用来设置HTTP连接的超时时间。
 * 如果在这个超时时间到达时HTTP连接上都没有任何的数据，那么就会自动关闭这个连接。
 * 设置这个超时时间的目的在于清除可能已经不存在的异常连接。
 *
 * 参数定义：
 *  mioCtx: 收发包模块上下文指针
 *  timeout: 超时时间，以秒为单位。默认为1800秒（半小时）
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_setHTTPConnectionTimeout( MIO_VOID *mioCtx, MIO_UINT32 timeout );
											


/*
 * 将ip地址和端口号拼装成HTTP URL。格式为 http://ip:port/
 *
 * 参数定义：
 *  retURL: URL的输出缓存
 *  len: 输出缓存的长度
 *  ip: ip地址
 *  port: 端口号
 *
 * 返回值：
 *  MIO_TRUE表示拼装成功。
 *  MIO_FALSE表示拼装失败，通常是因为输出缓存的长度不够。
 *
 */
MIO_API MIO_BOOL MIO_fillHTTPUrl( MIO_CHAR *retURL,
									MIO_INT32 len,
									MIO_CHAR *ip,
									MIO_UINT16 port );

/*
 * 用来拼装SIP URL。格式为 sip:[username@]ip:port （[]包括的部分为可选的）
 *
 * 参数定义：
 *  retURL: URL的输出缓存
 *  len: 输出缓存的长度
 *  username: SIP地址的用户名部分，如果为空，则没有地址中用户名部分
 *  ip: SIP地址的域名部分
 *  port: SIP地址的端口号
 *
 * 返回值：
 *  MIO_TRUE表示拼装成功。
 *  MIO_FALSE表示拼装失败，通常是因为输出缓存的长度不够。
 *
 */
MIO_API MIO_BOOL MIO_fillSIPUrl( MIO_CHAR *retURL,
									MIO_INT32 len,
									MIO_CHAR *username,
									MIO_CHAR *ip,
									MIO_UINT16 port );
/*
 * 用HTTP协议通讯时的消息携带方式
 */
typedef enum mioeHTTPEncodeMode{
	MIO_HTTP_EM_POST_XML,			// 使用 POST 方法携带 XML 格式的消息体
	MIO_HTTP_EM_POST_URLENCODED,	// 使用 POST 方法携带 application/x-www-form-urlencoded 格式的消息体
	MIO_HTTP_EM_GET					// 使用 GET 方法，将消息体携带在请求 URL 中 
}mioeHTTPEncodeMode;

/*
 * 因为HTTP的信令格式有多种方式，这个函数用来设置HTTP在发送信令的时候使用什么格式。
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *  encodeMode: 编码的模式，参照 mioeHTTPEncodeMode 的说明
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_setHTTPEncodeMode( MIO_VOID *mioCtx, mioeHTTPEncodeMode encodeMode );

/*
 * 用来发送HTTP请求消息。
 * 特别提供这个函数是用来使应用者可以对每一条消息都设置不同的消息封装格式。
 * 正常情况下使用MIO_SendMsg或MIO_SendMsgEx就可以满足要求。
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *  url: 目的URL
 *  msg: 消息内容
 *  msgUserData: 上层模块的私有消息数据。参见MIO_SendMsg中的说明
 *  ip: 发送的目标地址，如果为空，那么使用url中解析出来的地址
 *  port: 发送的目标端口号
 *  httpEncodeMode: 编码的模式，参见MIO_setHTTPEncodeMode
 *
 * 返回值：
 *  消息ID号（MIO_INVALID_MSGID为无效的消息ID号，当返回这个值时时表示函数调用失败）
 *
 */
MIO_API MIO_UINT32 MIO_SendHttpReq( MIO_VOID *mioCtx,
										MIO_CHAR *url,
										miosMSG *msg,
										MIO_VOID *msgUserData,
										MIO_CHAR *ip,
										MIO_UINT16 port,
										mioeHTTPEncodeMode httpEncodeMode );

/*
 * 当上层应用作为 REGISTER服务器时，用来使能digest认证。
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *  realm: digest认证时提示给客户端的领域名
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_enableDigest( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *realm );

/*
 * 当上层应用作为 REGISTER服务器时，用来取消digest认证。
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_disableDigest( MIO_VOID *mioCtx );

/*
 * 用来开启日志功能。
 * 接口模块的日志文件在Windows平台下存储在"c:\miolog\"目录下，
 * 在linux平台下存储在"当前工作目录/miolog"目录中。
 * 如果对应的目录不存在，就不会建立日志文件。
 * 使能日志输出以后，会依据间隔时间去尝试建立日志文件。
 * 默认情况下日志功能是开启的。
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *  logCheckInterval: 检查是否建立日志文件的间隔时间，默认值为10秒。
 *                    如果这个值为0表示保持原来的值，如果值小于5就认为指定了最小值5秒
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_enableLog( MIO_VOID *mioCtx, MIO_UINT32 logCheckInterval );

/*
 * 关闭日志功能。
 * 调用这个函数会去关闭日志文件，关闭文件的动作可能不能立即生效，大约有一个50毫秒的延时。
 * 如果在这个函数后紧接着调用 MIO_enableLog ，那么这个函数有可能不起任何作用。
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_disableLog( MIO_VOID *mioCtx );

/*
 * 向接口模块的日志文件中写入一段数据。
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *  buf: 输出的数据指针
 *  len: 输出的数据长度
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_logWrite( MIO_VOID *mioCtx, MIO_CONST MIO_BYTE *buf, MIO_INT32 len );

/*
 * 向接口模块的日志文件中写入一段格式化的数据。
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *  format: 输出数据的格式，具体格式请参见printf的格式。
 *  ...: 需要格式化输出的数据
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_logVaWrite( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *format, ... );

/*
 * 向收发包模块的日志文件中写入一段格式化的数据。
 * 这个函数和上一个函数的区别在于给每一个要格式化输出的文本提供了附加的格式化输出前缀。
 * 目前主要用于mediasip模块中对osip日志的输出管理
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *  format: 输出数据的格式，具体格式请参见printf的格式。
 *  args: 输出的可变数据参数列表
 *  preformat: 输出前缀的格式，具体格式请参见printf的格式。
 *  ...: 需要格式化输出的前缀
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_logVaWriteEx( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *format, va_list args, MIO_CONST MIO_CHAR *preformat, ... );

/*
 * 用来设置收到请求消息后，等待上层模块发送回应的最大的等待时间。
 * 设置这个超时时间的目的在于，当上层模块不发送回应时可以清除掉收发包模块的一些相关的资源。
 * 这个超时时间对HTTP消息尤其有用，因为HTTP信令采用的是先来先回应的模式。
 * 如果一个消息不回应，会导致后续的消息也没有办法回应。
 * 当超时时间到达时，对于HTTP消息，收发包模块会自动发送一个错误的回应。
 * 因为超时时间有一定的时长，对于HTTP消息，如果上层模块不回应，
 * 只有到当前消息超时以后才可能发送后续的相应，效率上会有很大的降低，所以请上层模块确保每一个消息都会发送回应。
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *  timeout: 超时时间，单位为秒。默认为64秒。
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_setRespWaitTimeout( MIO_VOID *mioCtx, MIO_UINT32 timeout );

/*
 * 用来初始化收发包模块。这个函数会在MIO_CreateCtx或MIO_CreateCtxEx中调用，
 * 但是如果有多个线程同时调用MIO_CreateCtx或MIO_CreateCtxEx时，因为初始化互斥锁可能没有完成，
 * 导致可能出现意想不到的错误，所以如果有多个线程调用会调用MIO_CreateCtx或MIO_CreateCtxEx时，
 * 请确保首先在唯一的一个地方调用这个函数来初始化收发包模块。
 *
 * 参数定义：
 *  无
 *
 * 返回值：
 *  MIO_TRUE 表示初始化成功。
 *  MIO_FALSE 表示初始化失败。
 *
 */
MIO_API MIO_BOOL MIO_initMIOModule( MIO_VOID );

/*
 * 用来卸载收发包模块。
 * 基于提供MIO_initMIOModule同样的原因，预防多个线程同时调用MIO_DestroyCtx时可能产生的错误。
 * 如果有多个线程调用MIO_DestroyCtx时，请确保在唯一的一个地方调用这个函数来卸载收发包模块。
 *
 * 参数定义：
 *  无
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_exitMIOModule( MIO_VOID );

/*
 * 用来将UTF-8字符转换成GB2312字符
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *  utf8Str: 将要被转换的UTF-8字符串
 *  utf8StrLen: UTF-8字符串的长度
 *  gb2312Str: GB2312字符串的输出缓冲区
 *  gb2312StrLen: GB2312输出缓冲区的长度
 *
 * 返回值：
 *  转换后填写到GB2312缓冲区中的字符长度
 *
 */
MIO_API MIO_INT32 MIO_convUTF8ToGB2312( MIO_VOID *mioCtx,
										MIO_CONST MIO_BYTE *utf8Str,
										MIO_INT32 utf8StrLen,
										MIO_BYTE *gb2312Str,
										MIO_INT32 gb2312StrLen );

/*
 * 用来将GB2312字符转换成UTF-8字符
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *  gb2312Str: 将要被转换的GB2312字符串
 *  gb2312StrLen: GB2312字符串的长度
 *  utf8Str: UTF-8字符串的输出缓冲区
 *  utf8StrLen: UTF-8输出缓冲区的长度
 *
 * 返回值：
 *  转换后填写到UTF-8缓冲区中的字符长度
 *
 */
MIO_API MIO_INT32 MIO_convGB2312ToUTF8( MIO_VOID *mioCtx,
										MIO_CONST MIO_BYTE *gb2312Str,
										MIO_INT32 gb2312StrLen,
										MIO_BYTE *utf8Str,
										MIO_INT32 utf8StrLen );

/*
 * 用来告诉接口模块，上层应用在发送消息结构中携带的字符串是GB2312还是UTF-8。
 * 如果为GB2312时，接口模块需要将其转换成UTF-8。
 * 如果为UTF-8，那么接口模块就直接将其输出。默认接口模块认为消息结构中的字符串为GB2312。
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *  bUseUTF8: 用来指示消息结构中使用的字符串是否为UTF-8字符
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_setStrIOFlag( MIO_VOID *mioCtx, MIO_BOOL bUseUTF8 );

/*
 * 发送请求时的压缩模式
 */
typedef enum mioeDeflateMode{
	MIO_DM_NO_DEFLATE,		// 不对发送的消息进行压缩
	MIO_DM_DEFLATE,			// 对所有消息都压缩后发送
	MIO_DM_AUTO_DEFLATE		// 判断目的是否可以接收压缩
							// 如果可以接收压缩，就压缩
							// 否则不压缩。
							// 判断目的是否可以接收压缩的方法是根据目的之前发送来的数据包是否进行了压缩。
							// 如果进行了压缩，就表示可以接受压缩，反之则不能。
							// 如果还没有收到过目的任何数据包，那么默认是不压缩。
}mioeDeflateMode;

/*
 * 这个函数用来设置消息体压缩处理模式。
 * 因为有时候消息体会太大，导致SIP封装的UDP包过大，导致出现IP分片，进而影响发送效率。
 * 甚至某些低端的路由器在做NAT转换时会将分片的后续包丢弃。
 * 因而设计这个函数来对消息体进行一定的压缩，但是压缩的比率也并不高。
 * 这只能缓解问题，但是不能根本解决问题。
 * 因为压缩需要得到所有服务单元的一致处理，否则会导致消息无法解析。
 * 所以目前采用SIP的Content-Encoding头字段来指示消息内容是否进行了压缩。
 * 当Content-Encoding为deflate时，表示消息体使用了deflate压缩，否则没有。
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *  deflateMode: 发送消息时压缩的处理模式
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_setDeflateMode( MIO_VOID *mioCtx, mioeDeflateMode deflateMode );

/*
 * 用来计算Digest认证。
 * 当在回调函数种收到MIO_NC_RECV_REGISTER通知时，
 * 可以将miosRegisterNotifyExtraParam结构中的计算参数以及用户的密码传给这个函数来计算认证。
 *
 * 参数定义：
 *  nonce: SIP Authorization 头字段中的 nonce
 *  cNonce: SIP Authorization 头字段中的 cnonce
 *  user: SIP Authorization 头字段中的 username
 *  realm: SIP Authorization 头字段中的 realm
 *  pass: 用来计算的密码
 *  alg: SIP Authorization 头字段中的 algorithm
 *  nonceCount: SIP Authorization 头字段中的 nc
 *  method: SIP 消息的方法名
 *  qop: SIP Authorization 头字段中的 qop
 *  uri: SIP Authorization 头字段中的 uri
 *  response: SIP Authorization 头字段中的 response
 *
 * 返回值：
 *  MIO_TRUE 表示认证成功
 *  MIO_FALSE 表示认证失败
 *
 */
MIO_API MIO_BOOL MIO_calcAuthorization( MIO_CONST MIO_CHAR *nonce,
										MIO_CONST MIO_CHAR *cNonce,
										MIO_CONST MIO_CHAR *user,
										MIO_CONST MIO_CHAR *realm,
										MIO_CONST MIO_CHAR *pass,
										MIO_CONST MIO_CHAR *alg,
										MIO_CONST MIO_CHAR *nonceCount,
										MIO_CONST MIO_CHAR *method,
										MIO_CONST MIO_CHAR *qop,
										MIO_CONST MIO_CHAR *uri,
										MIO_CONST MIO_CHAR *response );

/*
 * 用来获得IE结构的内存大小
 *
 * 参数定义：
 *  type: IE的编号值
 *
 * 返回值：
 *  IE结构的内存大小
 *
 */
MIO_API MIO_UINT32 MIO_getIESizeByType( mioeIEType type );

/*
 * 用来设置使用HTTP通讯的时候，是否使用长连接方式。
 * 使用长连接的考虑主要是针对在NAT内的设备，方便NAT的穿越。
 * 默认情况下现在HTTP协议栈是使用短连接的方式，发送或接收完回应以后就将连接断开。
 * 长连接的方式就是不主动断开连接，由通讯的另一方控制。
 * 这样的方式有一点点缺陷，那就是不能自适应的断开连接。
 * 在HTTP协议中有一些头字段是用来控制连接的保持的，或许后续的版本可以使用这来做到自适应。
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *  bEnableLongConn: 是否使能长连接
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_setHttpConnMode( MIO_VOID *mioCtx, MIO_BOOL bEnableLongConn );

/*
 * 将形如"YYYY-MM-DD hh:mm:ss"格式的时间字符串转换成自1970年1月1日以来的秒数。
 *
 * 参数定义：
 *  time: 输出的自1970年1月1日以来的秒数
 *  srcStr: "YYYY-MM-DD hh:mm:ss"格式的时间字符串
 *
 * 返回值：
 *  MIO_TRUE 表示转换成功
 *  MIO_FALSE 表示转换失败
 *
 */
MIO_API MIO_BOOL MIO_decodeTime( MIO_TIME *time, MIO_CONST MIO_CHAR *srcStr );

/*
 * 将自1970年1月1日以来的秒数转换成形如"YYYY-MM-DD hh:mm:ss"格式的时间字符串。
 *
 * 参数定义：
 *  time: 输入自1970年1月1日以来的秒数
 *  dstStr: 储存"YYYY-MM-DD hh:mm:ss"格式的输出时间字符串的缓冲区
 *  avaLen: 缓冲区的长度
 *
 * 返回值：
 *  MIO_TRUE 表示转换成功
 *  MIO_FALSE 表示转换失败
 *
 */
MIO_API MIO_BOOL MIO_encodeTime( MIO_TIME *time, MIO_CHAR *dstStr, MIO_INT32 avaLen );

/*
 * 产生一个整数随机数。
 *
 * 参数定义：
 *  无
 *
 * 返回值：
 *  产生的随机数
 *
 */
MIO_API MIO_UINT32 MIO_random( MIO_VOID );

/*
 * 分配一块内存，
 * 这个函数需要两个附加的参数，文件名和行号。用C语言预定义的宏__FILE__和__LINE__可以得到。
 *
 * 参数定义：
 *  size: 需要分配的内存大小
 *  fileName: 调用分配函数的文件名
 *  lineNumber: 调用分配函数的行号
 *
 * 返回值：
 *  分配的内存指针
 *
 */
MIO_API MIO_VOID* MIO_mallocDebug( MIO_UINT32 size, MIO_CONST MIO_CHAR *fileName, MIO_INT32 lineNumber );

/*
 * 重新分配一块内存，
 * 这个函数需要两个附加的参数，文件名和行号。用C语言预定义的宏__FILE__和__LINE__可以得到。
 *
 * 参数定义：
 *  memblock: 原来的内存指针
 *  size: 新的分配大小
 *  fileName: 调用分配函数的文件名
 *  lineNumber: 调用分配函数的行号
 *
 * 返回值：
 *  分配的内存指针
 *
 */
MIO_API MIO_VOID* MIO_reallocDebug( MIO_VOID *memblock, MIO_UINT32 size, MIO_CONST MIO_CHAR *fileName, MIO_INT32 lineNumber );

/*
 * 释放一块内存，
 * 这个函数需要两个附加的参数，文件名和行号。用C语言预定义的宏__FILE__和__LINE__可以得到。
 *
 * 参数定义：
 *  memblock: 需要被释放的内存指针
 *  fileName: 调用释放函数的文件名
 *  lineNumber: 调用释放函数的行号
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_freeDebug( MIO_VOID *memblock, MIO_CONST MIO_CHAR *fileName, MIO_INT32 lineNumber );


/*
 * 分配一块内存。
 *
 * 参数定义：
 *  memblock: 需要被释放的内存指针
 *
 * 返回值：
 *  分配的内存指针
 *
 */
MIO_API MIO_VOID* MIO_malloc( MIO_UINT32 size );

/*
 * 重新分配一块内存。
 *
 * 参数定义：
 *  memblock: 原来的内存指针
 *  size: 新的分配大小
 *
 * 返回值：
 *  分配的内存指针
 *
 */
MIO_API MIO_VOID* MIO_realloc( MIO_VOID *memblock, MIO_UINT32 size );

/*
 * 释放一块内存。
 *
 * 参数定义：
 *  memblock: 需要被释放的内存指针
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_free( MIO_VOID *memblock );

/*
 * 用来启用接口模块的内存调试模式。
 * 启用以后，接口退出时会在日志文件中输出是否有内存以及导致内存泄漏的文件和行号。
 *
 * 参数定义：
 *  无
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_enableMemDebug();

/*
 * 用来关闭接口模块的内存调试模式。
 *
 * 参数定义：
 *  无
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_disableMemDebug();

/*
 * 用来创建单纯的客户端接口模块，不需要提供本地的侦听端口。
 * 此时只能使用HTTP的客户端模式去发送请求。
 *
 * 参数定义：
 *  sipUserData: SIP回调消息中回传的用户不透明数据
 *  sipNotifyCB: SIP通知回调
 *  httpUserData: HTTP回调消息中回传的用户不透明数据
 *  httpNotifyCB: HTTP通知回调。如果为空，那么就使用sipNotifyCB和sipUserData。
 *
 * 返回值：
 *  模块上下文指针（MIO_NULL表示创建失败）
 *
 */
MIO_API MIO_VOID* MIO_CreateCtxForClient( MIO_VOID *sipUserData,
											MIO_NotifyCB sipNotifyCB,
											MIO_VOID *httpUserData,
											MIO_NotifyCB httpNotifyCB );

/*
 * 用来设置SIP的侦听端口号。
 * 如果已经设置过了，那么不起该函数作用。
 * 适用于使用MIO_CreateCtxForClient创建接口以后，再设置端口号。
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *  sipPort: SIP的侦听端口号
 *
 * 返回值：
 *  MIO_TRUE 表示设置成功
 *  MIO_FALSE 表示设置失败
 *
 */
MIO_API MIO_BOOL MIO_setSipPort( MIO_VOID *mioCtx, MIO_UINT16 sipPort );

/*
 * 用来设置HTTP的侦听端口号。
 * 如果已经设置过了，那么不起该函数作用。
 * 适用于使用MIO_CreateCtxForClient创建接口以后，再设置端口号。
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *  httpPort: HTTP的侦听端口号
 *
 * 返回值：
 *  MIO_TRUE 表示设置成功
 *  MIO_FALSE 表示设置失败
 *
 */
MIO_API MIO_BOOL MIO_setHttpPort( MIO_VOID *mioCtx, MIO_UINT16 httpPort );


/*
 * 调用这个函数以后，如果遇到注册失败的时候，不再继续发起后续的注册。
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_enableStopRegWhenFail( MIO_VOID *mioCtx );

/*
 * 调用这个函数以后，如果遇到注册失败的时候，会继续发起后续的注册。
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_VOID MIO_disableStopRegWhenFail( MIO_VOID *mioCtx );

/*
 * 给发出去的HTTP消息自动增加IEX_HEADER
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *  msg: 需要自动增加IEX_HEADER的消息
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_BOOL MIO_patchOutHttpMsg( MIO_VOID *mioCtx, miosMSG *msg );

/*
 * 给接收到的HTTP消息自动提取IEX_HEADER中的内容
 *
 * 参数定义：
 *  mioCtx: 接口模块上下文指针
 *  msg: 需要自动提取IEX_HEADER内容的消息
 *
 * 返回值：
 *  无
 *
 */
MIO_API MIO_BOOL MIO_patchInHttpMsg( MIO_VOID *mioCtx, miosMSG *msg );



/////////////////////////////////////////////////////////////////////////////////
//	为了和mediasip共同在windows编译而附加的函数
//	基本上和上面提供的接口函数一一对应
//
//	为什么要设置这样的重复函数？
//		当和mediasip在windows一块编译的时候，是将 MIO 模块编译成一个静态库（staticmsgio.lib）由
//	mediasip在生成dll的时候链接，如果直接使用静态库链接，那么静态库内的函数没有办法在dll中导出。
//	因此就需要mediasip在编译的时候不仅链接 staticmsgio.lib 。还要附加编译一些代码来导出静态库中的函数。
//	这写代码的实现就是 miointerface.c 文件。这个文件基本上只做调用静态库中函数的动作。
//	当mediasip在编译的时候附加编译这个文件就可以了。
//
//	如下这些函数是接口模块的内部真正实现函数
//	上面提供给外面使用的接口函数基本上都是在 miointerface.c 中实现
/////////////////////////////////////////////////////////////////////////////////


MIO_VOID* MIO_CreateCtxExInternal( MIO_UINT16 listenPort,
									MIO_VOID *userData,
									MIO_NotifyCB notifyCB);


MIO_VOID* MIO_CreateCtxInternal( MIO_UINT16 listenPort,
									MIO_VOID *userData);

MIO_VOID MIO_DestroyCtxInternal( MIO_VOID *mioCtx );


MIO_UINT32 MIO_SendMsgInternal( MIO_VOID *mioCtx,
								MIO_CHAR *to,
								MIO_CHAR *from,
								MIO_UINT32 msgID,
								miosMSG *msg,
								MIO_VOID *msgUserData,
								MIO_BOOL bEsRequest,
								MIO_CHAR *ip,
								MIO_UINT16 port );

MIO_UINT32 MIO_SendRegInternal( MIO_VOID *mioCtx,
								MIO_CHAR *to,
								MIO_CHAR *from,
								MIO_CHAR *userName,
								MIO_CHAR *passWord,
								MIO_INT32 expires,
								MIO_VOID *regUserData,
								MIO_CHAR *ip,
								MIO_UINT16 port );

MIO_UINT32 MIO_SendRegExInternal( MIO_VOID *mioCtx,
									MIO_CHAR *to,
									MIO_CHAR *from,
									MIO_CHAR *userName,
									MIO_CHAR *passWord,
									MIO_INT32 expires,
									MIO_VOID *regUserData,
									MIO_CHAR *ip,
									MIO_UINT16 port,
									MIO_CHAR *regCallId );

MIO_BOOL MIO_cancelRegInternal( MIO_VOID *mioCtx,
								MIO_UINT32 regID );


MIO_UINT32 MIO_SendRegRespInternal( MIO_VOID *mioCtx,
									MIO_UINT32 msgID,
									MIO_INT32 respCode,
									MIO_CHAR *passWord );

MIO_UINT32 MIO_SendRegRespExInternal( MIO_VOID *mioCtx,
										MIO_UINT32 msgID,
										MIO_INT32 respCode,
										MIO_CHAR *passWord,
										MIO_CONST MIO_CHAR *respReasonPhrase );




miosMSG* MIO_mallocMsgHeaderInternal( MIO_VOID *mioCtx );

MIO_VOID MIO_freeMsgHeaderInternal( MIO_VOID *mioCtx, miosMSG* msg );

MIO_VOID* MIO_mallocIEInternal( MIO_VOID *mioCtx, MIO_UINT32 size );

MIO_VOID MIO_freeIEInternal( MIO_VOID *mioCtx, MIO_VOID *ie, MIO_UINT32 size);

miosList* MIO_mallocListNodeInternal( MIO_VOID *mioCtx );

MIO_VOID MIO_freeListNodeInternal( MIO_VOID *mioCtx, miosList *listNode );

MIO_VOID MIO_freeIEListInternal( MIO_VOID *mioCtx, miosList *ieList );

MIO_VOID MIO_freeWholeMsgInternal( MIO_VOID *mioCtx, miosMSG* msg );

MIO_BOOL MIO_guessLocalIPInternal( MIO_VOID *mioCtx, MIO_INT32 family, MIO_CHAR *ipAddr, MIO_INT32 len, MIO_CHAR *dest );

MIO_VOID MIO_handleExosipEvent( MIO_VOID *mioCtx, MIO_VOID *eXosipEvent );

miosMSG* MIO_decodeMSGInternal( MIO_VOID *mioCtx, MIO_BYTE *buf, MIO_INT32 len, mioeCodeMode codeMode );

MIO_INT32 MIO_encodeMSGInternal( MIO_VOID *mioCtx, miosMSG *msg, MIO_BYTE *buf, MIO_INT32 len, mioeCodeMode codeMode );

miosMSG* MIO_cloneWholeMsgInternal( MIO_VOID *mioCtx, miosMSG* msg );

MIO_VOID MIO_selfLearnDeviceIPInternal( MIO_VOID *mioCtx, MIO_BOOL bEnable );

MIO_VOID MIO_setCheckLearnDeviceIPCallBackInternal( MIO_VOID *mioCtx, MIO_checkLearnDeviceIPCB checkLearnDeviceIPCB );

MIO_BOOL MIO_addDeviceAddrInternal( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *deviceID, MIO_CONST MIO_CHAR *ip, MIO_UINT16 port );

MIO_VOID MIO_removeDeviceAddrInternal( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *deviceID );

MIO_VOID MIO_setLogLimitInternal( MIO_UINT32 totalBytes, MIO_UINT32 bytesPerFile );

MIO_VOID MIO_cancelSendingMsgInternal( MIO_VOID *mioCtx, MIO_UINT32 msgID );

MIO_VOID MIO_setUserMsgAndIEInternal( MIO_CONST miosUserMsgDef *userMsgList, MIO_CONST miosUserIEDef *userIEList );

MIO_CONST MIO_CHAR* MIO_getVersionStrInternal( MIO_VOID );

MIO_INT32 MIO_serializeMsgInternal( MIO_VOID *mioCtx, miosMSG* msg, MIO_BYTE *buf, MIO_INT32 len );

miosMSG* MIO_deserializeMsgInternal( MIO_VOID *mioCtx, MIO_BYTE *buf, MIO_INT32 len );


MIO_BOOL MIO_initHTTPCtxInternal( MIO_VOID *mioCtx,
									MIO_INT32 listenIpFamily,
									MIO_UINT16 listenPort,
									MIO_VOID *userData,
									MIO_NotifyCB notifyCB );

MIO_BOOL MIO_closeHTTPConnectionInternal( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *ip, MIO_UINT16 port );

MIO_VOID MIO_setHTTPConnectionTimeoutInternal( MIO_VOID *mioCtx, MIO_UINT32 timeout );


MIO_BOOL MIO_fillHTTPUrlInternal( MIO_CHAR *retURL,
									MIO_INT32 len,
									MIO_CHAR *ip,
									MIO_UINT16 port );

MIO_BOOL MIO_fillSIPUrlInternal( MIO_CHAR *retURL,
									MIO_INT32 len,
									MIO_CHAR *username,
									MIO_CHAR *ip,
									MIO_UINT16 port );


MIO_VOID MIO_setHTTPEncodeModeInternal( MIO_VOID *mioCtx, mioeHTTPEncodeMode encodeMode );

MIO_UINT32 MIO_SendHttpReqInternal( MIO_VOID *mioCtx,
									MIO_CHAR *url,
									miosMSG *msg,
									MIO_VOID *msgUserData,
									MIO_CHAR *ip,
									MIO_UINT16 port,
									mioeHTTPEncodeMode httpEncodeMode );

MIO_VOID MIO_enableDigestInternal( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *realm );

MIO_VOID MIO_disableDigestInternal( MIO_VOID *mioCtx );

MIO_BOOL MIO_addAuthInfoInternal( MIO_VOID *mioCtx,
									MIO_CONST MIO_CHAR *deviceid,
									MIO_CONST MIO_CHAR *digestUserName,
									MIO_CONST MIO_CHAR *password );

MIO_VOID MIO_enableLogInternal( MIO_VOID *mioCtx, MIO_UINT32 logCheckInterval );

MIO_VOID MIO_disableLogInternal( MIO_VOID *mioCtx );

MIO_VOID MIO_logWriteInternal( MIO_VOID *mioCtx, MIO_CONST MIO_BYTE *buf, MIO_INT32 len );

MIO_VOID MIO_logVaWriteInternal( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *format, va_list args );

MIO_VOID MIO_logVaWriteExInternal( MIO_VOID *mioCtx, MIO_CONST MIO_CHAR *format, va_list args, MIO_CONST MIO_CHAR *preformat, va_list preargs );

MIO_VOID MIO_setRespWaitTimeoutInternal( MIO_VOID *mioCtx, MIO_UINT32 timeout );

MIO_BOOL MIO_initMIOModuleInternal( MIO_VOID );

MIO_VOID MIO_exitMIOModuleInternal( MIO_VOID );


MIO_INT32 MIO_convUTF8ToGB2312Internal( MIO_VOID *mioCtx,
										MIO_CONST MIO_BYTE *utf8Str,
										MIO_INT32 utf8StrLen,
										MIO_BYTE *gb2312Str,
										MIO_INT32 gb2312StrLen );

MIO_INT32 MIO_convGB2312ToUTF8Internal( MIO_VOID *mioCtx,
										MIO_CONST MIO_BYTE *gb2312Str,
										MIO_INT32 gb2312StrLen,
										MIO_BYTE *utf8Str,
										MIO_INT32 utf8StrLen );

MIO_VOID MIO_setStrIOFlagInternal( MIO_VOID *mioCtx, MIO_BOOL bUseUTF8 );


MIO_VOID MIO_setDeflateModeInternal( MIO_VOID *mioCtx, mioeDeflateMode deflateMode );


MIO_BOOL MIO_calcAuthorizationInternal( MIO_CONST MIO_CHAR *nonce,
										MIO_CONST MIO_CHAR *cNonce,
										MIO_CONST MIO_CHAR *user,
										MIO_CONST MIO_CHAR *realm,
										MIO_CONST MIO_CHAR *pass,
										MIO_CONST MIO_CHAR *alg,
										MIO_CONST MIO_CHAR *nonceCount,
										MIO_CONST MIO_CHAR *method,
										MIO_CONST MIO_CHAR *qop,
										MIO_CONST MIO_CHAR *uri,
										MIO_CONST MIO_CHAR *response );

MIO_UINT32 MIO_getIESizeByTypeInternal( mioeIEType type );

MIO_VOID MIO_setHttpConnModeInternal( MIO_VOID *mioCtx, MIO_BOOL bEnableLongConn );

MIO_BOOL MIO_decodeTimeInternal( MIO_TIME *time, MIO_CONST MIO_CHAR *srcStr );
MIO_BOOL MIO_encodeTimeInternal( MIO_TIME *time, MIO_CHAR *dstStr, MIO_INT32 avaLen );

MIO_UINT32 MIO_randomInternal( MIO_VOID );

MIO_VOID* MIO_mallocDebugInternal( MIO_UINT32 size, MIO_CONST MIO_CHAR *fileName, MIO_INT32 lineNumber );
MIO_VOID* MIO_reallocDebugInternal( MIO_VOID *memblock, MIO_UINT32 size, MIO_CONST MIO_CHAR *fileName, MIO_INT32 lineNumber );
MIO_VOID MIO_freeDebugInternal( MIO_VOID *memblock, MIO_CONST MIO_CHAR *fileName, MIO_INT32 lineNumber );
MIO_VOID* MIO_mallocInternal( MIO_UINT32 size );
MIO_VOID* MIO_reallocInternal( MIO_VOID *memblock, MIO_UINT32 size );
MIO_VOID MIO_freeInternal( MIO_VOID *memblock );

MIO_VOID MIO_enableMemDebugInternal();
MIO_VOID MIO_disableMemDebugInternal();

MIO_VOID* MIO_CreateCtxForClientInternal( MIO_VOID *sipUserData,
											MIO_NotifyCB sipNotifyCB,
											MIO_VOID *httpUserData,
											MIO_NotifyCB httpNotifyCB );

MIO_BOOL MIO_setSipPortInternal( MIO_VOID *mioCtx, MIO_UINT16 sipPort );
MIO_BOOL MIO_setHttpPortInternal( MIO_VOID *mioCtx, MIO_UINT16 httpPort );


MIO_UINT32 MIO_SendRegEx2Internal( MIO_VOID *mioCtx,
									MIO_CHAR *to,
									MIO_CHAR *from,
									MIO_CHAR *userName,
									MIO_CHAR *passWord,
									MIO_INT32 expires,
									MIO_VOID *regUserData,
									MIO_CHAR *ip,
									MIO_UINT16 port,
									MIO_CHAR *regCallId,
									miosMSG *msg );

MIO_UINT32 MIO_SendRegRespEx2Internal( MIO_VOID *mioCtx,
										MIO_UINT32 msgID,
										MIO_INT32 respCode,
										MIO_CHAR *passWord,
										MIO_CONST MIO_CHAR *respReasonPhrase,
										miosMSG *msg );

MIO_VOID MIO_enableStopRegWhenFailInternal( MIO_VOID *mioCtx );

MIO_VOID MIO_disableStopRegWhenFailInternal( MIO_VOID *mioCtx );

MIO_BOOL MIO_patchOutHttpMsgInternal( MIO_VOID *mioCtx, miosMSG *msg );

MIO_BOOL MIO_patchInHttpMsgInternal( MIO_VOID *mioCtx, miosMSG *msg );

#ifdef __cplusplus
}
#endif



#endif


