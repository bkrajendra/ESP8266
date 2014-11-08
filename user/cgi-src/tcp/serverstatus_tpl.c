#include <string.h>
#include <osapi.h>
#include "user_interface.h"
#include "mem.h"
#include "httpd/httpd.h"
#include "espmissingincludes.h"

#include "ip/TcpServer.h"


//Template code for the Tcp server status
void ICACHE_FLASH_ATTR tplTcpServerStatus(HttpdConnData *connData, char *token, void **arg) {
	char buff[1024];
	//int x;
	static struct station_config stconf;


	if (token==NULL) return;
	wifi_station_get_config(&stconf);

	os_strcpy(buff, "Unknown");

	if (os_strcmp(token, "WiFiSettings")==0) {
		os_printf("DEBUG Getting ip settings to replace token: %s \r\n", token);
		char ipSettings[256] = { 0};
		GetTcpServerStatus(ipSettings);
		os_strcpy(buff, ipSettings);
		os_printf("DEBUG Found ip settings : %s \r\n", buff);
		//delete ipSettings;
	}
	espconn_sent(connData->conn, (uint8 *)buff, os_strlen(buff));
}