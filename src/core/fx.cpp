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

/*
 * Set the color and store it in settings
 */
void Core::set_color(long color)
{
    uint32_t boxed_color = constrain(color, (long)LOW_COLOR, (long)HIGH_COLOR);
    ws2812fx.setColor(boxed_color);
    settings.color = boxed_color;
}

/*
 * Set the brightness and store it in settings
 * constrain the long value between LOW_BRIGHTNESS and HIGH_BRIGHTNESS
 */
void Core::set_brightness(long brightness)
{
    uint8_t boxed_brightness = constrain(brightness + 1, LOW_BRIGHTNESS, HIGH_BRIGHTNESS);
    ws2812fx.setBrightness(boxed_brightness);
    settings.brightness = boxed_brightness;
}

/*
 * Set the brightness and store it in settings
 * constrain the double value between LOW_BRIGHTNESS and HIGH_BRIGHTNESS
 */
void Core::set_brightness(double brightness)
{
    long boxed_brightness_rounded = constrain(brightness, LOW_BRIGHTNESS, HIGH_BRIGHTNESS) + 0.5;
    uint8_t boxed_brightness = constrain(boxed_brightness_rounded + 1, LOW_BRIGHTNESS, HIGH_BRIGHTNESS);
    ws2812fx.setBrightness(boxed_brightness);
    settings.brightness = boxed_brightness;
}

/*
 * Set the speed and store it in settings
 * constrain the long value between LOW_SPEED and HIGH_SPEED
 */
void Core::set_speed(long speed)
{
    uint16_t boxed_speed = constrain(speed, LOW_SPEED, HIGH_SPEED);
    ws2812fx.setSpeed(boxed_speed);
    settings.speed = boxed_speed;
}

/*
 * Set the speed and store it in settings
 * constrain the double value between LOW_SPEED and HIGH_SPEED
 */
void Core::set_speed(double speed)
{
    long boxed_speed_rounded = constrain(speed, LOW_SPEED, HIGH_SPEED) + 0.5;
    uint16_t boxed_speed = constrain(boxed_speed_rounded, LOW_SPEED, HIGH_SPEED);
    ws2812fx.setSpeed(boxed_speed);
    settings.speed = boxed_speed;
}