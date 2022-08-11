SRC:= wiotp_main.c ubusmsg.c deamon_init.c ibm_functions.c

LDFLAGS:= -lblobmsg_json -lubox -lubus -liotp-as-device -lpaho-mqtt3as -largp
.PHONY:all clean

all:ibmcloud

ibmcloud: $(SRC)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf ibmcloud