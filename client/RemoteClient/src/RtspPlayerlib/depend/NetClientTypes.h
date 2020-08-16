#ifndef NETCLIENTTYPES_H
#define NETCLIENTTYPES_H

#define	MAX_CHANNEL_NUM		16
#define MAX_CONNECTION		16
#define MAX_PORT_NUM        16

#define MAX_RECV_CHANNEL    1024
#define MAX_ENCODER         1024

#define LENGTH_USER_NAME	16
#define LENGTH_PASSWORD		16
#define LENGTH_CHN_TITLE    32
#define LENGTH_DEVICE_NAME  32

//connect mode
#define NETMODE_TCP     1   //Tcp connect
#define NETMODE_UDP     2   //Udp connect
#define NETMODE_MC      3   //Multicast connect
#define NVS_ACTIVE      4   //Positive Mode（Current version not support）

//Video resolution
#define QCIF	0   //Quarter Cif 	172*144
#define HCIF	1   //Half Cif	352*144	
#define FCIF	2	//Full Cif	352*288	
#define HD1	    3	//Half D1	720*288
#define FD1	    4	//Full D1	720*576

//Stream type
#define LAN_VIDEO   0           //Basic stream(hight quality)
#define WAN_VIDEO   1           //Extended stream(low bitrate)

//Device type
#define NVS_T       0           //T serials NVS
#define NVS_S       1           //S serials NVS
#define NVS_TPLUS   2           //T+ serials NVS

//H264 Decod mode
#define H264DEC_DECTWO	0		//decode 2 field
#define H264DEC_DECTOP	1		//decode top field （low CPU cost）

//Message define
#define WCM_RECVMESSAGE         1   //Received string
#define WCM_ERR_ORDER           2   //Occur error in command socket
#define WCM_ERR_DATANET         3   //Occur error in data socket (no use)
#define WCM_TIMEOUT_DATANET     4   //Process stream timeout
#define WCM_ERR_PLAYER          5   //Occur error in player
#define WCM_ERR_USER            6   //User define error
#define WCM_LOGON_NOTIFY        7   //Logon notify
#define WCM_VIDEO_HEAD          8   //Received video head
#define WCM_VIDEO_DISCONNECT    9   //the connection were disconnect by mediacenter

//Message of Mediacenter
#define WCM_CLIENT_CONNECT      10  //There a client connected to Mediacenter
#define WCM_CLIENT_DISCONNECT   11  //A client disconnected from Mediacenter
#define WCM_CLIENT_LOGON        12  //A client logon/logogg the Mediacenter

#define WCM_RECORD_ERR          13  //Occur when recording file

//Directory Service Mode
#define WCM_DSM_REGERR          14  //Error on proxy regist to Directory server
#define WCM_DSM_ENCODERADD      15  //A NVS regist on the proxy
#define WCM_DSM_ENCODERDEL      16  //A NVS's regist connection disconnected.

//Message of Download logfile
#define WCM_LOGFILE_FINISHED    17  //When logfile download finished

//Message of query file
#define WCM_QUERYFILE_FINISHED  18  //Query finished record files

#define WCM_DWONLOAD_FINISHED   19  //Download finished
#define WCM_REBUILDINDEX        22  //Finished of rebuild index file

//User authority
enum
{
    AUT_BROWSE			   = 1,		//Only can preview video
    AUT_BROWSE_CTRL		   = 2,		//Can preview and control device
    AUT_BROWSE_CTRL_SET	   = 3,		//Preview, control device, modify settings
    AUT_ADMIN			   = 4		//Super user, No.0 user is super user,
									//User name is Admin, which can not be modified,
    								//Can add, delete, modify user's authority
};

//Alarm type
enum ALARMTYPE
{
    ALARM_VDO_MOTION,       //Video motion alarm
    ALARM_VDO_REC,          //video mask alarm
    ALARM_VDO_LOST,         //Video lost alarm
    ALARM_VDO_INPORT        //Input port alarm
};

