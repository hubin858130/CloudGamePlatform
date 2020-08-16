/******************************************************************
 *  $Id: nanohttp-common.h,v 1.31 2006/07/09 16:24:19 snowdrop Exp $
 * 
 * CSOAP Project:  A http client/server library in C
 * Copyright (C) 2003-2004  Ferhat Ayaz
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA  02111-1307, USA.
 * 
 * Email: ferhatayaz@yahoo.com
 ******************************************************************/
#ifndef NANO_HTTP_COMMON_H
#define NANO_HTTP_COMMON_H

#include <stdlib.h>
#include <time.h>

#define HEADER_CONTENT_ID		"Content-Id"
#define HEADER_CONTENT_TRANSFER_ENCODING "Content-Transfer-Encoding"
#define TRANSFER_ENCODING_CHUNKED	"chunked"

/**
 *
 * General Header Fields
 *
 * There are a few header fields which have general applicability for both
 * request and response messages, but which do not apply to the entity being
 * transferred. These header fields apply only to the message being transmitted. 
 * (see RFC2616)
 *
 */
#define HEADER_CACHE_CONTROL		"Cache-Control"
#define HEADER_CONNECTION		"Connection"
#define HEADER_DATE			"Date"
#define HEADER_PRAGMA			"Pragma"
#define HEADER_TRAILER			"Trailer"
#define HEADER_TRANSFER_ENCODING	"Transfer-Encoding"
#define HEADER_UPGRADE			"Upgrade"
#define HEADER_VIA			"Via"
#define HEADER_WARNING			"Warning"

/**
 *
 * Entity Header Fields
 *
 * Entity-header fields define metainformation about the entity-body or, if no
 * body is present, about the resource identified by the request. Some of this
 * metainformation is OPTIONAL; some might be REQUIRED by portions of this
 * specification. (see RFC2616 7.1)
 *
 */
#define HEADER_ALLOW			"Allow"
#define HEADER_CONTENT_ENCODING		"Content-Encoding"
#define HEADER_CONTENT_LANGUAGE		"Content-Language"
#define HEADER_CONTENT_LENGTH		"Content-Length"
#define HEADER_CONTENT_LOCATION		"Content-Location"
#define HEADER_CONTENT_MD5		"Content-MD5"
#define HEADER_CONTENT_RANGE		"Content-Range"
#define HEADER_CONTENT_TYPE		"Content-Type"
#define HEADER_EXPIRES			"Expires"
#define HEADER_LAST_MODIFIED		"Last-Modified"


/**
 *
 * XXX: move to nanohttp-response.h
 *
 * Response Header Fields
 *
 * The response-header fields allow the server to pass additional information
 * about the response which cannot be placed in the Status-Line. These header
 * fields give information about the server and about further access to the
 * resource identified by the Request-URI. (see RFC2616)
 *
 */
#define HEADER_ACCEPT_RANGES		"Accept-Ranges"
#define HEADER_AGE			"Age"
#define HEADER_EXTENSION_TAG		"ETag"
#define HEADER_LOCATION			"Location"
#define HEADER_PROXY_AUTHENTICATE	"Proxy-Authenticate"
#define HEADER_RETRY_AFTER		"Retry-After"
#define HEADER_SERVER			"Server"
#define HEADER_VARY			"Vary"
#define HEADER_WWW_AUTHENTICATE		"WWW-Authenticate"

/**
 *
 * XXX: move to nanohttp-request.h
 *
 * Request Header Fields
 *
 * The request-header fields allow the client to pass additional information
 * about the request, and about the client itself, to the server. These fields
 * act as request modifiers, with semantics equivalent to the parameters on a
 * programming language method invocation (see RFC2616).
 *
 */
