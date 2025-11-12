/*
  WS2812FX Backend

  LICENSE

  The MIT License (MIT)

  Copyright (c) 2016  Harm Aldick
  Copyright (c) 2025  Spi

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.


  CHANGELOG
  2016-11-26 initial version (Harm Aldick)
  2018-01-06 added custom effects list option and auto-cycle feature (Harm Aldick)
  2025-05-13 added WiFiManager (manage SSID and passphrase in flash); OTA support via ArduinoOTA
  2025-11-05 Use platformIO and migrate code from ino to cpp with a new structure for future features
  2025-11-07 Introduce Core class to provide settings that will be exposed to users
*/

#include <Arduino.h>
#include "wireless.h"
#include "server.h"
#include "core.h"

/*
 * Core is dynamically allocated to support user settings during runtime like:
 * - led count
 * - led pin
 */
Core *core = nullptr;

/*
 * One-time call to setup the board after a reset or power on.
 */
void setup()
{
  Serial.begin(115200);
  delay(500);
  Serial.println("\n\nStarting...");

  wifi_setup(WIFI_TIMEOUT);
  ota_setup();

  // Storage setup is externalized from core->setup() for possible future usage
  // like sharing eeprom with some external Core usage or multiple Core instances.
  // This feature is not yet supported.
  // TODO: If there is no needs, we should move out this code in core->setup().
  Core::storage_setup();
  settings_t settings = Core::read_settings();

  core = new Core(settings);
  core->setup();

  server_setup();

  Serial.println("ready!");
}

/*
 * The "worker"
 */
void loop()
{
  wifi_reconnect_on_timeout(WIFI_TIMEOUT);
  ota_handler();

  server_client_handler();

  core->loop();
}