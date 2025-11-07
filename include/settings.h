#ifndef SETTINGS_H_
#define SETTINGS_H_

// Pin and led count (not really based on ARCH; TODO: use a dynamic solution)
#ifdef ARDUINO_ARCH_ESP32
constexpr uint8_t LED_PIN = 23;    // Ajouté par Spi  // 0 = GPIO0, 2=GPIO2
constexpr uint16_t LED_COUNT = 96; // 106            // Ajouté par Spi
#else
constexpr uint8_t LED_PIN = 12;    // Ajouté par Spi  // 0 = GPIO0, 2=GPIO2
constexpr uint16_t LED_COUNT = 78; // Ajouté par Spi  // 0 = GPIO0, 2=GPIO2
#endif

constexpr uint32_t LOW_COLOR = 0x000000;
constexpr uint32_t HIGH_COLOR = 0xFFFFFF; // can be cast as long; take care of the signed bit (max 2**31-1)
constexpr uint16_t LOW_SPEED = 6;
constexpr uint16_t HIGH_SPEED = 65535;
constexpr uint8_t LOW_BRIGHTNESS = 6;
constexpr uint8_t HIGH_BRIGHTNESS = 255;
constexpr uint8_t LOW_MODE_INDEX = 0;
constexpr uint8_t HIGH_MODE_INDEX = 255;

typedef struct auto_cycle
{
    bool enable{false};

    // cycle effect mode every ms (default: 10 seconds)
    ulong every_ms{10000};
} auto_cycle_t;

// Will be used to store setting into EEPROM
// Limited to 4KiB on ESP12F
typedef struct settings
{
    uint8_t led_pin{LED_PIN};
    uint16_t led_count{LED_COUNT};
    uint32_t color{0xFF5900};
    uint16_t speed{1000};
    uint8_t brightness{LOW_BRIGHTNESS};
    uint8_t mode{FX_MODE_STATIC};
    auto_cycle_t auto_cycle{};
    uint8_t reserved[20]{0};
} settings_t;

#endif