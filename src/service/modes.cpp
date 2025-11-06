#include "globals.h"

constexpr uint MODES_STRING_RESERVE=5000;

String modes = "";
uint8_t myModes[] = {}; // *** optionally create a custom list of effect/mode numbers

unsigned long auto_last_change = 0;
bool auto_cycle = false;

/*
 * Build <li> string for all modes.
 */
void modes_setup()
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

/*
 * Returns a list of modes for the html web page.
 */
void srv_handle_modes()
{
  server.send(200, "text/plain", modes);
}

/*
 * Change the mode if auto cycle is enabled every milliseconds (every_ms).
 */
void modes_auto_cycle(unsigned long every_ms)
{
  unsigned long now = millis();

  if (auto_cycle && (now - auto_last_change > every_ms))
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
    ws2812fx.setMode(next_mode);
    Serial.print("mode is ");
    Serial.println(ws2812fx.getModeName(ws2812fx.getMode()));
    auto_last_change = now;
  }
}

/*
 * Stop auto cycle
 */
void modes_auto_cycle_stop()
{
  auto_cycle = false;
}

/*
 * Start auto cycle and reset the last change
 */
void modes_auto_cycle_start()
{
  auto_cycle = true;
  auto_last_change = 0;
}

/*
 * Use a specific mode and stop auto cycle if required.
 */
void use_mode(uint8_t request)
{
  uint8_t new_mode = sizeof(myModes) > 0 ? myModes[request % sizeof(myModes)] : request % ws2812fx.getModeCount();
  modes_auto_cycle_stop();
  ws2812fx.setMode(new_mode);
}