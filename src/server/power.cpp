#include "core.h"
#include "internal/server.h"

/*
 * Power Off
 */
void srv_handle_power_off()
{
  if (core->get_fx().isRunning())
    core->get_fx().stop();

  server.send(200, "text/plain", "off");
}

/*
 * Power On
 */
void srv_handle_power_on()
{
  if (!core->get_fx().isRunning())
    core->get_fx().start();

  server.send(200, "text/plain", "on");
}