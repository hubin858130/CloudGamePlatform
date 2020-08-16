
#ifndef _IEDEF_H_
#define _IEDEF_H_

#include "msgpretype.h"


#ifdef __cplusplus
extern "C" {
#endif


#include "msgdef.h"



typedef enum mioeIEType{
	IET_IE_CMS_INFO = 101,
	IET_IE_CUSTOMER = 102,
	IET_IEX_CUSTOMER_INFO = 151,
	IET_IEX_CU_OP_RIGHT = 152,
	IET_IEX_CUSTOMER_AUTH = 153,
	IET_IEX_DATA = 154,
	IET_IEX_DCS_INFO = 155,
	IET_IEX_DIGEST = 156,
	IET_IEX_HEADER = 157,
	IET_IEX_DEVICE_CHECK = 158,
	IET_IEX_PU_BASIC_PARA = 159,
	IET_IEX_STATE_TYPE = 160,
	IET_IE_QUERY_PARA = 161,
	IET_IE_PICTURE_INFO = 162,
	IET_IE_PU_ONLINE = 201,
	IET_IE_CHANNEL = 202,
	IET_IE_NODE_ATTRIB_NAME = 203,
	IET_IE_MANUFACTURE = 204,
	IET_IE_HARDDISK = 205,
	IET_IE_DEVICE_AUTHENTICATION = 206,
	IET_IE_QUERY_STATUS = 207,
	IET_IE_PTZ = 208,
	IET_IE_TRANSPARENTCMD_TEXT = 209,
	IET_IE_COMPORT_CONFIG = 210,
	IET_IE_MATRIX_CONFIG = 211,
	IET_IE_CHANNEL_MATRIX_OUTPUT = 212,
	IET_IE_CHANNEL_MATRIX_INPUT = 213,
	IET_IE_PU_SERIAL_PORT = 214,
	IET_IE_PU_INPUT = 215,
	IET_IE_PU_OUTPUT = 216,
	IET_IE_IMAGE_ENCODE_PARA = 217,
	IET_IE_IMAGE_DISPLAY_PARA = 218,
	IET_IE_IMAGE_TEXT_PARA = 219,
	IET_IE_PU_BASEINFO = 220,
	IET_IE_CHANNEL_PRIVILEGE = 221,
	IET_IE_CHANNEL_INFO = 222,
	IET_IE_CHANNEL_BASEINFO = 223,
	IET_IE_CHANNEL_ID = 224,
	IET_IE_PLATFORM = 225,
	IET_IEX_PTZID = 226,
	IET_IE_CRUISEPOINT = 227,
	IET_IEX_CRUISENUMBER = 228,
	IET_IE_PRESET_PTZ = 229,
	IET_IEX_PTZ_MODE = 230,
	IET_IE_PU_DEVICE_STATE = 232,
	IET_IE_PU_CAPACITY_STATE = 233,
	IET_IE_PU_DISK_STATE = 234,
	IET_IE_VIDEO_CHANNEL_STATE = 235,
	IET_IE_ALARM_IN_STATE = 236,
	IET_IE_ALARM_OUT_STATE = 237,
	IET_IEX_ALARM_CONFIG_TYPE = 238,
	IET_IE_DISK_PARA = 239,
	IET_IE_ALARM_RECORD = 240,
	IET_IE_CAP_PHOTO = 241,
	IET_IE_GPIN_ALARM = 242,
	IET_IE_VIDEO_LOSE_ALARM = 243,
	IET_IE_VIDEO_HIDE_ALARM = 244,
	IET_IE_VIDEO_MOVE_ALARM = 245,
	IET_IE_NODE_ONLINE = 246,
	IET_IEX_NPU_EXTRA = 248,
	IET_IEX_HARDDISK_FOR_PU = 251,
	IET_IEX_VIDEO_ENCODE = 253,
	IET_IEX_VIDEO_OSD = 254,
	IET_IEX_MOTION_DETECT_REGION = 255,
	IET_IEX_ALARM_ACTION = 256,
	IET_IE_AUDIO_ENCODE_PARA = 257,
	IET_IEX_AUDIO_ENCODE = 259,
	IET_IEX_PU_ONLINE = 260,
	IET_IEX_POLL_ENABLE = 261,
	IET_IEX_PU_PARA_TYPE = 262,
	IET_IEX_COVER_DETECT_REGION = 263,
	IET_IEX_COVER_REGION = 264,
	IET_IEX_PU_GROUP = 265,
	IET_IE_LOG_QUERY = 266,
	IET_IE_LOG_QUERY_RESULT = 267,
	IET_IEX_STORAGE_TASK = 268,
	IET_IEX_STORAGE_TASK_ID = 269,
	IET_IE_NPU_SERVER = 270,
	IET_IE_PHOTO_INFO = 271,
	IET_IE_LOCAL_STORAGE_TASK = 272,
	IET_IEX_NRU_CAPACITY = 273,
	IET_IEX_NRU_STATUS = 274,
	IET_IEX_NRU_PARA = 275,
	IET_IEX_VTDU_CAPACITY = 276,
	IET_IEX_VTDU_STATUS = 277,
	IET_IEX_VTDU_PARA = 278,
	IET_IEX_CU_STATUS = 279,
	IET_IE_PU_STATE = 280,
	IET_IE_PU_STATUS = 281,
	IET_IE_PU_LIST_ID = 282,
	IET_IEX_VTDU_ROUTE_MODE = 283,
	IET_IEX_PHOTO_INFO = 284,
	IET_IEX_PU_STATUS = 285,
	IET_IEX_RECORD_MGR = 286,
	IET_IEX_ALARM_ID = 287,
	IET_IEX_THRESHOLD = 288,
	IET_IEX_VIDEO_PACKET_INFO = 289,
	IET_IEX_ALARM_PRESET = 290,
	IET_IEX_DEFAULT_PRESET = 291,
	IET_IEX_PARAM_PAIR = 292,
	IET_IE_STORAGE_TASK = 293,
	IET_IE_SCHEDULE = 294,
	IET_IEX_NETWORK_PARA = 295,
	IET_IEX_NRU_SELECTION = 296,
	IET_IEX_PU_ACCESS_SERVER = 297,
	IET_IEX_NET_MANAGER_SERVER = 298,
	IET_IEX_MAX_VIDEO_CONNECTION_NUM = 299,
	IET_IE_NETLINK = 301,
	IET_IE_OPEN_VIDEO = 302,
	IET_IE_OPEN_VIDEO_ACK = 303,
	IET_IE_VIDEO_CHANNEL = 304,
	IET_IE_CHANNEL_YUNTAI_SET = 305,
	IET_IE_PORT_RANGE = 320,
	IET_IE_UA_REAL_IP = 321,
	IET_IE_URL = 322,
	IET_IE_SCHEDULE_NOTIFY = 323,
	IET_IE_NETLINK_PRE = 324,
	IET_IE_NETLINK_NEXT = 325,
	IET_IE_CALL_ID = 326,
	IET_IEX_CALL_INFO = 350,
	IET_IEX_CALL_ID = 351,
	IET_IEX_ROUTE_INFO = 352,
	IET_IEX_CALL_FLAG = 353,
	IET_IEX_FTP_LOG_INFO = 354,
	IET_IEX_MEDIA_FROM = 355,
	IET_IEX_MEDIA_TO = 356,
	IET_IEX_MEDIA_PARA = 357,
	IET_IEX_MONITOR_CHANNEL = 358,
	IET_IEX_MEDIA_RCV = 359,
	IET_IEX_MEDIA_RCV_CONVERSE = 360,
	IET_IEX_MEDIA_SEND = 361,
	IET_IEX_MEDIA_SEND_CONVERSE = 362,
	IET_IEX_MEDIA_DIRECT = 363,
	IET_IEX_MEDIA_PARA_PREV = 364,
	IET_IEX_MEDIA_PARA_NEXT = 365,
	IET_IEX_ALARM_AUDIO_OUT = 366,
	IET_IEX_PU_ACCESS_TYPE = 367,
	IET_IEX_STARTUP_MODE = 368,
	IET_IE_VCR_CONTROL = 401,
	IET_IE_BCSH = 402,
	IET_IE_ALARM_IN_CHANNEL = 501,
	IET_IE_ALARM_OUT_CHANNEL = 502,
	IET_IE_ALARM_INFO = 503,
	IET_IEX_ALARM_SET = 551,
	IET_IEX_ALARM_OP = 552,
	IET_IEX_ALARM_IN_CHANNEL = 553,
	IET_IEX_IO_CHANNEL = 554,
	IET_IEX_ALARM_VIDEO_SET = 555,
	IET_IEX_ALARM_ENABLE = 556,
	IET_IEX_RECORD_FILE_INFO = 601,
	IET_IEX_RECORD_PARAM_SET = 602,
	IET_IE_STORELOCATION = 603,
	IET_IE_TIME_FILE = 620,
	IET_IE_TIMESPAN = 621,
	IET_IEX_FILETYPE = 651,
	IET_IE_RESULT = 701,
	IET_IE_TIME_DETAIL_LIST = 702,
	IET_IE_TIME = 703,
	IET_IE_STORETYPE = 704,
	IET_IE_STARTTIME = 705,
	IET_IE_ENDTIME = 706,
	IET_IE_BEGINTIME = 707,
	IET_IE_FILEITEM = 708,
	IET_IE_TIME_STRING = 709,
	IET_IEX_LOG_INFO = 751,
	IET_IEX_MEDIA_INFO = 752,
	IET_IEX_FUNC_TYPE = 753,
	IET_IEX_QUERY_SLICE = 754,
	IET_IEX_STATE_INFO = 755,
	IET_IEX_DATABASE_INFO = 756,
	IET_IEX_AAA_INFO = 757,
	IET_IEX_VERSION = 758,
	IET_IEX_VERSION_ENABLE = 759,
	IET_IEX_MEDIA_LINK = 760,
	IET_IEX_ALARM_OP_CHANNEL = 761,
	IET_IEX_CHANNEL_LOCATION_INFO = 762,
	IET_IEX_COMPOUND_ENABLE = 763,
	IET_IEX_CHANNEL = 764,
	IET_IEX_ALARM_STATE_ENABLE = 765,
	IET_IEX_ALARM_STATE_MAINTAIN = 766,
	IET_IEX_POLL_PIC_SIZE = 767,
	IET_IEX_TIME_SPAN = 768,
	IET_IEX_TB_TYPE = 769,
	IET_IEX_SDP = 770,
	IET_IEX_IMAGE_ENCODE_PARA_SETS = 771,
	IET_IEX_IKEY_INFO = 772,
	IET_IEX_SHARED_CATALOG = 773,
	IET_IEX_REBOOT = 774,
	IET_puId = 10001,
	IET_puName = 10002,
	IET_puPassword = 10003,
	IET_netId = 10004,
	IET_ipAddress = 10005,
	IET_controlPort = 10006,
	IET_sipPort = 10007,
	IET_subnetMask = 10008,
	IET_dns = 10009,
	IET_gateway = 10010,
	IET_userName = 10011,
	IET_passWord = 10012,
	IET_priority = 10013,
	IET_serialPort = 10014,
	IET_baudRate = 10015,
	IET_dataBit = 10016,
	IET_parity = 10017,
	IET_stopBit = 10018,
	IET_mode = 10019,
	IET_flowControl = 10020,
	IET_decoderType = 10021,
	IET_decoderAddress = 10022,
	IET_timeOut = 10023,
	IET_input = 10024,
	IET_output = 10025,
	IET_ChannelNumber = 10026,
	IET_state = 10027,
	IET_hour = 10028,
	IET_minute = 10029,
	IET_second = 10030,
	IET_month = 10031,
	IET_date = 10032,
	IET_year = 10033,
	IET_videoId = 10034,
	IET_encodeMode = 10035,
	IET_picQuality = 10036,
	IET_bitRate = 10037,
	IET_bitRateType = 10038,
	IET_frameRate = 10039,
	IET_imageSize = 10040,
	IET_streamType = 10041,
	IET_iFrameInterval = 10042,
	IET_contrast = 10043,
	IET_bright = 10044,
	IET_hue = 10045,
	IET_saturation = 10046,
	IET_bitmapX = 10047,
	IET_bitmapY = 10048,
	IET_bitmapTimeEnable = 10049,
	IET_bitmapTextEnable = 10050,
	IET_bitmapText = 10051,
	IET_bitmapTextX = 10052,
	IET_bitmapTextY = 10053,
	IET_connectionDetectionEnabled = 10054,
	IET_diskFullAlarmEnabled = 10055,
	IET_diskFullHighThreshold = 10056,
	IET_diskFullLowThreshold = 10057,
	IET_diskErrorAlarmEnabled = 10058,
	IET_alarmPreRecordTime = 10059,
	IET_alarmRecordTime = 10060,
	IET_alarmOutputTime = 10061,
	IET_alarmOutputActivatedTimes = 10062,
	IET_photoResolution = 10063,
	IET_photoQuality = 10064,
	IET_shootTimes = 10065,
	IET_gpinAlarmEnabled = 10066,
	IET_gpinAlarmStatus = 10067,
	IET_gpinAlarmOutput = 10068,
	IET_gpinAlarmRecord = 10069,
	IET_gpinAlarmShoot = 10070,
	IET_videoLoseAlarmEnabled = 10071,
	IET_videoLoseAlarmOutput = 10072,
	IET_hideDetectionAlarmEnabled = 10073,
	IET_hideDetectionAlarmTime = 10074,
	IET_hideDetectionX = 10075,
	IET_hideDetectionY = 10076,
	IET_hideDetectionWidth = 10077,
	IET_hideDetectionHeight = 10078,
	IET_hideDetectionAlarmOutput = 10079,
	IET_hideDetectionAlarmRecord = 10080,
	IET_motionDetectionAlarmEnabled = 10081,
	IET_motionDetectionAlarmTime = 10082,
	IET_motionDetectionBlocks = 10083,
	IET_motionDetectionFrequency = 10084,
	IET_motionDetectionSensitivity = 10085,
	IET_motionDetectionAlarmOutput = 10086,
	IET_motionDetectionAlarmRecord = 10087,
	IET_motionDetectionAlarmShoot = 10088,
	IET_recordEnable = 10089,
	IET_recycleRecEnable = 10090,
	IET_schedule = 10091,
	IET_recordPolicy = 10092,
	IET_frameInterval = 10093,
	IET_filenameSuffix = 10094,
	IET_fileType = 10095,
	IET_fromDate = 10096,
	IET_toDate = 10097,
	IET_recordFile = 10098,
	IET_totalSize = 10099,
	IET_freeSize = 10100,
	IET_fileName = 10101,
	IET_deviceStatus = 10102,
	IET_disk = 10103,
	IET_videoChannel = 10104,
	IET_alarmIn = 10105,
	IET_alarmOut = 10106,
	IET_logType = 10107,
	IET_startLogDate = 10108,
	IET_endLogDate = 10109,
	IET_startIndex = 10110,
	IET_maxResults = 10111,
	IET_logInfo = 10112,
	IET_alarmServerIp = 10113,
	IET_alarmServerPort = 10114,
	IET_alarmUrl = 10115,
	IET_heartBeatServerIp = 10116,
	IET_heartBeatServerPort = 10117,
	IET_registerServerIp = 10118,
	IET_registerServerPort = 10119,
	IET_enableHeartBeat = 10120,
	IET_heartBeatPeriod = 10121,
	IET_ptzId = 10122,
	IET_cmd = 10123,
	IET_param = 10124,
	IET_speed = 10125,
	IET_protocol = 10126,
	IET_presetIndex = 10127,
	IET_presetName = 10128,
	IET_cruiseNumber = 10129,
	IET_cruisePoint = 10130,
	IET_controlAction = 10131,
	IET_fileUrl = 10132,
	IET_puIp = 10133,
	IET_alarmType = 10134,
	IET_serverType = 10135,
	IET_channelNumber = 10136,
	IET_diskNumber = 10137,
	IET_timeStamp = 10138,
	IET_data = 10139,
	IET_oldVersion = 10140,
	IET_newVersion = 10141,
	IET_upgradeResult = 10142,
	IET_transparentAction = 10143,
	IET_transparentData = 10144,
	IET_puPort = 10145,
	IET_puType = 10146,
	IET_enableLongConnection = 10147,
	IET_expires = 10148,
	IET_mediaType = 10149,
	IET_imageWidth = 10150,
	IET_imageHeight = 10151,
	IET_videoFormat = 10152,
	IET_cuId = 10153,
	IET_username = 10154,
	IET_userStatus = 10155,
	IET_domainUsername = 10156,
	IET_domainPassword = 10157,
	IET_customerId = 10158,
	IET_displayName = 10159,
	IET_userLevel = 10160,
	IET_description = 10161,
	IET_disabled = 10162,
	IET_address = 10163,
	IET_email = 10164,
	IET_dept = 10165,
	IET_fixedNumber = 10166,
	IET_mobileNumber = 10167,
	IET_creator = 10168,
	IET_createdDateStart = 10169,
	IET_createdDateEnd = 10170,
	IET_customerName = 10171,
	IET_type = 10172,
	IET_contactName = 10173,
	IET_faxNumber = 10174,
	IET_zipCode = 10175,
	IET_bankName = 10176,
	IET_bankAccount = 10177,
	IET_maxUsers = 10178,
	IET_maxOnlineUsers = 10179,
	IET_adminUsername = 10180,
	IET_createdDate = 10181,
	IET_areaId = 10182,
	IET_cuIdFrom = 10183,
	IET_cuIdTo = 10184,
	IET_maxVideoChannels = 10185,
	IET_userStatistic = 10186,
	IET_currentUsers = 10187,
	IET_currentOnlineUsers = 10188,
	IET_storageQuota = 10189,
	IET_diskFullAlarmThreshold = 10190,
	IET_autoFreeSpaceSize = 10191,
	IET_firstInputChannel = 10192,
	IET_firstOutputChannel = 10193,
	IET_firstVideoChannel = 10194,
	IET_firstAudioChannel = 10195,
	IET_maxInputChannel = 10196,
	IET_maxOutputChannel = 10197,
	IET_maxVideoChannel = 10198,
	IET_maxAudioChannel = 10199,
	IET_audioChannel = 10200,
	IET_vsType = 10201,
	IET_localStorageEnabled = 10202,
	IET_recordMode = 10203,
	IET_networkInterface = 10204,
	IET_puControlPort = 10205,
	IET_puSipPort = 10206,
	IET_videoPort = 10207,
	IET_audioPort = 10208,
	IET_dvsName = 10209,
	IET_loginUsername = 10210,
	IET_loginPassword = 10211,
	IET_x = 10212,
	IET_y = 10213,
	IET_gpio = 10214,
	IET_online = 10215,
	IET_manufacturerId = 10216,
	IET_manufacturerName = 10217,
	IET_productVersion = 10218,
	IET_softwareVersion = 10219,
	IET_lastUpgradeDate = 10220,
	IET_place = 10221,
	IET_cameraName = 10222,
	IET_vs = 10223,
	IET_width = 10224,
	IET_height = 10225,
	IET_ptzProtocol = 10226,
	IET_controlPTZType = 10227,
	IET_timePieceLen = 10228,
	IET_model = 10229,
	IET_setupType = 10230,
	IET_parentId = 10231,
	IET_areaName = 10232,
	IET_action = 10233,
	IET_subscriberId = 10234,
	IET_expiringDate = 10235,
	IET_linkable = 10236,
	IET_sourceType = 10237,
	IET_severity = 10238,
	IET_typeName = 10239,
	IET_alarmDate = 10240,
	IET_eliminated = 10241,
	IET_diskFullThreshold = 10242,
	IET_gpinAlarm = 10243,
	IET_cameraAlarm = 10244,
	IET_preset = 10245,
	IET_cruise = 10246,
	IET_taskName = 10247,
	IET_startTime = 10248,
	IET_duration = 10249,
	IET_taskType = 10250,
	IET_maxTimes = 10251,
	IET_task = 10252,
	IET_taskId = 10253,
	IET_startTimeStamp = 10254,
	IET_endTimeStamp = 10255,
	IET_fileSize = 10256,
	IET_filePath = 10257,
	IET_status = 10258,
	IET_fileId = 10259,
	IET_mduIpAddressList = 10260,
	IET_csgIpAddressList = 10261,
	IET_sourceId = 10262,
	IET_password = 10263,
	IET_forDecoder = 10264,
	IET_workMode = 10265,
	IET_httpRegisterServerIp = 10266,
	IET_httpRegisterServerPort = 10267,
	IET_enableHttpHeartbeat = 10268,
	IET_httpHeartbeatServerIp = 10269,
	IET_httpHeartbeatServerPort = 10270,
	IET_httpHeartbeatPeriod = 10271,
	IET_enableSipRegister = 10272,
	IET_sipRegisterServerIp = 10273,
	IET_sipRegisterServerPort = 10274,
	IET_enableSipHeartbeat = 10275,
	IET_sipHeartbeatServerIp = 10276,
	IET_sipHeartbeatServerPort = 10277,
	IET_sipHeartbeatPeriod = 10278,
	IET_diskPath = 10279,
	IET_diskOccupiedPercent = 10280,
	IET_userId = 10281,
	IET_keepAlivePeriod = 10282,
	IET_hideAreaEnabled = 10283,
	IET_hideImageArea = 10284,
	IET_customerStatus = 10285,
	IET_filename = 10286,
	IET_mduIpAddress = 10287,
	IET_csgIpAddress = 10288,
	IET_HttpHeartbeatPeriod = 10289,
	IET_gpinAlarm_gpinAlarmEnabled = 10400,
	IET_gpinAlarm_alarmOutputActivatedTimes = 10401,
	IET_gpinAlarm_gpinAlarmStatus = 10402,
	IET_gpinAlarm_gpinAlarmOutput = 10403,
	IET_gpinAlarm_gpinAlarmRecord = 10404,
	IET_gpinAlarm_gpinAlarmShoot = 10405,
	IET_cameraAlarm_videoLoseAlarmEnabled = 10406,
	IET_cameraAlarm_videoLoseAlarmOutput = 10407,
	IET_cameraAlarm_hideDetectionAlarmEnabled = 10408,
	IET_cameraAlarm_hideDetectionAlarmTime = 10409,
	IET_cameraAlarm_hideDetectionX = 10410,
	IET_cameraAlarm_hideDetectionY = 10411,
	IET_cameraAlarm_hideDetectionWidth = 10412,
	IET_cameraAlarm_hideDetectionHeight = 10413,
	IET_cameraAlarm_hideDetectionAlarmOutput = 10414,
	IET_cameraAlarm_hideDetectionAlarmRecord = 10415,
	IET_cameraAlarm_motionDetectionAlarmEnabled = 10416,
	IET_cameraAlarm_motionDetectionAlarmTime = 10417,
	IET_cameraAlarm_motionDetectionBlocks = 10418,
	IET_cameraAlarm_motionDetectionFrequency = 10419,
	IET_cameraAlarm_motionDetectionSensitivity = 10420,
	IET_cameraAlarm_motionDetectionAlarmOutput = 10421,
	IET_cameraAlarm_motionDetectionAlarmRecord = 10422,
	IET_cameraAlarm_motionDetectionAlarmShoot = 10423,
	IET_Name = 14100,
	IET_Address = 14101,
	IET_Privilege = 14102,
	IET_Parent = 14103,
	IET_Status = 14104,
	IET_Subnum = 14107,
	IET_Result = 14108,
	IET_Format = 14109,
	IET_Video = 14110,
	IET_Audio = 14111,
	IET_MaxBitrate = 14112,
	IET_ReceiveSocket = 14113,
	IET_Bitrate = 14114,
	IET_FileType = 14115,
	IET_MaxFileNum = 14116,
	IET_BeginTime = 14117,
	IET_EndTime = 14118,
	IET_RealFileNum = 14119,
	IET_SendFileNum = 14120,
	IET_Command = 14122,
	IET_Manufacturer = 14123,
	IET_Sublist = 14125,
	IET_Item = 14126,
	IET_Sublist_Item = 14127,
	IET_FileInfolist = 14128,
	IET_item = 14129,
	IET_FileInfolist_item = 14130,
	IET_Model = 14131,
	IET_Firmware = 14132,
	IET_Maxcamera = 14133,
	IET_Online = 14134,
	IET_Errencodenum = 14135,
	IET_Record = 14136,
	IET_SinceStartup = 14137,
	IET_Cameralist = 14138,
	IET_Cameralist_item = 14139,
	IET_Value = 14140,
	IET_All = 14141,
	IET_Free = 14142,
	IET_Medialink = 14143,
	IET_UNKNOWN = 0x7FFFFFFF
}mioeIEType;

typedef struct miosIE_CMS_INFO{
	MIO_UINT32 type;

	MIO_CHAR m_CmsID[19];
	MIO_CHAR m_CmsName[33];
	MIO_CHAR m_IPAddr[41];
	MIO_UINT8 m_ConnectType;
	MIO_UINT16 m_Port;
	MIO_CHAR m_Location[33];
	MIO_CHAR m_Descript[256];
}miosIE_CMS_INFO;

typedef struct miosIE_CUSTOMER{
	MIO_UINT32 type;

	MIO_CHAR m_CustomerID[19];
	MIO_CHAR m_CustomerName[33];
}miosIE_CUSTOMER;

typedef struct miosIEX_CUSTOMER_INFO{
	MIO_UINT32 type;

	MIO_CHAR m_CustomerID[19];
	MIO_CHAR m_CustomerName[33];
	MIO_UINT64 m_GroupID;
	MIO_CHAR m_GroupName[33];
	MIO_UINT8 m_Online;
}miosIEX_CUSTOMER_INFO;

typedef struct miosIEX_CU_OP_RIGHT{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[19];
	MIO_UINT8 m_ChannelType;
	MIO_UINT16 m_ChannelNo;
	MIO_CHAR m_ChannelName[33];
	MIO_UINT8 m_Priority;
	MIO_UINT32 m_UseStarttime;
	MIO_UINT32 m_UseTime;
	MIO_UINT32 m_DeviceExist;
	MIO_UINT32 m_UserRight;
	MIO_CHAR m_Region[12];
	MIO_DOUBLE m_Longitude;
	MIO_DOUBLE m_Latitude;
}miosIEX_CU_OP_RIGHT;

typedef struct miosIEX_CUSTOMER_AUTH{
	MIO_UINT32 type;

	MIO_CHAR m_KEY[33];
}miosIEX_CUSTOMER_AUTH;

typedef struct miosIEX_DATA{
	MIO_UINT32 type;

	MIO_UINT16 m_DataLength;
	MIO_CHAR m_Data[256];
}miosIEX_DATA;

typedef struct miosIEX_DCS_INFO{
	MIO_UINT32 type;

	MIO_UINT8 m_PTZmode;
	MIO_UINT8 m_Vtdumode;
	MIO_UINT16 m_CallNum;
}miosIEX_DCS_INFO;

typedef struct miosIEX_DIGEST{
	MIO_UINT32 type;

	MIO_CHAR m_userName[33];
	MIO_CHAR m_nonce[65];
	MIO_CHAR m_cnonce[33];
	MIO_CHAR m_realm[33];
	MIO_CHAR m_alg[33];
	MIO_CHAR m_nonceCount[17];
	MIO_CHAR m_method[17];
	MIO_CHAR m_qop[33];
	MIO_CHAR m_uri[256];
	MIO_CHAR m_response[33];
}miosIEX_DIGEST;

typedef struct miosIEX_HEADER{
	MIO_UINT32 type;

	MIO_UINT32 m_sequenceNumber;
	MIO_CHAR m_sessionID[17];
	MIO_CHAR m_sourceID[19];
	MIO_CHAR m_destinationID[19];
}miosIEX_HEADER;

typedef struct miosIEX_DEVICE_CHECK{
	MIO_UINT32 type;

	MIO_UINT8 m_DeviceType;
	MIO_CHAR m_DeviceID[19];
}miosIEX_DEVICE_CHECK;

typedef struct miosIEX_PU_BASIC_PARA{
	MIO_UINT32 type;

	MIO_CHAR m_Hardware_Version[33];
	MIO_CHAR m_Software_Version[33];
	MIO_CHAR m_Disk_Withhold_Size[33];
	MIO_CHAR m_Disk_Used_Size[33];
	MIO_CHAR m_Disk_Remain_Size[33];
	MIO_CHAR m_Device_Type[33];
}miosIEX_PU_BASIC_PARA;

typedef struct miosIEX_STATE_TYPE{
	MIO_UINT32 type;

	MIO_UINT8 m_type;
}miosIEX_STATE_TYPE;

typedef struct miosIE_QUERY_PARA{
	MIO_UINT32 type;

	MIO_UINT16 m_CapType;
	MIO_TIME m_StartTime;
	MIO_TIME m_EndTime;
}miosIE_QUERY_PARA;

typedef struct miosIE_PICTURE_INFO{
	MIO_UINT32 type;

	MIO_TIME m_CapTime;
	MIO_CHAR m_Name[257];
	MIO_UINT64 m_Size;
	MIO_CHAR m_Address[65];
	MIO_UINT16 m_Port;
	MIO_UINT8 m_CapPicType;
}miosIE_PICTURE_INFO;

typedef struct miosIE_PU_ONLINE{
	MIO_UINT32 type;

	MIO_CHAR m_NID[19];
	MIO_CHAR m_NodeName[33];
	MIO_UINT8 m_Online;
	MIO_UINT8 m_DeviceType;
	MIO_UINT16 m_ChannelNum;
}miosIE_PU_ONLINE;

typedef struct miosIE_CHANNEL{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[19];
	MIO_UINT8 m_ChannelType;
	MIO_UINT16 m_ChannelNo;
	MIO_UINT16 m_ChannelNum;
}miosIE_CHANNEL;

typedef struct miosIE_NODE_ATTRIB_NAME{
	MIO_UINT32 type;

	MIO_CHAR m_NID[19];
	MIO_CHAR m_NodeName[33];
}miosIE_NODE_ATTRIB_NAME;

typedef struct miosIE_MANUFACTURE{
	MIO_UINT32 type;

	MIO_CHAR m_MID[17];
	MIO_CHAR m_Name[33];
	MIO_UINT8 m_DeviceType;
	MIO_UINT16 m_Version;
	MIO_UINT32 m_DeviceTypeIndex;
}miosIE_MANUFACTURE;

typedef struct miosIE_HARDDISK{
	MIO_UINT32 type;

	MIO_UINT16 m_HardTotalCapacity;
	MIO_UINT16 m_HardSpareCapacity;
}miosIE_HARDDISK;

typedef struct miosIE_DEVICE_AUTHENTICATION{
	MIO_UINT32 type;

	MIO_CHAR m_KEY[33];
}miosIE_DEVICE_AUTHENTICATION;

typedef struct miosIE_QUERY_STATUS{
	MIO_UINT32 type;

	MIO_UINT8 m_IsContinue;
}miosIE_QUERY_STATUS;

typedef struct miosIE_PTZ{
	MIO_UINT32 type;

	MIO_UINT8 m_OpID;
	MIO_UINT16 m_Param1;
	MIO_UINT16 m_Param2;
}miosIE_PTZ;

typedef struct miosIE_TRANSPARENTCMD_TEXT{
	MIO_UINT32 type;

	MIO_UINT32 m_ComNum;
	MIO_UINT32 m_ComType;
	MIO_CHAR m_UartSpeed[8];
	MIO_UINT32 m_UartParity;
	MIO_UINT32 m_UartData;
	MIO_UINT32 m_UartStop;
	MIO_UINT32 m_UartFlow;
	MIO_UINT32 m_ComInitialization;
	MIO_CHAR m_CmdText[255];
}miosIE_TRANSPARENTCMD_TEXT;

typedef struct miosIE_COMPORT_CONFIG{
	MIO_UINT32 type;

	MIO_UINT16 m_ChannelNo;
	MIO_UINT8 m_ComType;
	MIO_UINT32 m_UartSpeed;
	MIO_UINT8 m_UartParity;
	MIO_UINT8 m_UartData;
	MIO_UINT8 m_UartStop;
	MIO_UINT8 m_UartFlow;
	MIO_UINT8 m_ComInitialization;
}miosIE_COMPORT_CONFIG;

typedef struct miosIE_MATRIX_CONFIG{
	MIO_UINT32 type;

	MIO_UINT16 m_ProtocolType;
	MIO_UINT16 m_MatrixInNumner;
	MIO_UINT16 m_MatrixOutputNumner;
}miosIE_MATRIX_CONFIG;

typedef struct miosIE_CHANNEL_MATRIX_OUTPUT{
	MIO_UINT32 type;

	MIO_UINT16 m_ProtocolType;
	MIO_UINT16 m_ChannelNo;
	MIO_UINT16 m_MatrixOutputNo;
}miosIE_CHANNEL_MATRIX_OUTPUT;

typedef struct miosIE_CHANNEL_MATRIX_INPUT{
	MIO_UINT32 type;

	MIO_UINT16 m_ProtocolType;
	MIO_UINT16 m_ChannelNo;
	MIO_UINT16 m_MatrixInputNo;
}miosIE_CHANNEL_MATRIX_INPUT;

typedef struct miosIE_PU_SERIAL_PORT{
	MIO_UINT32 type;

	MIO_UINT16 m_SerialPort;
	MIO_UINT32 m_BaudRate;
	MIO_UINT32 m_DataBit;
	MIO_UINT32 m_Parity;
	MIO_UINT32 m_StopBit;
	MIO_UINT32 m_Mode;
	MIO_UINT32 m_FlowControl;
	MIO_CHAR m_DecoderType[33];
	MIO_CHAR m_DecoderAddress[33];
}miosIE_PU_SERIAL_PORT;

typedef struct miosIE_PU_INPUT{
	MIO_UINT32 type;

	MIO_UINT16 m_ChannelNumber;
	MIO_UINT8 m_State;
}miosIE_PU_INPUT;

typedef struct miosIE_PU_OUTPUT{
	MIO_UINT32 type;

	MIO_UINT16 m_ChannelNumber;
	MIO_UINT8 m_State;
}miosIE_PU_OUTPUT;

typedef struct miosIE_IMAGE_ENCODE_PARA{
	MIO_UINT32 type;

	MIO_UINT16 m_VideoId;
	MIO_UINT8 m_EncodeMode;
	MIO_UINT8 m_PicQuality;
	MIO_UINT16 m_BitRate;
	MIO_UINT8 m_BitRateType;
	MIO_UINT8 m_FrameRate;
	MIO_UINT8 m_ImageSize;
	MIO_UINT8 m_StreamType;
	MIO_UINT16 m_IFrameInterval;
	MIO_UINT16 m_ChannelMode;
}miosIE_IMAGE_ENCODE_PARA;

typedef struct miosIE_IMAGE_DISPLAY_PARA{
	MIO_UINT32 type;

	MIO_UINT16 m_VideoId;
	MIO_UINT8 m_Contrast;
	MIO_UINT8 m_Bright;
	MIO_UINT8 m_Hue;
	MIO_UINT8 m_Saturation;
}miosIE_IMAGE_DISPLAY_PARA;

typedef struct miosIE_IMAGE_TEXT_PARA{
	MIO_UINT32 type;

	MIO_UINT16 m_VideoId;
	MIO_UINT32 m_bitmapX;
	MIO_UINT32 m_bitmapY;
	MIO_UINT8 m_bitmapTimeEnable;
	MIO_UINT8 m_bitmapTextEnable;
	MIO_CHAR m_bitmapText[129];
	MIO_UINT32 m_bitmapTextX;
	MIO_UINT32 m_bitmapTextY;
}miosIE_IMAGE_TEXT_PARA;

typedef struct miosIE_PU_BASEINFO{
	MIO_UINT32 type;

	MIO_CHAR m_ID[19];
	MIO_CHAR m_DomainID[7];
	MIO_CHAR m_Name[33];
	MIO_CHAR m_IP[41];
	MIO_UINT8 m_DeviceType;
	MIO_UINT32 m_PlatformManufactureID;
	MIO_UINT16 m_ManufactureID;
	MIO_UINT8 m_VideoInNum;
	MIO_UINT8 m_VideoOutNum;
	MIO_UINT8 m_AudioInNum;
	MIO_UINT8 m_AudioOutNum;
	MIO_UINT8 m_AlarmInNum;
	MIO_UINT8 m_AlarmOutNum;
	MIO_UINT8 m_NonStandardNum;
	MIO_UINT8 m_MatrixNum;
}miosIE_PU_BASEINFO;

typedef struct miosIE_CHANNEL_PRIVILEGE{
	MIO_UINT32 type;

	MIO_UINT16 m_channel_type;
	MIO_UINT16 m_channel_no;
	MIO_UINT8 m_priv;
}miosIE_CHANNEL_PRIVILEGE;

typedef struct miosIE_CHANNEL_INFO{
	MIO_UINT32 type;

	MIO_UINT8 m_direction;
	MIO_UINT8 m_qos;
	MIO_UINT8 m_payload;
	MIO_UINT8 m_resolution;
	MIO_UINT16 m_frame;
	MIO_UINT16 m_frame_interval;
	MIO_UINT32 m_time;
	MIO_UINT32 m_max_bitrate;
}miosIE_CHANNEL_INFO;

typedef struct miosIE_CHANNEL_BASEINFO{
	MIO_UINT32 type;

	MIO_UINT16 m_ChannelType;
	MIO_UINT16 m_ChannelNo;
	MIO_CHAR m_ChannelName[33];
	MIO_UINT16 m_VideoNo;
	MIO_UINT32 m_UserRight;
	MIO_DOUBLE m_Longitude;
	MIO_DOUBLE m_Latitude;
	MIO_UINT16 m_OrderState;
	MIO_CHAR m_DeviceType[129];
	MIO_CHAR m_DeviceID[19];
}miosIE_CHANNEL_BASEINFO;

typedef struct miosIE_CHANNEL_ID{
	MIO_UINT32 type;

	MIO_UINT8 m_channel_type;
	MIO_UINT16 m_channel_no;
}miosIE_CHANNEL_ID;

typedef struct miosIE_PLATFORM{
	MIO_UINT32 type;

	MIO_UINT32 m_PlatformManufactureID;
}miosIE_PLATFORM;

typedef struct miosIEX_PTZID{
	MIO_UINT32 type;

	MIO_UINT16 m_ptzId;
}miosIEX_PTZID;

typedef struct miosIE_CRUISEPOINT{
	MIO_UINT32 type;

	MIO_UINT16 m_presetIndex;
	MIO_UINT32 m_dwellTime;
	MIO_UINT8 m_Speed;
}miosIE_CRUISEPOINT;

typedef struct miosIEX_CRUISENUMBER{
	MIO_UINT32 type;

	MIO_UINT16 m_cruiseNumber;
}miosIEX_CRUISENUMBER;

typedef struct miosIE_PRESET_PTZ{
	MIO_UINT32 type;

	MIO_UINT16 m_ptzId;
	MIO_UINT16 m_presetIndex;
	MIO_CHAR m_presetName[33];
}miosIE_PRESET_PTZ;

typedef struct miosIEX_PTZ_MODE{
	MIO_UINT32 type;

	MIO_UINT8 m_PTZmode;
	MIO_UINT32 m_PTZTimeSlot;
}miosIEX_PTZ_MODE;

typedef struct miosIE_PU_DEVICE_STATE{
	MIO_UINT32 type;

	MIO_UINT8 m_deviceStatus;
}miosIE_PU_DEVICE_STATE;

typedef struct miosIE_PU_CAPACITY_STATE{
	MIO_UINT32 type;

	MIO_CHAR m_PU_MaxCapacity[33];
	MIO_CHAR m_PU_CurrCapacity[33];
	MIO_CHAR m_PU_MaxRecordStreams[33];
	MIO_CHAR m_PU_MaxVodStreams[33];
}miosIE_PU_CAPACITY_STATE;

typedef struct miosIE_PU_DISK_STATE{
	MIO_UINT32 type;

	MIO_UINT16 m_diskId;
	MIO_CHAR m_totalSize[33];
	MIO_CHAR m_freeSize[33];
	MIO_UINT8 m_status;
}miosIE_PU_DISK_STATE;

typedef struct miosIE_VIDEO_CHANNEL_STATE{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT8 m_recordStatus;
	MIO_UINT8 m_signalStatus;
	MIO_UINT8 m_hardwareStatus;
	MIO_CHAR m_bitRate[33];
}miosIE_VIDEO_CHANNEL_STATE;

typedef struct miosIE_ALARM_IN_STATE{
	MIO_UINT32 type;

	MIO_UINT16 m_channelNumber;
	MIO_UINT8 m_status;
}miosIE_ALARM_IN_STATE;

typedef struct miosIE_ALARM_OUT_STATE{
	MIO_UINT32 type;

	MIO_UINT16 m_channelNumber;
	MIO_UINT8 m_status;
}miosIE_ALARM_OUT_STATE;

typedef struct miosIEX_ALARM_CONFIG_TYPE{
	MIO_UINT32 type;

	MIO_UINT8 m_alarmConfigType;
}miosIEX_ALARM_CONFIG_TYPE;

typedef struct miosIE_DISK_PARA{
	MIO_UINT32 type;

	MIO_UINT8 m_diskFullAlarmEnabled;
	MIO_UINT8 m_diskFullHighThreshold;
	MIO_UINT8 m_diskFullLowThreshold;
	MIO_UINT8 m_diskErrorAlarmEnabled;
}miosIE_DISK_PARA;

typedef struct miosIE_ALARM_RECORD{
	MIO_UINT32 type;

	MIO_UINT8 m_alarmPreRecordTime;
	MIO_UINT32 m_alarmRecordTime;
}miosIE_ALARM_RECORD;

typedef struct miosIE_CAP_PHOTO{
	MIO_UINT32 type;

	MIO_INT8 m_photoResolution;
	MIO_UINT8 m_photoQuality;
	MIO_INT8 m_shootTimes;
}miosIE_CAP_PHOTO;

typedef struct miosIE_GPIN_ALARM{
	MIO_UINT32 type;

	MIO_UINT16 m_channelNumber;
	MIO_UINT8 m_gpinAlarmEnabled;
	MIO_UINT8 m_gpinAlarmStatus;
	MIO_CHAR m_alarmOutputActivatedTime[321];
	MIO_CHAR m_gpinAlarmOutput[257];
	MIO_CHAR m_gpinAlarmRecord[257];
	MIO_CHAR m_gpinAlarmShoot[257];
}miosIE_GPIN_ALARM;

typedef struct miosIE_VIDEO_LOSE_ALARM{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT8 m_videoLoseAlarmEnabled;
	MIO_CHAR m_videoLoseAlarmTime[321];
	MIO_CHAR m_videoLoseAlarmOutput[257];
	MIO_CHAR m_videoLoseAlarmRecord[257];
	MIO_CHAR m_videoLoseAlarmShoot[257];
}miosIE_VIDEO_LOSE_ALARM;

typedef struct miosIE_VIDEO_HIDE_ALARM{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT8 m_hideDetectionAlarmEnabled;
	MIO_CHAR m_hideDetectionAlarmTime[321];
	MIO_UINT32 m_hideDetectionX;
	MIO_UINT32 m_hideDetectionY;
	MIO_UINT32 m_hideDetectionWidth;
	MIO_UINT32 m_hideDetectionHeight;
	MIO_CHAR m_hideDetectionAlarmOutput[257];
	MIO_CHAR m_hideDetectionAlarmRecord[257];
}miosIE_VIDEO_HIDE_ALARM;

typedef struct miosIE_VIDEO_MOVE_ALARM{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT8 m_motionDetectionAlarmEnabled;
	MIO_CHAR m_motionDetectionAlarmTime[321];
	MIO_CHAR m_motionDetectionBlocks[513];
	MIO_UINT32 m_motionDetectionFrequency;
	MIO_UINT8 m_motionDetectionSensitivity;
	MIO_CHAR m_motionDetectionAlarmOutput[257];
	MIO_CHAR m_motionDetectionAlarmRecord[257];
	MIO_CHAR m_motionDetectionAlarmShoot[257];
}miosIE_VIDEO_MOVE_ALARM;

typedef struct miosIE_NODE_ONLINE{
	MIO_UINT32 type;

	MIO_CHAR m_NID[19];
	MIO_CHAR m_NodeName[33];
	MIO_UINT8 m_Online;
}miosIE_NODE_ONLINE;

typedef struct miosIEX_NPU_EXTRA{
	MIO_UINT32 type;

	MIO_CHAR m_user[33];
	MIO_CHAR m_passwd[33];
	MIO_CHAR m_path[129];
}miosIEX_NPU_EXTRA;

typedef struct miosIEX_HARDDISK_FOR_PU{
	MIO_UINT32 type;

	MIO_CHAR m_PUId[19];
	MIO_UINT16 m_ChannelNo;
	MIO_UINT16 m_TotalCapacity;
	MIO_UINT16 m_AvailCapacity;
	MIO_UINT8 m_StorePolicy;
}miosIEX_HARDDISK_FOR_PU;

typedef struct miosIEX_VIDEO_ENCODE{
	MIO_UINT32 type;

	MIO_UINT8 m_Encode_Format;
	MIO_UINT16 m_Encode_Bitrate;
	MIO_UINT8 m_Video_ABR;
	MIO_UINT8 m_Channel_Mode;
	MIO_UINT8 m_Encode_Framerate;
	MIO_UINT8 m_Encode_IPinterval;
	MIO_UINT8 m_Encode_Initquant;
	MIO_UINT8 m_Encode_Withaudio;
	MIO_CHAR m_Region[17];
}miosIEX_VIDEO_ENCODE;

typedef struct miosIEX_VIDEO_OSD{
	MIO_UINT32 type;

	MIO_UINT16 m_ChannelNo;
	MIO_UINT8 m_OSD_Enable;
	MIO_UINT32 m_X_POS;
	MIO_UINT32 m_Y_POS;
	MIO_UINT8 m_OSD_Type;
	MIO_CHAR m_OSD_Message[33];
}miosIEX_VIDEO_OSD;

typedef struct miosIEX_MOTION_DETECT_REGION{
	MIO_UINT32 type;

	MIO_UINT16 m_ChannelNo;
	MIO_UINT16 m_Region_Index;
	MIO_UINT8 m_Enable;
	MIO_UINT32 m_Frame_Interval;
	MIO_UINT32 m_Vector_Threshold;
	MIO_UINT16 m_SAD_Threshold;
	MIO_UINT16 m_DEV_Threshold;
	MIO_UINT16 m_Alarm_Threshold;
	MIO_UINT32 m_Region_x0;
	MIO_UINT32 m_Region_y0;
	MIO_UINT32 m_Region_x1;
	MIO_UINT32 m_Region_y1;
}miosIEX_MOTION_DETECT_REGION;

typedef struct miosIEX_ALARM_ACTION{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[19];
	MIO_UINT32 m_Action;
	MIO_UINT16 m_Image_Num;
	MIO_CHAR m_Ftp_IP[41];
	MIO_CHAR m_Ftp_User[17];
	MIO_CHAR m_Ftp_Pwd[17];
	MIO_CHAR m_Ftp_Path[33];
	MIO_UINT8 m_Location;
}miosIEX_ALARM_ACTION;

typedef struct miosIE_AUDIO_ENCODE_PARA{
	MIO_UINT32 type;

	MIO_UINT16 m_VideoId;
	MIO_UINT8 m_EncodeMode;
	MIO_UINT16 m_Encode_Samplerate;
	MIO_UINT16 m_Encode_Bitrate;
	MIO_UINT8 m_Track_No;
	MIO_UINT8 m_Quan_Bitrate;
}miosIE_AUDIO_ENCODE_PARA;

typedef struct miosIEX_AUDIO_ENCODE{
	MIO_UINT32 type;

	MIO_UINT8 m_Encode_Mode;
	MIO_UINT16 m_Encode_Samplerate;
	MIO_UINT16 m_Encode_Bitrate;
	MIO_UINT8 m_Track_No;
	MIO_UINT8 m_Quan_Bitrate;
}miosIEX_AUDIO_ENCODE;

typedef struct miosIEX_PU_ONLINE{
	MIO_UINT32 type;

	MIO_CHAR m_NID[19];
	MIO_CHAR m_NodeName[33];
	MIO_UINT8 m_Online;
	MIO_UINT8 m_DeviceType;
	MIO_CHAR m_DeviceTypeName[33];
	MIO_UINT16 m_ChannelNum;
	MIO_UINT64 m_GroupID;
	MIO_CHAR m_GroupName[33];
	MIO_CHAR m_Addr[41];
	MIO_UINT16 m_Port;
	MIO_DOUBLE m_Longitude;
	MIO_DOUBLE m_Latitude;
}miosIEX_PU_ONLINE;

typedef struct miosIEX_POLL_ENABLE{
	MIO_UINT32 type;

	MIO_UINT8 m_Polling_Enable;
	MIO_UINT8 m_Audio_flags;
}miosIEX_POLL_ENABLE;

typedef struct miosIEX_PU_PARA_TYPE{
	MIO_UINT32 type;

	MIO_UINT8 m_TYPE;
}miosIEX_PU_PARA_TYPE;

typedef struct miosIEX_COVER_DETECT_REGION{
	MIO_UINT32 type;

	MIO_UINT16 m_ChannelNo;
	MIO_UINT16 m_Region_Index;
	MIO_UINT8 m_Enable;
	MIO_UINT32 m_Region_x0;
	MIO_UINT32 m_Region_y0;
	MIO_UINT32 m_Region_x1;
	MIO_UINT32 m_Region_y1;
}miosIEX_COVER_DETECT_REGION;

typedef struct miosIEX_COVER_REGION{
	MIO_UINT32 type;

	MIO_UINT16 m_ChannelNo;
	MIO_UINT16 m_Region_Index;
	MIO_UINT8 m_Enable;
	MIO_UINT32 m_Region_x0;
	MIO_UINT32 m_Region_y0;
	MIO_UINT32 m_Region_x1;
	MIO_UINT32 m_Region_y1;
}miosIEX_COVER_REGION;

typedef struct miosIEX_PU_GROUP{
	MIO_UINT32 type;

	MIO_UINT64 m_GroupID;
	MIO_CHAR m_GroupName[33];
	MIO_UINT64 m_ParentID;
}miosIEX_PU_GROUP;

typedef struct miosIE_LOG_QUERY{
	MIO_UINT32 type;

	MIO_UINT8 m_logType;
	MIO_TIME m_startLogDate;
	MIO_TIME m_endLogDate;
	MIO_UINT32 m_startIndex;
	MIO_UINT32 m_maxResults;
}miosIE_LOG_QUERY;

typedef struct miosIE_LOG_QUERY_RESULT{
	MIO_UINT32 type;

	MIO_UINT8 m_logType;
	MIO_TIME m_logTime;
	MIO_CHAR m_netUser[33];
	MIO_UINT16 m_videoId;
	MIO_UINT16 m_diskNumber;
	MIO_UINT16 m_AlarmInPort;
	MIO_UINT16 m_AlarmOutPort;
}miosIE_LOG_QUERY_RESULT;

typedef struct miosIEX_STORAGE_TASK{
	MIO_UINT32 type;

	MIO_CHAR m_taskName[33];
	MIO_UINT8 m_taskType;
	MIO_UINT8 m_taskPolicy;
	MIO_CHAR m_stroageCapacity[33];
	MIO_CHAR m_DeviceInfo[257];
	MIO_CHAR m_startTime[33];
	MIO_CHAR m_endTime[33];
	MIO_UINT8 m_mediaType;
	MIO_CHAR m_mediaFormat[33];
}miosIEX_STORAGE_TASK;

typedef struct miosIEX_STORAGE_TASK_ID{
	MIO_UINT32 type;

	MIO_CHAR m_storageTaskId[33];
}miosIEX_STORAGE_TASK_ID;

typedef struct miosIE_NPU_SERVER{
	MIO_UINT32 type;

	MIO_CHAR m_address[129];
}miosIE_NPU_SERVER;

typedef struct miosIE_PHOTO_INFO{
	MIO_UINT32 type;

	MIO_CHAR m_fileName[129];
	MIO_TIME m_capTime;
	MIO_UINT8 m_capType;
	MIO_UINT32 m_fileSize;
}miosIE_PHOTO_INFO;

typedef struct miosIE_LOCAL_STORAGE_TASK{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_CHAR m_schedule[33];
	MIO_UINT8 m_recycleRecEnable;
	MIO_UINT8 m_recordPolicy;
	MIO_UINT8 m_frameInterval;
	MIO_CHAR m_filenameSuffix[33];
	MIO_UINT8 m_recordEnable;
}miosIE_LOCAL_STORAGE_TASK;

typedef struct miosIEX_NRU_CAPACITY{
	MIO_UINT32 type;

	MIO_CHAR m_NRU_MaxCapacity[33];
	MIO_CHAR m_NRU_MaxRecordStreams[33];
	MIO_CHAR m_NRU_MaxVodStreams[33];
}miosIEX_NRU_CAPACITY;

typedef struct miosIEX_NRU_STATUS{
	MIO_UINT32 type;

	MIO_CHAR m_NruID[19];
	MIO_UINT32 m_MaxCapacity;
	MIO_UINT32 m_CurrCapacity;
	MIO_UINT32 m_MaxRecordStreams;
	MIO_UINT32 m_CurrRecordStreams;
	MIO_UINT32 m_MaxVodStreams;
	MIO_UINT32 m_CurrVodStreams;
}miosIEX_NRU_STATUS;

typedef struct miosIEX_NRU_PARA{
	MIO_UINT32 type;

	MIO_CHAR m_NRU_CurrCapacity[33];
	MIO_CHAR m_NRU_CurrRecordStreams[33];
	MIO_CHAR m_NRU_CurrVodStreams[33];
}miosIEX_NRU_PARA;

typedef struct miosIEX_VTDU_CAPACITY{
	MIO_UINT32 type;

	MIO_CHAR m_VTDU_MaxCapacity[33];
}miosIEX_VTDU_CAPACITY;

typedef struct miosIEX_VTDU_STATUS{
	MIO_UINT32 type;

	MIO_CHAR m_VTDU_CurrCapacity[33];
}miosIEX_VTDU_STATUS;

typedef struct miosIEX_VTDU_PARA{
	MIO_UINT32 type;

	MIO_CHAR m_VTDU_MaxCapacity[33];
	MIO_CHAR m_VTDU_MaxRecordStreams[33];
	MIO_CHAR m_VTDU_MaxVodStreams[33];
}miosIEX_VTDU_PARA;

typedef struct miosIEX_CU_STATUS{
	MIO_UINT32 type;

	MIO_UINT32 m_CU_VideoCallNum;
	MIO_UINT32 m_CU_AudioCallNum;
}miosIEX_CU_STATUS;

typedef struct miosIE_PU_STATE{
	MIO_UINT32 type;

	MIO_UINT8 m_deviceStatus;
}miosIE_PU_STATE;

typedef struct miosIE_PU_STATUS{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[19];
	MIO_UINT16 m_ChannelID;
	MIO_UINT8 m_CallStatus;
}miosIE_PU_STATUS;

typedef struct miosIE_PU_LIST_ID{
	MIO_UINT32 type;

	MIO_UINT32 m_PUListID;
}miosIE_PU_LIST_ID;

typedef struct miosIEX_VTDU_ROUTE_MODE{
	MIO_UINT32 type;

	MIO_UINT8 m_RouteVtduAll;
	MIO_UINT8 m_Vtdumode;
	MIO_UINT16 m_CallNum;
}miosIEX_VTDU_ROUTE_MODE;

typedef struct miosIEX_PHOTO_INFO{
	MIO_UINT32 type;

	MIO_CHAR m_matchId[33];
	MIO_UINT32 m_jpgFlag;
	MIO_CHAR m_fileName[129];
	MIO_UINT32 m_fileWidth;
	MIO_UINT32 m_fileHeight;
}miosIEX_PHOTO_INFO;

typedef struct miosIEX_PU_STATUS{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[19];
	MIO_UINT16 m_ChannelID;
	MIO_UINT32 m_MaxCapacity;
	MIO_UINT32 m_CurrCapacity;
	MIO_UINT32 m_MaxRecordStreams;
	MIO_UINT32 m_CurrRecordStreams;
	MIO_UINT32 m_MaxVodStreams;
	MIO_UINT32 m_CurrVodStreams;
}miosIEX_PU_STATUS;

typedef struct miosIEX_RECORD_MGR{
	MIO_UINT32 type;

	MIO_UINT32 m_RecordMgr;
}miosIEX_RECORD_MGR;

typedef struct miosIEX_ALARM_ID{
	MIO_UINT32 type;

	MIO_CHAR m_AlarmId[33];
}miosIEX_ALARM_ID;

typedef struct miosIEX_THRESHOLD{
	MIO_UINT32 type;

	MIO_UINT32 m_ThresHoldType;
	MIO_UINT32 m_ThresHoldValue;
}miosIEX_THRESHOLD;

typedef struct miosIEX_VIDEO_PACKET_INFO{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[19];
	MIO_INT32 m_ChannelNo;
	MIO_UINT64 m_TotalRcvPacket;
	MIO_UINT64 m_TotalLostPacket;
}miosIEX_VIDEO_PACKET_INFO;

typedef struct miosIEX_ALARM_PRESET{
	MIO_UINT32 type;

	MIO_UINT8 m_Op;
	MIO_UINT16 m_AlarmType;
	MIO_UINT16 m_PresetId;
}miosIEX_ALARM_PRESET;

typedef struct miosIEX_DEFAULT_PRESET{
	MIO_UINT32 type;

	MIO_UINT32 m_ResetTime;
	MIO_UINT16 m_PresetId;
}miosIEX_DEFAULT_PRESET;

typedef struct miosIEX_PARAM_PAIR{
	MIO_UINT32 type;

	MIO_CHAR m_name[33];
	MIO_CHAR m_value[129];
}miosIEX_PARAM_PAIR;

typedef struct miosIE_STORAGE_TASK{
	MIO_UINT32 type;

	MIO_UINT16 m_taskPolicy;
	MIO_CHAR m_stroageCapacity[33];
	MIO_INT32 m_timeSlice;
	MIO_UINT16 m_recordPolicy;
	MIO_INT32 m_frameInterval;
	MIO_CHAR m_filenameSuffix[33];
	MIO_UINT16 m_mediaType;
	MIO_CHAR m_mediaFormat[33];
	MIO_CHAR m_startTime[33];
	MIO_CHAR m_endTime[33];
}miosIE_STORAGE_TASK;

typedef struct miosIE_SCHEDULE{
	MIO_UINT32 type;

	MIO_CHAR m_schedule[321];
}miosIE_SCHEDULE;

typedef struct miosIEX_NETWORK_PARA{
	MIO_UINT32 type;

	MIO_CHAR m_IPAddress[41];
	MIO_CHAR m_SubMask[41];
	MIO_CHAR m_Gateway[41];
	MIO_UINT8 m_DHCPEnable;
	MIO_CHAR m_PPPOEUsername[41];
	MIO_CHAR m_PPPOEPasswd[41];
	MIO_CHAR m_DNSPreferred[41];
	MIO_CHAR m_DNSReserved[41];
}miosIEX_NETWORK_PARA;

typedef struct miosIEX_NRU_SELECTION{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[33];
	MIO_CHAR m_NRUID[33];
}miosIEX_NRU_SELECTION;

typedef struct miosIEX_PU_ACCESS_SERVER{
	MIO_UINT32 type;

	MIO_CHAR m_address[65];
	MIO_UINT16 m_port;
}miosIEX_PU_ACCESS_SERVER;

typedef struct miosIEX_NET_MANAGER_SERVER{
	MIO_UINT32 type;

	MIO_CHAR m_address[65];
	MIO_UINT16 m_port;
}miosIEX_NET_MANAGER_SERVER;

typedef struct miosIEX_MAX_VIDEO_CONNECTION_NUM{
	MIO_UINT32 type;

	MIO_UINT16 m_max_video_connection_num;
}miosIEX_MAX_VIDEO_CONNECTION_NUM;

typedef struct miosIE_NETLINK{
	MIO_UINT32 type;

	MIO_UINT8 m_AddType;
	MIO_UINT8 m_AddrType;
	MIO_CHAR m_Address[41];
	MIO_UINT16 m_Port;
	MIO_UINT8 m_ConnectType;
	MIO_UINT8 m_TransType;
}miosIE_NETLINK;

typedef struct miosIE_OPEN_VIDEO{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[19];
	MIO_UINT16 m_ChannelNo;
	MIO_UINT8 m_MeidaType;
	MIO_UINT8 m_TransMode;
	MIO_UINT8 m_ReqReason;
	MIO_UINT8 m_MediaType;
	MIO_UINT8 m_TransType;
}miosIE_OPEN_VIDEO;

typedef struct miosIE_OPEN_VIDEO_ACK{
	MIO_UINT32 type;

	MIO_UINT8 m_MeidiaType;
	MIO_UINT8 m_VidEncode;
	MIO_UINT16 m_VidWidth;
	MIO_UINT16 m_VidHight;
	MIO_UINT8 m_VidFormat;
	MIO_UINT8 m_VidFrameRate;
	MIO_UINT8 m_AudEncode;
	MIO_UINT16 m_AudSamping;
	MIO_UINT16 m_AudBitRate;
	MIO_UINT8 m_AudTrack;
	MIO_UINT32 m_DeviceTypeIndex;
}miosIE_OPEN_VIDEO_ACK;

typedef struct miosIE_VIDEO_CHANNEL{
	MIO_UINT32 type;

	MIO_UINT16 m_ChannelNo;
	MIO_CHAR m_Name[33];
	MIO_UINT8 m_Mode;
	MIO_CHAR m_Address[41];
	MIO_UINT16 m_Port;
	MIO_UINT8 m_VideoFlag;
	MIO_UINT8 m_AudioFlag;
}miosIE_VIDEO_CHANNEL;

typedef struct miosIE_CHANNEL_YUNTAI_SET{
	MIO_UINT32 type;

	MIO_CHAR m_YUNTAI_ADDRESS_CODE[17];
	MIO_UINT16 m_DECODER;
	MIO_UINT16 m_MatrixInputNo;
}miosIE_CHANNEL_YUNTAI_SET;

typedef struct miosIE_PORT_RANGE{
	MIO_UINT32 type;

	MIO_UINT16 m_min_port;
	MIO_UINT16 m_max_port;
}miosIE_PORT_RANGE;

typedef struct miosIE_UA_REAL_IP{
	MIO_UINT32 type;

	MIO_CHAR m_value[16];
}miosIE_UA_REAL_IP;

typedef struct miosIE_URL{
	MIO_UINT32 type;

	MIO_CHAR m_value[255];
}miosIE_URL;

typedef struct miosIE_SCHEDULE_NOTIFY{
	MIO_UINT32 type;

	MIO_UINT8 m_reserve;
	MIO_UINT8 m_direction;
	MIO_UINT8 m_transport;
	MIO_UINT8 m_action;
	MIO_CHAR m_addr[16];
	MIO_UINT16 m_port;
	MIO_UINT8 m_trans_type;
	MIO_UINT8 m_ip_addr_reserve;
	MIO_CHAR m_actid[33];
}miosIE_SCHEDULE_NOTIFY;

typedef struct miosIE_NETLINK_PRE{
	MIO_UINT32 type;

	MIO_UINT8 m_AddType;
	MIO_UINT8 m_AddrType;
	MIO_CHAR m_Address[41];
	MIO_UINT16 m_Port;
	MIO_UINT8 m_ConnectType;
	MIO_UINT8 m_TransType;
}miosIE_NETLINK_PRE;

typedef struct miosIE_NETLINK_NEXT{
	MIO_UINT32 type;

	MIO_UINT8 m_AddType;
	MIO_UINT8 m_AddrType;
	MIO_CHAR m_Address[41];
	MIO_UINT16 m_Port;
	MIO_UINT8 m_ConnectType;
	MIO_UINT8 m_TransType;
}miosIE_NETLINK_NEXT;

typedef struct miosIE_CALL_ID{
	MIO_UINT32 type;

	MIO_CHAR m_CallId[17];
}miosIE_CALL_ID;

typedef struct miosIEX_CALL_INFO{
	MIO_UINT32 type;

	MIO_CHAR m_SessionID[17];
	MIO_UINT8 m_SessionStatus;
	MIO_UINT64 m_CallIdPre;
	MIO_UINT64 m_CallIdNext;
}miosIEX_CALL_INFO;

typedef struct miosIEX_CALL_ID{
	MIO_UINT32 type;

	MIO_CHAR m_CallId[17];
}miosIEX_CALL_ID;

typedef struct miosIEX_ROUTE_INFO{
	MIO_UINT32 type;

	MIO_CHAR m_NID[19];
	MIO_UINT8 m_NodeType;
	MIO_UINT8 m_RouteType;
	MIO_UINT8 m_AddType;
	MIO_CHAR m_Address[41];
	MIO_UINT16 m_Port;
	MIO_UINT8 m_ConnectType;
	MIO_UINT8 m_TransType;
}miosIEX_ROUTE_INFO;

typedef struct miosIEX_CALL_FLAG{
	MIO_UINT32 type;

	MIO_UINT8 m_Flag;
}miosIEX_CALL_FLAG;

typedef struct miosIEX_FTP_LOG_INFO{
	MIO_UINT32 type;

	MIO_CHAR m_Ftp_addr[65];
	MIO_UINT16 m_Ftp_port;
	MIO_CHAR m_Ftp_name[65];
	MIO_CHAR m_Ftp_password[65];
	MIO_UINT32 m_Ftp_timeout;
	MIO_CHAR m_Ftp_folder[129];
}miosIEX_FTP_LOG_INFO;

typedef struct miosIEX_MEDIA_FROM{
	MIO_UINT32 type;

	MIO_UINT8 m_AddrType;
	MIO_CHAR m_VideoAddress[41];
	MIO_CHAR m_AudioAddress[41];
	MIO_UINT16 m_VideoSendPort;
	MIO_UINT16 m_VideoRcvPort;
	MIO_UINT16 m_AudioSendPort;
	MIO_UINT16 m_AudioRcvPort;
	MIO_UINT8 m_ConnectType;
	MIO_UINT8 m_TransType;
}miosIEX_MEDIA_FROM;

typedef struct miosIEX_MEDIA_TO{
	MIO_UINT32 type;

	MIO_UINT8 m_AddrType;
	MIO_CHAR m_VideoAddress[41];
	MIO_CHAR m_AudioAddress[41];
	MIO_UINT16 m_VideoSendPort;
	MIO_UINT16 m_VideoRcvPort;
	MIO_UINT16 m_AudioSendPort;
	MIO_UINT16 m_AudioRcvPort;
	MIO_UINT8 m_ConnectType;
	MIO_UINT8 m_TransType;
}miosIEX_MEDIA_TO;

typedef struct miosIEX_MEDIA_PARA{
	MIO_UINT32 type;

	MIO_UINT8 m_MediaType;
	MIO_UINT8 m_VidEncode;
	MIO_UINT16 m_VidWidth;
	MIO_UINT16 m_VidHight;
	MIO_UINT8 m_VidFormat;
	MIO_UINT8 m_VidFrameRate;
	MIO_UINT32 m_VidBitRate;
	MIO_UINT8 m_AudEncode;
	MIO_UINT16 m_AudSamping;
	MIO_UINT16 m_AudBitRate;
	MIO_UINT8 m_AudTrack;
	MIO_UINT32 m_DeviceTypeIndex;
}miosIEX_MEDIA_PARA;

typedef struct miosIEX_MONITOR_CHANNEL{
	MIO_UINT32 type;

	MIO_UINT8 m_channel_type;
	MIO_UINT16 m_channel_no;
	MIO_CHAR m_channel_name[33];
	MIO_UINT32 m_DeviceExist;
	MIO_UINT32 m_UseStarttime;
	MIO_UINT32 m_UseTime;
	MIO_UINT8 m_Priority;
	MIO_UINT32 m_UserRight;
	MIO_CHAR m_Region[12];
	MIO_UINT16 m_video_in_no;
	MIO_UINT16 m_video_out_no;
	MIO_UINT16 m_audio_in_no;
	MIO_UINT16 m_audio_out_no;
	MIO_UINT16 m_switch_in_no;
	MIO_UINT16 m_switch_out_no;
	MIO_UINT16 m_ptz_no;
}miosIEX_MONITOR_CHANNEL;

typedef struct miosIEX_MEDIA_RCV{
	MIO_UINT32 type;

	MIO_UINT8 m_AddrType;
	MIO_CHAR m_VideoAddress[41];
	MIO_CHAR m_AudioAddress[41];
	MIO_UINT16 m_VideoSendPort;
	MIO_UINT16 m_VideoRcvPort;
	MIO_UINT16 m_AudioSendPort;
	MIO_UINT16 m_AudioRcvPort;
	MIO_UINT8 m_ConnectType;
	MIO_UINT8 m_TransType;
}miosIEX_MEDIA_RCV;

typedef struct miosIEX_MEDIA_RCV_CONVERSE{
	MIO_UINT32 type;

	MIO_UINT8 m_AddrType;
	MIO_CHAR m_VideoAddress[41];
	MIO_CHAR m_AudioAddress[41];
	MIO_UINT16 m_VideoSendPort;
	MIO_UINT16 m_VideoRcvPort;
	MIO_UINT16 m_AudioSendPort;
	MIO_UINT16 m_AudioRcvPort;
	MIO_UINT8 m_ConnectType;
	MIO_UINT8 m_TransType;
}miosIEX_MEDIA_RCV_CONVERSE;

typedef struct miosIEX_MEDIA_SEND{
	MIO_UINT32 type;

	MIO_UINT8 m_AddrType;
	MIO_CHAR m_VideoAddress[41];
	MIO_CHAR m_AudioAddress[41];
	MIO_UINT16 m_VideoSendPort;
	MIO_UINT16 m_VideoRcvPort;
	MIO_UINT16 m_AudioSendPort;
	MIO_UINT16 m_AudioRcvPort;
	MIO_UINT8 m_ConnectType;
	MIO_UINT8 m_TransType;
}miosIEX_MEDIA_SEND;

typedef struct miosIEX_MEDIA_SEND_CONVERSE{
	MIO_UINT32 type;

	MIO_UINT8 m_AddrType;
	MIO_CHAR m_VideoAddress[41];
	MIO_CHAR m_AudioAddress[41];
	MIO_UINT16 m_VideoSendPort;
	MIO_UINT16 m_VideoRcvPort;
	MIO_UINT16 m_AudioSendPort;
	MIO_UINT16 m_AudioRcvPort;
	MIO_UINT8 m_ConnectType;
	MIO_UINT8 m_TransType;
}miosIEX_MEDIA_SEND_CONVERSE;

typedef struct miosIEX_MEDIA_DIRECT{
	MIO_UINT32 type;

	MIO_UINT8 m_MediaDirect;
}miosIEX_MEDIA_DIRECT;

typedef struct miosIEX_MEDIA_PARA_PREV{
	MIO_UINT32 type;

	MIO_UINT8 m_MediaType;
}miosIEX_MEDIA_PARA_PREV;

typedef struct miosIEX_MEDIA_PARA_NEXT{
	MIO_UINT32 type;

	MIO_UINT8 m_MediaType;
}miosIEX_MEDIA_PARA_NEXT;

typedef struct miosIEX_ALARM_AUDIO_OUT{
	MIO_UINT32 type;

	MIO_UINT16 m_AudioOutId;
	MIO_UINT8 m_AudioAlarmEnable;
	MIO_UINT32 m_AlarmType;
	MIO_CHAR m_AudioAlarmFile[256];
}miosIEX_ALARM_AUDIO_OUT;

typedef struct miosIEX_PU_ACCESS_TYPE{
	MIO_UINT32 type;

	MIO_UINT8 m_AccessType;
	MIO_UINT8 m_AccessMode;
}miosIEX_PU_ACCESS_TYPE;

typedef struct miosIEX_STARTUP_MODE{
	MIO_UINT32 type;

	MIO_UINT8 m_StartupMode;
	MIO_UINT8 m_StartupInfo;
}miosIEX_STARTUP_MODE;

typedef struct miosIE_VCR_CONTROL{
	MIO_UINT32 type;

	MIO_UINT8 m_VCRAction;
	MIO_UINT16 m_Param;
}miosIE_VCR_CONTROL;

typedef struct miosIE_BCSH{
	MIO_UINT32 type;

	MIO_UINT8 m_Brightness;
	MIO_UINT8 m_Hue;
	MIO_UINT8 m_Saturation;
	MIO_UINT8 m_Contrast;
	MIO_UINT8 m_Whiteness;
}miosIE_BCSH;

typedef struct miosIE_ALARM_IN_CHANNEL{
	MIO_UINT32 type;

	MIO_UINT16 m_ChannelNo;
	MIO_CHAR m_Name[33];
	MIO_UINT8 m_Action;
	MIO_UINT16 m_WarnOutChannel;
	MIO_UINT16 m_VideoChannel;
	MIO_UINT8 m_DelayTime;
	MIO_UINT8 m_Enable;
	MIO_UINT16 m_Type;
}miosIE_ALARM_IN_CHANNEL;

typedef struct miosIE_ALARM_OUT_CHANNEL{
	MIO_UINT32 type;

	MIO_UINT16 m_ChannelNo;
	MIO_CHAR m_Name[33];
	MIO_UINT8 m_Action;
	MIO_UINT8 m_DelayTime;
	MIO_UINT8 m_Enable;
	MIO_UINT16 m_Type;
}miosIE_ALARM_OUT_CHANNEL;

typedef struct miosIE_ALARM_INFO{
	MIO_UINT32 type;

	MIO_UINT16 m_AlarmType;
	MIO_CHAR m_AlarmChannelName[33];
	MIO_UINT16 m_AlarmChannelType;
	MIO_UINT16 m_AlarmChannelNo;
	MIO_UINT16 m_VideoChannelNo;
	MIO_CHAR m_UserData[129];
	MIO_CHAR m_AlarmLevel[33];
}miosIE_ALARM_INFO;

typedef struct miosIEX_ALARM_SET{
	MIO_UINT32 type;

	MIO_CHAR m_DeviceID[19];
	MIO_UINT8 m_HardDiskAlarm;
	MIO_UINT16 m_HardSpareCapacity;
	MIO_UINT8 m_CallNumAlarm;
	MIO_UINT16 m_CallNum;
	MIO_UINT8 m_OtherAlarm;
}miosIEX_ALARM_SET;

typedef struct miosIEX_ALARM_OP{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[19];
	MIO_UINT16 m_ChannelNo;
	MIO_UINT8 m_Action;
	MIO_UINT8 m_MsgNot;
	MIO_UINT8 m_MailNot;
	MIO_UINT8 m_Record;
	MIO_UINT8 m_Type;
	MIO_CHAR m_ExtraInfo[129];
	MIO_UINT64 m_RecordTime;
	MIO_UINT32 m_PU_Action;
}miosIEX_ALARM_OP;

typedef struct miosIEX_ALARM_IN_CHANNEL{
	MIO_UINT32 type;

	MIO_UINT16 m_ChannelNo;
	MIO_CHAR m_Name[33];
	MIO_UINT8 m_Action;
	MIO_UINT16 m_WarnOutChannel;
	MIO_UINT16 m_VideoChannel;
	MIO_UINT8 m_DelayTime;
	MIO_UINT8 m_Enable;
	MIO_UINT16 m_Type;
	MIO_UINT16 m_WarnOutChannel2;
}miosIEX_ALARM_IN_CHANNEL;

typedef struct miosIEX_IO_CHANNEL{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[19];
	MIO_UINT16 m_ChannelNo;
	MIO_CHAR m_Name[33];
}miosIEX_IO_CHANNEL;

typedef struct miosIEX_ALARM_VIDEO_SET{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[19];
	MIO_UINT16 m_ChannelNo;
	MIO_UINT8 m_VideoLost;
	MIO_UINT8 m_VideoCover;
	MIO_UINT8 m_VideoMove;
	MIO_UINT16 m_WarnOutChannel;
	MIO_UINT8 m_DelayTime;
}miosIEX_ALARM_VIDEO_SET;

typedef struct miosIEX_ALARM_ENABLE{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[19];
	MIO_UINT8 m_AlarmEnable;
	MIO_UINT8 m_AlarmPeriod;
	MIO_CHAR m_startTime[33];
	MIO_CHAR m_endTime[33];
	MIO_UINT16 m_Image_Num;
	MIO_CHAR m_Ftp_IP[41];
	MIO_CHAR m_Ftp_User[17];
	MIO_CHAR m_Ftp_Pwd[17];
	MIO_CHAR m_Ftp_Path[33];
	MIO_UINT8 m_Location;
}miosIEX_ALARM_ENABLE;

typedef struct miosIEX_RECORD_FILE_INFO{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[19];
	MIO_UINT16 m_ChannelNo;
	MIO_CHAR m_RecordFileName[129];
	MIO_UINT32 m_FileSize;
	MIO_UINT8 m_FileType;
	MIO_UINT8 m_Operate;
	MIO_TIME m_StartTime;
	MIO_TIME m_EndTime;
	MIO_CHAR m_StoreLocation[65];
	MIO_CHAR m_AlarmId[33];
}miosIEX_RECORD_FILE_INFO;

typedef struct miosIEX_RECORD_PARAM_SET{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[19];
	MIO_UINT16 m_ChannelNo;
	MIO_UINT8 m_RecordMode;
	MIO_UINT8 m_RecordEvent;
	MIO_UINT8 m_RecordPeriod;
	MIO_UINT16 m_PreRecord;
	MIO_UINT16 m_SpareCapacity;
	MIO_UINT8 m_StorePolicy;
	MIO_UINT8 m_BackupType;
	MIO_UINT8 m_FileStore;
	MIO_UINT8 m_MediaType;
}miosIEX_RECORD_PARAM_SET;

typedef struct miosIE_STORELOCATION{
	MIO_UINT32 type;

	MIO_UINT8 m_Location;
}miosIE_STORELOCATION;

typedef struct miosIE_TIME_FILE{
	MIO_UINT32 type;

	MIO_UINT8 m_Flag;
	MIO_UINT8 m_Reserve;
	MIO_TIME m_BeginTime;
	MIO_TIME m_EndTime;
	MIO_CHAR m_Name[255];
	MIO_UINT64 m_Size;
	MIO_CHAR m_Address[41];
	MIO_UINT16 m_Port;
}miosIE_TIME_FILE;

typedef struct miosIE_TIMESPAN{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosIE_TIMESPAN;

typedef struct miosIEX_FILETYPE{
	MIO_UINT32 type;

	MIO_UINT8 m_FileType;
}miosIEX_FILETYPE;

typedef struct miosIE_RESULT{
	MIO_UINT32 type;

	MIO_UINT8 m_Value;
	MIO_UINT8 m_ErrorCode;
}miosIE_RESULT;

typedef struct miosIE_TIME_DETAIL_LIST{
	MIO_UINT32 type;

	MIO_UINT8 m_WorkDay;
	MIO_UINT8 m_BeginHour;
	MIO_UINT8 m_BeginMinute;
	MIO_UINT8 m_EndHour;
	MIO_UINT8 m_EndMinute;
}miosIE_TIME_DETAIL_LIST;

typedef struct miosIE_TIME{
	MIO_UINT32 type;

	MIO_UINT8 m_Mode;
	MIO_UINT16 m_Year;
	MIO_UINT8 m_Month;
	MIO_UINT8 m_Day;
	MIO_UINT8 m_Hour;
	MIO_UINT8 m_Minute;
	MIO_UINT8 m_Second;
}miosIE_TIME;

typedef struct miosIE_STORETYPE{
	MIO_UINT32 type;

	MIO_UINT16 m_StoreType;
}miosIE_STORETYPE;

typedef struct miosIE_STARTTIME{
	MIO_UINT32 type;

	MIO_TIME m_begin_time;
}miosIE_STARTTIME;

typedef struct miosIE_ENDTIME{
	MIO_UINT32 type;

	MIO_TIME m_end_time;
}miosIE_ENDTIME;

typedef struct miosIE_BEGINTIME{
	MIO_UINT32 type;

	MIO_TIME m_BeginTime;
	MIO_TIME m_EndTime;
}miosIE_BEGINTIME;

typedef struct miosIE_FILEITEM{
	MIO_UINT32 type;

	MIO_UINT32 m_From;
	MIO_UINT32 m_To;
	MIO_UINT8 m_Arrange;
}miosIE_FILEITEM;

typedef struct miosIE_TIME_STRING{
	MIO_UINT32 type;

	MIO_TIME m_timeString;
}miosIE_TIME_STRING;

typedef struct miosIEX_LOG_INFO{
	MIO_UINT32 type;

	MIO_UINT8 m_LogType;
	MIO_TIME m_LogTime;
	MIO_UINT8 m_LogEvent;
	MIO_CHAR m_LogObjectID[19];
	MIO_UINT16 m_LogChannel;
	MIO_UINT16 m_LogInfo;
	MIO_CHAR m_LogDesp[256];
	MIO_CHAR m_AlarmID[33];
	MIO_CHAR m_AlarmLevel[33];
}miosIEX_LOG_INFO;

typedef struct miosIEX_MEDIA_INFO{
	MIO_UINT32 type;

	MIO_CHAR m_MediaFileName[126];
	MIO_UINT64 m_MediaBeginTime;
	MIO_UINT64 m_MediaEndTime;
	MIO_UINT32 m_MediaFlex;
}miosIEX_MEDIA_INFO;

typedef struct miosIEX_FUNC_TYPE{
	MIO_UINT32 type;

	MIO_CHAR m_FuncType[2];
}miosIEX_FUNC_TYPE;

typedef struct miosIEX_QUERY_SLICE{
	MIO_UINT32 type;

	MIO_UINT32 m_Count;
}miosIEX_QUERY_SLICE;

typedef struct miosIEX_STATE_INFO{
	MIO_UINT32 type;

	MIO_UINT8 m_event_type;
	MIO_UINT64 m_event_time;
	MIO_UINT8 m_event_result;
	MIO_UINT8 m_event_reason;
	MIO_UINT8 m_store_type;
	MIO_UINT8 m_reserve;
}miosIEX_STATE_INFO;

typedef struct miosIEX_DATABASE_INFO{
	MIO_UINT32 type;

	MIO_UINT8 m_DBFlag;
	MIO_UINT8 m_DBType;
	MIO_UINT16 m_DBAccess;
	MIO_CHAR m_DBIpAddr[33];
	MIO_UINT32 m_DBPort;
	MIO_CHAR m_DBUsername[33];
	MIO_CHAR m_DBPwd[17];
	MIO_UINT8 m_DBPwdEncrypt;
	MIO_CHAR m_DBDatabase[33];
	MIO_UINT8 m_DBEncode;
	MIO_CHAR m_DBTnsname[33];
	MIO_UINT32 m_DBReconn;
}miosIEX_DATABASE_INFO;

typedef struct miosIEX_AAA_INFO{
	MIO_UINT32 type;

	MIO_UINT8 m_AAAEnable;
	MIO_CHAR m_AAAIpAddr[33];
	MIO_UINT16 m_AAAAuthPort;
	MIO_UINT16 m_AAAAccountPort;
	MIO_CHAR m_AAAEcryptKey[17];
	MIO_UINT32 m_AAATimeout;
	MIO_UINT32 m_AAAResent;
}miosIEX_AAA_INFO;

typedef struct miosIEX_VERSION{
	MIO_UINT32 type;

	MIO_CHAR m_Version[33];
	MIO_UINT8 m_CuRole;
	MIO_UINT8 m_SoftwareFlag;
	MIO_UINT8 m_UpdateFlag;
}miosIEX_VERSION;

typedef struct miosIEX_VERSION_ENABLE{
	MIO_UINT32 type;

	MIO_UINT8 m_VersionEnable;
}miosIEX_VERSION_ENABLE;

typedef struct miosIEX_MEDIA_LINK{
	MIO_UINT32 type;

	MIO_CHAR m_MediaSessionId[65];
	MIO_UINT16 m_MediaDirection;
	MIO_UINT16 m_MediaSrcPort;
	MIO_CHAR m_RemoteIp[41];
	MIO_UINT16 m_RemotePort;
	MIO_CHAR m_LocalIp[41];
	MIO_UINT16 m_LocalPort;
	MIO_UINT8 m_TransType;
	MIO_UINT8 m_ConnMode;
}miosIEX_MEDIA_LINK;

typedef struct miosIEX_ALARM_OP_CHANNEL{
	MIO_UINT32 type;

	MIO_CHAR m_puid[20];
	MIO_UINT16 m_channelNo;
	MIO_UINT16 m_alarmOp;
	MIO_UINT16 m_presetIndex;
}miosIEX_ALARM_OP_CHANNEL;

typedef struct miosIEX_CHANNEL_LOCATION_INFO{
	MIO_UINT32 type;

	MIO_CHAR m_puid[20];
	MIO_UINT16 m_channelNo;
	MIO_DOUBLE m_Longitude;
	MIO_DOUBLE m_Latitude;
	MIO_UINT16 m_ChannelType;
}miosIEX_CHANNEL_LOCATION_INFO;

typedef struct miosIEX_COMPOUND_ENABLE{
	MIO_UINT32 type;

	MIO_UINT8 m_bEnable;
	MIO_UINT8 m_seqEnable;
	MIO_CHAR m_sequnce[65];
}miosIEX_COMPOUND_ENABLE;

typedef struct miosIEX_CHANNEL{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[20];
	MIO_UINT8 m_ChannelType;
	MIO_UINT16 m_ChannelNo;
	MIO_UINT8 m_ChannelNoSeq;
	MIO_UINT8 m_RegionNum;
	MIO_INT32 m_IntervalSpan;
}miosIEX_CHANNEL;

typedef struct miosIEX_ALARM_STATE_ENABLE{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[20];
	MIO_UINT8 m_ChannelType;
	MIO_UINT16 m_ChannelNo;
	MIO_UINT8 m_AlarmStateEnable;
}miosIEX_ALARM_STATE_ENABLE;

typedef struct miosIEX_ALARM_STATE_MAINTAIN{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[20];
	MIO_UINT8 m_ChannelType;
	MIO_UINT16 m_ChannelNo;
	MIO_INT32 m_AlarmStateMaintain;
}miosIEX_ALARM_STATE_MAINTAIN;

typedef struct miosIEX_POLL_PIC_SIZE{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[20];
	MIO_UINT8 m_ChannelType;
	MIO_UINT16 m_ChannelNo;
	MIO_UINT8 m_PicSize;
}miosIEX_POLL_PIC_SIZE;

typedef struct miosIEX_TIME_SPAN{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[20];
	MIO_UINT8 m_ChannelType;
	MIO_UINT16 m_ChannelNo;
	MIO_INT32 m_IntervalSpan;
}miosIEX_TIME_SPAN;

typedef struct miosIEX_TB_TYPE{
	MIO_UINT32 type;

	MIO_CHAR m_PUID[20];
	MIO_UINT8 m_ChannelType;
	MIO_UINT16 m_ChannelNo;
	MIO_UINT8 m_TbType;
}miosIEX_TB_TYPE;

typedef struct miosIEX_SDP{
	MIO_UINT32 type;

	MIO_CHAR m_value[513];
}miosIEX_SDP;

typedef struct miosIEX_IMAGE_ENCODE_PARA_SETS{
	MIO_UINT32 type;

	MIO_CHAR m_StreamType[3];
	MIO_CHAR m_ParameterSets[65];
}miosIEX_IMAGE_ENCODE_PARA_SETS;

typedef struct miosIEX_IKEY_INFO{
	MIO_UINT32 type;

	MIO_UINT8 m_Ikey_enable;
	MIO_CHAR m_Ikey_challenge_num[33];
	MIO_CHAR m_Reserve[33];
}miosIEX_IKEY_INFO;

typedef struct miosIEX_SHARED_CATALOG{
	MIO_UINT32 type;

	MIO_CHAR m_Name[65];
	MIO_CHAR m_Address[21];
	MIO_CHAR m_Privilege[21];
	MIO_CHAR m_Parent[21];
	MIO_UINT8 m_Status;
	MIO_DOUBLE m_Longitude;
	MIO_DOUBLE m_Latitude;
	MIO_CHAR m_DecoderTag[65];
	MIO_UINT32 m_Subnum;
}miosIEX_SHARED_CATALOG;

typedef struct miosIEX_REBOOT{
	MIO_UINT32 type;

	MIO_UINT8 m_RebootEnable;
}miosIEX_REBOOT;

typedef struct miospuId{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miospuId;

typedef struct miospuName{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miospuName;

typedef struct miospuPassword{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miospuPassword;

typedef struct miosnetId{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosnetId;

typedef struct miosipAddress{
	MIO_UINT32 type;

	MIO_CHAR m_value[41];
}miosipAddress;

typedef struct mioscontrolPort{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}mioscontrolPort;

typedef struct miossipPort{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miossipPort;

typedef struct miossubnetMask{
	MIO_UINT32 type;

	MIO_CHAR m_value[41];
}miossubnetMask;

typedef struct miosdns{
	MIO_UINT32 type;

	MIO_CHAR m_value[41];
}miosdns;

typedef struct miosgateway{
	MIO_UINT32 type;

	MIO_CHAR m_value[41];
}miosgateway;

typedef struct miosuserName{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosuserName;

typedef struct miospassWord{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miospassWord;

typedef struct miospriority{
	MIO_UINT32 type;

}miospriority;

typedef struct miosserialPort{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miosserialPort;

typedef struct miosbaudRate{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosbaudRate;

typedef struct miosdataBit{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosdataBit;

typedef struct miosparity{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosparity;

typedef struct miosstopBit{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosstopBit;

typedef struct miosmode{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosmode;

typedef struct miosflowControl{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosflowControl;

typedef struct miosdecoderType{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miosdecoderType;

typedef struct miosdecoderAddress{
	MIO_UINT32 type;

	MIO_CHAR m_value[17];
}miosdecoderAddress;

typedef struct miostimeOut{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miostimeOut;

typedef struct miosinput{
	MIO_UINT32 type;

	MIO_UINT16 m_channelNumber;
	MIO_UINT8 m_state;
}miosinput;

typedef struct miosoutput{
	MIO_UINT32 type;

	MIO_UINT16 m_channelNumber;
	MIO_INT32 m_state;
}miosoutput;

typedef struct miosChannelNumber{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miosChannelNumber;

typedef struct miosstate{
	MIO_UINT32 type;

	MIO_INT32 m_value;
}miosstate;

typedef struct mioshour{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}mioshour;

typedef struct miosminute{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosminute;

typedef struct miossecond{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miossecond;

typedef struct miosmonth{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosmonth;

typedef struct miosdate{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosdate;

typedef struct miosyear{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miosyear;

typedef struct miosvideoId{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miosvideoId;

typedef struct miosencodeMode{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosencodeMode;

typedef struct miospicQuality{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miospicQuality;

typedef struct miosbitRate{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miosbitRate;

typedef struct miosbitRateType{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosbitRateType;

typedef struct miosframeRate{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosframeRate;

typedef struct miosimageSize{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosimageSize;

typedef struct miosstreamType{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosstreamType;

typedef struct miosiFrameInterval{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miosiFrameInterval;

typedef struct mioscontrast{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}mioscontrast;

typedef struct miosbright{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosbright;

typedef struct mioshue{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}mioshue;

typedef struct miossaturation{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miossaturation;

typedef struct miosbitmapX{
	MIO_UINT32 type;

	MIO_INT32 m_value;
}miosbitmapX;

typedef struct miosbitmapY{
	MIO_UINT32 type;

	MIO_INT32 m_value;
}miosbitmapY;

typedef struct miosbitmapTimeEnable{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosbitmapTimeEnable;

typedef struct miosbitmapTextEnable{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosbitmapTextEnable;

typedef struct miosbitmapText{
	MIO_UINT32 type;

	MIO_CHAR m_value[129];
}miosbitmapText;

typedef struct miosbitmapTextX{
	MIO_UINT32 type;

	MIO_INT32 m_value;
}miosbitmapTextX;

typedef struct miosbitmapTextY{
	MIO_UINT32 type;

	MIO_INT32 m_value;
}miosbitmapTextY;

typedef struct miosconnectionDetectionEnabled{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosconnectionDetectionEnabled;

typedef struct miosdiskFullAlarmEnabled{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosdiskFullAlarmEnabled;

typedef struct miosdiskFullHighThreshold{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosdiskFullHighThreshold;

typedef struct miosdiskFullLowThreshold{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosdiskFullLowThreshold;

typedef struct miosdiskErrorAlarmEnabled{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosdiskErrorAlarmEnabled;

typedef struct miosalarmPreRecordTime{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosalarmPreRecordTime;

typedef struct miosalarmRecordTime{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosalarmRecordTime;

typedef struct miosalarmOutputTime{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosalarmOutputTime;

typedef struct miosalarmOutputActivatedTimes{
	MIO_UINT32 type;

	MIO_UINT16 m_channelNumber;
	MIO_CHAR m_time[10];
}miosalarmOutputActivatedTimes;

typedef struct miosphotoResolution{
	MIO_UINT32 type;

	MIO_INT8 m_value;
}miosphotoResolution;

typedef struct miosphotoQuality{
	MIO_UINT32 type;

	MIO_INT8 m_value;
}miosphotoQuality;

typedef struct miosshootTimes{
	MIO_UINT32 type;

	MIO_INT8 m_value;
}miosshootTimes;

typedef struct miosgpinAlarmEnabled{
	MIO_UINT32 type;

	MIO_UINT16 m_channelNumber;
	MIO_UINT8 m_alarmState;
}miosgpinAlarmEnabled;

typedef struct miosgpinAlarmStatus{
	MIO_UINT32 type;

	MIO_UINT16 m_channelNumber;
	MIO_UINT8 m_alarmState;
}miosgpinAlarmStatus;

typedef struct miosgpinAlarmOutput{
	MIO_UINT32 type;

	MIO_UINT16 m_channelNumber;
	MIO_UINT16 m_outputChannelNumber;
	MIO_INT32 m_alarmState;
}miosgpinAlarmOutput;

typedef struct miosgpinAlarmRecord{
	MIO_UINT32 type;

	MIO_UINT16 m_channelNumber;
	MIO_UINT16 m_recordChannelNumber;
}miosgpinAlarmRecord;

typedef struct miosgpinAlarmShoot{
	MIO_UINT32 type;

	MIO_UINT16 m_channelNumber;
	MIO_UINT16 m_shootChannelNumber;
}miosgpinAlarmShoot;

typedef struct miosvideoLoseAlarmEnabled{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT8 m_alarmState;
}miosvideoLoseAlarmEnabled;

typedef struct miosvideoLoseAlarmOutput{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT16 m_outputChannelNumber;
	MIO_INT32 m_alarmState;
}miosvideoLoseAlarmOutput;

typedef struct mioshideDetectionAlarmEnabled{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT8 m_alarmState;
}mioshideDetectionAlarmEnabled;

typedef struct mioshideDetectionAlarmTime{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_CHAR m_time[10];
}mioshideDetectionAlarmTime;

typedef struct mioshideDetectionX{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT32 m_xPos;
}mioshideDetectionX;

typedef struct mioshideDetectionY{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT32 m_yPos;
}mioshideDetectionY;

typedef struct mioshideDetectionWidth{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT32 m_width;
}mioshideDetectionWidth;

typedef struct mioshideDetectionHeight{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT32 m_height;
}mioshideDetectionHeight;

typedef struct mioshideDetectionAlarmOutput{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT16 m_outputChannelNumber;
	MIO_INT32 m_alarmState;
}mioshideDetectionAlarmOutput;

typedef struct mioshideDetectionAlarmRecord{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT16 m_recordChannelNumber;
}mioshideDetectionAlarmRecord;

typedef struct miosmotionDetectionAlarmEnabled{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT8 m_alarmState;
}miosmotionDetectionAlarmEnabled;

typedef struct miosmotionDetectionAlarmTime{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_CHAR m_time[10];
}miosmotionDetectionAlarmTime;

typedef struct miosmotionDetectionBlocks{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT32 m_blockNumber;
}miosmotionDetectionBlocks;

typedef struct miosmotionDetectionFrequency{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT32 m_frequency;
}miosmotionDetectionFrequency;

typedef struct miosmotionDetectionSensitivity{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT8 m_sensitivity;
}miosmotionDetectionSensitivity;

typedef struct miosmotionDetectionAlarmOutput{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT16 m_outputChannelNumber;
	MIO_INT32 m_alarmState;
}miosmotionDetectionAlarmOutput;

typedef struct miosmotionDetectionAlarmRecord{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT16 m_recordChannelNumber;
}miosmotionDetectionAlarmRecord;

typedef struct miosmotionDetectionAlarmShoot{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT16 m_shootChannelNumber;
}miosmotionDetectionAlarmShoot;

typedef struct miosrecordEnable{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosrecordEnable;

typedef struct miosrecycleRecEnable{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosrecycleRecEnable;

typedef struct miosschedule{
	MIO_UINT32 type;

	MIO_UINT8 m_weekday;
	MIO_UINT8 m_startHour;
	MIO_UINT8 m_startMin;
	MIO_UINT8 m_stopHour;
	MIO_UINT8 m_stopMin;
}miosschedule;

typedef struct miosrecordPolicy{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosrecordPolicy;

typedef struct miosframeInterval{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosframeInterval;

typedef struct miosfilenameSuffix{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosfilenameSuffix;

typedef struct miosfileType{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosfileType;

typedef struct miosfromDate{
	MIO_UINT32 type;

	MIO_TIME m_value;
}miosfromDate;

typedef struct miostoDate{
	MIO_UINT32 type;

	MIO_TIME m_value;
}miostoDate;

typedef struct miosrecordFile{
	MIO_UINT32 type;

	MIO_CHAR m_fileName[129];
	MIO_TIME m_startTime;
	MIO_TIME m_stopTime;
	MIO_UINT64 m_size;
}miosrecordFile;

typedef struct miostotalSize{
	MIO_UINT32 type;

	MIO_UINT64 m_value;
}miostotalSize;

typedef struct miosfreeSize{
	MIO_UINT32 type;

	MIO_UINT64 m_value;
}miosfreeSize;

typedef struct miosfileName{
	MIO_UINT32 type;

	MIO_CHAR m_value[129];
}miosfileName;

typedef struct miosdeviceStatus{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosdeviceStatus;

typedef struct miosdisk{
	MIO_UINT32 type;

	MIO_UINT32 m_diskId;
	MIO_UINT64 m_totalSize;
	MIO_UINT64 m_freeSize;
	MIO_UINT32 m_status;
}miosdisk;

typedef struct miosvideoChannel{
	MIO_UINT32 type;

	MIO_UINT16 m_videoId;
	MIO_UINT8 m_recordStatus;
	MIO_UINT8 m_signalStatus;
	MIO_UINT8 m_hardwareStatus;
	MIO_UINT16 m_bitRate;
}miosvideoChannel;

typedef struct miosalarmIn{
	MIO_UINT32 type;

	MIO_UINT16 m_channelNumber;
	MIO_UINT8 m_status;
}miosalarmIn;

typedef struct miosalarmOut{
	MIO_UINT32 type;

	MIO_UINT16 m_channelNumber;
	MIO_UINT8 m_status;
}miosalarmOut;

typedef struct mioslogType{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}mioslogType;

typedef struct miosstartLogDate{
	MIO_UINT32 type;

	MIO_TIME m_value;
}miosstartLogDate;

typedef struct miosendLogDate{
	MIO_UINT32 type;

	MIO_TIME m_value;
}miosendLogDate;

typedef struct miosstartIndex{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosstartIndex;

typedef struct miosmaxResults{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosmaxResults;

typedef struct mioslogInfo{
	MIO_UINT32 type;

	MIO_UINT8 m_LOGTYPE;
	MIO_TIME m_LOGTIME;
	MIO_CHAR m_NETUSER[33];
	MIO_UINT16 m_videoID;
	MIO_UINT32 m_diskNumber;
	MIO_UINT16 m_AlarmInPort;
	MIO_UINT16 m_AlarmOutPort;
}mioslogInfo;

typedef struct miosalarmServerIp{
	MIO_UINT32 type;

	MIO_CHAR m_value[41];
}miosalarmServerIp;

typedef struct miosalarmServerPort{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miosalarmServerPort;

typedef struct miosalarmUrl{
	MIO_UINT32 type;

	MIO_CHAR m_value[512];
}miosalarmUrl;

typedef struct miosheartBeatServerIp{
	MIO_UINT32 type;

	MIO_CHAR m_value[41];
}miosheartBeatServerIp;

typedef struct miosheartBeatServerPort{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miosheartBeatServerPort;

typedef struct miosregisterServerIp{
	MIO_UINT32 type;

	MIO_CHAR m_value[41];
}miosregisterServerIp;

typedef struct miosregisterServerPort{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miosregisterServerPort;

typedef struct miosenableHeartBeat{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosenableHeartBeat;

typedef struct miosheartBeatPeriod{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosheartBeatPeriod;

typedef struct miosptzId{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miosptzId;

typedef struct mioscmd{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}mioscmd;

typedef struct miosparam{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosparam;

typedef struct miosspeed{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosspeed;

typedef struct miosprotocol{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosprotocol;

typedef struct miospresetIndex{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miospresetIndex;

typedef struct miospresetName{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miospresetName;

typedef struct mioscruiseNumber{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}mioscruiseNumber;

typedef struct mioscruisePoint{
	MIO_UINT32 type;

	MIO_UINT32 m_presetIndex;
	MIO_UINT32 m_dwellTime;
	MIO_UINT8 m_speed;
}mioscruisePoint;

typedef struct mioscontrolAction{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}mioscontrolAction;

typedef struct miosfileUrl{
	MIO_UINT32 type;

	MIO_CHAR m_value[512];
}miosfileUrl;

typedef struct miospuIp{
	MIO_UINT32 type;

	MIO_CHAR m_value[41];
}miospuIp;

typedef struct miosalarmType{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosalarmType;

typedef struct miosserverType{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosserverType;

typedef struct mioschannelNumber{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}mioschannelNumber;

typedef struct miosdiskNumber{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosdiskNumber;

typedef struct miostimeStamp{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miostimeStamp;

typedef struct miosdata{
	MIO_UINT32 type;

	miosList* m_value;
}miosdata;

typedef struct miosoldVersion{
	MIO_UINT32 type;

	MIO_CHAR m_value[128];
}miosoldVersion;

typedef struct miosnewVersion{
	MIO_UINT32 type;

	MIO_CHAR m_value[128];
}miosnewVersion;

typedef struct miosupgradeResult{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosupgradeResult;

typedef struct miostransparentAction{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miostransparentAction;

typedef struct miostransparentData{
	MIO_UINT32 type;

	MIO_CHAR m_value[256];
}miostransparentData;

typedef struct miospuPort{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miospuPort;

typedef struct miospuType{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miospuType;

typedef struct miosenableLongConnection{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosenableLongConnection;

typedef struct miosexpires{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosexpires;

typedef struct miosmediaType{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosmediaType;

typedef struct miosimageWidth{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosimageWidth;

typedef struct miosimageHeight{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosimageHeight;

typedef struct miosvideoFormat{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosvideoFormat;

typedef struct mioscuId{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}mioscuId;

typedef struct miosusername{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosusername;

typedef struct miosuserStatus{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosuserStatus;

typedef struct miosdomainUsername{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosdomainUsername;

typedef struct miosdomainPassword{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosdomainPassword;

typedef struct mioscustomerId{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}mioscustomerId;

typedef struct miosdisplayName{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosdisplayName;

typedef struct miosuserLevel{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosuserLevel;

typedef struct miosdescription{
	MIO_UINT32 type;

	MIO_CHAR m_value[129];
}miosdescription;

typedef struct miosdisabled{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosdisabled;

typedef struct miosaddress{
	MIO_UINT32 type;

	MIO_CHAR m_value[257];
}miosaddress;

typedef struct miosemail{
	MIO_UINT32 type;

	MIO_CHAR m_value[129];
}miosemail;

typedef struct miosdept{
	MIO_UINT32 type;

	MIO_CHAR m_value[129];
}miosdept;

typedef struct miosfixedNumber{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosfixedNumber;

typedef struct miosmobileNumber{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosmobileNumber;

typedef struct mioscreator{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}mioscreator;

typedef struct mioscreatedDateStart{
	MIO_UINT32 type;

	MIO_TIME m_value;
}mioscreatedDateStart;

typedef struct mioscreatedDateEnd{
	MIO_UINT32 type;

	MIO_TIME m_value;
}mioscreatedDateEnd;

typedef struct mioscustomerName{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}mioscustomerName;

typedef struct miostype{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miostype;

typedef struct mioscontactName{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}mioscontactName;

typedef struct miosfaxNumber{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosfaxNumber;

typedef struct mioszipCode{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}mioszipCode;

typedef struct miosbankName{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosbankName;

typedef struct miosbankAccount{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosbankAccount;

typedef struct miosmaxUsers{
	MIO_UINT32 type;

	MIO_INT32 m_value;
}miosmaxUsers;

typedef struct miosmaxOnlineUsers{
	MIO_UINT32 type;

	MIO_INT32 m_value;
}miosmaxOnlineUsers;

typedef struct miosadminUsername{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosadminUsername;

typedef struct mioscreatedDate{
	MIO_UINT32 type;

	MIO_TIME m_value;
}mioscreatedDate;

typedef struct miosareaId{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosareaId;

typedef struct mioscuIdFrom{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}mioscuIdFrom;

typedef struct mioscuIdTo{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}mioscuIdTo;

typedef struct miosmaxVideoChannels{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosmaxVideoChannels;

typedef struct miosuserStatistic{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosuserStatistic;

typedef struct mioscurrentUsers{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}mioscurrentUsers;

typedef struct mioscurrentOnlineUsers{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}mioscurrentOnlineUsers;

typedef struct miosstorageQuota{
	MIO_UINT32 type;

	MIO_UINT64 m_value;
}miosstorageQuota;

typedef struct miosdiskFullAlarmThreshold{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosdiskFullAlarmThreshold;

typedef struct miosautoFreeSpaceSize{
	MIO_UINT32 type;

	MIO_UINT64 m_value;
}miosautoFreeSpaceSize;

typedef struct miosfirstInputChannel{
	MIO_UINT32 type;

	MIO_INT32 m_value;
}miosfirstInputChannel;

typedef struct miosfirstOutputChannel{
	MIO_UINT32 type;

	MIO_INT32 m_value;
}miosfirstOutputChannel;

typedef struct miosfirstVideoChannel{
	MIO_UINT32 type;

	MIO_INT32 m_value;
}miosfirstVideoChannel;

typedef struct miosfirstAudioChannel{
	MIO_UINT32 type;

	MIO_INT32 m_value;
}miosfirstAudioChannel;

typedef struct miosmaxInputChannel{
	MIO_UINT32 type;

	MIO_INT32 m_value;
}miosmaxInputChannel;

typedef struct miosmaxOutputChannel{
	MIO_UINT32 type;

	MIO_INT32 m_value;
}miosmaxOutputChannel;

typedef struct miosmaxVideoChannel{
	MIO_UINT32 type;

	MIO_INT32 m_value;
}miosmaxVideoChannel;

typedef struct miosmaxAudioChannel{
	MIO_UINT32 type;

	MIO_INT32 m_value;
}miosmaxAudioChannel;

typedef struct miosaudioChannel{
	MIO_UINT32 type;

	MIO_UINT16 m_channelNumber;
	MIO_CHAR m_channelName[33];
}miosaudioChannel;

typedef struct miosvsType{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosvsType;

typedef struct mioslocalStorageEnabled{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}mioslocalStorageEnabled;

typedef struct miosrecordMode{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosrecordMode;

typedef struct miosnetworkInterface{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosnetworkInterface;

typedef struct miospuControlPort{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miospuControlPort;

typedef struct miospuSipPort{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miospuSipPort;

typedef struct miosvideoPort{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miosvideoPort;

typedef struct miosaudioPort{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miosaudioPort;

typedef struct miosdvsName{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosdvsName;

typedef struct miosloginUsername{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosloginUsername;

typedef struct miosloginPassword{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosloginPassword;

typedef struct miosx{
	MIO_UINT32 type;

	MIO_DOUBLE m_value;
}miosx;

typedef struct miosy{
	MIO_UINT32 type;

	MIO_DOUBLE m_value;
}miosy;

typedef struct miosgpio{
	MIO_UINT32 type;

	MIO_CHAR m_name[33];
	MIO_UINT8 m_normalState;
	MIO_UINT16 m_channelNumber;
	MIO_UINT8 m_direction;
	MIO_CHAR m_description[129];
	MIO_UINT16 m_alarmType;
}miosgpio;

typedef struct miosonline{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosonline;

typedef struct miosmanufacturerId{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosmanufacturerId;

typedef struct miosmanufacturerName{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosmanufacturerName;

typedef struct miosproductVersion{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosproductVersion;

typedef struct miossoftwareVersion{
	MIO_UINT32 type;

	MIO_CHAR m_value[129];
}miossoftwareVersion;

typedef struct mioslastUpgradeDate{
	MIO_UINT32 type;

	MIO_TIME m_value;
}mioslastUpgradeDate;

typedef struct miosplace{
	MIO_UINT32 type;

	MIO_CHAR m_value[129];
}miosplace;

typedef struct mioscameraName{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}mioscameraName;

typedef struct miosvs{
	MIO_UINT32 type;

	miosList* m_value;
}miosvs;

typedef struct mioswidth{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}mioswidth;

typedef struct miosheight{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosheight;

typedef struct miosptzProtocol{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosptzProtocol;

typedef struct mioscontrolPTZType{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}mioscontrolPTZType;

typedef struct miostimePieceLen{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miostimePieceLen;

typedef struct miosmodel{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosmodel;

typedef struct miossetupType{
	MIO_UINT32 type;

	MIO_INT8 m_value;
}miossetupType;

typedef struct miosparentId{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosparentId;

typedef struct miosareaName{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosareaName;

typedef struct miosaction{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosaction;

typedef struct miossubscriberId{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miossubscriberId;

typedef struct miosexpiringDate{
	MIO_UINT32 type;

	MIO_TIME m_value;
}miosexpiringDate;

typedef struct mioslinkable{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}mioslinkable;

typedef struct miossourceType{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miossourceType;

typedef struct miosseverity{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosseverity;

typedef struct miostypeName{
	MIO_UINT32 type;

	MIO_CHAR m_value[257];
}miostypeName;

typedef struct miosalarmDate{
	MIO_UINT32 type;

	MIO_TIME m_value;
}miosalarmDate;

typedef struct mioseliminated{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}mioseliminated;

typedef struct miosdiskFullThreshold{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosdiskFullThreshold;

typedef struct miosgpinAlarm{
	MIO_UINT32 type;

	miosList* m_value;
}miosgpinAlarm;

typedef struct mioscameraAlarm{
	MIO_UINT32 type;

	miosList* m_value;
}mioscameraAlarm;

typedef struct miospreset{
	MIO_UINT32 type;

	MIO_UINT32 m_presetIndex;
	MIO_CHAR m_presetName[33];
}miospreset;

typedef struct mioscruise{
	MIO_UINT32 type;

	miosList* m_value;
}mioscruise;

typedef struct miostaskName{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miostaskName;

typedef struct miosstartTime{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosstartTime;

typedef struct miosduration{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosduration;

typedef struct miostaskType{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miostaskType;

typedef struct miosmaxTimes{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosmaxTimes;

typedef struct miostask{
	MIO_UINT32 type;

	MIO_CHAR m_id[33];
	MIO_CHAR m_puId[33];
	MIO_UINT16 m_channelNumber;
	MIO_UINT16 m_alarmType;
}miostask;

typedef struct miostaskId{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miostaskId;

typedef struct miosstartTimeStamp{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosstartTimeStamp;

typedef struct miosendTimeStamp{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosendTimeStamp;

typedef struct miosfileSize{
	MIO_UINT32 type;

	MIO_UINT64 m_value;
}miosfileSize;

typedef struct miosfilePath{
	MIO_UINT32 type;

	MIO_CHAR m_value[513];
}miosfilePath;

typedef struct miosstatus{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosstatus;

typedef struct miosfileId{
	MIO_UINT32 type;

	MIO_CHAR m_value[513];
}miosfileId;

typedef struct miosmduIpAddressList{
	MIO_UINT32 type;

	miosList* m_value;
}miosmduIpAddressList;

typedef struct mioscsgIpAddressList{
	MIO_UINT32 type;

	miosList* m_value;
}mioscsgIpAddressList;

typedef struct miossourceId{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miossourceId;

typedef struct miospassword{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miospassword;

typedef struct miosforDecoder{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosforDecoder;

typedef struct miosworkMode{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosworkMode;

typedef struct mioshttpRegisterServerIp{
	MIO_UINT32 type;

	MIO_CHAR m_value[41];
}mioshttpRegisterServerIp;

typedef struct mioshttpRegisterServerPort{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}mioshttpRegisterServerPort;

typedef struct miosenableHttpHeartbeat{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosenableHttpHeartbeat;

typedef struct mioshttpHeartbeatServerIp{
	MIO_UINT32 type;

	MIO_CHAR m_value[41];
}mioshttpHeartbeatServerIp;

typedef struct mioshttpHeartbeatServerPort{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}mioshttpHeartbeatServerPort;

typedef struct mioshttpHeartbeatPeriod{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}mioshttpHeartbeatPeriod;

typedef struct miosenableSipRegister{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosenableSipRegister;

typedef struct miossipRegisterServerIp{
	MIO_UINT32 type;

	MIO_CHAR m_value[41];
}miossipRegisterServerIp;

typedef struct miossipRegisterServerPort{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miossipRegisterServerPort;

typedef struct miosenableSipHeartbeat{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosenableSipHeartbeat;

typedef struct miossipHeartbeatServerIp{
	MIO_UINT32 type;

	MIO_CHAR m_value[41];
}miossipHeartbeatServerIp;

typedef struct miossipHeartbeatServerPort{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miossipHeartbeatServerPort;

typedef struct miossipHeartbeatPeriod{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miossipHeartbeatPeriod;

typedef struct miosdiskPath{
	MIO_UINT32 type;

	MIO_CHAR m_value[257];
}miosdiskPath;

typedef struct miosdiskOccupiedPercent{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosdiskOccupiedPercent;

typedef struct miosuserId{
	MIO_UINT32 type;

	MIO_CHAR m_value[33];
}miosuserId;

typedef struct mioskeepAlivePeriod{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}mioskeepAlivePeriod;

typedef struct mioshideAreaEnabled{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}mioshideAreaEnabled;

typedef struct mioshideImageArea{
	MIO_UINT32 type;

	MIO_UINT32 m_hideAreaX;
	MIO_UINT32 m_hideAreaY;
	MIO_UINT32 m_hideAreaWidth;
	MIO_UINT32 m_hideAreaHeight;
}mioshideImageArea;

typedef struct mioscustomerStatus{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}mioscustomerStatus;

typedef struct miosfilename{
	MIO_UINT32 type;

	MIO_CHAR m_value[129];
}miosfilename;

typedef struct miosmduIpAddress{
	MIO_UINT32 type;

	MIO_UINT32 m_sequence;
	MIO_CHAR m_IpAddress[41];
	MIO_UINT16 m_sipPort;
}miosmduIpAddress;

typedef struct mioscsgIpAddress{
	MIO_UINT32 type;

	MIO_UINT32 m_sequence;
	MIO_CHAR m_IpAddress[41];
	MIO_UINT16 m_httpPort;
}mioscsgIpAddress;

typedef struct miosHttpHeartbeatPeriod{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosHttpHeartbeatPeriod;

typedef struct miosgpinAlarm_gpinAlarmEnabled{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosgpinAlarm_gpinAlarmEnabled;

typedef struct miosgpinAlarm_alarmOutputActivatedTimes{
	MIO_UINT32 type;

	MIO_CHAR m_value[10];
}miosgpinAlarm_alarmOutputActivatedTimes;

typedef struct miosgpinAlarm_gpinAlarmStatus{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosgpinAlarm_gpinAlarmStatus;

typedef struct miosgpinAlarm_gpinAlarmOutput{
	MIO_UINT32 type;

	MIO_UINT16 m_outputChannelNumber;
	MIO_INT32 m_alarmState;
}miosgpinAlarm_gpinAlarmOutput;

typedef struct miosgpinAlarm_gpinAlarmRecord{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miosgpinAlarm_gpinAlarmRecord;

typedef struct miosgpinAlarm_gpinAlarmShoot{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}miosgpinAlarm_gpinAlarmShoot;

typedef struct mioscameraAlarm_videoLoseAlarmEnabled{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}mioscameraAlarm_videoLoseAlarmEnabled;

typedef struct mioscameraAlarm_videoLoseAlarmOutput{
	MIO_UINT32 type;

	MIO_UINT16 m_outputChannelNumber;
	MIO_INT32 m_alarmState;
}mioscameraAlarm_videoLoseAlarmOutput;

typedef struct mioscameraAlarm_hideDetectionAlarmEnabled{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}mioscameraAlarm_hideDetectionAlarmEnabled;

typedef struct mioscameraAlarm_hideDetectionAlarmTime{
	MIO_UINT32 type;

	MIO_CHAR m_value[10];
}mioscameraAlarm_hideDetectionAlarmTime;

typedef struct mioscameraAlarm_hideDetectionX{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}mioscameraAlarm_hideDetectionX;

typedef struct mioscameraAlarm_hideDetectionY{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}mioscameraAlarm_hideDetectionY;

typedef struct mioscameraAlarm_hideDetectionWidth{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}mioscameraAlarm_hideDetectionWidth;

typedef struct mioscameraAlarm_hideDetectionHeight{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}mioscameraAlarm_hideDetectionHeight;

typedef struct mioscameraAlarm_hideDetectionAlarmOutput{
	MIO_UINT32 type;

	MIO_UINT16 m_outputChannelNumber;
	MIO_INT32 m_alarmState;
}mioscameraAlarm_hideDetectionAlarmOutput;

typedef struct mioscameraAlarm_hideDetectionAlarmRecord{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}mioscameraAlarm_hideDetectionAlarmRecord;

typedef struct mioscameraAlarm_motionDetectionAlarmEnabled{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}mioscameraAlarm_motionDetectionAlarmEnabled;

typedef struct mioscameraAlarm_motionDetectionAlarmTime{
	MIO_UINT32 type;

	MIO_CHAR m_value[10];
}mioscameraAlarm_motionDetectionAlarmTime;

typedef struct mioscameraAlarm_motionDetectionBlocks{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}mioscameraAlarm_motionDetectionBlocks;

typedef struct mioscameraAlarm_motionDetectionFrequency{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}mioscameraAlarm_motionDetectionFrequency;

typedef struct mioscameraAlarm_motionDetectionSensitivity{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}mioscameraAlarm_motionDetectionSensitivity;

typedef struct mioscameraAlarm_motionDetectionAlarmOutput{
	MIO_UINT32 type;

	MIO_UINT16 m_outputChannelNumber;
	MIO_INT32 m_alarmState;
}mioscameraAlarm_motionDetectionAlarmOutput;

typedef struct mioscameraAlarm_motionDetectionAlarmRecord{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}mioscameraAlarm_motionDetectionAlarmRecord;

typedef struct mioscameraAlarm_motionDetectionAlarmShoot{
	MIO_UINT32 type;

	MIO_UINT16 m_value;
}mioscameraAlarm_motionDetectionAlarmShoot;

typedef struct miosName{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosName;

typedef struct miosAddress{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosAddress;

typedef struct miosPrivilege{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosPrivilege;

typedef struct miosParent{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosParent;

typedef struct miosStatus{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosStatus;

typedef struct miosSubnum{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosSubnum;

typedef struct miosResult{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosResult;

typedef struct miosFormat{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosFormat;

typedef struct miosVideo{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosVideo;

typedef struct miosAudio{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosAudio;

typedef struct miosMaxBitrate{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosMaxBitrate;

typedef struct miosReceiveSocket{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosReceiveSocket;

typedef struct miosBitrate{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosBitrate;

typedef struct miosFileType{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosFileType;

typedef struct miosMaxFileNum{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosMaxFileNum;

typedef struct miosBeginTime{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosBeginTime;

typedef struct miosEndTime{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosEndTime;

typedef struct miosRealFileNum{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosRealFileNum;

typedef struct miosSendFileNum{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosSendFileNum;

typedef struct miosCommand{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosCommand;

typedef struct miosManufacturer{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosManufacturer;

typedef struct miosSublist{
	MIO_UINT32 type;

	miosList* m_value;
}miosSublist;

typedef struct miosItem{
	MIO_UINT32 type;

	MIO_CHAR m_Name[65];
	MIO_CHAR m_Address[65];
	MIO_CHAR m_Privilege[65];
	MIO_CHAR m_Parent[65];
	MIO_UINT8 m_Status;
	MIO_DOUBLE m_Longitude;
	MIO_DOUBLE m_Latitude;
	MIO_UINT32 m_Subnum;
}miosItem;

typedef struct miosSublist_Item{
	MIO_UINT32 type;

	MIO_CHAR m_Name[65];
	MIO_CHAR m_Address[65];
	MIO_CHAR m_Privilege[65];
	MIO_CHAR m_Parent[65];
	MIO_UINT8 m_Status;
	MIO_DOUBLE m_Longitude;
	MIO_DOUBLE m_Latitude;
	MIO_UINT32 m_Subnum;
}miosSublist_Item;

typedef struct miosFileInfolist{
	MIO_UINT32 type;

	miosList* m_value;
}miosFileInfolist;

typedef struct miositem{
	MIO_UINT32 type;

	MIO_CHAR m_name[65];
	MIO_CHAR m_creationtime[65];
	MIO_CHAR m_lastaccesstime[65];
	MIO_CHAR m_lastwritetime[65];
	MIO_UINT32 m_filesize;
}miositem;

typedef struct miosFileInfolist_item{
	MIO_UINT32 type;

	MIO_CHAR m_name[65];
	MIO_CHAR m_creationtime[65];
	MIO_CHAR m_lastaccesstime[65];
	MIO_CHAR m_lastwritetime[65];
	MIO_UINT32 m_filesize;
}miosFileInfolist_item;

typedef struct miosModel{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosModel;

typedef struct miosFirmware{
	MIO_UINT32 type;

	MIO_CHAR m_value[65];
}miosFirmware;

typedef struct miosMaxcamera{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosMaxcamera;

typedef struct miosOnline{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosOnline;

typedef struct miosErrencodenum{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosErrencodenum;

typedef struct miosRecord{
	MIO_UINT32 type;

	MIO_UINT8 m_value;
}miosRecord;

typedef struct miosSinceStartup{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosSinceStartup;

typedef struct miosCameralist{
	MIO_UINT32 type;

	miosList* m_value;
}miosCameralist;

typedef struct miosCameralist_item{
	MIO_UINT32 type;

	MIO_CHAR m_camera[65];
	MIO_CHAR m_reason[65];
}miosCameralist_item;

typedef struct miosValue{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosValue;

typedef struct miosAll{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosAll;

typedef struct miosFree{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosFree;

typedef struct miosMedialink{
	MIO_UINT32 type;

	MIO_UINT32 m_value;
}miosMedialink;

typedef struct miosMaxIE{
	union {
		miosIE_CMS_INFO m_IE_CMS_INFO;
		miosIE_CUSTOMER m_IE_CUSTOMER;
		miosIEX_CUSTOMER_INFO m_IEX_CUSTOMER_INFO;
		miosIEX_CU_OP_RIGHT m_IEX_CU_OP_RIGHT;
		miosIEX_CUSTOMER_AUTH m_IEX_CUSTOMER_AUTH;
		miosIEX_DATA m_IEX_DATA;
		miosIEX_DCS_INFO m_IEX_DCS_INFO;
		miosIEX_DIGEST m_IEX_DIGEST;
		miosIEX_HEADER m_IEX_HEADER;
		miosIEX_DEVICE_CHECK m_IEX_DEVICE_CHECK;
		miosIEX_PU_BASIC_PARA m_IEX_PU_BASIC_PARA;
		miosIEX_STATE_TYPE m_IEX_STATE_TYPE;
		miosIE_QUERY_PARA m_IE_QUERY_PARA;
		miosIE_PICTURE_INFO m_IE_PICTURE_INFO;
		miosIE_PU_ONLINE m_IE_PU_ONLINE;
		miosIE_CHANNEL m_IE_CHANNEL;
		miosIE_NODE_ATTRIB_NAME m_IE_NODE_ATTRIB_NAME;
		miosIE_MANUFACTURE m_IE_MANUFACTURE;
		miosIE_HARDDISK m_IE_HARDDISK;
		miosIE_DEVICE_AUTHENTICATION m_IE_DEVICE_AUTHENTICATION;
		miosIE_QUERY_STATUS m_IE_QUERY_STATUS;
		miosIE_PTZ m_IE_PTZ;
		miosIE_TRANSPARENTCMD_TEXT m_IE_TRANSPARENTCMD_TEXT;
		miosIE_COMPORT_CONFIG m_IE_COMPORT_CONFIG;
		miosIE_MATRIX_CONFIG m_IE_MATRIX_CONFIG;
		miosIE_CHANNEL_MATRIX_OUTPUT m_IE_CHANNEL_MATRIX_OUTPUT;
		miosIE_CHANNEL_MATRIX_INPUT m_IE_CHANNEL_MATRIX_INPUT;
		miosIE_PU_SERIAL_PORT m_IE_PU_SERIAL_PORT;
		miosIE_PU_INPUT m_IE_PU_INPUT;
		miosIE_PU_OUTPUT m_IE_PU_OUTPUT;
		miosIE_IMAGE_ENCODE_PARA m_IE_IMAGE_ENCODE_PARA;
		miosIE_IMAGE_DISPLAY_PARA m_IE_IMAGE_DISPLAY_PARA;
		miosIE_IMAGE_TEXT_PARA m_IE_IMAGE_TEXT_PARA;
		miosIE_PU_BASEINFO m_IE_PU_BASEINFO;
		miosIE_CHANNEL_PRIVILEGE m_IE_CHANNEL_PRIVILEGE;
		miosIE_CHANNEL_INFO m_IE_CHANNEL_INFO;
		miosIE_CHANNEL_BASEINFO m_IE_CHANNEL_BASEINFO;
		miosIE_CHANNEL_ID m_IE_CHANNEL_ID;
		miosIE_PLATFORM m_IE_PLATFORM;
		miosIEX_PTZID m_IEX_PTZID;
		miosIE_CRUISEPOINT m_IE_CRUISEPOINT;
		miosIEX_CRUISENUMBER m_IEX_CRUISENUMBER;
		miosIE_PRESET_PTZ m_IE_PRESET_PTZ;
		miosIEX_PTZ_MODE m_IEX_PTZ_MODE;
		miosIE_PU_DEVICE_STATE m_IE_PU_DEVICE_STATE;
		miosIE_PU_CAPACITY_STATE m_IE_PU_CAPACITY_STATE;
		miosIE_PU_DISK_STATE m_IE_PU_DISK_STATE;
		miosIE_VIDEO_CHANNEL_STATE m_IE_VIDEO_CHANNEL_STATE;
		miosIE_ALARM_IN_STATE m_IE_ALARM_IN_STATE;
		miosIE_ALARM_OUT_STATE m_IE_ALARM_OUT_STATE;
		miosIEX_ALARM_CONFIG_TYPE m_IEX_ALARM_CONFIG_TYPE;
		miosIE_DISK_PARA m_IE_DISK_PARA;
		miosIE_ALARM_RECORD m_IE_ALARM_RECORD;
		miosIE_CAP_PHOTO m_IE_CAP_PHOTO;
		miosIE_GPIN_ALARM m_IE_GPIN_ALARM;
		miosIE_VIDEO_LOSE_ALARM m_IE_VIDEO_LOSE_ALARM;
		miosIE_VIDEO_HIDE_ALARM m_IE_VIDEO_HIDE_ALARM;
		miosIE_VIDEO_MOVE_ALARM m_IE_VIDEO_MOVE_ALARM;
		miosIE_NODE_ONLINE m_IE_NODE_ONLINE;
		miosIEX_NPU_EXTRA m_IEX_NPU_EXTRA;
		miosIEX_HARDDISK_FOR_PU m_IEX_HARDDISK_FOR_PU;
		miosIEX_VIDEO_ENCODE m_IEX_VIDEO_ENCODE;
		miosIEX_VIDEO_OSD m_IEX_VIDEO_OSD;
		miosIEX_MOTION_DETECT_REGION m_IEX_MOTION_DETECT_REGION;
		miosIEX_ALARM_ACTION m_IEX_ALARM_ACTION;
		miosIE_AUDIO_ENCODE_PARA m_IE_AUDIO_ENCODE_PARA;
		miosIEX_AUDIO_ENCODE m_IEX_AUDIO_ENCODE;
		miosIEX_PU_ONLINE m_IEX_PU_ONLINE;
		miosIEX_POLL_ENABLE m_IEX_POLL_ENABLE;
		miosIEX_PU_PARA_TYPE m_IEX_PU_PARA_TYPE;
		miosIEX_COVER_DETECT_REGION m_IEX_COVER_DETECT_REGION;
		miosIEX_COVER_REGION m_IEX_COVER_REGION;
		miosIEX_PU_GROUP m_IEX_PU_GROUP;
		miosIE_LOG_QUERY m_IE_LOG_QUERY;
		miosIE_LOG_QUERY_RESULT m_IE_LOG_QUERY_RESULT;
		miosIEX_STORAGE_TASK m_IEX_STORAGE_TASK;
		miosIEX_STORAGE_TASK_ID m_IEX_STORAGE_TASK_ID;
		miosIE_NPU_SERVER m_IE_NPU_SERVER;
		miosIE_PHOTO_INFO m_IE_PHOTO_INFO;
		miosIE_LOCAL_STORAGE_TASK m_IE_LOCAL_STORAGE_TASK;
		miosIEX_NRU_CAPACITY m_IEX_NRU_CAPACITY;
		miosIEX_NRU_STATUS m_IEX_NRU_STATUS;
		miosIEX_NRU_PARA m_IEX_NRU_PARA;
		miosIEX_VTDU_CAPACITY m_IEX_VTDU_CAPACITY;
		miosIEX_VTDU_STATUS m_IEX_VTDU_STATUS;
		miosIEX_VTDU_PARA m_IEX_VTDU_PARA;
		miosIEX_CU_STATUS m_IEX_CU_STATUS;
		miosIE_PU_STATE m_IE_PU_STATE;
		miosIE_PU_STATUS m_IE_PU_STATUS;
		miosIE_PU_LIST_ID m_IE_PU_LIST_ID;
		miosIEX_VTDU_ROUTE_MODE m_IEX_VTDU_ROUTE_MODE;
		miosIEX_PHOTO_INFO m_IEX_PHOTO_INFO;
		miosIEX_PU_STATUS m_IEX_PU_STATUS;
		miosIEX_RECORD_MGR m_IEX_RECORD_MGR;
		miosIEX_ALARM_ID m_IEX_ALARM_ID;
		miosIEX_THRESHOLD m_IEX_THRESHOLD;
		miosIEX_VIDEO_PACKET_INFO m_IEX_VIDEO_PACKET_INFO;
		miosIEX_ALARM_PRESET m_IEX_ALARM_PRESET;
		miosIEX_DEFAULT_PRESET m_IEX_DEFAULT_PRESET;
		miosIEX_PARAM_PAIR m_IEX_PARAM_PAIR;
		miosIE_STORAGE_TASK m_IE_STORAGE_TASK;
		miosIE_SCHEDULE m_IE_SCHEDULE;
		miosIEX_NETWORK_PARA m_IEX_NETWORK_PARA;
		miosIEX_NRU_SELECTION m_IEX_NRU_SELECTION;
		miosIEX_PU_ACCESS_SERVER m_IEX_PU_ACCESS_SERVER;
		miosIEX_NET_MANAGER_SERVER m_IEX_NET_MANAGER_SERVER;
		miosIEX_MAX_VIDEO_CONNECTION_NUM m_IEX_MAX_VIDEO_CONNECTION_NUM;
		miosIE_NETLINK m_IE_NETLINK;
		miosIE_OPEN_VIDEO m_IE_OPEN_VIDEO;
		miosIE_OPEN_VIDEO_ACK m_IE_OPEN_VIDEO_ACK;
		miosIE_VIDEO_CHANNEL m_IE_VIDEO_CHANNEL;
		miosIE_CHANNEL_YUNTAI_SET m_IE_CHANNEL_YUNTAI_SET;
		miosIE_PORT_RANGE m_IE_PORT_RANGE;
		miosIE_UA_REAL_IP m_IE_UA_REAL_IP;
		miosIE_URL m_IE_URL;
		miosIE_SCHEDULE_NOTIFY m_IE_SCHEDULE_NOTIFY;
		miosIE_NETLINK_PRE m_IE_NETLINK_PRE;
		miosIE_NETLINK_NEXT m_IE_NETLINK_NEXT;
		miosIE_CALL_ID m_IE_CALL_ID;
		miosIEX_CALL_INFO m_IEX_CALL_INFO;
		miosIEX_CALL_ID m_IEX_CALL_ID;
		miosIEX_ROUTE_INFO m_IEX_ROUTE_INFO;
		miosIEX_CALL_FLAG m_IEX_CALL_FLAG;
		miosIEX_FTP_LOG_INFO m_IEX_FTP_LOG_INFO;
		miosIEX_MEDIA_FROM m_IEX_MEDIA_FROM;
		miosIEX_MEDIA_TO m_IEX_MEDIA_TO;
		miosIEX_MEDIA_PARA m_IEX_MEDIA_PARA;
		miosIEX_MONITOR_CHANNEL m_IEX_MONITOR_CHANNEL;
		miosIEX_MEDIA_RCV m_IEX_MEDIA_RCV;
		miosIEX_MEDIA_RCV_CONVERSE m_IEX_MEDIA_RCV_CONVERSE;
		miosIEX_MEDIA_SEND m_IEX_MEDIA_SEND;
		miosIEX_MEDIA_SEND_CONVERSE m_IEX_MEDIA_SEND_CONVERSE;
		miosIEX_MEDIA_DIRECT m_IEX_MEDIA_DIRECT;
		miosIEX_MEDIA_PARA_PREV m_IEX_MEDIA_PARA_PREV;
		miosIEX_MEDIA_PARA_NEXT m_IEX_MEDIA_PARA_NEXT;
		miosIEX_ALARM_AUDIO_OUT m_IEX_ALARM_AUDIO_OUT;
		miosIEX_PU_ACCESS_TYPE m_IEX_PU_ACCESS_TYPE;
		miosIEX_STARTUP_MODE m_IEX_STARTUP_MODE;
		miosIE_VCR_CONTROL m_IE_VCR_CONTROL;
		miosIE_BCSH m_IE_BCSH;
		miosIE_ALARM_IN_CHANNEL m_IE_ALARM_IN_CHANNEL;
		miosIE_ALARM_OUT_CHANNEL m_IE_ALARM_OUT_CHANNEL;
		miosIE_ALARM_INFO m_IE_ALARM_INFO;
		miosIEX_ALARM_SET m_IEX_ALARM_SET;
		miosIEX_ALARM_OP m_IEX_ALARM_OP;
		miosIEX_ALARM_IN_CHANNEL m_IEX_ALARM_IN_CHANNEL;
		miosIEX_IO_CHANNEL m_IEX_IO_CHANNEL;
		miosIEX_ALARM_VIDEO_SET m_IEX_ALARM_VIDEO_SET;
		miosIEX_ALARM_ENABLE m_IEX_ALARM_ENABLE;
		miosIEX_RECORD_FILE_INFO m_IEX_RECORD_FILE_INFO;
		miosIEX_RECORD_PARAM_SET m_IEX_RECORD_PARAM_SET;
		miosIE_STORELOCATION m_IE_STORELOCATION;
		miosIE_TIME_FILE m_IE_TIME_FILE;
		miosIE_TIMESPAN m_IE_TIMESPAN;
		miosIEX_FILETYPE m_IEX_FILETYPE;
		miosIE_RESULT m_IE_RESULT;
		miosIE_TIME_DETAIL_LIST m_IE_TIME_DETAIL_LIST;
		miosIE_TIME m_IE_TIME;
		miosIE_STORETYPE m_IE_STORETYPE;
		miosIE_STARTTIME m_IE_STARTTIME;
		miosIE_ENDTIME m_IE_ENDTIME;
		miosIE_BEGINTIME m_IE_BEGINTIME;
		miosIE_FILEITEM m_IE_FILEITEM;
		miosIE_TIME_STRING m_IE_TIME_STRING;
		miosIEX_LOG_INFO m_IEX_LOG_INFO;
		miosIEX_MEDIA_INFO m_IEX_MEDIA_INFO;
		miosIEX_FUNC_TYPE m_IEX_FUNC_TYPE;
		miosIEX_QUERY_SLICE m_IEX_QUERY_SLICE;
		miosIEX_STATE_INFO m_IEX_STATE_INFO;
		miosIEX_DATABASE_INFO m_IEX_DATABASE_INFO;
		miosIEX_AAA_INFO m_IEX_AAA_INFO;
		miosIEX_VERSION m_IEX_VERSION;
		miosIEX_VERSION_ENABLE m_IEX_VERSION_ENABLE;
		miosIEX_MEDIA_LINK m_IEX_MEDIA_LINK;
		miosIEX_ALARM_OP_CHANNEL m_IEX_ALARM_OP_CHANNEL;
		miosIEX_CHANNEL_LOCATION_INFO m_IEX_CHANNEL_LOCATION_INFO;
		miosIEX_COMPOUND_ENABLE m_IEX_COMPOUND_ENABLE;
		miosIEX_CHANNEL m_IEX_CHANNEL;
		miosIEX_ALARM_STATE_ENABLE m_IEX_ALARM_STATE_ENABLE;
		miosIEX_ALARM_STATE_MAINTAIN m_IEX_ALARM_STATE_MAINTAIN;
		miosIEX_POLL_PIC_SIZE m_IEX_POLL_PIC_SIZE;
		miosIEX_TIME_SPAN m_IEX_TIME_SPAN;
		miosIEX_TB_TYPE m_IEX_TB_TYPE;
		miosIEX_SDP m_IEX_SDP;
		miosIEX_IMAGE_ENCODE_PARA_SETS m_IEX_IMAGE_ENCODE_PARA_SETS;
		miosIEX_IKEY_INFO m_IEX_IKEY_INFO;
		miosIEX_SHARED_CATALOG m_IEX_SHARED_CATALOG;
		miosIEX_REBOOT m_IEX_REBOOT;
		miospuId m_puId;
		miospuName m_puName;
		miospuPassword m_puPassword;
		miosnetId m_netId;
		miosipAddress m_ipAddress;
		mioscontrolPort m_controlPort;
		miossipPort m_sipPort;
		miossubnetMask m_subnetMask;
		miosdns m_dns;
		miosgateway m_gateway;
		miosuserName m_userName;
		miospassWord m_passWord;
		miospriority m_priority;
		miosserialPort m_serialPort;
		miosbaudRate m_baudRate;
		miosdataBit m_dataBit;
		miosparity m_parity;
		miosstopBit m_stopBit;
		miosmode m_mode;
		miosflowControl m_flowControl;
		miosdecoderType m_decoderType;
		miosdecoderAddress m_decoderAddress;
		miostimeOut m_timeOut;
		miosinput m_input;
		miosoutput m_output;
		miosChannelNumber m_ChannelNumber;
		miosstate m_state;
		mioshour m_hour;
		miosminute m_minute;
		miossecond m_second;
		miosmonth m_month;
		miosdate m_date;
		miosyear m_year;
		miosvideoId m_videoId;
		miosencodeMode m_encodeMode;
		miospicQuality m_picQuality;
		miosbitRate m_bitRate;
		miosbitRateType m_bitRateType;
		miosframeRate m_frameRate;
		miosimageSize m_imageSize;
		miosstreamType m_streamType;
		miosiFrameInterval m_iFrameInterval;
		mioscontrast m_contrast;
		miosbright m_bright;
		mioshue m_hue;
		miossaturation m_saturation;
		miosbitmapX m_bitmapX;
		miosbitmapY m_bitmapY;
		miosbitmapTimeEnable m_bitmapTimeEnable;
		miosbitmapTextEnable m_bitmapTextEnable;
		miosbitmapText m_bitmapText;
		miosbitmapTextX m_bitmapTextX;
		miosbitmapTextY m_bitmapTextY;
		miosconnectionDetectionEnabled m_connectionDetectionEnabled;
		miosdiskFullAlarmEnabled m_diskFullAlarmEnabled;
		miosdiskFullHighThreshold m_diskFullHighThreshold;
		miosdiskFullLowThreshold m_diskFullLowThreshold;
		miosdiskErrorAlarmEnabled m_diskErrorAlarmEnabled;
		miosalarmPreRecordTime m_alarmPreRecordTime;
		miosalarmRecordTime m_alarmRecordTime;
		miosalarmOutputTime m_alarmOutputTime;
		miosalarmOutputActivatedTimes m_alarmOutputActivatedTimes;
		miosphotoResolution m_photoResolution;
		miosphotoQuality m_photoQuality;
		miosshootTimes m_shootTimes;
		miosgpinAlarmEnabled m_gpinAlarmEnabled;
		miosgpinAlarmStatus m_gpinAlarmStatus;
		miosgpinAlarmOutput m_gpinAlarmOutput;
		miosgpinAlarmRecord m_gpinAlarmRecord;
		miosgpinAlarmShoot m_gpinAlarmShoot;
		miosvideoLoseAlarmEnabled m_videoLoseAlarmEnabled;
		miosvideoLoseAlarmOutput m_videoLoseAlarmOutput;
		mioshideDetectionAlarmEnabled m_hideDetectionAlarmEnabled;
		mioshideDetectionAlarmTime m_hideDetectionAlarmTime;
		mioshideDetectionX m_hideDetectionX;
		mioshideDetectionY m_hideDetectionY;
		mioshideDetectionWidth m_hideDetectionWidth;
		mioshideDetectionHeight m_hideDetectionHeight;
		mioshideDetectionAlarmOutput m_hideDetectionAlarmOutput;
		mioshideDetectionAlarmRecord m_hideDetectionAlarmRecord;
		miosmotionDetectionAlarmEnabled m_motionDetectionAlarmEnabled;
		miosmotionDetectionAlarmTime m_motionDetectionAlarmTime;
		miosmotionDetectionBlocks m_motionDetectionBlocks;
		miosmotionDetectionFrequency m_motionDetectionFrequency;
		miosmotionDetectionSensitivity m_motionDetectionSensitivity;
		miosmotionDetectionAlarmOutput m_motionDetectionAlarmOutput;
		miosmotionDetectionAlarmRecord m_motionDetectionAlarmRecord;
		miosmotionDetectionAlarmShoot m_motionDetectionAlarmShoot;
		miosrecordEnable m_recordEnable;
		miosrecycleRecEnable m_recycleRecEnable;
		miosschedule m_schedule;
		miosrecordPolicy m_recordPolicy;
		miosframeInterval m_frameInterval;
		miosfilenameSuffix m_filenameSuffix;
		miosfileType m_fileType;
		miosfromDate m_fromDate;
		miostoDate m_toDate;
		miosrecordFile m_recordFile;
		miostotalSize m_totalSize;
		miosfreeSize m_freeSize;
		miosfileName m_fileName;
		miosdeviceStatus m_deviceStatus;
		miosdisk m_disk;
		miosvideoChannel m_videoChannel;
		miosalarmIn m_alarmIn;
		miosalarmOut m_alarmOut;
		mioslogType m_logType;
		miosstartLogDate m_startLogDate;
		miosendLogDate m_endLogDate;
		miosstartIndex m_startIndex;
		miosmaxResults m_maxResults;
		mioslogInfo m_logInfo;
		miosalarmServerIp m_alarmServerIp;
		miosalarmServerPort m_alarmServerPort;
		miosalarmUrl m_alarmUrl;
		miosheartBeatServerIp m_heartBeatServerIp;
		miosheartBeatServerPort m_heartBeatServerPort;
		miosregisterServerIp m_registerServerIp;
		miosregisterServerPort m_registerServerPort;
		miosenableHeartBeat m_enableHeartBeat;
		miosheartBeatPeriod m_heartBeatPeriod;
		miosptzId m_ptzId;
		mioscmd m_cmd;
		miosparam m_param;
		miosspeed m_speed;
		miosprotocol m_protocol;
		miospresetIndex m_presetIndex;
		miospresetName m_presetName;
		mioscruiseNumber m_cruiseNumber;
		mioscruisePoint m_cruisePoint;
		mioscontrolAction m_controlAction;
		miosfileUrl m_fileUrl;
		miospuIp m_puIp;
		miosalarmType m_alarmType;
		miosserverType m_serverType;
		mioschannelNumber m_channelNumber;
		miosdiskNumber m_diskNumber;
		miostimeStamp m_timeStamp;
		miosdata m_data;
		miosoldVersion m_oldVersion;
		miosnewVersion m_newVersion;
		miosupgradeResult m_upgradeResult;
		miostransparentAction m_transparentAction;
		miostransparentData m_transparentData;
		miospuPort m_puPort;
		miospuType m_puType;
		miosenableLongConnection m_enableLongConnection;
		miosexpires m_expires;
		miosmediaType m_mediaType;
		miosimageWidth m_imageWidth;
		miosimageHeight m_imageHeight;
		miosvideoFormat m_videoFormat;
		mioscuId m_cuId;
		miosusername m_username;
		miosuserStatus m_userStatus;
		miosdomainUsername m_domainUsername;
		miosdomainPassword m_domainPassword;
		mioscustomerId m_customerId;
		miosdisplayName m_displayName;
		miosuserLevel m_userLevel;
		miosdescription m_description;
		miosdisabled m_disabled;
		miosaddress m_address;
		miosemail m_email;
		miosdept m_dept;
		miosfixedNumber m_fixedNumber;
		miosmobileNumber m_mobileNumber;
		mioscreator m_creator;
		mioscreatedDateStart m_createdDateStart;
		mioscreatedDateEnd m_createdDateEnd;
		mioscustomerName m_customerName;
		miostype m_type;
		mioscontactName m_contactName;
		miosfaxNumber m_faxNumber;
		mioszipCode m_zipCode;
		miosbankName m_bankName;
		miosbankAccount m_bankAccount;
		miosmaxUsers m_maxUsers;
		miosmaxOnlineUsers m_maxOnlineUsers;
		miosadminUsername m_adminUsername;
		mioscreatedDate m_createdDate;
		miosareaId m_areaId;
		mioscuIdFrom m_cuIdFrom;
		mioscuIdTo m_cuIdTo;
		miosmaxVideoChannels m_maxVideoChannels;
		miosuserStatistic m_userStatistic;
		mioscurrentUsers m_currentUsers;
		mioscurrentOnlineUsers m_currentOnlineUsers;
		miosstorageQuota m_storageQuota;
		miosdiskFullAlarmThreshold m_diskFullAlarmThreshold;
		miosautoFreeSpaceSize m_autoFreeSpaceSize;
		miosfirstInputChannel m_firstInputChannel;
		miosfirstOutputChannel m_firstOutputChannel;
		miosfirstVideoChannel m_firstVideoChannel;
		miosfirstAudioChannel m_firstAudioChannel;
		miosmaxInputChannel m_maxInputChannel;
		miosmaxOutputChannel m_maxOutputChannel;
		miosmaxVideoChannel m_maxVideoChannel;
		miosmaxAudioChannel m_maxAudioChannel;
		miosaudioChannel m_audioChannel;
		miosvsType m_vsType;
		mioslocalStorageEnabled m_localStorageEnabled;
		miosrecordMode m_recordMode;
		miosnetworkInterface m_networkInterface;
		miospuControlPort m_puControlPort;
		miospuSipPort m_puSipPort;
		miosvideoPort m_videoPort;
		miosaudioPort m_audioPort;
		miosdvsName m_dvsName;
		miosloginUsername m_loginUsername;
		miosloginPassword m_loginPassword;
		miosx m_x;
		miosy m_y;
		miosgpio m_gpio;
		miosonline m_online;
		miosmanufacturerId m_manufacturerId;
		miosmanufacturerName m_manufacturerName;
		miosproductVersion m_productVersion;
		miossoftwareVersion m_softwareVersion;
		mioslastUpgradeDate m_lastUpgradeDate;
		miosplace m_place;
		mioscameraName m_cameraName;
		miosvs m_vs;
		mioswidth m_width;
		miosheight m_height;
		miosptzProtocol m_ptzProtocol;
		mioscontrolPTZType m_controlPTZType;
		miostimePieceLen m_timePieceLen;
		miosmodel m_model;
		miossetupType m_setupType;
		miosparentId m_parentId;
		miosareaName m_areaName;
		miosaction m_action;
		miossubscriberId m_subscriberId;
		miosexpiringDate m_expiringDate;
		mioslinkable m_linkable;
		miossourceType m_sourceType;
		miosseverity m_severity;
		miostypeName m_typeName;
		miosalarmDate m_alarmDate;
		mioseliminated m_eliminated;
		miosdiskFullThreshold m_diskFullThreshold;
		miosgpinAlarm m_gpinAlarm;
		mioscameraAlarm m_cameraAlarm;
		miospreset m_preset;
		mioscruise m_cruise;
		miostaskName m_taskName;
		miosstartTime m_startTime;
		miosduration m_duration;
		miostaskType m_taskType;
		miosmaxTimes m_maxTimes;
		miostask m_task;
		miostaskId m_taskId;
		miosstartTimeStamp m_startTimeStamp;
		miosendTimeStamp m_endTimeStamp;
		miosfileSize m_fileSize;
		miosfilePath m_filePath;
		miosstatus m_status;
		miosfileId m_fileId;
		miosmduIpAddressList m_mduIpAddressList;
		mioscsgIpAddressList m_csgIpAddressList;
		miossourceId m_sourceId;
		miospassword m_password;
		miosforDecoder m_forDecoder;
		miosworkMode m_workMode;
		mioshttpRegisterServerIp m_httpRegisterServerIp;
		mioshttpRegisterServerPort m_httpRegisterServerPort;
		miosenableHttpHeartbeat m_enableHttpHeartbeat;
		mioshttpHeartbeatServerIp m_httpHeartbeatServerIp;
		mioshttpHeartbeatServerPort m_httpHeartbeatServerPort;
		mioshttpHeartbeatPeriod m_httpHeartbeatPeriod;
		miosenableSipRegister m_enableSipRegister;
		miossipRegisterServerIp m_sipRegisterServerIp;
		miossipRegisterServerPort m_sipRegisterServerPort;
		miosenableSipHeartbeat m_enableSipHeartbeat;
		miossipHeartbeatServerIp m_sipHeartbeatServerIp;
		miossipHeartbeatServerPort m_sipHeartbeatServerPort;
		miossipHeartbeatPeriod m_sipHeartbeatPeriod;
		miosdiskPath m_diskPath;
		miosdiskOccupiedPercent m_diskOccupiedPercent;
		miosuserId m_userId;
		mioskeepAlivePeriod m_keepAlivePeriod;
		mioshideAreaEnabled m_hideAreaEnabled;
		mioshideImageArea m_hideImageArea;
		mioscustomerStatus m_customerStatus;
		miosfilename m_filename;
		miosmduIpAddress m_mduIpAddress;
		mioscsgIpAddress m_csgIpAddress;
		miosHttpHeartbeatPeriod m_HttpHeartbeatPeriod;
		miosgpinAlarm_gpinAlarmEnabled m_gpinAlarm_gpinAlarmEnabled;
		miosgpinAlarm_alarmOutputActivatedTimes m_gpinAlarm_alarmOutputActivatedTimes;
		miosgpinAlarm_gpinAlarmStatus m_gpinAlarm_gpinAlarmStatus;
		miosgpinAlarm_gpinAlarmOutput m_gpinAlarm_gpinAlarmOutput;
		miosgpinAlarm_gpinAlarmRecord m_gpinAlarm_gpinAlarmRecord;
		miosgpinAlarm_gpinAlarmShoot m_gpinAlarm_gpinAlarmShoot;
		mioscameraAlarm_videoLoseAlarmEnabled m_cameraAlarm_videoLoseAlarmEnabled;
		mioscameraAlarm_videoLoseAlarmOutput m_cameraAlarm_videoLoseAlarmOutput;
		mioscameraAlarm_hideDetectionAlarmEnabled m_cameraAlarm_hideDetectionAlarmEnabled;
		mioscameraAlarm_hideDetectionAlarmTime m_cameraAlarm_hideDetectionAlarmTime;
		mioscameraAlarm_hideDetectionX m_cameraAlarm_hideDetectionX;
		mioscameraAlarm_hideDetectionY m_cameraAlarm_hideDetectionY;
		mioscameraAlarm_hideDetectionWidth m_cameraAlarm_hideDetectionWidth;
		mioscameraAlarm_hideDetectionHeight m_cameraAlarm_hideDetectionHeight;
		mioscameraAlarm_hideDetectionAlarmOutput m_cameraAlarm_hideDetectionAlarmOutput;
		mioscameraAlarm_hideDetectionAlarmRecord m_cameraAlarm_hideDetectionAlarmRecord;
		mioscameraAlarm_motionDetectionAlarmEnabled m_cameraAlarm_motionDetectionAlarmEnabled;
		mioscameraAlarm_motionDetectionAlarmTime m_cameraAlarm_motionDetectionAlarmTime;
		mioscameraAlarm_motionDetectionBlocks m_cameraAlarm_motionDetectionBlocks;
		mioscameraAlarm_motionDetectionFrequency m_cameraAlarm_motionDetectionFrequency;
		mioscameraAlarm_motionDetectionSensitivity m_cameraAlarm_motionDetectionSensitivity;
		mioscameraAlarm_motionDetectionAlarmOutput m_cameraAlarm_motionDetectionAlarmOutput;
		mioscameraAlarm_motionDetectionAlarmRecord m_cameraAlarm_motionDetectionAlarmRecord;
		mioscameraAlarm_motionDetectionAlarmShoot m_cameraAlarm_motionDetectionAlarmShoot;
		miosName m_Name;
		miosAddress m_Address;
		miosPrivilege m_Privilege;
		miosParent m_Parent;
		miosStatus m_Status;
		miosSubnum m_Subnum;
		miosResult m_Result;
		miosFormat m_Format;
		miosVideo m_Video;
		miosAudio m_Audio;
		miosMaxBitrate m_MaxBitrate;
		miosReceiveSocket m_ReceiveSocket;
		miosBitrate m_Bitrate;
		miosFileType m_FileType;
		miosMaxFileNum m_MaxFileNum;
		miosBeginTime m_BeginTime;
		miosEndTime m_EndTime;
		miosRealFileNum m_RealFileNum;
		miosSendFileNum m_SendFileNum;
		miosCommand m_Command;
		miosManufacturer m_Manufacturer;
		miosSublist m_Sublist;
		miosItem m_Item;
		miosSublist_Item m_Sublist_Item;
		miosFileInfolist m_FileInfolist;
		miositem m_item;
		miosFileInfolist_item m_FileInfolist_item;
		miosModel m_Model;
		miosFirmware m_Firmware;
		miosMaxcamera m_Maxcamera;
		miosOnline m_Online;
		miosErrencodenum m_Errencodenum;
		miosRecord m_Record;
		miosSinceStartup m_SinceStartup;
		miosCameralist m_Cameralist;
		miosCameralist_item m_Cameralist_item;
		miosValue m_Value;
		miosAll m_All;
		miosFree m_Free;
		miosMedialink m_Medialink;
	}unionMember;
}miosMaxIE;

typedef struct miosMinIE{
	MIO_UINT32 type;
}miosMinIE;




#ifdef __cplusplus
}
#endif


#endif
