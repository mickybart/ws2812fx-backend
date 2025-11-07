#ifndef INTERNAL_CORE_H_
#define INTERNAL_CORE_H_

#include <WS2812FX.h>
#include "settings.h"

class Core
{
public:
    Core(settings_t settings);
    void setup();
    void loop();
    void use_mode(long mode);
    void modes_auto_cycle_start();
    void modes_auto_cycle_stop();
    String &get_modes();
    WS2812FX &get_fx();

    void set_color(long color);
    void set_brightness(long brightness);
    void set_brightness(double brightness);
    void set_speed(long speed);
    void set_speed(double speed);

private:
    WS2812FX ws2812fx;
    settings_t settings;

    // built-in modes for html page
    String modes = "";

    // optionally create a custom list of effect/mode numbers
    // cannot exceed more than 256 entries as ws2812fx.getModeCount() is an uint8_t
    uint8_t myModes[0] = {};

    // Last mode change timestamp for auto cycle
    ulong mode_change_timestamp = 0;

    void fx_setup();
    void fx_service();
    void modes_setup();
    void modes_auto_cycle();
};

#endif