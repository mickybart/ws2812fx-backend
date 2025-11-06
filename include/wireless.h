#ifndef WIRELESS_H_
#define WIRELESS_H_

void ota_setup();
void ota_handler();
void wifi_setup(unsigned long timeout);
void wifi_reconnect_on_timeout(unsigned long timeout);

#endif