//Logon state
enum
{
    LOGON_DSMING        = 3,    //DSM（Directory Sevices Mode）connecting
    LOGON_RETRY         = 2,    //Retry
    LOGON_SUCCESS       = 0,    //Logon successfully
    LOGON_ING           = 1,    //Being logon
    LOGON_FAILED        = -1,   //Fail to logon
    LOGON_TIMEOUT       = -2,   //Logon timeout
    NOT_LOGON           = -3,   //Not logon
    LOGON_DSMFAILED     = -4,   //DSM connection failure
    LOGON_DSMTIMEOUT    = -5    //DSM connection overtime
};

//Player state
enum
{
    PLAYER_STOP         = 0,    //Not require to play
    PLAYER_WAITTING     = 0x01, //Require to play but not play, waiting for data
    PLAYER_PLAYING      = 0x02, //Playing
    PLAYER_CARDWAITTING = 0x04, //Require to hardware decode
    PLAYER_CARDPLAYING  = 0x08  //Being hardware decode output
};

//PAL/NTSC
enum VIDEO_NORM
{
    VIDEO_MODE_PAL    = 0x00,
    VIDEO_MODE_NTSC   = 0x01,
    VIDEO_MODE_AUTO   = 0x02
};

//Character overlay type
enum
{
    OSDTYPE_TIME      = 0x01,   //Overlay time
    OSDTYPE_TITLE     = 0x02,   //Overlay character string
    OSDTYPE_LOGO      = 0x04    //Overlay mark
};

//Image property
enum
{
    BRIGHTNESS = 0,         //Brightness
    CONTRAST   = 1,         //Contrast
    SATURATION = 2,         //Saturation
    HUE        = 3          //Hue
};

//Prefer mode
enum
{
    VDOQUALITY = 0,     //Video quality prefer
    FRAMERATE  = 2      //Framerate prefer
};

//Stream encode type
enum
{
    NO_STREAM   = 0,    //Null
    ONLY_VIDEO  = 1,    //Video stream
    ONLY_AUDIO  = 2,    //Audio stream
    VIDEO_AUDIO = 3     //Video and audio stream
};

enum
{
    DISABLE     = 0,
    ENABLE      = 1
};

enum
{
    LOW         = 0,
    HIGH        = 1
};

//Talk
enum
{
    TALK_BEGIN_OK       = 0,    //Start talk successfully
    TALK_BEGIN_ERROR    = -1,   //Fail to start talk
    TALK_ERROR          = -2    //Talk error
};

//Core remote upgrade
enum
{
    PRO_UPGRADE_OK      = 0,    // Remote upgrade success
    PRO_UPGRADE_ERROR   = -1    // Remote upgrade failure
};

enum
{
    WEB_UPGRADE_OK      = 0,    // Remote upgrade success
    WEB_UPGRADE_ERROR   = -1    // Remote upgrade failure
};

//视频参数定义
enum PARATYPE
{
    PARA_VIDOEPARA          =0,     //Generate when modify video adjustment (Brightness, contrast, sue, saturation);
    PARA_VIDEOQUALITY       =1,     //Generate when modify video quality parameter;
    PARA_FRAMERATE          =2,     //Generate when modify video frame parameter;
    PARA_IFRAMERATE         =3,     //Generate when modify video key frame;
    PARA_STREAMTYPE         =4,     //Generate when compressed video stream is changed;
    PARA_MOTIONDETECTAREA   =5,     //Generate when video motion test area is changed;
    PARA_THRESHOLD          =6,     //Generate when video motion sensitivity is changed;
    PARA_MOTIONDETECT       =7,     //Generate when the start of video motion alarm is changed;
    PARA_OSDTEXT            =8,     //Generate when character overlay property is changed;
    PARA_OSDTYPE            =9,     //Generate when character overlay type is changed;
    PARA_ALMINMODE          =10,    //Generate when input port alarm state is changed;
    PARA_ALMOUTMODE         =11,    //Generate when output port alarm state is changed;
    PARA_ALARMINPUT         =12,    //Generate when input port triggering relationship is changed;
    PARA_ALARMOUTPUT        =13,    //Generate when output port triggering relationship is changed;
    PARA_AlMVDOCOVTHRESHOLD =14,    //Generate when video mask sensitivity is changed, it is not offered temporarily;
    PARA_ALMVIDEOCOV        =15,    //Generate when video mask alarm state is changed, it is not offered temporarily;
    PARA_RECORDCOVERAREA    =16,    //Generate when record mask area is changed, it is not offered temporarily;
    PARA_RECORDCOVER        =17,    //Generate when record mask is changed, it is not offered temporarily;
    PARA_ALMVDOLOST         =18,    //Generate when video lost state is changed;
    PARA_DEVICETYPE         =19,    //Generate when camera site type is changed;
    PARA_NEWIP              =20,    //Notice when device IP address is changed;
    PARA_AUDIOCHN           =21,    //Generate when audio channel triggering is changed;
    PARA_IPFILTER           =22,    //Generate when IP address parameter is changed;
    PARA_COVERAREA          =23,    //Generate when video mask area is changed;
    PARA_VIDEOHEADER        =24,    //Generate when video head is changed;
    PARA_VIDEOSIZE          =25,    //Generate when video size is changed;
    PARA_BITRATE            =26,    //Generate when stream rate parameter is changed;
    PARA_DATACHANGED		=27,    //Generate when user data is changed;
    PARA_PARSECHANGED		=28,    //Generate when domain analysis parameter is changed;

