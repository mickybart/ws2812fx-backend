#include "core.h"
#include "internal/server.h"

/*
 * Set the LEDs color
 */
void set_color(uint8_t arg_num)
{
  long color = strtol(server.arg(arg_num).c_str(), NULL, 10);
  core->set_color(color);
}

/*
 * Set the fx mode
 */
void set_mode(uint8_t arg_num)
{
  long mode = strtol(server.arg(arg_num).c_str(), NULL, 10);
  core->use_mode(mode);
  Serial.print("mode is ");
  Serial.println(core->get_fx().getModeName(core->get_fx().getMode()));
}

/*
 * Set the LEDs brightness
 */
void set_brightness(uint8_t arg_num)
{
  if (server.arg(arg_num)[0] == '-')
    core->set_brightness(core->get_fx().getBrightness() * 0.8);
  else if (server.arg(arg_num)[0] == ' ')
    core->set_brightness(core->get_fx().getBrightness() * 1.2);
  else
  {
    // set brightness directly
    long speed = strtol(server.arg(arg_num).c_str(), NULL, 10);
    core->set_brightness(speed);
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
    core->set_speed(core->get_fx().getSpeed() * 1.2);
  else if (server.arg(arg_num)[0] == ' ')
    core->set_speed(core->get_fx().getSpeed() * 0.8);
  else
  {
    long speed = strtol(server.arg(arg_num).c_str(), NULL, 10);
    core->set_speed(speed);
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
    core->modes_auto_cycle_stop();
  else
    core->modes_auto_cycle_start();
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