#ifndef _MEDIASIP_INTERFACE_H
#define _MEDIASIP_INTERFACE_H

#if defined(MEDIASIPDLL_EXPORTS)
#define MEDIASIP_API __declspec(dllexport)
#elif defined(MEDIASIPDLL_IMPORTS)
#define MEDIASIP_API __declspec(dllimport)
#else
#define MEDIASIP_API
#endif

#include "miointerface.h"

#define MEDIASIP_IP_MAXLEN 40
#define MEDIASIP_PUID_MAXLEN 64
#define MEDIASIP_USERID_MAXLEN 64

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * 错误码。用于回调通知和发送错误回应中
 */

typedef enum error_code
{
	MS_REQUEST_TIMEOUT = 1,		// 请求超时
	MS_REQUEST_NORIGHT,			// 请求没有权限
	MS_CALL_CHECK_FAIL,			// 呼叫心跳检查失败
	MS_REMOTE_SDP_NULL,			// 收到的200OK中没有携带SDP
	MS_CALL_LIMIT,				// 呼叫超过限制
	MS_UNKNOWN_ERROR,			// 未知错误
	MS_200_OK,					// 正确
	MS_ERROR_CODE_COUNT
}error_code_t;

/*
 * QUERYSTATE_REQ请求时的会话状态码，目前没有使用
 */
typedef enum media_state
{
	MS_NULL_STATE,
	MS_CONNECTING_STATE,
	MS_CONNECTED_STATE,
	MS_DISCONNECTED_STATE,
	MS_STATE_COUNT
}media_state_t;

#ifndef HAVE_STRUCT_SDP_MESSAGE

typedef void sdp_message_t;

#endif


/*
 * 路由的结构
 */
#define MS_MAX_ROUTE_IP_LEN			40
typedef struct ms_route_info	ms_route_info_t;
struct ms_route_info
{
	ms_route_info_t		*next;						// 指向下一个路由
	char				ip[MS_MAX_ROUTE_IP_LEN+1];	// IP地址
	unsigned short		port;						// 端口号
};

/*
 * 发起呼叫的信息结构
 */
typedef struct call_info call_info_t;
struct call_info{
	char			puid[MEDIASIP_PUID_MAXLEN+1];       // SIP To 头中的SIP地址的用户名部分
	char			nexthopip[MEDIASIP_IP_MAXLEN+1];	// SIP To 头中的SIP地址的IP地址部分
	int				nexthopport;						// SIP To 头中的SIP地址的端口部分
	char			usrid[MEDIASIP_USERID_MAXLEN+1];    // SIP From 头中的SIP地址的用户名部分
	sdp_message_t	*sdpinfo;							// SDP消息体，调用完毕以后，由应用层释放
	ms_route_info_t	*route_info;						// 需要添加的路由信息列表
														// 调用完毕以后，由应用层释放
	void			*user_data;							// 和呼叫相关的应用层数据
	char			usrip[MEDIASIP_IP_MAXLEN+1];		// SIP From 头中的SIP地址的IP地址部分
}; 


/*
 * 调用mediasip_indicate时所要做的动作类型
 */
typedef enum ms_indicate_type
{
	QUERYSTATE_REQ,			// 查询呼叫状态，目前没有实现
	INVITE_REQ,				// 发起呼叫
	S200_REQ,				// 发送正确应答
	BYE_REQ,				// 挂断已经建立的呼叫或者取消发出的呼叫
	ERROR_REQ,				// 发送错误应答
	ACK_REQ,				// 发送ACK
	INFO_REQ,				// 发送INFO
	INFO_ANSWER_REQ,		// 发送INFO应答
	INDICATE_TYPE_COUNT
}ms_indicate_type_t;

/*
 * 调用mediasip_indicate的动作结构
 */
typedef struct ms_indicate_info ms_indicate_info_t;
struct ms_indicate_info
{
	ms_indicate_type_t	type;		// 动作类型
	int					callid;		// 对应的会话ID
									// 当type为INVITE_REQ时，这个为输出参数，返回新建立会话的ID
									// 当type为其他类型时，这个参数为输入参数，标志之前建立的会话ID
	void				*msgbuf;	// 动作相关的参数
									// type为QUERYSTATE_REQ时，为指向media_state结构的指针，目前没有实现
									// type为INVITE_REQ时，为指向call_info_t结构的指针
									// type为S200_REQ时，为指向sdp_message_t结构的指针
									// type为BYE_REQ时，为空
									// type为ERROR_REQ时，为指向error_code的指针
									// type为ACK_REQ时，为指向sdp_message_t结构的指针
	miosMSG				*msg;		// 动作相关的 XML 消息体（发送invite,200ok,ack时有效）
									// 调用完毕以后，由应用层释放
};


/*
 * 通知回调的通知类型
 */
typedef enum ms_notify_type
{
	INVITE_RCV,				// 收到呼叫请求
	S200_RCV,				// 收到200OK
	ACK_RCV,				// 收到ACK
	BYE_RCV,				// 收到呼叫挂断请求
	ERROR_RCV,				// 错误通知
	INFO_RCV,				// 收到INFO
	INFO_ANSWER_RCV,		// 收到INFO应答
	NOTIFY_TYPE_COUNT
}ms_notify_type_t;

/*
 * 通知回调的通知结构，这个结构在通知处理以后需要调用mediasip_notify_info_free释放
 */
