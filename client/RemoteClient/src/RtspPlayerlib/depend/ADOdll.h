
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ADODLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ADODLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef ADODLL_EXPORTS
#define ADODLL_API __declspec(dllexport)
#else
#define ADODLL_API __declspec(dllimport)
#endif


#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","rsEOF")

/***********************************/

#define GROUPNAME_DELETE 1
#define GROUPINFO_DELETE 0
#define PUNAME_DELETE 1
#define PUINFO_DELETE 0
#define CHANNEL_DELETE 1
#define CHANNEL_ALLDELETE 0
#define POLLINFO_DELETE 1
#define POLLPLAN_ALLDELETE 0
#define BCPLAN_DELETE 1
#define BCINFO_ALLDELETE 0
#define CONFIG_SAVE 0
#define CONFIG_MODIFY 1
#define LOGIN_SAVE 0
#define LOGIN_MODIFY 1
#define CHANNELGROUP_DELGROUP 1
#define CHANNELGROUP_DELCHANNEL 0

/************************************/

// This class is exported from the ADOdll.dll
//class ADODLL_API CADOdll {
//public:
//	CADOdll(void);
//	// TODO: add your methods here.
//};
//
//extern ADODLL_API int nADOdll;
//
// ADODLL_API int fnADOdll(void);




/********************************************/

struct PuNodeInfo 
{
	BOOL		Online;
	int			DeviceType;
	char		ManufactureID[18];
	int			ChannelNum;
	char		VideoInNum[18];
	char		VideoOutNum[18];
	char		AudioInNum[18];
	char		AudioOutNum[18];
	char		AlarmInNum[18];
	char		AlarmOutNum[18];
	char		NonStandardNum[18];
	char		MatrixNum[32];
	char		IPAddr[40];
	int			DevicePort;
};

struct PuChannelInfo
{
	int			ChannelType;
	int			VideoNo;
	double		Longitude;
	double		Latitude;
};

struct GroupInfo
{
	struct	GroupInfo	*next;
	
	int 		GroupID;
	char		GroupName[32];

	struct  PuNodeIDNode		*pulist;
};

struct PuNodeIDNode 
{
	struct	PuNodeIDNode		*next;

	int			GroupID;
	char		NID[18];
	char		NodeName[32];

	struct  PuNodeInfo		puinfo;
	struct	ChannelNoNode	*channellist;
};

struct ChannelNoNode
{
	struct	ChannelNoNode		*next;	

	char		NID[18];
	int			ChannelNo;
	char		ChannelName[32];
	struct  PuChannelInfo		channelinfo;
};


struct ConfigurationInfo		//配置信息
{
	char		RecFilePath[255];
	char		LoadRecFilePath[255];
	char		PhotoFilePath[255];
	char		AlarmLogPath[255];
	BOOL        SavePassword;
	char		LastCustomerName[32];
	char		LastCustomerID[32];
	char		LastPassWord[32];
	char		CMSIP[32];
	char        CMSID[16];
	UINT        CMSPort;
};

struct LoggingIn				//用户登录相关信息
{
	char		CustomerName[32];
	char		CustomerID[32];
	char        SessionID[33];
	int			CustomerGroup;
	BOOL		Online;
	char		PassWord[32];
	char		NMSIP[32];
	char		CMSIP[32];
	char		CCSIP[32];
	int			Port;
	int			Level;
	int			Privilege;
};

struct AlarmInfo 
{
	struct AlarmInfo	*next;

	char		PuID[18];
	int			ChannelNo;
	int			AlarmAction;
	int			AlarmType;
	char		AlarmChannelName[32];
	int			AlarmChannelType;
	int			AlarmChannelNo;
	int			VideoChannelNo;
	char		UseData[255];
	char		AlarmTime[32];


}; 

struct PollInfo
{
	struct  PollInfo	*next;

	char		PuID[18];
	int			ChannelNo;
	char		ChannelName[32];
	int			PollTime;
	BOOL		Audio_flags;

};

struct PollList
{
	struct	PollList	*next;

	char		PollName[32];
	char		CustomerID[32];
	char		CustomerName[32];

	struct  PollInfo    *pollinfo;

};

struct BroadcastList
{	
	struct BroadcastList *next;

	char		BcGroupName[32];
	char		CustomerID[32];
	char		CustomerName[32];

	struct  BroadcastInfo  *bcinfolist;

};