    PARA_APPIFRAMERATE      =29,    //Generate when sub stream key frame rate is changed;
    PARA_APPFRAMERATE       =30,    //Generate when sub stream frame rate is changed;
    PARA_APPVIDEOQUALITY    =31,    //Generate when sub stream video quality is changed;
    PARA_APPVIDEOSIZE       =32,    //Generate when sub stream video size is changed;
    PARA_APPSTREAMTYPE      =33,    //Generate when sub stream compression type is changed;
    PARA_APPBITRATE         =34,    //Generate when sub stream rate limit property is changed;
    PARA_APPCOVERAREA       =35,    //Generate when sub stream video mask property is changed;
    PARA_APPVIDEOHEADER     =36,    //Generate when sub stream video head is changed;

    PARA_REDUCENOISE        =37,    //Generate when noise reduce state is changed;
    PARA_BOTHSTREAMSAME     =38,    //Generate when whether main and sub stream property are set same is changed;
    PARA_PPPOE              =39,    //Generate when PPPoE dial property is changed;

    PARA_ENCODETYPE         =40,    //Generate when VBR/CBR property is changed;
    PARA_PREFERMODE         =41,    //Generate when Frame Rate Prefer/Quality Prefer property is changed;
    
    PARA_LOGFILE            =42,    //Generate when log property is changed;
    PARA_SETLOGOOK          =43,    //Generate when succeed to set LOGO overlay (Support T serials only)

    PARA_STORAGE_SCHEDULE   =44,    //Generate when schedule record plan is changed;
    PARA_STORAGE_TASKSTATE  =45,    //Generate when schedule record state is changed;
    PARA_STORAGE_ALARMSTATE =46,    //Generate when alarm record state is changed;
    PARA_STORAGE_PRERECORD  =47,    //Generate when alarm pre-record parameter is changed;
    PARA_STORAGE_RECORDRULE =49,    //Generate when record package time, dealing rules when disk is full, or minimum free space is changed;
    PARA_STORAGE_EXTNAME    =50,    //Generate when record file extended name is changed;
    PARA_STORAGE_MAPDEVICE  =51,    //Generate when storage device mapping parameter is changed;
    PARA_STORAGE_MOUNTUSB   =52,    //Generate when USB device state is changed;
    PARA_STORAGE_DISKSTATE  =53,    //Generate when disk state is changed;
    PARA_AUDIOCODER         =54,    //Generate when audio encode format is changed;
    PARA_NPMODE             =55,    //Generate when video format is changed;
    PARA_STORAGE_RECORDSTATE=56,     //Generate when current record state is changed

    PARA_PU_MANAGERSVR      =57,    //Generate when Manager server info is changed;
    PARA_PU_DEVICEID        =58,    //Generate when Device ID is changed;
    PARA_STREAMCLIENT       =59,    //Generate when Stream client info changed;
    PARA_DATEFORMAT         =60,    //Generate when Date format is changed;
    PARA_HTTPPORT           =61,    //Generate when HTTP service port is changed;

    PARA_CMOS_SCENE         =62,    //Generate when scene is changed;
    PARA_SMTP_INTO          =63,    //Generate when smtp information is changed;
    PARA_SMTP_ENABLE        =64,     //Generate when smtp notify enable is changed;
    PARA_SENSORFLIP         =65     //Generate when flip enable is changed;

};

