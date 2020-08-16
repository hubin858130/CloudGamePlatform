#ifndef NANOHTTP_CLIENTSERVER_H
#define NANOHTTP_CLIENTSERVER_H

#include "nanohttp-common.h"

#define HTTPCD_REQUEST_MAX_PATH_SIZE		REQUEST_MAX_PATH_SIZE
#define HTTPCD_RESPONSE_MAX_DESC_SIZE		RESPONSE_MAX_DESC_SIZE
#define HTTPCD_MAX_IP_LEN					39
#define HTTPCD_DEFAULT_RESP_WAIT_TIMEOUT	32

typedef struct _httpcd_request		httpcd_request_t;
typedef struct _httpcd_response		httpcd_response_t;

struct _httpcd_request{
	httpcd_request_t	*next;
	hreq_method_t		method;
	http_version_t		version;
	char				path[HTTPCD_REQUEST_MAX_PATH_SIZE+1];

	hpair_t				*query;
	hpair_t				*query_tail;
	hpair_t				*header;
	hpair_t				*header_tail;

	hurl_t				url;
	char				*body;
	int					len;

	void				*user_data;

	// internal used
	httpcd_response_t	*resp;
	unsigned int		msg_id;
	char				dst_ip[HTTPCD_MAX_IP_LEN+1];
	unsigned short		port;
	void				*conn;
	int					need_resend;		// 用来标记连接中断时，这个请求是否要重新发送。
	unsigned int		birth_time;
};

struct _httpcd_response{
	http_version_t		version;
	int					errcode;
	char				desc[RESPONSE_MAX_DESC_SIZE+1];

	hpair_t				*header;
	hpair_t				*header_tail;

	char				*body;
	int					len;

	// internal used
	unsigned int		msg_id;
	httpcd_request_t	*req;
	int					b_auto_gen;
};


#ifdef __cplusplus
extern "C"
{
#endif



typedef enum _httpcd_notify_code{
	HTTPCD_NC_RECV_REQ = 0,
	HTTPCD_NC_RECV_RESP,
	HTTPCD_NC_SND_REQ_FAIL,
	HTTPCD_NC_SND_RESP_FAIL,
	HTTPCD_NC_SND_AUTO_RESP,
	HTTPCD_NC_UNKNOWN
}httpcd_notify_code_t;

#define HTTPCD_INVALID_MSG_ID			0

// when notify_code is HTTPCD_NC_RECV_REQ, the notify_param is the pointer of the following struct

typedef struct _httpcd_recv_req_notify_param{
	httpcd_request_t	*req;
	char				*recv_ip;
	unsigned short		recv_port;
	unsigned int		msg_id;
}httpcd_recv_req_notify_param_t;

// when notify_code is HTTPCD_NC_RECV_RESP, the notify_param is the pointer of the following struct

typedef struct _httpcd_recv_resp_notify_param{
	httpcd_response_t	*resp;
	unsigned int		msg_id;
}httpcd_recv_resp_notify_param_t;

// when notify_code is HTTPCD_NC_SND_REQ_FAIL, the notify_param is the pointer of the following struct
typedef struct _httpcd_snd_req_fail_notify_param{
	httpcd_request_t	*req;
	unsigned int		msg_id;
}httpcd_snd_req_fail_notify_param_t;

// when notify_code is HTTPCD_NC_SND_REQ_FAIL, the notify_param is the pointer of the following struct
typedef struct _httpcd_snd_resp_fail_notify_param{
	httpcd_response_t	*resp;
	unsigned int		msg_id;
}httpcd_snd_resp_fail_notify_param_t;

// when notify_code is HTTPCD_NC_SND_AUTO_RESP, the notify_param is the pointer of the following struct
typedef struct _httpcd_snd_auto_resp_notify_param{
	httpcd_response_t	*resp;
	unsigned int		msg_id;
}httpcd_snd_auto_resp_notify_param_t;

typedef int (*httpcd_notify_cb_t)( void *user_data, httpcd_notify_code_t notify_code, void *notify_param );
typedef unsigned int (*httpcd_gen_msgid_cb_t)( void *user_data );


int httpcd_init( httpcd_notify_cb_t notify_cb, void *user_data, unsigned short port, httpcd_gen_msgid_cb_t gen_msgid_cb );
void httpcd_destroy( void );

httpcd_request_t* httpcd_build_request( hreq_method_t method, const char *url, const char *content_type, const char *body, int len, void *user_data );
int httpcd_set_request_header( httpcd_request_t* req, const char *name, const char *value );
int httpcd_send_request( httpcd_request_t *req, char *ip, unsigned short port, int *ret_msg_id );


httpcd_response_t* httpcd_build_response( int code, char *desc, const char *content_type, char *body, int len );
int httpcd_set_response_header( httpcd_response_t* resp, const char *name, const char *value );
int httpcd_send_response( httpcd_response_t *resp, int msg_id );

void httpcd_set_log_level( int level );

typedef int (*httpcd_dump_cb_t)( void *user_data, char *buf, int len );

void httpcd_dump_request( httpcd_request_t *req, void* user_data, httpcd_dump_cb_t dump_cb );
void httpcd_dump_response( httpcd_response_t *resp, void* user_data, httpcd_dump_cb_t dump_cb );

int httpcd_close_conn( const char *ip, unsigned short port );
void httpcd_set_conn_timeout( unsigned int timeout );

void httpcd_set_resp_wait_timeout( unsigned int timeout );

#ifdef __cplusplus
}
#endif

#endif


