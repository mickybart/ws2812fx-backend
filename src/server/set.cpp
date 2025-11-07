#include "core.h"
#include "internal/server.h"

/*
 * Set the LEDs color
 */
void set_color(uint8_t arg_num)
{
  uint32_t tmp = (uint32_t)strtol(server.arg(arg_num).c_str(), NULL, 10);
  if (tmp <= 0xFFFFFF)
  {
    core->get_fx().setColor(tmp);
  }
}

/*
 * Set the fx mode
 */
void set_mode(uint8_t arg_num)
{
  uint8_t request = (uint8_t)strtol(server.arg(arg_num).c_str(), NULL, 10);
  core->use_mode(request);
  Serial.print("mode is ");
  Serial.println(core->get_fx().getModeName(core->get_fx().getMode()));
}

/*
 * Set the LEDs brightness
 */
void set_brightness(uint8_t arg_num)
{
  if (server.arg(arg_num)[0] == '-')
  {
    core->get_fx().setBrightness(core->get_fx().getBrightness() * 0.8);
  }
  else if (server.arg(arg_num)[0] == ' ')
  {
    int newBrightness = constrain(core->get_fx().getBrightness() * 1.2, 6, 255);
    core->get_fx().setBrightness(newBrightness);
  }
  else
  { // set brightness directly
    uint8_t tmp = (uint8_t)strtol(server.arg(arg_num).c_str(), NULL, 10);
    core->get_fx().setBrightness(tmp);
  }
  Serial.print("brightness is ");
  Serial.println(core->get_fx().getBrightness());
}

/*
 * Set the fx speed
 */
void set_speed(uint8_t arg_num)
{
  if (server.arg(arg_num)[0] == '-')
  {
    int newSpeed = constrain(core->get_fx().getSpeed() * 1.2, 6, 65535);
    core->get_fx().setSpeed(newSpeed);
  }
  else if (server.arg(arg_num)[0] == ' ')
  {
    core->get_fx().setSpeed(core->get_fx().getSpeed() * 0.8);
  }
  else
  {
    uint16_t tmp = (uint16_t)strtol(server.arg(arg_num).c_str(), NULL, 10);
    core->get_fx().setSpeed(tmp);
  }
  Serial.print("speed is ");
  Serial.println(core->get_fx().getSpeed());
}

/*
 * Enable/Disable the fx mode auto cycle
 */
void set_auto_cycle(uint8_t arg_num)
{
  if (server.arg(arg_num)[0] == '-')
      {
        core->modes_auto_cycle_stop();
      }
      else
      {
        core->modes_auto_cycle_start();
      }
}

/*
 * Manage all the settings (brightness, color, speed, modes, auto cycle, ...).
 */
void srv_handle_set()
{
  for (uint8_t i = 0; i < server.args(); i++)
  {
    if (server.argName(i) == "c")
      set_color(i);
    else if (server.argName(i) == "m")
      set_mode(i);
    else if (server.argName(i) == "b")
      set_brightness(i);
    else if (server.argName(i) == "s")
      set_speed(i);
    else if (server.argName(i) == "a")
      set_auto_cycle(i);
    else
      Serial.println("unsupported query '" + server.argName(i) + "' for set");
  }
  server.send(200, "text/plain", "OK");
}