typedef struct ms_notify_info ms_notify_info_t;
struct ms_notify_info
{
	ms_notify_type_t	type;			// 通知类型
	int					callid;			// 会话ID
	void				*msgbuf;		// 和通知类型相关的附加数据
										// 当type为INVITE_RCV时，为指向sdp_message_t的结构指针
										// 当type为S200_RCV时，为指向sdp_message_t的结构指针
										// 当type为ACK_RCV时，为指向sdp_message_t的结构指针
										// 当type为BYE_RCV时，为空
										// 当type为ERROR_RCV和INFO_ANSWER_RCV时，为指向error_code_t的结构指针
															// 当type为S200_RCV时，
	miosMSG				*msg;								// XML消息体（收到invite,200ok,ack,info时有效）
	ms_route_info_t		*route_info;						// 路由列表信息
	char				dstuser[MEDIASIP_PUID_MAXLEN+1];	// SIP To 头中的SIP地址的用户名部分
	char				dstip[MEDIASIP_IP_MAXLEN+1];		// SIP To 头中的SIP地址的IP地址部分
	unsigned short		dstport;							// SIP To 头中的SIP地址的端口部分
	void				*user_data;							// 如果是主动发起的会话，就是建立会话时的应用层数据
	char				srcuser[MEDIASIP_PUID_MAXLEN+1];	// SIP From 头中的SIP地址的用户名部分
	char				srcip[MEDIASIP_IP_MAXLEN+1];		// SIP From 头中的SIP地址的IP地址部分
	unsigned short		srcport;							// SIP From 头中的SIP地址的端口部分
};

/*
 * 通知回调函数原型
 *
 * 参数定义：
 *  notifyinfo: 通知回调的数据结构指针。处理完毕以后需要调用mediasip_notify_info_free释放
 *
 * 返回值：
 *  小于零表示处理失败
 *  否则表示成功
 *
 */
typedef int (*mediasip_notify_cb_t)(ms_notify_info_t *notifyinfo);

/*
 * 利用 OSIP 事件管道，由应用层使用的异步通知回调函数原型
 *
 * 参数定义：
 *  evt: 不透明的用户通知数据
 *
 * 返回值：
 *  小于零表示处理失败
 *  否则表示成功
 *
 */
typedef int (*mediasip_ccm_evt_cb_t)(void *evt);



/*
 * mediasip模块的初始化结构
 */
typedef struct ms_config ms_config_t;
struct ms_config
{
	mediasip_notify_cb_t	ms_notify_cb;	/* callback func for notify */
	mediasip_ccm_evt_cb_t	ms_ccm_evt_cb;	/* callback func for VTDU */

	int		family;/*AF_INET, AF_INET6*/
	int						listen_port;	/* 0 : default 5060 */
	int						protocol;		/* 1 : IPPROTO_TCP;
											 * 2 : TLS;
											 * 0 : default IPPROTO_UDP */
};

/*mediasip basic API*/

/*
 * 初始化 mediasip 模块
 *
 * 参数定义：
 *  msconfig: 初始化结构
 *
 * 返回值：
 *  小于零表示失败，其中-12表示侦听端口号失败
 *  否则表示成功
 *
 */
MEDIASIP_API int mediasip_initial( ms_config_t *msconfig );

/*
 * 销毁 mediasip 模块
 *
 * 参数定义：
 *  无
 *
 * 返回值：
 *  无
 *
 */
MEDIASIP_API void mediasip_destroy( void );

/*
 * 释放通知结构
 *
 * 参数定义：
 *  notifyinfo: 通知结构指针
 *
 * 返回值：
 *  无
 *
 */
MEDIASIP_API void mediasip_notify_info_free( ms_notify_info_t *notifyinfo );

/*
 * 请求 mediasip 做动作，
 *
 * 参数定义：
 *  indicateinfo: 动作结构指针，其中有动作的类型。调用完毕以后结构中所用到的内存都由应用层负责释放
 *  param: 当动作类型为INVITE_REQ时，用来返回新生成的会话ID
 *
 * 返回值：
 *  小于零表示失败
 *  否则表示成功
 *
 */
MEDIASIP_API int mediasip_indicate( ms_indicate_info_t *indicateinfo, void *param );

/*
 * 应用层利用 OSIP 管道给自己发送不透明的异步通知。
 * 通知通过异步通知回调函数返回。
 *
 * 参数定义：
 *  evt: 不透明的异步通知事件
 *
 * 返回值：
 *  小于零表示失败
 *  否则表示成功
 *
 */
MEDIASIP_API int fcm_to_ccm_evt_add( void *evt );


/*
 * 目前没有实现
 */
MEDIASIP_API char *mediasip_get_call_caller( int callid );

/*
 * 目前没有实现
 */
MEDIASIP_API char *mediasip_get_call_callee( int callid );

/*
 * 判断该会话是否通过了NAT，这个判断未必准确
 *
 * 参数定义：
 *  callid: 会话ID
 *
 * 返回值：
 *  小于零表示失败
 *  等于零表示没有通过NAT
 *  大于零表示通过了NAT
 *
 */
MEDIASIP_API int mediasip_if_call_through_nat( int callid );

/*API for operating SDP*/

/*
 * SDP中的方向描述
 */
// 只发送
#define MEDIASIP_SDP_DIRECTION_SENDONLY		0
// 只接收
#define MEDIASIP_SDP_DIRECTION_RECVONLY		1
// 同时发送和接收
#define MEDIASIP_SDP_DIRECTION_SENDRECV		2
// 没有设置方向
#define MEDIASIP_SDP_DIRECTION_UNKNOWN		3
// 获取方向的时候发生错误
#define MEDIASIP_SDP_DIRECTION_ERROR		4

/*
 * 生成一个最基本的SDP结构。只包含一些最基本的SDP信息，没有任何媒体信息
 *
 * 参数定义：
 *  sdp: 返回新生成的sdp。
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_build_sdp_message( sdp_message_t **sdp );

/*
 * 释放sdp结构使用的内存
 *
 * 参数定义：
 *  sdp: 返回新生成的sdp。
 *
 * 返回值：
 *  无
 *
 */
MEDIASIP_API void mediasip_sdp_message_free( sdp_message_t *sdp );

