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

    WS2812FX &get_fx();
    settings_t &get_settings();

    /*
     * Modes
     */

    void use_mode(long mode);
    void modes_auto_cycle_start();
    void modes_auto_cycle_stop();
    String &get_modes();

    /*
     * Color, speed and brightness
     */

    void set_color(long color);
    void set_brightness(long brightness);
    void set_brightness(double brightness);
    void set_speed(long speed);
    void set_speed(double speed);

    /*
     * Persistence for settings
     */

    static void storage_setup();
    static settings_t read_settings();

private:
    WS2812FX ws2812fx;
    settings_t settings;

    void fx_setup();
    void fx_service();

    /*
     * Modes
     */

    // built-in modes for html page
    String modes = "";

    // optionally create a custom list of effect/mode numbers
    // cannot exceed more than 256 entries as ws2812fx.getModeCount() is an uint8_t
    uint8_t myModes[0] = {};

    // Since when the mode changed ? (auto cycle)
    ulong _mode_changed_timestamp = 0;

    void modes_setup();
    void modes_auto_cycle(ulong now);

    /*
     * Persistence for settings
     */

    // is settings dirty ?
    bool _dirty_settings;
    // since when settings is dirty ?
    ulong _dirty_settings_timestamp = 0;

    void set_dirty_settings_flag();
    bool can_write_settings(ulong now);
    void write_settings_when_dirty(ulong now);
    void unset_dirty_settings_flag();
};

#endif