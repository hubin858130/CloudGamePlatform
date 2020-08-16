/***************************************************************************
 *
 * Copyright	£º2007 santachi corp.
 * File name	£ºdev_type.h
 * Description	£ºdefine all device type for santachi 
 * Created	: liuqs<liuqs_santachi@126.com> --- 2007-01-22
 * Modified 	: add some struct ---2007-02-02:zhangkk
 * Modified 	: add some device type by liuqs on 2007-06-04 
 *
 ***************************************************************************/

#ifndef __DEV_TYPE_H__
#define __DEV_TYPE_H__

/*----------------------------device type-----------------------------*/
/* santachi dvr device type define */
#define DEV_TYPE_HD420		0x54530000	/* z1510 :mpeg1/2 4 channel CIF */
#define DEV_TYPE_HD820		0x54530001	/* z1510 :mpeg1/2 8 channel CIF */
#define DEV_TYPE_HD8004		0x54530002	/* vweb2010 :mpeg4 4 channel D1 */
#define DEV_TYPE_HD8008		0x54530003	/* vweb2010 :mpeg4 8 channel D1 */
#define DEV_TYPE_HD8016		0x54530004	/* at204x :mpeg4 16 channel CIF */

/* santachi dvs device type define */
#define DEV_TYPE_NT200A		0x54530100	/* at204x: mpeg4 1 channel encoder */
#define DEV_TYPE_NT200B		0x54530101	/* at204x: mpeg4 1 channel decoder */
#define DEV_TYPE_NT200C		0x54530102	/* at204x: mpeg4 1 channel codec */
#define DEV_TYPE_NT200D		0x54530103	/* at204x: mpeg4 1 channel encoder with hard disk */
#define DEV_TYPE_NT204A		0x54530104 	/* at204x: mpeg4 4 channel encoder */
#define DEV_TYPE_NT204D		0x54530105	/* at204x: mpeg4 4 channel encoder with hard disk */

#define DEV_TYPE_NT200HA	0x54530200	/* hi3510: h.264 1 channel encoder */
#define DEV_TYPE_NT200HB	0x54530201	/* hi3510: h.264 1 channel decoder */
#define DEV_TYPE_NT200HC	0x54530202	/* hi3510: h.264 1 channel codec */
#define DEV_TYPE_NT200HD	0x54530203	/* hi3510: h.264 1 channel encoder with hard disk */
#define DEV_TYPE_NT204HA	0x54530204	/* hi3510: h.264 4 channel encoder */
#define DEV_TYPE_NT204HD	0x54530205	/* hi3510: h.264 4 channel encoder with hard disk */
#define DEV_TYPE_NT202HD	0x54530206	/* hi3510: h.264 2 channel encoder with hard disk */
#define DEV_TYPE_NT202HA	0x54530207	/* hi3510: h.264 2 channel encoder  */

/* santahci ip camera device type define */
#define DEV_TYPE_NT6050		0x54530300	/* at204x :mpeg4 1 channel D1 */
#define DEV_TYPE_NT8189		0x54530301	/* at204x :mpeg4 1 channel D1 */
#define DEV_TYPE_NT4094		0x54530302	/* at204x :mpeg4 1 channel D1 --no this device */
#define DEV_TYPE_NT6050H	0x54530303	/* hi3510 :h.264 1 channel D1 */
#define DEV_TYPE_NT8189H	0x54530304	/* hi3510 :h.264 1 channel D1 */
#define DEV_TYPE_NT4094H	0x54530305	/* hi3510 :h.264 1 channel D1 */
#define DEV_TYPE_NT1102H	0x54530306	/* hi3510 :h.264 1 channel D1 */

/* santachi nvr device type define */
#define DEV_TYPE_NVR		0x54530400	/* powerpc 8245 nvr */

/* other device type define */

/*------------------------frame struct------------------------------*/

#define SANTACHI_I_FRAME_TYPE 1 //I Frame
#define SANTACHI_P_FRAME_TYPE 2 //P Frame
#define SANTACHI_A_FRAME_TYPE 3 //Audio Frame
#define SANTACHI_OSD_FRAME_TYPE 4 // Osd Frame

#define VIDEO_FORMAT_D1		0x01
#define VIDEO_FORMAT_HD1	0x02
#define VIDEO_FORMAT_CIF	0x03
#define VIDEO_FORMAT_QCIF	0x04

typedef struct __frame_head_t
{
        unsigned long	device_type;
        unsigned long	frame_size;
        unsigned long	frame_no;
		unsigned char	video_format;
        unsigned char	frame_type;
		unsigned char	frame_rate;
		unsigned char	reserved;
		unsigned long	sec;
        unsigned long	usec;
		_int64			pts;
}frame_head_t;

typedef struct __frame_t
{
	frame_head_t frame_head;
	unsigned char *frame_data;
}frame_t;

/*-----------------------file struct------------------------------*/
#define MAX_LOGO_SIZE	32
#define SANTACHI_FLIE_VERSION01 0x00000001 /*first created 07-02-02*/
#define SANTACHI_FLIE_VERSION02 0x00000002

typedef struct __file_head_t
{
	int file_version;
	int device_type;
	int record_type;
	char logo[MAX_LOGO_SIZE];
}file_head_t;

typedef struct __file_t
{
	file_head_t file_head;
	frame_t *p_frame;
}file_t;


#endif /* __DEV_TYPE_H__ */