/*
 * 复制sdp结构
 *
 * 参数定义：
 *  sdp: 需要被复制的sdp
 *  dest: 返回新生成的sdp。
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_clone( sdp_message_t *sdp, sdp_message_t **dest );

/*
 * 打印sdp结构
 *
 * 参数定义：
 *  sdp: 需要被复制的sdp
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_dump( sdp_message_t *sdp );

/*
 * 设置SDP中 o 字段的sessionid。mediasip_build_sdp_message生成的默认sessionid是 "123456"
 *
 * 参数定义：
 *  sdp: sdp结构
 *  sessionid: 新的sessionid
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_session_id( sdp_message_t *sdp, const char *sessionid );

/*
 * 设置SDP中 o 字段和 c 字段 的ip。
 * 如果有些媒体有自己的 c 字段，那么这些字段会被删除
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaip: 新的的IP地址
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_session_ip( sdp_message_t *sdp, const char *mediaip );

/*
 * 设置某一个媒体的 c 字段地址。如果媒体存在多个 c 字段地址，会将已有的字段都删除
 * 当 pos_media 大于或等于零时，表示要设置某一个媒体的地址
 * 当 pos_media 小于零，而mediaformat不为空，表示要设置所有这个类型媒体的地址
 * 当 pos_media 小于零，而且mediaformat也为空，就和mediasip_sdp_message_set_session_ip效果相同
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaformat: 媒体格式，如"audio"，"video"等等
 *  pos_media: 媒体的序号。是相对于mediaformat的媒体。
 *             如果mediaformat为空，那么就表示在所有媒体中的序号
 *  mediaip: 新的的IP地址
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_media_ip_ex( sdp_message_t *sdp, const char *mediaformat, int pos_media, const char *mediaip );

/*
 * 这个函数只是为了兼容以前的接口，不再推荐使用。
 * 效果和mediasip_sdp_message_set_session_ip相同
 *
 */
// deprecated interface, please use mediasip_sdp_message_set_session_ip
MEDIASIP_API int mediasip_sdp_message_set_media_ip( sdp_message_t *sdp, const char *mediaip );