struct BroadcastInfo
{
	struct BroadcastInfo *next;

	int			PuListID;
	char		PuID[18];
	int			ChannelNo;
	char		ChannelName[32];
	char		BcLogInfo[255];
};

struct  RecordInfo
{
	struct RecordInfo *next;

	char		FileName[128];
	int			FileType;
	int			StoreType;
	char		BeginTime[32];
	char		EndTime[32];
	char		Size[32];
	char		CustomerID[32];
	char		CustomerName[32];
	char		PuID[32];
	int			ChannelNo;
	char		ChannelName[32];
};

struct  CustomerLogInfo
{
	struct CustomerLogInfo *next;

	char		CustomerName[32];
	char		LogTime[32];
	int			LogEvent;
	char		LogObjectID[18];
	char		LogChannel[32];
	char		LogInfo[255];
};

struct  CapPhotoInfo
{
	struct CapPhotoInfo *next;

	char		PuID[18];
	char		UserName[32];
	int			ChannelNo;
	char		ChannelName[32];
	int			PhotoWidth;
	int			PhotoHeight;						
	char		PhotoPath[32];
	char		PhotoType[2];								//告警抓拍 手动抓拍
	char		CapTime[32];
};

struct ChannelGroupList
{
	struct ChannelGroupList *next;

	char		CustomerName[32];
	char		CustomerID[32];
	char		GroupName[32];

	struct ChannelGroupInfo *cginfo;
};

struct ChannelGroupInfo
{
	struct	ChannelGroupInfo  *next;

	char		CustomerID[32];
	char		GroupName[32];
	int			ChannelNo;
	char		PuID[18];
	char		ChannelName[32];
	BOOL		Online;
};





/********DataBase*********/

ADODLL_API BOOL ConnectionDataBase();

ADODLL_API _RecordsetPtr OpenSourceData(_bstr_t strsql);

ADODLL_API BOOL CloseConnectionDataBase();

ADODLL_API int fhnado_FreeGroupInfo();

ADODLL_API int fhnado_FreePuNodeIDNode();

ADODLL_API int fhnado_FreeChannelNoNode();

ADODLL_API int fhnado_FreePollList();

ADODLL_API int fhnado_FreePollInfo();

ADODLL_API int fhnado_FreeBroadcastList();

ADODLL_API int fhnado_FreeBroadcastInfo();

ADODLL_API int fhnado_FreeRecordInfo();

ADODLL_API int fhnado_FreeAlarmInfo();

ADODLL_API int fhnado_FreeCustomerLogInfo();

ADODLL_API int fhnado_FreeCapPhotoInfo();


/*******GroupInfo********/

ADODLL_API int fhnado_SaveGroupInfo(GroupInfo group);							/*save to database*/

ADODLL_API int fhnado_DelGroupInfo(int groupid, int deltype);					/*删除选中Group信息*/

ADODLL_API struct GroupInfo * fhnado_GetAllGroupInfo();							/*获得所有Group的名称*/

ADODLL_API struct GroupInfo fhnado_GetSelectGroupInfo(int groupid);				/*获得选定Group*/

ADODLL_API struct PuNodeIDNode * fhnado_GetPuOfGroup(int groupid);				/*获得Group下的Pu名称*/
 
/*******PuNodeInfo********/	

ADODLL_API int fhnado_SavePuNode(PuNodeIDNode punodeid);						/*保存Pu信息到数据库*/
		
ADODLL_API int fhnado_DelPuNode(char *puid, int deltype);						/*删除Pu信息*/
	
ADODLL_API struct PuNodeIDNode * fhnado_GetAllPuNodeInfo();						/*获得所有Pu*/

ADODLL_API struct PuNodeIDNode fhnado_GetSelectPuNodeInfo(char *puid);			/*获得被选定的Pu信息*/

ADODLL_API struct ChannelNoNode * fhnado_GetChannelOfPuNode(char *puid);		/*获得Pu下的通道名称*/					

/********PuChannelInfo*********/

ADODLL_API int fhnado_SavePuChannel(ChannelNoNode channelno);					/*保存channel到数据库*/

ADODLL_API int fhnado_DelPuChannel(char *puid, int channelno, int deltype);		/*删除channel信息*/

ADODLL_API struct ChannelNoNode * fhnado_GetAllChannelInfo();					/*获得所有channel信息*/

ADODLL_API struct ChannelNoNode fhnado_GetSelectChannelInfo(char *puid, int channelno);

