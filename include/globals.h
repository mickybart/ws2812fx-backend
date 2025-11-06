#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <WString.h>
#include <WS2812FX.h>

extern WS2812FX ws2812fx;

#ifdef ARDUINO_ARCH_ESP32
#include <WebServer.h>
extern WebServer server;
#else
#include <ESP8266WebServer.h>
extern ESP8266WebServer server;
#endif

#endif