/*
 * 给某一个媒体添加的 c 字段地址
 * 会在SDP增加一条类似如下的行（其中%之间为函数对应的参数值）
 *
 *  c=IN IP4 %mediaip%
 *
 * 当 pos_media 大于或等于零时，表示要给某一个媒体添加 c 字段地址
 * 当 pos_media 小于零，而mediaformat不为空，表示要给所有这个类型媒体添加 c 字段地址
 * 当 pos_media 小于零，而且mediaformat也为空，就和mediasip_sdp_message_set_session_ip效果相同
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaformat: 媒体格式，如"audio"，"video"等等
 *  pos_media: 媒体的序号。是相对于mediaformat的媒体。
 *             如果mediaformat为空，那么就表示在所有媒体中的序号
 *  mediaip: 新的的IP地址
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_media_ip( sdp_message_t *sdp, const char *mediaformat, int pos_media, const char *mediaip );

/*
 * 设置音频媒体的地址
 * 相当于调用mediasip_sdp_message_set_media_ip_ex时，mediaformat为"audio"，pos_media为 -1
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaip: 新的的IP地址
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_audio_ip( sdp_message_t *sdp, const char *mediaip );

/*
 * 设置视频媒体的地址
 * 相当于调用mediasip_sdp_message_set_media_ip_ex时，mediaformat为"video"，pos_media为 -1
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaip: 新的的IP地址
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_video_ip( sdp_message_t *sdp, const char *mediaip );

/*
 * 删除某个媒体的 a 字段
 * 当 pos_media 大于或等于零时，表示要在某一个媒体中删除对应的 a 字段
 * 当 pos_media 小于零，而mediaformat不为空，表示要在所有这个类型的媒体中删除对应的 a 字段
 * 当 pos_media 小于零，而且mediaformat也为空，就是要在全局列表中删除对应的 a 字段
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaformat: 媒体格式，如"audio"，"video"等等
 *  pos_media: 媒体的序号。是相对于mediaformat的媒体。
 *             如果mediaformat为空，那么就表示在所有媒体中的序号
 *  att_field: 要被删除的 a 字段属性名
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_attribute_del( sdp_message_t * sdp, const char *mediaformat, int pos_media, const char *att_field );

/*
 * 添加某个媒体的 a 字段
 * 会在SDP增加一条类似如下的行（其中%之间为函数对应的参数值）
 *
 *  a=%att_field%:%att_value%
 *
 * 当 pos_media 大于或等于零时，表示要在某一个媒体中添加对应的 a 字段
 * 当 pos_media 小于零，而mediaformat不为空，表示要在所有这个类型的媒体中添加对应的 a 字段
 * 当 pos_media 小于零，而且mediaformat也为空，就是要在全局列表中添加对应的 a 字段
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaformat: 媒体格式，如"audio"，"video"等等
 *  pos_media: 媒体的序号。是相对于mediaformat的媒体。
 *             如果mediaformat为空，那么就表示在所有媒体中的序号
 *  att_field: 要被添加的 a 字段属性名
 *  att_value: 要被添加的 a 字段属性值
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_attribute_add( sdp_message_t * sdp, const char *mediaformat, int pos_media, const char *att_field, const char *att_value );

/*
 * 设置某个媒体的 a 字段，如果已经存在相同的属性字段，会将他们先删除，然后再添加
 * 当 pos_media 大于或等于零时，表示要设置某一个媒体对应的 a 字段
 * 当 pos_media 小于零，而mediaformat不为空，表示要设置所有这个类型媒体的 a 字段
 * 当 pos_media 小于零，而且mediaformat也为空，就是要设置全局列表中对应的 a 字段
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaformat: 媒体格式，如"audio"，"video"等等
 *  pos_media: 媒体的序号。是相对于mediaformat的媒体。
 *             如果mediaformat为空，那么就表示在所有媒体中的序号
 *  att_field: 要被设置的 a 字段属性名
 *  att_value: 要被设置的 a 字段属性值
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_attribute_set( sdp_message_t * sdp, const char *mediaformat, int pos_media, const char *att_field, const char *att_value );

/*
 * 设置某个媒体的数据发送方向
 * 调用这个函数的时候会先将已有的指示方向字段删除，然后添加新的字段
 *
 * 当direction为MEDIASIP_SDP_DIRECTION_SENDONLY时，添加如下字段
 *
 *  a=sendonly
 *
 * 当direction为MEDIASIP_SDP_DIRECTION_RECVONLY时，添加如下字段
 *
 *  a=recvonly
 *
 * 当direction为MEDIASIP_SDP_DIRECTION_SENDRECV时，添加如下字段
 *
 *  a=sendrecv
 *
 * 当direction为MEDIASIP_SDP_DIRECTION_UNKNOWN时，指示将已有的方向字段删除，不再添加
 *
 *
 * 当 pos_media 大于或等于零时，表示要设置某一个媒体的数据发送方向
 * 当 pos_media 小于零，而mediaformat不为空，表示要设置所有这个类型媒体的数据发送方向
 * 当 pos_media 小于零，而且mediaformat也为空，就是要设置全局的数据发送方向
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaformat: 媒体格式，如"audio"，"video"等等
 *  pos_media: 媒体的序号。是相对于mediaformat的媒体。
 *             如果mediaformat为空，那么就表示在所有媒体中的序号
 *  direction: 媒体数据的发送方向
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_media_direction( sdp_message_t *sdp, const char *mediaformat, int pos_media, int direction );

/*
 * 设置音频数据的发送方向
 * 相当于调用mediasip_sdp_message_set_media_direction时，meidaformat为"audio"，pos_media为-1
 *
 * 参数定义：
 *  sdp: sdp结构
 *  direction: 媒体数据的发送方向
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_audio_direction( sdp_message_t *sdp, int direction );

/*
 * 设置音频数据的发送方向
 * 相当于调用mediasip_sdp_message_set_media_direction时，meidaformat为"video"，pos_media为-1
 *
 * 参数定义：
 *  sdp: sdp结构
 *  direction: 媒体数据的发送方向
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_video_direction( sdp_message_t *sdp, int direction );

/*
 * 设置某个媒体的数据的端口号
 * 调用这个函数只是更改如下字段中的端口号值（%port%部分）
 *   m=%mediaformat% %port% %protocol% %old_payload_type_list%
 *
 * 当 pos_media 大于或等于零时，表示要设置某一个媒体的端口号
 * 当 pos_media 小于零，而mediaformat不为空，表示要设置所有这个类型媒体的端口号
 * 当 pos_media 小于零，而且mediaformat也为空，会返回失败
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaformat: 媒体格式，如"audio"，"video"等等
 *  pos_media: 媒体的序号。是相对于mediaformat的媒体。
 *             如果mediaformat为空，那么就表示在所有媒体中的序号
 *  port: 媒体数据的端口号
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_media_port( sdp_message_t *sdp, const char *mediaformat, int pos_media, int port );

/*
 * 设置音频的数据端口号
 * 相当于调用mediasip_sdp_message_set_media_port时，meidaformat为"audio"，pos_media为-1
 *
 * 参数定义：
 *  sdp: sdp结构
 *  port: 媒体数据的端口号
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_audio_port( sdp_message_t *sdp, int port );

/*
 * 设置视频的数据端口号
 * 相当于调用mediasip_sdp_message_set_media_port时，meidaformat为"video"，pos_media为-1
 *
 * 参数定义：
 *  sdp: sdp结构
 *  port: 媒体数据的端口号
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_video_port( sdp_message_t *sdp, int port );

/*
 * 设置某个媒体的数据的承载协议
 * 调用这个函数只是更改如下字段中的协议字段（%protocol%部分）
 *   m=%mediaformat% %port% %protocol% %old_payload_type_list%
 *
 * 当 pos_media 大于或等于零时，表示要设置某一个媒体的协议字段
 * 当 pos_media 小于零，而mediaformat不为空，表示要设置所有这个类型媒体的协议字段
 * 当 pos_media 小于零，而且mediaformat也为空，会返回失败
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaformat: 媒体格式，如"audio"，"video"等等
 *  pos_media: 媒体的序号。是相对于mediaformat的媒体。
 *             如果mediaformat为空，那么就表示在所有媒体中的序号
 *  protocol: 要设置的协议
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_media_protocol( sdp_message_t *sdp, const char *mediaformat, int pos_media, const char *protocol );

/*
 * 设置音频的承载协议
 * 相当于调用mediasip_sdp_message_set_media_protocol时，meidaformat为"audio"，pos_media为-1
 *
 * 参数定义：
 *  sdp: sdp结构
 *  protocol: 要设置的协议
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_audio_protocol( sdp_message_t *sdp, const char *protocol );

/*
 * 设置视频的承载协议
 * 相当于调用mediasip_sdp_message_set_media_protocol时，meidaformat为"video"，pos_media为-1
 *
 * 参数定义：
 *  sdp: sdp结构
 *  protocol: 要设置的协议
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_set_video_protocol( sdp_message_t *sdp, const char *protocol );

/*
 * 往某个媒体中添加的数据包类型
 * 调用这个函数要在m字段中增加一个%payload_type%，并且增加和这个payload_type相关的属性表
 *
 * 将
 *   m=%mediaformat% %port% %protocol% %old_payload_type_list%
 * 变成
 *   m=%mediaformat% %port% %protocol% %old_payload_type_list% %payload_type%
 * 并且依据attrs中的值，添加如下的字段
 *   a=%attrs[0]%:%attrs[1]%
 *   a=%attrs[2]%:%attrs[3]%
 *   ...
 *
 * 当 pos_media 大于或等于零时，表示要在某一个媒体中添加数据包类型
 * 当 pos_media 小于零，而mediaformat不为空，表示要在所有这个类型的媒体中添加数据包类型
 * 当 pos_media 小于零，而且mediaformat也为空，会返回失败
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaformat: 媒体格式，如"audio"，"video"等等
 *  pos_media: 媒体的序号。是相对于mediaformat的媒体。
 *             如果mediaformat为空，那么就表示在所有媒体中的序号
 *  payload_type: 要添加的数据包类型
 *  attrs: 和这个payload_type相关的附加属性
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_media_payload( sdp_message_t *sdp, const char *mediaformat, int pos_media, const char *payload_type, const char **attrs );

/*
 * 添加一个音频数据包类型
 *
 * 将
 *   m=audio %port% %protocol% %old_payload_type_list%
 * 变成
 *   m=audio %port% %protocol% %old_payload_type_list% %payload_type%
 * 并添加如下的字段
 *   a=rtpmap:%a_rtpmap%
 *
 * 参数定义：
 *  sdp: sdp结构
 *  payload_type: 要添加的数据包类型
 *  a_rtpmap: rtpmap属性
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_audio_payload( sdp_message_t *sdp, const char *payload_type, const char *a_rtpmap );

/*
 * 添加一个视频数据包类型
 *
 * 将
 *   m=video %port% %protocol% %old_payload_type_list%
 * 变成
 *   m=video %port% %protocol% %old_payload_type_list% %payload_type%
 * 并添加如下的字段
 *   a=rtpmap:%a_rtpmap%
 *
 * 参数定义：
 *  sdp: sdp结构
 *  payload_type: 要添加的数据包类型
 *  a_rtpmap: rtpmap属性
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_video_payload( sdp_message_t *sdp, const char *payload_type, const char *a_rtpmap, const char *a_fmtp );

/*
 * 添加一个媒体
 * 将添加如下字段
 *
 *   m=%mediaformat% %port% %protocol%
 *   a=%attrs[0]%:%attrs[1]%
 *   a=%attrs[2]%:%attrs[3]%
 *   ...
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaformat: 媒体格式，如"audio"，"video"等等
 *  port: 媒体数据使用的端口号
 *  protocol: 媒体数据使用的协议类型
 *  attrs: 附加的媒体相关属性
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_media( sdp_message_t *sdp, const char *mediaformat, int port, const char *protocol, const char **attrs );

/*
 * 添加一个音频
 * 将添加如下字段
 *
 *   m=audio %port% %protocol% %payload_type%
 *   a=rtpmap:%a_rtpmap%
 *   a=( sendonly 或 recvonly 或 sendrecv )
 *
 * 参数定义：
 *  sdp: sdp结构
 *  port: 使用的端口号
 *  payload_type: 数据包格式
 *  a_rtpmap: rtpmap 属性
 *  protocol: 使用的协议类型
 *  direction: 传送的方向
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_audio_media_ex2( sdp_message_t *sdp, int port, const char *payload_type, const char *a_rtpmap, const char *protocol, int direction );

/*
 * 添加一个音频
 * 将添加如下字段
 *
 *   m=audio %port% %protocol% %payload_type%
 *   a=rtpmap:%a_rtpmap%
 *
 * 参数定义：
 *  sdp: sdp结构
 *  port: 使用的端口号
 *  payload_type: 数据包格式
 *  a_rtpmap: rtpmap 属性
 *  protocol: 使用的协议类型
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_audio_media_ex( sdp_message_t *sdp, int port, const char *payload_type, const char *a_rtpmap, const char *protocol );

/*
 * 添加一个音频
 * 将添加如下字段
 *
 *   m=audio %port% RTP/AVP %payload_type%
 *   a=rtpmap:%a_rtpmap%
 *
 * 参数定义：
 *  sdp: sdp结构
 *  port: 使用的端口号
 *  payload_type: 数据包格式
 *  a_rtpmap: rtpmap 属性
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_audio_media( sdp_message_t *sdp, int port, const char *payload_type, const char *a_rtpmap );

/*
 * 添加一个视频
 * 将添加如下字段
 *
 *   m=video %port% %protocol% %payload_type%
 *   a=rtpmap:%a_rtpmap%
 *   a=fmtp:%a_fmtp%
 *   a=framerate:%framerate%
 *   a=( sendonly 或 recvonly 或 sendrecv )
 *
 * 参数定义：
 *  sdp: sdp结构
 *  port: 使用的端口号
 *  payload_type: 数据包格式
 *  a_rtpmap: rtpmap 属性
 *  a_fmtp: fmtp 属性
 *  protocol: 使用的协议类型
 *  framerate: 帧率
 *  direction: 传送的方向
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_video_media_ex2( sdp_message_t *sdp, int port, const char *payload_type, const char *a_rtpmap, const char *a_fmtp, const char *protocol, const char *framerate, int direction );

/*
 * 添加一个视频
 * 将添加如下字段
 *
 *   m=video %port% %protocol% %payload_type%
 *   a=rtpmap:%a_rtpmap%
 *   a=fmtp:%a_fmtp%
 *   a=framerate:%framerate%
 *   a=( sendonly 或 recvonly 或 sendrecv )
 *
 * 参数定义：
 *  sdp: sdp结构
 *  port: 使用的端口号
 *  payload_type: 数据包格式
 *  a_rtpmap: rtpmap 属性
 *  a_fmtp: fmtp 属性
 *  protocol: 使用的协议类型
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_video_media_ex( sdp_message_t *sdp, int port, const char *payload_type, const char *a_rtpmap, const char *a_fmtp, const char *protocol );

/*
 * 添加一个视频
 * 将添加如下字段
 *
 *   m=video %port% %protocol% %payload_type%
 *   a=rtpmap:%a_rtpmap%
 *   a=fmtp:%a_fmtp%
 *   a=framerate:%framerate%
 *   a=( sendonly 或 recvonly 或 sendrecv )
 *
 * 参数定义：
 *  sdp: sdp结构
 *  port: 使用的端口号
 *  payload_type: 数据包格式
 *  a_rtpmap: rtpmap 属性
 *  a_fmtp: fmtp 属性
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_add_video_media( sdp_message_t *sdp, int port, const char *payload_type, const char *a_rtpmap, const char *a_fmtp );




/*
 * 获得 SDP 中的 sessionid，对应于 O 字段中的 %sessionid%
 *
 *   o=MediaSIP %sessionid% 0 IN IP4 10.18.34.75
 *
 * 参数定义：
 *  sdp: sdp结构
 *
 * 返回值：
 *  返回的sessionid
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_session_id( sdp_message_t *sdp );

/*
 * 获得 SDP 中的 ip，对应于全局的c字段中的 %ip%
 *
 *   c=IN IP4 %ip%
 *
 * 参数定义：
 *  sdp: sdp结构
 *
 * 返回值：
 *  返回的 ip
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_session_ip( sdp_message_t *sdp );

/*
 * 获得某个媒体相关的 c 字段中的 %ip%
 * 如果对应的 c 字段没有找到，那么会返回全局的 c 字段中的 %ip%
 *
 *   c=IN IP4 %ip%
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaformat: 媒体格式，如"audio"，"video"等等
 *  pos_media: 媒体的序号。是相对于mediaformat的媒体。
 *             如果mediaformat为空，那么就表示在所有媒体中的序号
 *  pos_conn: c 字段的序号
 *
 * 返回值：
 *  返回的 ip
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_media_ip_ex( sdp_message_t *sdp, const char *mediaformat, int pos_media, int pos_conn );


/*
 * 等同于 mediasip_sdp_message_get_session_ip，不推荐使用这个函数
 * 获得 SDP 中的 ip，对应于全局的c字段中的 %ip%
 *
 *   c=IN IP4 %ip%
 *
 * 参数定义：
 *  sdp: sdp结构
 *
 * 返回值：
 *  返回的 ip
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_media_ip( sdp_message_t *sdp );

/*
 * 获得音频媒体的 ip
 * 相当于调用 mediasip_sdp_message_get_media_ip_ex 时 mediaformat为"audio"，pos_media和pos_conn都为0
 *
 * 参数定义：
 *  sdp: sdp结构
 *
 * 返回值：
 *  返回的 ip
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_audio_ip( sdp_message_t *sdp );

/*
 * 获得视频媒体的 ip
 * 相当于调用 mediasip_sdp_message_get_media_ip_ex 时 mediaformat为"video"，pos_media和pos_conn都为0
 *
 * 参数定义：
 *  sdp: sdp结构
 *
 * 返回值：
 *  返回的 ip
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_video_ip( sdp_message_t *sdp );

/*
 * 获得某个媒体的端口号，对应如下字段的 %port% 部分
 *
 *   m=%mediaformat% %port% %protocol% %payload_type_list%
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaformat: 媒体格式，如"audio"，"video"等等
 *  pos_media: 媒体的序号。是相对于mediaformat的媒体。
 *             如果mediaformat为空，那么就表示在所有媒体中的序号
 *
 * 返回值：
 *  返回的端口号
 *  小于零表示获取失败
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_media_port( sdp_message_t *sdp, const char *mediaformat, int pos_media );

/*
 * 获得音频端口号
 * 相当于调用 mediasip_sdp_message_get_media_port 时，mediaformat为"audio"，pos_media为0
 *
 * 参数定义：
 *  sdp: sdp结构
 *
 * 返回值：
 *  返回的端口号
 *  小于零表示获取失败
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_audio_port( sdp_message_t *sdp );

/*
 * 获得视频端口号
 * 相当于调用 mediasip_sdp_message_get_media_port 时，mediaformat为"video"，pos_media为0
 *
 * 参数定义：
 *  sdp: sdp结构
 *
 * 返回值：
 *  返回的端口号
 *  小于零表示获取失败
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_video_port( sdp_message_t *sdp );

/*
 * 获得某个媒体的协议类型，对应如下字段的 %protocol% 部分
 *
 *   m=%mediaformat% %port% %protocol% %payload_type_list%
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaformat: 媒体格式，如"audio"，"video"等等
 *  pos_media: 媒体的序号。是相对于mediaformat的媒体。
 *             如果mediaformat为空，那么就表示在所有媒体中的序号
 *
 * 返回值：
 *  返回的协议类型
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_media_protocol( sdp_message_t *sdp, const char *mediaformat, int pos_media );

/*
 * 获得音频协议类型
 * 相当于调用 mediasip_sdp_message_get_media_protocol 时，mediaformat为"audio"，pos_media为0
 *
 * 参数定义：
 *  sdp: sdp结构
 *
 * 返回值：
 *  返回的协议类型
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_audio_protocol( sdp_message_t *sdp );

/*
 * 获得视频协议类型
 * 相当于调用 mediasip_sdp_message_get_media_protocol 时，mediaformat为"video"，pos_media为0
 *
 * 参数定义：
 *  sdp: sdp结构
 *
 * 返回值：
 *  返回的协议类型
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_video_protocol( sdp_message_t *sdp );

/*
 * 获得某个媒体数据包相关的属性值
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaformat: 媒体类型
 *  pos_media: 媒体的序号。是相对于mediaformat的媒体。
 *             如果mediaformat为空，那么就表示在所有媒体中的序号
 *  payload_index: 数据包类型序号，是相对于mediaformat和pos_media限定的媒体。
 *                 如果pos_media大于或等于0，那么就是相对这个媒体的数据包类型序号
 *                 如果pos_media小于0，并且mediaformat不为空，那么就是相对这一类媒体的数据包类型序号
 *                 如果pos_media小于0，并且mediaformat也为空，那么就表示在所有媒体中的数据包类型序号
 *  payload_type: 返回的数据包类型
 *  att_field: 要获得的数据包相关属性，如 rtpmap，fmtp等等
 *
 * 返回值：
 *  返回的属性值
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_payload_attribute_ex( sdp_message_t *sdp, const char *mediaformat, int pos_media, int payload_index, const char **payload_type, const char *att_field );

/*
 * 获得某个媒体数据包相关的属性值
 * 这个函数相当于调用mediasip_sdp_message_get_payload_attribute_ex时，pos_media为-1
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaformat: 媒体类型
 *  payload_index: 数据包类型序号，是相对于mediaformat限定的媒体。
 *                 如果mediaformat不为空，那么就是相对这一类媒体的数据包类型序号
 *                 如果mediaformat为空，那么就表示在所有媒体中的数据包类型序号
 *  payload_type: 返回的数据包类型
 *  att_field: 要获得的数据包相关属性，如 rtpmap，fmtp等等
 *
 * 返回值：
 *  返回的属性值
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_get_payload_attribute( sdp_message_t *sdp, const char *mediaformat, int payload_index, const char **payload_type, const char *att_field );

/*
 * 获得音频解码参数
 *
 * 参数定义：
 *  sdp: sdp结构
 *  pos_audio: 音频媒体的序号，如果大于或等于零，那么表示payload_index是在这个媒体中的序号
 *  payload_index: 音频数据包类型序号
 *  payload_type: 返回的数据包类型
 *  a_rtpmap: 返回的rtpmap属性
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_audio_codec_ex( sdp_message_t *sdp, int pos_audio, int payload_index, const char **payload_type, const char **a_rtpmap );

/*
 * 获得音频解码参数
 *
 * 参数定义：
 *  sdp: sdp结构
 *  payload_index: 音频数据包类型序号
 *  payload_type: 返回的数据包类型
 *  a_rtpmap: 返回的rtpmap属性
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_audio_codec( sdp_message_t *sdp, int payload_index, const char **payload_type, const char **a_rtpmap );

/*
 * 获得视频解码参数
 *
 * 参数定义：
 *  sdp: sdp结构
 *  pos_video: 视频媒体的序号，如果大于或等于零，那么表示payload_index是在这个媒体中的序号
 *  payload_index: 视频数据包类型序号
 *  payload_type: 返回的数据包类型
 *  a_rtpmap: 返回的 rtpmap 属性
 *  a_fmtp: 返回的 fmtp 属性
 *  a_framerate: 返回的帧率
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_video_codec_ex2( sdp_message_t *sdp, int pos_video, int payload_index, const char **payload_type, const char **a_rtpmap, const char **a_fmtp, const char **a_framerate );

/*
 * 获得视频解码参数
 *
 * 参数定义：
 *  sdp: sdp结构
 *  payload_index: 视频数据包类型序号
 *  payload_type: 返回的数据包类型
 *  a_rtpmap: 返回的 rtpmap 属性
 *  a_fmtp: 返回的 fmtp 属性
 *  a_framerate: 返回的帧率
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_video_codec_ex( sdp_message_t *sdp, int payload_index, const char **payload_type, const char **a_rtpmap, const char **a_fmtp, const char **a_framerate );

/*
 * 获得视频解码参数
 *
 * 参数定义：
 *  sdp: sdp结构
 *  payload_index: 视频数据包类型序号
 *  payload_type: 返回的数据包类型
 *  a_rtpmap: 返回的 rtpmap 属性
 *  a_fmtp: 返回的 fmtp 属性
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_video_codec( sdp_message_t *sdp, int payload_index, const char **payload_type, const char **a_rtpmap, const char **a_fmtp );

/*
 * 获得某个媒体属性值
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaformat: 媒体类型
 *  pos_media: 数体序号，是相对于mediaformat的媒体。
 *             如果mediaformat为空，那么就表示在所有媒体中的序号
 *  att_field: 要获得的数据包相关属性，如 rtpmap，fmtp等等
 *  pos: 属性的序号，这是针对可以携带的多个相同属性名的属性
 *
 * 返回值：
 *  返回的属性值
 *
 */