#define HEADER_ACCEPT			"Accept"
#define HEADER_CHARSET			"Accept-Charset"
#define HEADER_ACCEPT_ENCODING		"Accept-Encoding"
#define HEADER_ACCEPT_LANGUAGE		"Accept-Language"
#define HEADER_AUTHORIZATION		"Authorization"
#define HEADER_EXPECT			"Expect"
#define HEADER_FROM			"From"
#define HEADER_HOST			"Host"
#define HEADER_IF_MATCH			"If-Match"
#define HEADER_IF_MODIFIED_SINCE	"If-Modified-Since"
#define HEADER_IF_NONE_MATCH		"If-None-Match"
#define HEADER_IF_RANGE			"If-Range"
#define HEADER_IF_UNMODIFIED_SINCE	"If-Unmodified-Since"
#define HEADER_IF_MAX_FORWARDS		"Max-Forwards"
#define HEADER_PROXY_AUTHORIZATION	"Proxy-Authorization"
#define HEADER_RANGE			"Range"
#define HEADER_REFERER			"Referer"
#define HEADER_TRANSFER_EXTENSION	"TE"
#define HEADER_USER_AGENT		"User-Agent"

/**
 *
 * nanohttp command line flags
 *
 */
#define NHTTPD_ARG_PORT		"-NHTTPport"
#define NHTTPD_ARG_TERMSIG	"-NHTTPtsig"
#define NHTTPD_ARG_MAXCONN	"-NHTTPmaxconn"
#define NHTTPD_ARG_TIMEOUT	"-NHTTPtimeout"

#define NHTTP_ARG_CERT		"-NHTTPcert"
#define NHTTP_ARG_CERTPASS	"-NHTTPcertpass"
#define NHTTP_ARG_CA		"-NHTTPCA"
#define NHTTP_ARG_HTTPS		"-NHTTPS"

#ifndef SAVE_STR
#define SAVE_STR(str) ((str==0)?("(null)"):(str))
#endif

#define BOUNDARY_LENGTH 18

#define MAX_HEADER_SIZE 4256
#define MAX_SOCKET_BUFFER_SIZE 4256
#define MAX_FILE_BUFFER_SIZE 4256

#define URL_MAX_HOST_SIZE      120
#define URL_MAX_CONTEXT_SIZE  1024

#define HSOCKET_MAX_BUFSIZE 1024

#define REQUEST_MAX_PATH_SIZE 1024
#define RESPONSE_MAX_DESC_SIZE 1024

/*
  DIME common stuff
*/
#define DIME_VERSION_1      0x08
#define DIME_FIRST_PACKAGE  0x04
#define DIME_LAST_PACKAGE   0x02
#define DIME_CHUNKED        0x01
#define DIME_TYPE_URI       0x2



/* TODO (#1#): find proper ports */
#define URL_DEFAULT_PORT_HTTP 80
#define URL_DEFAULT_PORT_HTTPS 81
#define URL_DEFAULT_PORT_FTP 120

/* Success flag */
#define H_OK 0

/* File errors */
#define FILE_ERROR_OPEN 8000
#define FILE_ERROR_READ 8001

/* Socket errors */
#define HSOCKET_ERROR_CREATE		1001
#define HSOCKET_ERROR_GET_HOSTNAME	1002
#define HSOCKET_ERROR_CONNECT		1003
#define HSOCKET_ERROR_SEND		1004
#define HSOCKET_ERROR_RECEIVE		1005
#define HSOCKET_ERROR_BIND		1006
#define HSOCKET_ERROR_LISTEN		1007
#define HSOCKET_ERROR_ACCEPT		1008
#define HSOCKET_ERROR_NOT_INITIALIZED	1009
#define HSOCKET_ERROR_IOCTL		1010
#define HSOCKET_ERROR_SSLCLOSE		1011
#define HSOCKET_ERROR_SSLCTX		1011

/* URL errors */
#define URL_ERROR_UNKNOWN_PROTOCOL	1101
#define URL_ERROR_NO_PROTOCOL		1102
#define URL_ERROR_NO_HOST		1103

/* Stream errors */
#define STREAM_ERROR_INVALID_TYPE	1201
#define STREAM_ERROR_SOCKET_ERROR	1202
#define STREAM_ERROR_NO_CHUNK_SIZE	1203
#define STREAM_ERROR_WRONG_CHUNK_SIZE	1204


/* MIME errors */
#define MIME_ERROR_NO_BOUNDARY_PARAM	1301
#define MIME_ERROR_NO_START_PARAM	1302
#define MIME_ERROR_PARSE_ERROR		1303
#define MIME_ERROR_NO_ROOT_PART		1304
#define MIME_ERROR_NOT_MIME_MESSAGE	1305


