#ifndef SYSLOG_H
#include <syslog.h>
#define SYSLOG_H
#endif

#ifndef IOTP_DEVICE_H
#include <iotp_device.h>
#define WIOTP_DEVICE_H
#endif

int config_set(IoTPConfig **config, char *orgId, char *typeId, char *deviceId, char *auth);
int wiotp_init(IoTPConfig **config,IoTPDevice **device, char **orgId, char **typeId, char **deviceId, char **auth);
int wiotp_cleanup(IoTPConfig *config,IoTPDevice *device);
int send_data(IoTPDevice*device,char* deviceId, long total, long free);