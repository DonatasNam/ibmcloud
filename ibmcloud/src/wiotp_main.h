#include <signal.h>
#include <syslog.h>
#include <iotp_device.h>
#include <unistd.h>
#include <argp.h>
#include "ibm_functions.h"
#include "ubusmsg.h"
#include "deamon_init.h"

#define IOTP_DEVICE_H
#define UNISTD_H
#define SYSLOG_H


volatile sig_atomic_t stop;

static char arg_doc[] = "orgId typeId deviceId token";

static struct argp_option options[]= {
    {"deamon",  'D', 0, 0, "initiates fork"},
    {"orgId",   'o', "orgid", 0, "orgId parameter"},
    {"typeId",  't', "typeid", 0, "typeId parameter"},
    {"deviceId",'d', "deviceid", 0, "deviceId parameter"},
    {"auth",    'a', "authenticator", 0, "generated authorization token"},
    {0}
};

struct arguments{
    char *args[4];
    int fork;
    char *orgid;
    char *typeid;
    char *deviceid;
    char *auth;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state);
static struct argp argp = {options, parse_opt, arg_doc};
int ibmcloud_loop(struct ubus_context *ctx, struct data *response,IoTPDevice*device,char *deviceId, long total,long free);