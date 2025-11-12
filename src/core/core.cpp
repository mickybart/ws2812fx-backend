#include "core.h"
#include "settings.h"

/*
 * Construct a Core instance from settings
 * WS2812FX will be construct at this stage
 */
Core::Core(settings_t settings)
    : ws2812fx(settings.led_count, settings.led_pin, NEO_GRB + NEO_KHZ800)
{
    this->settings = settings;
    this->_dirty_settings = false;
}

/*
 * Must be call by void setup()
 */
void Core::setup()
{
    fx_setup();
    modes_setup();
}

/*
 * Must be call by void loop()
 */
void Core::loop()
{
    ulong now = millis();

    modes_auto_cycle(now);
    fx_service();
    write_settings_when_dirty(now);
}

/*
 * Get a settings reference
 */
settings_t &Core::get_settings()
{
    return settings;
}