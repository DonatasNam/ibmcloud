#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#ifndef SYSLOG_H
#include <syslog.h>
#define SYSLOG_H
#endif

#ifndef UNISTD_H   
#include <unistd.h>
#define UNISTD_H
#endif

enum deamon_init_err{
    
    DEAMON_INIT_SUCCESS= 0,
    DEAMON_INIT_FORK_ERR= 101,
    DEAMON_INIT_SSID_ERR= 102,
    DEAMON_INIT_CHDIR_ERR= 103,
    DEAMON_INIT_CLOSE_ERR=104
};

int deamon_init();