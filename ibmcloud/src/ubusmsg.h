#include <libubox/blobmsg_json.h>
#include <libubus.h>

#ifndef SYSLOG_H
#include <syslog.h>
#define SYSLOG_H
#endif

enum {
	TOTAL_MEMORY,
	FREE_MEMORY,
	SHARED_MEMORY,
	BUFFERED_MEMORY,
	__MEMORY_MAX,
};

enum {
	MEMORY_DATA,
	__INFO_MAX,
};

enum ubusmsg_err{
	UBUSMSG_SUCCESS =200,
	UBUSMSG_ERR= 201
};

struct data{
    long int total;
    long int free;
};

struct ubus_context *ctx;
struct ubus_request_data*rq;

static const struct blobmsg_policy memory_policy[__MEMORY_MAX] = {
	[TOTAL_MEMORY] = { .name = "total", .type = BLOBMSG_TYPE_INT64 },
	[FREE_MEMORY] = { .name = "free", .type = BLOBMSG_TYPE_INT64 },
};

static const struct blobmsg_policy info_policy[__INFO_MAX] = {
	[MEMORY_DATA] = { .name = "memory", .type = BLOBMSG_TYPE_TABLE },
};

void board_cb(struct ubus_request *req, int type, struct blob_attr *msg);
int get_ubusmsg(struct ubus_context *ctx,struct data *response);