MEDIASIP_API const char* mediasip_sdp_message_attribute_get_value( sdp_message_t *sdp, const char *mediaformat, int pos_media, const char *att_field, int pos );

/*
 * 获得全局的媒体传送方向
 *
 * 参数定义：
 *  sdp: sdp结构
 *
 * 返回值：
 *  返回的方向值
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_session_direction( sdp_message_t *sdp );

/*
 * 获得某个媒体的传送方向
 *
 * 参数定义：
 *  sdp: sdp结构
 *  mediaformat: 媒体类型
 *  pos_media: 数体序号，是相对于mediaformat的媒体。
 *             如果mediaformat为空，那么就表示在所有媒体中的序号
 *
 * 返回值：
 *  返回的方向值
 *  MEDIASIP_SDP_DIRECTION_SENDONLY表示只发送
 *  MEDIASIP_SDP_DIRECTION_RECVONLY表示只接收
 *  MEDIASIP_SDP_DIRECTION_SENDRECV表示同时发送和接收
 *  MEDIASIP_SDP_DIRECTION_UNKNOWN表示没有设置方向
 *  MEDIASIP_SDP_DIRECTION_ERROR表示获取方向的时候发生错误，通常是因为指定的媒体不存在
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_media_direction( sdp_message_t *sdp, const char *mediaformat, int pos_media );

/*
 * 获得音频的传送方向
 * 相当于调用 mediasip_sdp_message_get_media_direction 时，mediaformat为"audio"，pos_media为0
 *
 * 参数定义：
 *  sdp: sdp结构
 *
 * 返回值：
 *  返回的方向值
 *  MEDIASIP_SDP_DIRECTION_SENDONLY表示只发送
 *  MEDIASIP_SDP_DIRECTION_RECVONLY表示只接收
 *  MEDIASIP_SDP_DIRECTION_SENDRECV表示同时发送和接收
 *  MEDIASIP_SDP_DIRECTION_UNKNOWN表示没有设置方向
 *  MEDIASIP_SDP_DIRECTION_ERROR表示获取方向的时候发生错误，通常是因为指定的媒体不存在
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_audio_direction( sdp_message_t *sdp );

/*
 * 获得视频的传送方向
 * 相当于调用 mediasip_sdp_message_get_media_direction 时，mediaformat为"video"，pos_media为0
 *
 * 参数定义：
 *  sdp: sdp结构
 *
 * 返回值：
 *  返回的方向值
 *  MEDIASIP_SDP_DIRECTION_SENDONLY表示只发送
 *  MEDIASIP_SDP_DIRECTION_RECVONLY表示只接收
 *  MEDIASIP_SDP_DIRECTION_SENDRECV表示同时发送和接收
 *  MEDIASIP_SDP_DIRECTION_UNKNOWN表示没有设置方向
 *  MEDIASIP_SDP_DIRECTION_ERROR表示获取方向的时候发生错误，通常是因为指定的媒体不存在
 *
 */
