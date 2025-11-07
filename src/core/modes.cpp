#include "core.h"

constexpr uint MODES_STRING_RESERVE = 5000;

/*
 * Build <li> string for all modes.
 */
void Core::modes_setup()
{
  modes = "";
  modes.reserve(MODES_STRING_RESERVE);

  uint8_t num_modes = sizeof(myModes) > 0 ? sizeof(myModes) : ws2812fx.getModeCount();
  for (uint8_t i = 0; i < num_modes; i++)
  {
    uint8_t m = sizeof(myModes) > 0 ? myModes[i] : i;
    modes += "<li><a href='#'>";
    modes += ws2812fx.getModeName(m);
    modes += "</a></li>";
  }
}

String &Core::get_modes()
{
  return modes;
}

/*
 * Change the mode if auto cycle is enabled and the current mode timeout
 */
void Core::modes_auto_cycle()
{
  ulong now = millis();

  if (settings.auto_cycle.enable && (now - mode_change_timestamp > settings.auto_cycle.every_ms))
  {
    uint8_t next_mode = (ws2812fx.getMode() + 1) % ws2812fx.getModeCount();
    if (sizeof(myModes) > 0)
    { // if custom list of modes exists
      for (ulong i = 0; i < sizeof(myModes); i++)
      {
        if (myModes[i] == ws2812fx.getMode())
        {
          next_mode = ((i + 1) < sizeof(myModes)) ? myModes[i + 1] : myModes[0];
          break;
        }
      }
    }
    settings.mode = next_mode;
    ws2812fx.setMode(settings.mode);
    Serial.print("mode is ");
    Serial.println(ws2812fx.getModeName(ws2812fx.getMode()));
    mode_change_timestamp = now;
  }
}

/*
 * Stop auto cycle
 */
void Core::modes_auto_cycle_stop()
{
  settings.auto_cycle.enable = false;
}

/*
 * Start auto cycle and reset the last change
 */
void Core::modes_auto_cycle_start()
{
  mode_change_timestamp = 0;
  settings.auto_cycle.enable = true;
}

/*
 * Use a specific mode and stop auto cycle if required.
 */
void Core::use_mode(uint8_t request)
{
  uint8_t new_mode = sizeof(myModes) > 0 ? myModes[request % sizeof(myModes)] : request % ws2812fx.getModeCount();

  modes_auto_cycle_stop();
  settings.mode = new_mode;
  ws2812fx.setMode(settings.mode);
}