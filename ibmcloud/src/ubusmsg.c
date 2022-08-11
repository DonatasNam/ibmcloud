#include "ubusmsg.h"

void board_cb(struct ubus_request *req, int type, struct blob_attr *msg){

    int rc =0;
    struct data *dat= (struct data*)req->priv;
	struct blob_attr *tb[__INFO_MAX];
	struct blob_attr *memory[__MEMORY_MAX];

	rc =blobmsg_parse(info_policy, __INFO_MAX, tb, blob_data(msg), blob_len(msg));
	if (!tb[MEMORY_DATA]) {
		syslog(LOG_ERR,"Blobmsg_parse error: %d",rc);
		rc=UBUSMSG_ERR;
		return;
	}

	rc =blobmsg_parse(memory_policy, __MEMORY_MAX, memory,blobmsg_data(tb[MEMORY_DATA]), blobmsg_data_len(tb[MEMORY_DATA]));
	if(rc!=0){
		syslog(LOG_ERR,"Blobmsg_parse error: %d",rc);
		rc =UBUSMSG_ERR;
		return;
	}
	dat->total =blobmsg_get_u64(memory[TOTAL_MEMORY]);
	dat->free =blobmsg_get_u64(memory[FREE_MEMORY]);
}

int get_ubusmsg(struct ubus_context *ctx,struct data *response){
	uint32_t id;
	int rc =0;
	ctx = ubus_connect(NULL);
		if (!ctx) {
			syslog(LOG_ERR,"ubus failed to connect");
			return 	UBUSMSG_ERR;
		}
	rc =ubus_lookup_id(ctx,"system",&id);
        if (rc!=0){
    		syslog(LOG_ERR, "ubus_lookup_id error: %d",rc);
			return UBUSMSG_ERR;
        }
    rc= ubus_invoke(ctx, id, "info", NULL, board_cb, response, 3000);
        if(rc!=0){
            syslog(LOG_ERR, "ubus invoke error: %d",rc);
			return UBUSMSG_ERR;
        }
	ubus_free(ctx);
	return UBUSMSG_SUCCESS;
}