ADODLL_API void fhnado_GetChannelNoAndPuID(char *channelname, ChannelNoNode &chninfo);

/*******PollInfo*******/

ADODLL_API int fhnado_SavePollInfo(PollList plist);								/*保存轮询计划信息*/

ADODLL_API struct PollList * fhnado_GetAllPollName(char *customerID);			/*获得全部轮询计划的名称*/

ADODLL_API struct PollInfo * fhnado_GetSelectPollInfo(char *customerID, char *pollname);			/*获得被选中计划的信息*/

ADODLL_API int fhnado_DelPollList(char *customerID, char *pollname, int deltype);					/*删除轮询计划列表*/

ADODLL_API int fhnado_DelChannelOfPoll(char *customerID, char *pollname, PollInfo pollchannel);	/*删除某轮询计划下的监控通道*/

ADODLL_API int fhnado_SaveChannelOfPoll(char *customerID, char *pollname, PollInfo pollchannel);	/*往某轮询计划下添加监控通道*/

ADODLL_API int fhnado_ModifyPollTime(char *customerID, char *pollname, PollInfo pollchannel);
		
ADODLL_API int fhnado_PollPlanExport(char *pollfile, PollList polllist);		/*轮询计划导出*/

ADODLL_API int fhnado_PollPlanImport(char *pollfile);							/*轮询计划导入*/

/******BroadcastInfo*******/

ADODLL_API int fhnado_SaveBCInfo(BroadcastList bclist);	

ADODLL_API struct BroadcastList * fhnado_GetAllBCName(char *cusid);

ADODLL_API struct BroadcastInfo * fhnado_GetSelectBCInfo(char *cusid, char *bcname);

ADODLL_API int fhnado_DelBCList(char *cusid, char *bcname, int deltype);

ADODLL_API int fhnado_DelChannelOfBC(char *cusid, char *bcname, BroadcastInfo bcchannel);

ADODLL_API int fhnado_SaveChannelofBC(char *cusid, char *bcname, BroadcastInfo bcchannel);

/********RecordInfo********/

ADODLL_API int fhnado_SaveRecInfo(RecordInfo recinfo);

ADODLL_API struct RecordInfo * fhnado_QueryRecInfo(char *puid, int channelno, int storetype, int filetype, char *starttime, char *endtime);

ADODLL_API int fhnado_DelRecinfo(char *puid, int channelno, int deltype);

/*********Logging In***********/

ADODLL_API int fhnado_SaveLoggingIn(LoggingIn login, int savetype);							/*保存用户登录信息*/

ADODLL_API int fhnado_DelLoggingIn(char *cusid, int deltype);					/*删除选定用户登录信息*/

ADODLL_API struct LoggingIn fhnado_GetSelectLogIn(char *cusid);					/*获得被选中用户信息*/

/****CU Software Info****/

ADODLL_API int fhnado_SaveConfigurationInfo(ConfigurationInfo configinfo, int savetype);/*保存系统配置信息*/

ADODLL_API struct ConfigurationInfo fhnado_GetConfigurationInfo();				/*获得系统配置信息*/

ADODLL_API int fhnado_DelConfigurationInfo();

ADODLL_API int fhnado_SaveRecFilePath(char *cusid, char *path);					/*保存本地录像文件路径*/

ADODLL_API int fhnado_GetRecFilePath(char *cusid, char *recfilepath/*out*/);	/*获得本地录像路径*/

ADODLL_API int fhnado_SaveLoadRecFilePath(char *cusid, char *path);				/*保存下载录像文件路径*/

ADODLL_API int fhnado_GetLoadRecFilePath(char *cusid, char *loadrecfilepath);	/*获得下载文件路径*/

ADODLL_API int	fhnado_SavePhotoFilePath(char *cusid, char *path);				/*保存图片路径*/

ADODLL_API int fhnado_GetPhotoFilePath(char *cusid, char *photofilepath);		/*获得图片路径*/

ADODLL_API int fhnado_SaveAlarmLogPath(char *cusid, char *path);				/*保存报警*/

ADODLL_API int fhnado_GetAlarmLogPath(char *cusid, char *alarmlogpath);

/*********AlarmInfo**********/

ADODLL_API int fhnado_SaveAlarmInfo(AlarmInfo alarm);							/*保存报警消息*/