MEDIASIP_API int mediasip_sdp_message_get_video_direction( sdp_message_t *sdp );


/*
 * 将SDP结构转换成原始文本
 * 
 *
 * 参数定义：
 *  sdp: sdp结构
 *  buf: 输出sdp文本的缓冲区，提供的缓冲区的大小必须大于或等于sdp的文本长度加一
 *  buf_len: 缓冲区的长度
 *
 * 返回值：
 *  小于零表示缓冲区长度不够，取其相反数为sdp文本的长度，将这个长度加一就是需要的最少缓冲区长度
 *  大于零表示成功，返回sdp文本的长度
 *  等于零表示sdp文本的长度为0，或许意味着某种失败
 *
 */
MEDIASIP_API int mediasip_sdp_message_to_str( sdp_message_t *sdp, char *buf, int buf_len );

/*
 * 解析SDP文本
 *
 * 参数定义：
 *  sdp_buf: 要被解析的 sdp 文本
 *
 * 返回值：
 *  解析得到的sdp结构
 *
 */
MEDIASIP_API sdp_message_t* mediasip_sdp_message_parse( const char *sdp_buf );


/*
 * 设置帧率。因为接口不明确，为兼容之前版本而保留的，不推荐使用
 * 函数调用后，会给所有的视频媒体加上framerate属性
 * 
 *
 * 参数定义：
 *  sdp: sdp结构
 *  framerate: 新的帧率
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
// deprecated interface
MEDIASIP_API int mediasip_sdp_message_set_a_framerate( sdp_message_t *sdp, const char *framerate );

/*
 * 获得帧率。因为接口不明确，为兼容之前版本而保留的，不推荐使用
 * 函数调用后，返回的是第一个视频媒体的framerate属性
 *
 * 参数定义：
 *  sdp: sdp结构
 *
 * 返回值：
 *  返回的framerate属性值
 *
 */
