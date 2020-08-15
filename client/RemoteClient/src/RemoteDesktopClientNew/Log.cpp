#include "stdafx.h"
#include "Log.h"
#include <direct.h>

int LogInit(string strUnitId)
{
	// ÈÕÖ¾
	SharedAppenderPtr m_pSharePtr;
	log4cplus::Logger m_tlogger;

	string strPath = GetExePath()+"/log" ;
	_mkdir(strPath.c_str());
	char szLogFileName[1024];
	sprintf_s(szLogFileName,"%s\\VideoDetect_%s.log",strPath.c_str(),strUnitId.c_str());
	m_pSharePtr = new RollingFileAppender(szLogFileName, 20*1024*1024, 2, true);

	m_pSharePtr->setName(ALARM_SERVER_LOG);
	std::string pattern = "%D{%m/%d/%y %H:%M:%S} - [%t] - %m %n";
	std::auto_ptr<Layout> _layout(new PatternLayout(pattern));
	m_pSharePtr->setLayout( _layout );
	m_tlogger = Logger::getInstance(ALARM_SERVER_LOG);
	m_tlogger.addAppender(m_pSharePtr);
	m_tlogger.setLogLevel(INFO_LOG_LEVEL);

	return 0;
}