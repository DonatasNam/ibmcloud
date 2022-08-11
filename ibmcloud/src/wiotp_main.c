#include "wiotp_main.h"

void sig_hndlr(int signum){
    stop = 1;
    syslog(LOG_INFO, "system signal recieved");
}

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;
    switch (key)
    {
    case 'D':
        arguments->fork = 1;
        break;
    case 'o':
        arguments->orgid= arg;
        break;
    case 't':
        arguments->typeid= arg;
        break;
    case 'd':
        arguments->deviceid= arg;
        break;
    case 'a':
        arguments->auth= arg;
        break;
    case ARGP_KEY_ARG:
        if (state->arg_num >= 4)
            argp_usage(state);
            arguments->args[state->arg_num] = arg;
        break;
    case ARGP_KEY_END:
        if ((!arguments->orgid) || (!arguments->typeid) || (!arguments->deviceid) || (!arguments->auth))
            argp_usage(state);
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}


int main(int argc, char* argv[]){

    IoTPConfig *config = NULL;
    IoTPDevice *device = NULL;
    struct data response = {0, 0};
    struct ubus_context *ctx;
    struct arguments arguments = {NULL, 0,0,0,0,0};


    int rc = 0;

    openlog("ibmcloud",LOG_PID, LOG_USER);
    signal(SIGINT, sig_hndlr);
    rc =argp_parse(&argp, argc, argv, 0, 0, &arguments);
    if(rc!=0){
        syslog(LOG_ERR,"ARGP parser error: %d",rc);
        goto program_exit;
    }

    if (arguments.fork == 1){
        rc =deamon_init();
        if(rc != DEAMON_INIT_SUCCESS){
            syslog(LOG_ERR,"Failed to initialize deamon err: %d",rc);
            goto program_exit;
        }
    }

    rc =wiotp_init(&config,&device,&arguments.orgid,&arguments.typeid,&arguments.deviceid,&arguments.auth);
    if (rc != IOTPRC_SUCCESS){
        syslog(LOG_ERR,"Failed to initialize iotp device, err: %d", rc);
        goto program_exit;
    }

    while(!stop){

        rc =get_ubusmsg(ctx,&response);
        if (rc!=UBUSMSG_SUCCESS){
            syslog(LOG_ERR,"Failed getting information from uBus, err: %d", rc);
            goto disconect_device;
        }
        rc =send_data(device,arguments.deviceid,response.total,response.free);
            if (rc!=IOTPRC_SUCCESS){
            syslog(LOG_ERR,"Failed to send data, err: %d", rc);
            goto disconect_device;
        }
        struct data response = {0, 0};
        sleep(10);
    }

    disconect_device:
        rc =wiotp_cleanup(config, device);
        if(rc!=IOTPRC_SUCCESS){
            syslog(LOG_ERR,"wiotp_cleanup failure, err:%d", rc);
            goto program_exit;
        }
    
    program_exit:
        closelog();
        return rc;
}   