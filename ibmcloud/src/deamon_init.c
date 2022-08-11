# include "deamon_init.h"

int deamon_init(){
	FILE *fp= NULL;
	pid_t process_id = 0;
	pid_t sid = 0;
	int rc =0;

	process_id = fork();
	if (process_id < 0) {
		syslog(LOG_ERR, "Failed forking the proces id");
		return DEAMON_INIT_FORK_ERR;
	}
	if (process_id > 0) {
		syslog(LOG_ERR, "Failed forking the proces id");
		return DEAMON_INIT_FORK_ERR;
	}

	umask(0);
	sid = setsid();
	if(sid < 0) {
		syslog(LOG_ERR,"Failed to create a new process id");
		return DEAMON_INIT_SSID_ERR;
	}
	
	rc =chdir("/");
	if(rc!=0){
		return DEAMON_INIT_CHDIR_ERR;
	}
	
	rc =close(STDIN_FILENO);
	if(rc!=0){
		return DEAMON_INIT_CLOSE_ERR;
	}
	close(STDOUT_FILENO);
		if(rc!=0){
		return DEAMON_INIT_CLOSE_ERR;
	}
	close(STDERR_FILENO);
	if(rc!=0){
		return DEAMON_INIT_CLOSE_ERR;
	}

	return DEAMON_INIT_SUCCESS;
}
