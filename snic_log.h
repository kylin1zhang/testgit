#include "zlog.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <time.h>

void get_file_name(const char *,char *);


/*judge log is older than timer time*/
/*0 expired -1 not expired*/

int log_expired(const char *,time_t*);

/*detect log file size ,if over designed size return size ,else -1*/

long detect_log_size(const char *filepath,long targetsize);

/*  log compress and delete old file*/

void compress_log(const char *);


/* * delete  the whole expired file*/
/* * succes 0 failed -1*/

int dellog(const char *);

#define LevelOff                 0
#define PANICEnable		 1
#define ERREnable                2
#define WARNEnable               3
#define INFOEnable               4
#define DBGEnable                5


#define MODULE_NET                 0
#define MODULE_BLK                 1
#define MODULE_SYS                 2


enum{
	ZLOG_LEVEL_PANIC = 110,
};
#define zlog_middle(module, fmt, arg...) \
	zlog(module, __FILE__, sizeof(__FILE__)-1, \
	__func__, sizeof(__func__)-1, __LINE__, \
	ZLOG_LEVEL_PANIC, fmt,  ##arg);

#define zlog_panic(module, fmt, arg...) do { \
	zlog_middle(module, fmt, ##arg);\
	abort();\
} while (0)

/*#define zlog_panic(module, fmt, arg...) \*/
/*	zlog(module, __FILE__, sizeof(__FILE__)-1, \*/
/*	__func__, sizeof(__func__)-1, __LINE__, \*/
/*	ZLOG_LEVEL_PANIC, fmt,  ##arg);*/

#define SNIC__PRINT_DBG(module, fmt, arg...) do { \
if (snic_get_dbg_level() >= DBGEnable) { \
    snic_logfilter(ZLOG_LEVEL_DEBUG, module,__FILE__, sizeof(__FILE__) - 1,__func__,\
	sizeof(__func__) -1,__LINE__, fmt, ##arg);\
} } while (0)

#define SNIC__PRINT_INFO(module, fmt, arg...) do { \
if (snic_get_dbg_level() >= INFOEnable) { \
    snic_logfilter(ZLOG_LEVEL_INFO, module,__FILE__, sizeof(__FILE__) - 1,__func__,\
	sizeof(__func__) -1,__LINE__, fmt, ##arg);\
} } while (0)

#define SNIC__PRINT_WARN(module, fmt, arg...) do { \
if (snic_get_dbg_level() >= WARNEnable) { \
    snic_logfilter(ZLOG_LEVEL_WARN, module,__FILE__, sizeof(__FILE__) - 1,__func__,\
	sizeof(__func__) -1,__LINE__, fmt, ##arg);\
} } while (0)

#define SNIC__PRINT_ERR(module, fmt, arg...) do { \
if (snic_get_dbg_level() >= ERREnable) { \
    snic_logfilter(ZLOG_LEVEL_ERROR, module,__FILE__, sizeof(__FILE__) - 1,__func__,\
	sizeof(__func__) -1,__LINE__, fmt, ##arg);\
} } while (0)

#define SNIC__PRINT_PANIC(module, fmt, arg...) do { \
if (snic_get_dbg_level() >= PANICEnable) { \
    snic_logfilter(ZLOG_LEVEL_FATAL, module,__FILE__, sizeof(__FILE__) - 1,__func__,\
	sizeof(__func__) -1,__LINE__, fmt, ##arg);\
} } while (0)

//#define SNIC__PANIC(module, fmt, arg...) do { \
	SNIC__PRINT_ERR(module, fmt, ##arg);\
	abort();\
} while (0)

int snic_log_init();

