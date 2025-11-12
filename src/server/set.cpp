#include "core.h"
#include "internal/server.h"
#include <string>

/*
 * Set the LEDs color
 */
uint32_t set_color(const String &value)
{
  long color = strtol(value.c_str(), NULL, 10);
  core->set_color(color);

  return core->get_fx().getColor();
}

/*
 * Set the fx mode
 */
uint8_t set_mode(const String &value)
{
  long mode = strtol(value.c_str(), NULL, 10);
  core->use_mode(mode);

  return core->get_fx().getMode();
}

/*
 * Set the LEDs brightness
 */
uint8_t set_brightness(const String &value)
{
  if (value[0] == '-')
    core->set_brightness(core->get_fx().getBrightness() * 0.8);
  else if (value[0] == ' ')
    core->set_brightness(core->get_fx().getBrightness() * 1.2);
  else
  {
    // set brightness directly
    long brightness = strtol(value.c_str(), NULL, 10);
    core->set_brightness(brightness);
  }

  return core->get_fx().getBrightness();
}

/*
 * Set the fx speed
 */
uint16_t set_speed(const String &value)
{
  if (value[0] == '-')
    core->set_speed(core->get_fx().getSpeed() * 1.2);
  else if (value[0] == ' ')
    core->set_speed(core->get_fx().getSpeed() * 0.8);
  else
  {
    long speed = strtol(value.c_str(), NULL, 10);
    core->set_speed(speed);
  }

  return core->get_fx().getSpeed();
}

/*
 * Enable/Disable the fx mode auto cycle
 */
bool set_auto_cycle(const String &value)
{
  if (value[0] == '-')
    core->modes_auto_cycle_stop();
  else
    core->modes_auto_cycle_start();

  return core->get_settings().auto_cycle.enable;
}

/*
 * Manage all the settings (brightness, color, speed, modes, auto cycle, ...).
 */
void srv_handle_set()
{
  if (server.args() != 1)
  {
    server.send(400, "text/plain", "Malformed query");
    return;
  }

  const String &name = server.argName(0);
  const String &value = server.arg(0);

  if (name == "c")
  {
    uint32_t ret = set_color(value);
    server.send(200, "text/plain", String(std::to_string(ret).c_str()));
  }
  else if (name == "m")
  {
    uint8_t ret = set_mode(value);
    server.send(200, "text/plain", String(std::to_string(ret).c_str()));
  }
  else if (name == "b")
  {
    uint8_t ret = set_brightness(value);
    server.send(200, "text/plain", String(std::to_string(ret).c_str()));
  }
  else if (name == "s")
  {
    uint16_t ret = set_speed(value);
    server.send(200, "text/plain", String(std::to_string(ret).c_str()));
  }
  else if (name == "a")
  {
    bool ret = set_auto_cycle(value);
    server.send(200, "text/plain", ret ? "on" : "off");
  }
  else
  {
    server.send(400, "text/plain", "Unsupported query '" + name + "'");
  }
}
