#include "globals.h"
#include "modes_auto_cycle.h"

/*
 * Manage all the settings (brightness, color, speed, modes, auto cycle, ...).
 */
void srv_handle_set()
{
  for (uint8_t i = 0; i < server.args(); i++)
  {
    if (server.argName(i) == "c")
    {
      uint32_t tmp = (uint32_t)strtol(server.arg(i).c_str(), NULL, 10);
      if (tmp <= 0xFFFFFF)
      {
        ws2812fx.setColor(tmp);
      }
    }

    if (server.argName(i) == "m")
    {
      uint8_t request = (uint8_t)strtol(server.arg(i).c_str(), NULL, 10);
      use_mode(request);
      Serial.print("mode is ");
      Serial.println(ws2812fx.getModeName(ws2812fx.getMode()));
    }

    if (server.argName(i) == "b")
    {
      if (server.arg(i)[0] == '-')
      {
        ws2812fx.setBrightness(ws2812fx.getBrightness() * 0.8);
      }
      else if (server.arg(i)[0] == ' ')
      {
        int newBrightness = constrain(ws2812fx.getBrightness() * 1.2, 6, 255);
        ws2812fx.setBrightness(newBrightness);
      }
      else
      { // set brightness directly
        uint8_t tmp = (uint8_t)strtol(server.arg(i).c_str(), NULL, 10);
        ws2812fx.setBrightness(tmp);
      }
      Serial.print("brightness is ");
      Serial.println(ws2812fx.getBrightness());
    }

    if (server.argName(i) == "s")
    {
      if (server.arg(i)[0] == '-')
      {
        int newSpeed = constrain(ws2812fx.getSpeed() * 1.2, 6, 65535);
        ws2812fx.setSpeed(newSpeed);
      }
      else if (server.arg(i)[0] == ' ')
      {
        ws2812fx.setSpeed(ws2812fx.getSpeed() * 0.8);
      }
      else
      {
        uint16_t tmp = (uint16_t)strtol(server.arg(i).c_str(), NULL, 10);
        ws2812fx.setSpeed(tmp);
      }
      Serial.print("speed is ");
      Serial.println(ws2812fx.getSpeed());
    }

    if (server.argName(i) == "a")
    {
      if (server.arg(i)[0] == '-')
      {
        modes_auto_cycle_stop();
      }
      else
      {
        modes_auto_cycle_start();
      }
    }
  }
  server.send(200, "text/plain", "OK");
}