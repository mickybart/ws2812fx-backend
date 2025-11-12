#include <string>
#include "core.h"
#include "internal/server.h"

/*
 * Returns the content of settings
 */
void srv_handle_settings()
{
    settings_t &settings = core->get_settings();

    /*
    {
        "led_pin": 0,
        "led_count": 0,
        "color": 0,
        "speed": 0,
        "brightness": 0,
        "mode": 0,
        "auto_cycle": {
            "enable": false,
            "every_ms": 10000,
        }
    }
    */
    String status = String("{ \"led_pin\": ");
    status.concat(settings.led_pin);
    status.concat(", \"led_count\": ");
    status.concat(settings.led_count);
    status.concat(", \"color\": ");
    status.concat(settings.color);
    status.concat(", \"speed\": ");
    status.concat(settings.speed);
    status.concat(", \"brightness\": ");
    status.concat(settings.brightness);
    status.concat(", \"mode\": ");
    status.concat(settings.mode);
    status.concat(", \"auto_cycle\": { \"enable\": ");
    status.concat(settings.auto_cycle.enable ? "true" : "false");
    status.concat(", \"every_ms\": ");
    status.concat(settings.auto_cycle.every_ms);
    status.concat(" } }");

    server.send(200, "application/json", status);
}