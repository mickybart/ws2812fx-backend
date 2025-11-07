#include "core.h"
#include "internal/server.h"

/*
 * Returns a list of modes for the html web page.
 */
void srv_handle_modes()
{
  server.send(200, "text/plain", core->get_modes());
}