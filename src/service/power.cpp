#include "globals.h"

/*
 * Toggle LEDs power.
 */
void srv_handle_power()
{
  if (ws2812fx.isRunning())
  {
    ws2812fx.stop();
  }
  else
  {
    ws2812fx.start();
  }

  server.send(200, "text/plain", "OK");
}