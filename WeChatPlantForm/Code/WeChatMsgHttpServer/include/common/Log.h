
#ifndef __LOG_H_
#define __LOG_H_
#include <spdlog/spdlog.h>
#include <spdlog/sinks/sink.h>
#include <spdlog/sinks/daily_file_sink.h>
//#include <spdlog/sinks/syslog_sink.h>
#include <string.h>

#ifdef WIN32
#define LOG_INFO(LOG,...) if(LOG){LOG->info(__VA_ARGS__);}
#define LOG_WARN(LOG,...) if(LOG){LOG->warn(__VA_ARGS__);}
#define LOG_ERR(LOG,...)  if(LOG){LOG->error(__VA_ARGS__);}
#define LOG_DBG(LOG,...) if(LOG){LOG->debug(__VA_ARGS__);}
#else
#define LOG_INFO(LOG,msg...) if(LOG){LOG->info(msg);}
#define LOG_WARN(LOG,msg...) if(LOG){LOG->warn(msg);}
#define LOG_ERR(LOG,msg...)  if(LOG){LOG->error(msg);}
#define LOG_DBG(LOG,msg...) if(LOG){LOG->debug(msg);}
#endif

#define __FILENAME__ (strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1) : __FILE__)
#endif