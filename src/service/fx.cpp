#include "globals.h"

// Pin and led count (not really based on ARCH; TODO: use a dynamic solution)
#ifdef ARDUINO_ARCH_ESP32
constexpr uint8_t LED_PIN=23;    // Ajouté par Spi  // 0 = GPIO0, 2=GPIO2
constexpr uint16_t LED_COUNT=96; // 106            // Ajouté par Spi
#else
constexpr uint8_t LED_PIN=12;    // Ajouté par Spi  // 0 = GPIO0, 2=GPIO2
constexpr uint16_t LED_COUNT=78; // Ajouté par Spi  // 0 = GPIO0, 2=GPIO2
#endif

// Default values
constexpr uint32_t _DEFAULT_COLOR=0xFF5900;
constexpr uint16_t _DEFAULT_SPEED=1000;
constexpr uint8_t _DEFAULT_BRIGHTNESS=8;

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

/*
 * WS2812FX support and initialization.
 */
void fx_setup()
{
    Serial.println("WS2812FX setup");
    ws2812fx.init();
    ws2812fx.setMode(FX_MODE_STATIC);
    ws2812fx.setColor(_DEFAULT_COLOR);
    ws2812fx.setSpeed(_DEFAULT_SPEED);
    ws2812fx.setBrightness(_DEFAULT_BRIGHTNESS);
    ws2812fx.start();
}

/*
 * Run WS2812FX service. This is used in the loop() to update LEDs status.
 */
void fx_service()
{
    ws2812fx.service();
}