/* General errors */
#define GENERAL_INVALID_PARAM		1400
#define GENERAL_HEADER_PARSE_ERROR	1401

/* Thread errors */
#define THREAD_BEGIN_ERROR		1500

/* XML Errors */
#define XML_ERROR_EMPTY_DOCUMENT	1600
#define XML_ERROR_PARSE			1601

/* SSL Errors */
#define HSSL_ERROR_CA_LIST		1710
#define HSSL_ERROR_CONTEXT		1720
#define HSSL_ERROR_CERTIFICATE		1730
#define HSSL_ERROR_PEM			1740
#define HSSL_ERROR_CLIENT		1750
#define HSSL_ERROR_SERVER		1760
#define HSSL_ERROR_CONNECT		1770

/*
Set Sleep function platform depended
*/
#ifdef WIN32
#define system_sleep(seconds) Sleep(seconds*1000);
#else
#define system_sleep(seconds) sleep(seconds);
#endif

/**
  Indicates the version of the 
  used HTTP protocol.
*/
typedef enum _http_version
{
  HTTP_1_0,
  HTTP_1_1                      /* default */
} http_version_t;


/**
  Indicates the used method
*/
typedef enum _hreq_method
{
  HTTP_REQUEST_POST,
  HTTP_REQUEST_GET,
  HTTP_REQUEST_OPTIONS,
  HTTP_REQUEST_HEAD,
  HTTP_REQUEST_PUT,
  HTTP_REQUEST_DELETE,
  HTTP_REQUEST_TRACE,
  HTTP_REQUEST_CONNECT,
  HTTP_REQUEST_UNKOWN
} hreq_method_t;


#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#include <string.h>
char *strtok_r(char *s, const char *delim, char **save_ptr);
struct tm *localtime_r(const time_t * const timep, struct tm *p_tm);
#endif

typedef unsigned char byte_t;
typedef void *herror_t;

herror_t herror_new(const char *func, int errcode, const char *format, ...);
int herror_code(herror_t err);
char *herror_func(herror_t err);
char *herror_message(herror_t err);
void herror_release(herror_t err);

/*
  hpairnode_t represents a pair (key, value) pair.
  This is also a linked list.
 */
typedef struct hpair hpair_t;
struct hpair
{
  char *key;
  char *value;
  hpair_t *next;
};


/**
  Creates a new pair with the given parameters. Both strings
  key and value will be cloned while creating the pair. 

  @param key the key of the (key,value) pair
  @param value the value of the (key,value) pair
  @param next next pair node in the linked list

  @returns A newly crated hpair_t object. Use hpair_free() 
    or hpair_free_deep() to free the pair.
*/
hpair_t *hpairnode_new(const char *key, const char *value, hpair_t * next);


/**
  Creates a new pair from a given string. This function 
  will split 'str' with the found first delimiter 'delim'.
  The 'value' field  of the newly created pair will have 
  the value "", if no delimiter was found/
  Whitespaces (' ') will be removed from the beginnig of 
  the parsed value.

  @param str A string to parse
  @param delim a delimiter to use while splitting into key,value 
  @param next next pair node in the linked list

  @returns A newly crated hpair_t object. Use hpair_free() 
    or hpair_free_deep() to free the pair.
*/
hpair_t *hpairnode_parse(const char *str, const char *delim, hpair_t * next);


/**
  Frees a given pair.

  @param pair the pair to free
*/
void hpairnode_free(hpair_t * pair);


/**
  Makes a deep free operation. All pairnodes,
  beginning with the given pari, in the 
  linked list will be destroyed. 

  @param pair the pair to start to free the linked list
*/
void hpairnode_free_deep(hpair_t * pair);


/**
  Returns the (key,value) pair, which key is the 
  given 'key'.

  @param pair the first pair to start to search from.
  @param key key to find the in the pair.
  @returns if a value will be found, this function will 
    return the value (do not free this string) or NULL
    if no pair was found with the key 'key'.
*/
char *hpairnode_get(hpair_t * pair, const char *key);


