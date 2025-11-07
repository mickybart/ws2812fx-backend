#include "core.h"

/*
 * Init WS2812FX and set default settings (mode, color, speed, ...)
 */
void Core::fx_setup()
{
    Serial.println("WS2812FX setup");
    ws2812fx.init();
    ws2812fx.setMode(settings.mode);
    ws2812fx.setColor(settings.color);
    ws2812fx.setSpeed(settings.speed);
    ws2812fx.setBrightness(settings.brightness);
    ws2812fx.start();
}

/*
 * Run WS2812FX service. This is used in the loop() to update LEDs status.
 */
void Core::fx_service()
{
    ws2812fx.service();
}

/*
 * Get a direct access to WS2812FX instance
 */
WS2812FX &Core::get_fx()
{
    return ws2812fx;
}