enum IDENTIFY {CLIENT=0,PROXY,CLIENT_PROXY};
enum DECDATATYPE {T_AUDIO8,T_YUV420,T_YUV422};

typedef struct
{
    int     m_iPara[10];
    char    m_cPara[32];
}STR_Para;

typedef struct
{
	unsigned char m_u8Brightness;
    unsigned char m_u8Contrast;
    unsigned char m_u8Saturation;
    unsigned char m_u8Hue;
}STR_VideoParam;

typedef struct
{
    char 	cEncoder[16];		//NVS IP，
    char 	cClientIP[16];		//Client IP，
    int		iChannel;			//Channel Number，
    int     iStreamNO;          //Stream type
    int 	iMode;			    //Network mode，1（TCP）， 2（UDP），3（multicast）
}LINKINFO, *PLINKINFO;

typedef struct
{
    int		        iCount;			            //Connect Count，
    unsigned int  	uiID[MAX_ENCODER];		    //ID
}UIDLIST, *PUIDLIST;

typedef struct
{
    char		m_cHostName[32];    //NVS host name
    char		m_cEncoder[16];   	//NNS (IP)
    int         m_iRecvMode;    	//Network mode
    char     	m_cProxy[16];     	//Proxy (IP)
    int         m_iPort;        	//NVS port
    int         m_nvsType;          //NVS type(NVS_T or NVS_S)
}ENCODERINFO,*PENCODERINFO;

typedef struct
{
	int 			m_iChannelNo;	    //Remote host to be connected video channel number (Begin from 0)
    char            m_cNetFile[255];    //Play the file on net, not used temporarily
	char		 	m_cRemoteIP[16];	//IP address of remote host
	int 			m_iNetMode;		    //Select net mode 1--TCP  2--UDP  3--Multicast
	int				m_iTimeout;		    //Timeout length for data receipt
	int 			m_iTTL;			    //TTL value when Multicast
    int             m_iBufferCount;     //Buffer number
    int             m_iDelayNum;        //Start to call play progress after which buffer is filled
    int             m_iDelayTime;       //Delay time(second), reserve
    int             m_iStreamNO;        //Stream type
}CLIENTINFO;

//Version message structure, with which to transmit SDK version message
typedef struct
{
	unsigned short	m_ulMajorVersion;
	unsigned short	m_ulMinorVersion;
	unsigned short	m_ulBuilder;
	char*			m_cVerInfo;
}SDK_VERSION;

//OSD param
typedef struct
{
	unsigned char	ucCovTime;
	unsigned char 	ucCovWord;
	int             iCovYear;
	int             iCovMonth;
    int             iCovDay;
    int             iCovHour;
    int             iCovMinute;
    int             iCovSecond;
    unsigned char   ucPosition;
    char            cCovWord[32];
}OSD_PROPERTY;

//Hardware decode to show external data parameter
typedef struct
{
    int     m_iChannelNum;      //Decode card hardware channel number
	int     m_iVideoWidth;		//Video width
	int     m_iVideoHeight;		//Video height
	int     m_iFrameRate;		//Frame rate
	int     m_iDisPos;			//Video display position
    int     m_iAudioOut;        //whether to output audio
}DecoderParam;

typedef struct
{
    unsigned long nWidth;    //Video width, audio data is 0；
    unsigned long nHeight;   //Video height, audio data is 0；
    unsigned long nStamp;    //Time stamp(ms)。
    unsigned long nType;     //Audio type，T_AUDIO8,T_YUV420，。
    unsigned long nFrameRate;//Frame rate。
    unsigned long nReserved; //reserve
}FRAME_INFO;

enum RAWFRAMETYPE
{
    VI_FRAME = 0,   //视频I帧
    VP_FRAME = 1,   //视频P帧
    AUDIO_FRAME = 5 //音频帧
};
typedef struct
{
    unsigned long nWidth;    //Video width, audio data is 0；
    unsigned long nHeight;   //Video height, audio data is 0；
    unsigned long nStamp;    //Time stamp(ms)。
    unsigned long nType;     //RAWFRAMETYPE，。
    unsigned long nEnCoder;  //Audio or Video encoder(Video,0:H263,1:H264, 2:MP4. Audio:AUDIO_ENCODER)
    unsigned long nFrameRate;//Frame rate。
    unsigned long nReserved; //reserve
}RAWFRAME_INFO;