/**
  Returns the (key,value) pair, which key is the 
  given 'key'. The case will be ignored while 
  comparing the key strings.

  @param pair the first pair to start to search from.
  @param key key to find the in the pair.
  @returns if a value will be found, this function will 
    return the value (do not free this string) or NULL
    if no pair was found with the key 'key'.
*/
char *hpairnode_get_ignore_case(hpair_t * pair, const char *key);


/**
  This function will create a new pair and fills the 
  (key,value) fields of a given pair. Note that the 'next'
  field will not be copied.

  @param src the source pair object to copy.

  @returns a newly created pair with the same (key,value) 
   pairs as in 'src'. This fields will be cloned. The'next'
   field will be set to NULL.

  @see hpairnode_copy_deep
*/
hpair_t *hpairnode_copy(const hpair_t * src);


/**
  Clones the hole linked list. 

  @param src the source pair object to copy from

  @returns the first object in the linked list. 

  @see hpairnode_copy
*/
hpair_t *hpairnode_copy_deep(const hpair_t * src);

/* Debug functions */
void hpairnode_dump_deep(hpair_t * pair);
void hpairnode_dump(hpair_t * pair);

/**
  The protocol types in enumeration 
  format. Used in some other nanohttp objects
  like hurl_t.

  @see hurl_t
*/
typedef enum _hprotocol
{
  PROTOCOL_HTTP,
  PROTOCOL_HTTPS,
  PROTOCOL_FTP
} hprotocol_t;



/**
  The URL object. A representation 
  of an URL like:<P>
   
  [protocol]://[host]:[port]/[context]

*/
typedef struct _hurl
{
  /**
    The transfer protocol. 
    Note that only PROTOCOL_HTTP is supported by nanohttp.
  */
  hprotocol_t protocol;

  /**
    The port number. If no port number was given in the URL,
    one of the default port numbers will be selected. 
    URL_HTTP_DEFAULT_PORT    
    URL_HTTPS_DEFAULT_PORT   
    URL_FTP_DEFAULT_PORT    
  */
  int port;

  /** The hostname */
  char host[URL_MAX_HOST_SIZE];

  /** The string after the hostname. */
  char context[URL_MAX_CONTEXT_SIZE];
} hurl_t;


/**
  Parses the given 'urlstr' and fills the given hurl_t object.

  @param obj the destination URL object to fill
  @param url the URL in string format

  @returns H_OK on success or one of the following otherwise

    URL_ERROR_UNKNOWN_PROTOCOL 
    URL_ERROR_NO_PROTOCOL 
    URL_ERROR_NO_HOST 
*/
herror_t hurl_parse(hurl_t * obj, const char *url);

/*
  Object representation of the content-type field 
  in a HTTP header: 
  <P>
  Example:<P>
  
  text/xml; key="value" key2="value2' ...
*/
typedef struct _content_type
{
  char type[128];
  hpair_t *params;
} content_type_t;


/**
  Parses the given string and creates a new ccontent_type_t
  object. 

  @param content_type_str the string representation of the
  content-type field in a HTTP header.

  @returns A newly created content_type_t object. Free this
    object with content_type_free();

  @see content_type_free
*/
content_type_t *content_type_new(const char *content_type_str);


/**
  Frees the given content_type_t object
*/
void content_type_free(content_type_t * ct);



/*
  part. Attachment
*/
typedef struct _part
{
  char id[250];
  char location[250];
  hpair_t *header;
  char content_type[128];
  char transfer_encoding[128];
  char filename[250];
  struct _part *next;
  int deleteOnExit;             /* default is 0 */
} part_t;


part_t *part_new(const char *id, const char *filename,
                 const char *content_type, const char *transfer_encoding,
                 part_t * next);
void part_free(part_t * part);




/*
  Attachments
*/
typedef struct _attachments
{
  part_t *parts;
  part_t *last;
  part_t *root_part;
} attachments_t;

attachments_t *attachments_new();       /* should be used internally */

/*
  Free a attachment. Create attachments with MIME
  and DIME (DIME is not supported yet).

  @see mime_get_attachments
*/
void attachments_free(attachments_t * message);
void attachments_add_part(attachments_t * attachments, part_t * part);

#ifdef __cplusplus
}
#endif

#endif
