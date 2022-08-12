#include "ibm_functions.h"

int config_set(IoTPConfig **config, char *orgId, char *typeId, char *deviceId, char *auth){

    int rc =0;
    rc= IoTPConfig_create(config,NULL);
    if ( rc != IOTPRC_SUCCESS ) {
        syslog(LOG_ERR,"%s, error code: %d",IOTPRC_toString(rc),rc);
        return rc;
    }
    rc= IoTPConfig_setProperty(*config, "identity.orgId", orgId);
    if ( rc != IOTPRC_SUCCESS ) {
        syslog(LOG_ERR,"%s, error code: %d",IOTPRC_toString(rc),rc);
        return rc;
    }
    rc= IoTPConfig_setProperty(*config, "identity.typeId", typeId);
    if ( rc != IOTPRC_SUCCESS ) {
        syslog(LOG_ERR,"%s, error code: %d",IOTPRC_toString(rc),rc);
        return rc;
    }
    rc= IoTPConfig_setProperty(*config, "identity.deviceId", deviceId);
    if ( rc != IOTPRC_SUCCESS ) {
        syslog(LOG_ERR,"%s, error code: %d",IOTPRC_toString(rc),rc);
        return rc;
    }
    rc= IoTPConfig_setProperty(*config, "auth.token", auth);
    if ( rc != IOTPRC_SUCCESS ) {
        syslog(LOG_ERR,"%s, error code: %d",IOTPRC_toString(rc),rc);
        return rc;
    }
    syslog(LOG_INFO,"Configuration applied succesfully");
    return rc;
}

int wiotp_init(IoTPConfig **config,IoTPDevice **device, char **orgId, char **typeId, char **deviceId, char **auth){
    
    int rc= 0;
    rc= config_set(config, *orgId,*typeId,*deviceId,*auth);
    if ( rc != IOTPRC_SUCCESS ) {
        syslog(LOG_ERR,"%s, error code: %d",IOTPRC_toString(rc),rc);
        return rc;
    }
    rc = IoTPDevice_create(device,*config);
    if ( rc != IOTPRC_SUCCESS ) {
        syslog(LOG_ERR,"%s, error code: %d",IOTPRC_toString(rc),rc);
        return rc;
    }
    rc = IoTPDevice_connect(*device);
    if ( rc != IOTPRC_SUCCESS ) {
        syslog(LOG_ERR,"%s, error code: %d",IOTPRC_toString(rc),rc);
        return rc;
    }
    syslog(LOG_INFO,"Connection succesfull");
    return rc;
}

int wiotp_cleanup(IoTPConfig *config,IoTPDevice *device){

    int rc =0;
    rc = IoTPDevice_disconnect(device);
    if ( rc != IOTPRC_SUCCESS ) {
        syslog(LOG_ERR,"%s, error code: %d",IOTPRC_toString(rc),rc);
        return rc;
    }
    rc = IoTPDevice_destroy(device);
    if ( rc != IOTPRC_SUCCESS ) {
        syslog(LOG_ERR,"%s, error code: %d",IOTPRC_toString(rc),rc);
        return rc;
    }
    rc = IoTPConfig_clear(config);
    if ( rc != IOTPRC_SUCCESS ) {
        syslog(LOG_ERR,"%s, error code: %d",IOTPRC_toString(rc),rc);
        return rc;
    }
    syslog(LOG_INFO,"Cleanup succesfull");
}

int send_data(IoTPDevice*device,char* deviceId, long total, long free){
    int rc =0;
    char string[256];
    sprintf(string,"{\"Memory\" : {\"RouterID\": \"%s\", \"Total\"  : %ld, \"Free\": %ld }}",deviceId,total, free);
    rc = IoTPDevice_sendEvent(device,"Ram_data", string, "json",QoS0, NULL);
    if(rc == IOTPRC_SUCCESS){
        syslog(LOG_INFO,"Data sent to cloud succesfully");
    }
    if(rc != IOTPRC_SUCCESS){
        syslog(LOG_ERR,"%s, error code: %d",IOTPRC_toString(rc),rc);
        return rc;
    }
    memset(string,0,sizeof(string));
    return IOTPRC_SUCCESS;
}

