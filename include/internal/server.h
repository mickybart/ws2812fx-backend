#ifndef INTERNAL_SERVER_H_
#define INTERNAL_SERVER_H_

#include "server.h"

#ifdef ARDUINO_ARCH_ESP32
#include <WebServer.h>
extern WebServer server;
#else
#include <ESP8266WebServer.h>
extern ESP8266WebServer server;
#endif

void srv_handle_modes();
void srv_handle_set();
void srv_handle_power();
void srv_handle_index_html();
void srv_handle_main_js();
void srv_handle_not_found();
void srv_handle_settings();

#endif