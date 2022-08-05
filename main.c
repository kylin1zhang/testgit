#include <stdio.h>
#include<string.h>
#include "zlog.h"
//#include "snic_log.h"
#include "snic_log.c"
/*int parser_log_level()*/
/*{*/
/*	int log_level = read_local_file();*/
/*	snic_set_dbg_level(log_level);*/
/*}*/

int main(int argc,char** argv)
{
	int rc = 0;
	
	int log_level =4;
/*根据指定的级别以该级别以上的级别输出*/
	if(log_level == 5){
	rc = snic_log_init("debug.conf");
	}
	else if(log_level == 4){
	rc = snic_log_init("info.conf");
	}
	else if(log_level == 3){
	rc = snic_log_init("warn.conf");
	}
	else if(log_level == 2){
	rc = snic_log_init("err.conf");
	}
	else if(log_level == 1){
	rc = snic_log_init("panic.conf");
	}
/*判断是否初始化成功*/
	if (rc){
	//....
		printf("init failed\n");
		return -1;
	}


	zlog_category_t *category = snic_logfilter(1);

	zlog_debug(category,"HELLO，DBG");
	zlog_info(category,"HELLO，INFO");
	zlog_warn(category,"HELLO，WARN");
	zlog_error(category,"HELLO，ERR");
	//zlog_panic(category,"HELLO，PANIC");
	

	snic_log_fini();

	return 0;
}
