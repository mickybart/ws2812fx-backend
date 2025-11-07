#include "core.h"
#include "internal/server.h"

/*
 * Toggle LEDs power.
 */
void srv_handle_power()
{
  if (core->get_fx().isRunning())
  {
    core->get_fx().stop();
  }
  else
  {
    core->get_fx().start();
  }

  server.send(200, "text/plain", "OK");
}