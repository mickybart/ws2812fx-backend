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
    fx_service();
    modes_auto_cycle();
}
