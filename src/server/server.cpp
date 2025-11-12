#include "core.h"
#include "internal/server.h"

extern const char index_html[];
extern const char main_js[];

constexpr int HTTP_PORT = 80;

#ifdef ARDUINO_ARCH_ESP32
WebServer server(HTTP_PORT);
#else
ESP8266WebServer server(HTTP_PORT);
#endif

/*
 * Web server routes setup
 */
void server_setup()
{
  Serial.println("HTTP server setup");
  server.on("/", srv_handle_index_html);
  server.on("/main.js", srv_handle_main_js);
  server.on("/modes", srv_handle_modes);
  server.on("/set", srv_handle_set);
  server.on("/power/on", srv_handle_power_on);
  server.on("/power/off", srv_handle_power_off);
  server.on("/settings", srv_handle_settings);
  server.onNotFound(srv_handle_not_found);
  server.begin();
  Serial.println("HTTP server started.");
}

/*
 * Handle a client request from the web server.
 */
void server_client_handler()
{
  server.handleClient();
}

/*
 * Returns the index page of the website.
 */
void srv_handle_index_html()
{
  server.send_P(200, "text/html", index_html);
}

/*
 * Returns the main.js javascript file used by the website.
 */
void srv_handle_main_js()
{
  server.send_P(200, "application/javascript", main_js);
}

/*
 * Defaut 404 not found
 */
void srv_handle_not_found()
{
  server.send(404, "text/plain", "File Not Found");
}