ADODLL_API AlarmInfo * fhnado_QueryAlarmInfo(char *puid, int channelno, char *starttime, char *endtime);

ADODLL_API int fhnado_DelAlarmInfo(char *puid, int channelno, int deltype);

/*****CustomerLogInfo*****/

ADODLL_API int fhnado_SaveCusInfo(CustomerLogInfo cusinfo);

ADODLL_API CustomerLogInfo * fhnado_GetDateTime();

//ADODLL_API CustomerLogInfo * fhnado_QueryCusLog(char *cusname, char *logtime);

ADODLL_API CustomerLogInfo * fhnado_QueryCustomerLogInfo(char *cusname, char *logtime);

ADODLL_API int fhnado_DelAllCustomerLogInfo();

/****CapPhotoInfo*****/

ADODLL_API int fhnado_SaveCapPhotoInfo(CapPhotoInfo photoinfo);

ADODLL_API CapPhotoInfo * fhnado_QueryCapPhotoInfo(char *puid, int channelno, char *starttime, char *endtime);

ADODLL_API int fhnado_DelAllCapPhotoInfo();

/*****ChannelGroupByCustomer*****/

ADODLL_API int fhnado_SaveChannelGroup(ChannelGroupList cgroup);

ADODLL_API struct ChannelGroupList * fhnado_GetAllCGName(char *customerid);

ADODLL_API struct ChannelGroupInfo * fhnado_GetSelectCGroupInfo(char *customerid, char *cgroupname);

ADODLL_API int fhnado_DelChannelGroupList(char *customerid, char *groupname, int deltype);

ADODLL_API int fhnado_DelChannelOfChnGroup(char *customerid, char *groupname, ChannelGroupInfo cgchannel);

ADODLL_API int fhnado_SaveChannelofCGroup(char *customerid, char *cgroupname, ChannelGroupInfo cgchannel);







/*********创建动态链表***********/

//struct PuNodeInfo * PutPuNodeInfoToList(PuNodeInfo punode);
//
//struct PuChannelInfo * PutChannelInfoToList(PuChannelInfo puchannel);
//
//struct OperationInfo * PutLoginInfoToList(OperationInfo login);
//
//struct AlarmInfo * PutAlarmInfoToList(AlarmInfo alarm);
//
//struct GroupInfo * AddGroupNodeToList(GroupList &grouplist, GroupInfo group);
//
//void fhnado_AddPuNodeToList(PuNodeList &nodelist, PuNodeInfo punode);
//
//struct ChannelNoNode * AddChannelNodeToList(ChannelList &chnlist, PuChannelInfo puchannel);
//
//int SelectPuIDonGroupID(GroupInfo group);
//
// int SelectChannelonPuID(PuNodeInfo punode);

//extern ADODLL_API struct GroupList		g_groupList;
//
//extern ADODLL_API struct PuNodeList		g_nodeList;
//
// extern ADODLL_API struct ChannelList	g_channellist;

//struct GroupList		//组的头尾指针
//{
//	struct		GroupInfo *phead;
//	struct		GroupInfo *ptail;
//	int		Data;
//};
//
//struct PuNodeList		//Pu的头尾指针
//{
//
//	struct		PuNodeIDNode	*phead;
//	struct		PuNodeIDNode	*ptail;
//	int		Data;
//};
//
//struct ChannelList		//通道的头尾指针
//{
//
//	struct		ChannelNoNode		*phead;
//	struct		ChannelNoNode		*ptail;
//	int		Data;
//};

//ADODLL_API int fhnado_SavePollName(PollList plist);								/*保存轮询计划*/
//ADODLL_API int fhnado_BCSave(char *BCchnData, char *bcGroupname, int pulistid, char *bcloginfo);

//ADODLL_API int fhnado_UpdateBCName();
//ADODLL_API int fhnado_PollSave(char *ChannelData, char *PuData, char *pollname, int polltime, bool audioflags);

//ADODLL_API int fhnado_UpdatePollName();										/*将轮询名称表中的名称和计划表中的名称对比*/
//ADODLL_API int fhnado_DelPollInfo(char *pollname, int deltype);				/*删除轮询计划*/
//ADODLL_API int fhnado_DelBCInfo(char *bcname, int deltype);
//ADODLL_API int fhnado_SaveBCList(BroadcastList bclist);
//ADODLL_API struct LoggingIn * fhnado_GetAllLogIn();								/*获得全部用户注册信息*/
