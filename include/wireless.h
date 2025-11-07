#ifndef WIRELESS_H_
#define WIRELESS_H_

// checks WiFi every ...ms. Reset after this time, if WiFi cannot reconnect.
constexpr ulong WIFI_TIMEOUT = 30000;

void ota_setup();
void ota_handler();
void wifi_setup(ulong timeout);
void wifi_reconnect_on_timeout(ulong timeout);

#endif