typedef void (__stdcall *RECVDATA_NOTIFY)(unsigned char* _ucData,unsigned long _ulIP,int _iPort,int _iNetMode,int _iLen);
typedef void (__stdcall *LOGON_NOTIFY)(char* _cIP,int _iLogonState);
typedef void (__stdcall *ALARM_NOTIFY)(char* _cIP,int _iCh,void* _vContext,ALARMTYPE _iAlarmType);
typedef void (__stdcall *PARACHANGE_NOTIFY)(char* _cIP,int _iCh,PARATYPE _iParaType,STR_Para* _strPara);
typedef void (__stdcall *TALK_NOTIFY)(char* _cIP,int _iServerResponse);
typedef void (__stdcall *PROUPGRADE_NOTIFY)(char* _cIP,int _iServerState);
typedef void (__stdcall *WEBUPGRADE_NOTIFY)(char* _cIP,int _iServerState);
typedef void (__stdcall *COMRECV_NOTIFY)(char* _cIP, char *_buf, int _length,int _iComNo);

typedef void (__stdcall *DECYUV_NOTIFY)(unsigned long _ulID, unsigned char* _ucData, int _iSize, FRAME_INFO *_pFrameInfo, void* _pContext);
typedef void (__stdcall *RAWFRAME_NOTIFY)(unsigned long _ulID, unsigned char* _ucData, int _iSize, RAWFRAME_INFO *_pRawFrameInfo, void* _pContext);

//===========================================================================
//  storage  add 2007.6.13
//===========================================================================

#define MAX_DAYS 7
#define MAX_TIMESEGMENT 4
#define MAX_PAGE_SIZE   20

//Record type： 1-Manual record，2-Schedule record，3-Alarm record
enum RECORD_TYPE {RECORD_ALL=0xFF, RECORD_MANUAL=1, RECORD_TIME=2, RECORD_ALARM=3, RECORD_OTHER = 4};
//Record state：
enum RECORD_STATE {REC_STOP=0, REC_MANUAL=1, REC_TIME=2, REC_ALARM=3};
//Audio encoder：
enum AUDIO_ENCODER
{
    G711_A              = 0x01,  /* 64kbps G.711 A, see RFC3551.txt  4.5.14 PCMA */
    G711_U              = 0x02,  /* 64kbps G.711 U, see RFC3551.txt  4.5.14 PCMU */
    ADPCM_DVI4          = 0x03,  /* 32kbps ADPCM(DVI4) */

    G726_24KBPS         = 0x05,  /* 24kbps G.726, see RFC3551.txt  4.5.4 G726-24 */
    G726_32KBPS         = 0x06,  /* 32kbps G.726, see RFC3551.txt  4.5.4 G726-32 */
    G726_40KBPS         = 0x07,  /* 40kbps G.726, see RFC3551.txt  4.5.4 G726-40 */
    MPEG_LAYER2         = 0x0E,  /* Mpeg layer 2*/
    ADPCM_IMA           = 0x23,  /* 32kbps ADPCM(IMA) */
    MEDIA_G726_16KBPS   = 0x24,  /* G726 16kbps for ASF ... */
    MEDIA_G726_24KBPS   = 0x25,  /* G726 24kbps for ASF ... */
    MEDIA_G726_32KBPS   = 0x26,  /* G726 32kbps for ASF ... */
    MEDIA_G726_40KBPS   = 0x27   /* G726 40kbps for ASF ... */
};

//Schedle time
typedef struct
{
	unsigned short iStartHour;
	unsigned short iStartMin;
    unsigned short iStopHour;
	unsigned short iStopMin;
}NVS_SCHEDTIME,*PNVS_SCHEDTIME;

//Record rule
typedef struct
{
	int             iTaskRecord; 	/*Schedle record enabled 0-Enable 1-Disable*/
	int             iAlarmRecord; 	/*Alaum record enabled 0-Enable 1-Disable*/
	NVS_SCHEDTIME	struRecordSched[MAX_DAYS][MAX_TIMESEGMENT];
}NVS_CHAN_RECORD,*PNVS_CHAN_RECORD;