// deprecated interface
MEDIASIP_API const char* mediasip_sdp_message_get_a_framerate( sdp_message_t *sdp );


/*API for setting mediasip profile*/

/*
 * 设置可接收的最大媒体呼叫数，默认为500
 *
 * 参数定义：
 *  num: 可接收的最大媒体呼叫数
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_set_max_incoming_calls(int num);

/*
 * 设置可发送的最大媒体呼叫数，默认为500
 *
 * 参数定义：
 *  num: 可接收的最大媒体呼叫数
 *
 * 返回值：
 *  小于零表示失败
 *  否则为成功
 *
 */
MEDIASIP_API int mediasip_set_max_outgoing_calls(int num);

/*
 * 设置NAT端口的刷新时间。
 * 当发现呼叫穿越了NAT，会在这个时间间隔内发送数据包刷新NAT。
 * 默认没有使能。
 *
 * 参数定义：
 *  interval: NAT的刷新间隔，以秒为单位，小于30就认为是30
 *
 * 返回值：
 *  无
 *
 */
MEDIASIP_API void mediasip_set_nat_port_refresh_interval(int interval); /*interval: s */

/*
 * 设置呼叫心跳包发送时间。
 * 当发送的3次心跳包都没有回应时，就表示会话已经断开，会释放并通知应用层。
 * 默认没有使能。
 *
 * 参数定义：
 *  interval: 心跳的刷新时间间隔
 *
 * 返回值：
 *  无
 *
 */
