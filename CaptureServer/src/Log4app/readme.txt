来源：
http://log4cplus.sourceforge.net/

版本：
log4cplus 1.0.4

2011-06-16  modify by hu
增加了DailyFileAppender类，支持按时段（月、周、日、半日、时、小时、分钟）写日志文件，同一时段的日志写在同一个文件中

2012-08-06  modify by hu
修改了FileAppender::open(std::ios::openmode mode)函数，防止带中文路径的日志文件打开失败；