//Record mode param
typedef struct
{
    int  iPreRecord;        /* Prerecord enabled: 0-Enable 1-Disable*/
    int  iPreRecordTime; 	/* Prerecord time 5-30s，default 10s */
    int  iDelayTime;        /* Delay time*/
    char cExternName[10];	/* Record file extended name */
    int  iRecordTime; 	    /* Record time length */
    int  iRecPolicy;        /* Storage strategy */
    int  iFreeDisk;         /* Minimum free disk space */
}NVS_RECORD,*PNVS_RECORD;

//Record time parameter
typedef struct
{
	unsigned short iYear;   /* Year */
	unsigned short iMonth;  /* Month */
	unsigned short iDay;    /* Day */
	unsigned short iHour;   /* Hour */
	unsigned short iMinute; /* Minute */
	unsigned short iSecond; /* Second */
} NVS_FILE_TIME,*PNVS_FILE_TIME;

//Record File Property
typedef struct
{
	int             iType; 	        /* Record type 1-Manual record, 2-Schedule record, 3-Alarm record*/
	int 	        iChannel; 	    /* Record channel 0~channel defined channel number*/
	char 		    cFileName[250]; /* File name */
	NVS_FILE_TIME	struStartTime; 	/* File start time */
	NVS_FILE_TIME	struStoptime; 	/* File end time */
	int             iFileSize; 	    /* File size */
}NVS_FILE_DATA,*PNVS_FILE_DATA;

//Reserch parameter
typedef struct
{
	int          	iType; 	        /* Record type 0xFF-All, 1-Manual record, 2-Schedule record, 3-Alarm record*/
	int     	    iChannel; 	    /* Record channel 0xFF-All, 0~channel-defined channel number*/
	NVS_FILE_TIME	struStartTime; 	/* Start time of file */
	NVS_FILE_TIME	struStopTime; 	/* End time of file */
	int     	    iPageSize;	    /* Record number returned by each research*/
	int         	iPageNo;	    /* From which page to research */
    int             iFiletype;      /* File type, 0-All, 1-AVstream, 2-picture*/
}NVS_FILE_QUERY, *PNVS_FILE_QUERY;

//Net storage device
typedef struct
{
    char cDeviceIP[16];
    char cStorePath[250];
    char cUsername[16];
    char cPassword[16];
    int  iState;
}NVS_NFS_DEV,*PNVS_NFS_DEV;

//Diskinfo
typedef struct
{
    int  iTotal;        //total size
    int  iFree;         //free size
    int  iReserved;     //reserved
}NVS_DISKINFO, *PNVS_DISKINFO;

//Storage device info
typedef struct
{
    NVS_DISKINFO  usbDisk;  //usb disk information
    NVS_DISKINFO  nfsDisk;  //nfs disk information
    NVS_DISKINFO  ideDisk;  //ide disk information
}NVS_STORAGEDEV, *PNVS_STORAGEDEV;

enum SMTP_AUTHTYPE {AUTH_OFF=0,AUTH_PLAIN,AUTH_CRAM_MD5,AUTH_DIGEST_MD5,AUTH_GSSAPI,AUTH_EXTERNAL,AUTH_LOGIN,AUTH_NTLM,SMTP_AUTHTYPE_LAST};
enum SCENE_TYPE {AUTO=0, SCENE1,SCENE2,SCENE3,SCENE4,SCENE5,SCENE6,SCENE7,SCENE8,SCENE9,SCENE10,SCENE11,SCENE_TYPE_LAST};

//SMTP alarm info
typedef struct
{
    char            cSmtpServer[32];    //smtp server
    unsigned short  wdSmtpPort;         //smtp server port
    char            cEmailAccount[32];  //mail account
    char            cEmailPassword[32];  //mail password
    SMTP_AUTHTYPE   iAuthtype;           //authtype
    char            cEmailAddress[32];  //mailbox address
    char            cMailSubject[32];   //mail subject
}SMTP_INFO,*PSMTP_INFO;
//---------------------------------------------------------------------------
#endif