MEDIASIP_API void mediasip_set_call_keep_alive_interval(int interval);   /*interval: s */

/*API for pinrting mediasip info*/

/*
 * 设置调试跟踪级别
 *
 * 参数定义：
 *  level: 调试跟踪级别
 *
 * 返回值：
 *  无
 *
 */
MEDIASIP_API void mediasip_set_trace_level(int level);

/*
 * 在屏幕上打印内存信息，目前没有用
 *
 * 参数定义：
 *  无
 *
 * 返回值：
 *  无
 *
 */
MEDIASIP_API void mediasip_print_mem_info();

/*
 * 在屏幕上打印内存详细信息，目前没有用
 *
 */
MEDIASIP_API void mediasip_print_mem_detail_info(int n,int start, int num);

/*
 * 在屏幕上打印mediasip协议栈所使用的一些资源情况
 * 因为没有维护，目前我也不清楚打印了一些什么。:)
 *
 * 参数定义：
 *  level: 打印级别
 *
 * 返回值：
 *  无
 *
 */
MEDIASIP_API void mediasip_resource_print(int level);

#ifdef MEDIASIP_DEBUG

MEDIASIP_API void mediasip_event_static_print();

MEDIASIP_API void mediasip_event_static_clean();

#endif

/*api for route info */

/*
 * 生成一个route节点
 *
 * 参数定义：
 *  无
 *
 * 返回值：
 *  新生成的route节点
 *
 */
MEDIASIP_API ms_route_info_t* mediasip_new_route_info( void );

/*
 * 释放一个route节点
 *
 * 参数定义：
 *  route_info: 需要被释放的route节点
 *
 * 返回值：
 *  无
 *
 */
MEDIASIP_API void mediasip_free_route_info( ms_route_info_t *route_info );

/*
 * 释放route节点列表
 *
 * 参数定义：
 *  route_info_list: 需要被释放的route节点列表
 *
 * 返回值：
 *  无
 *
 */
MEDIASIP_API void mediasip_free_route_info_list( ms_route_info_t *route_info_list );

/*
 * 复制route节点
 *
 * 参数定义：
 *  src: 需要被复制的route节点列表
 *
 * 返回值：
 *  新生成的route节点列表
 *
 */
MEDIASIP_API ms_route_info_t* mediasip_clone_route_info( ms_route_info_t *src );

/*
 * 复制route节点列表
 *
 * 参数定义：
 *  src: 需要被复制的route节点列表
 *
 * 返回值：
 *  新生成的route节点列表
 *
 */
MEDIASIP_API ms_route_info_t* mediasip_clone_route_info_list( ms_route_info_t *src );

/* for disable auto ack */
/*
 * 取消mediasip自动回应 ACK 的功能，主要用于需要在 ACK 中携带SDP的会话
 *
 * 参数定义：
 *  无
 *
 * 返回值：
 *  无
 *
 */
MEDIASIP_API void mediasip_disable_auto_ack( void );

#ifdef __cplusplus
}
#endif

#endif


