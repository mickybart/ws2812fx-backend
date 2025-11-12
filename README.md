# WS2812FX Backend

Webservice backend for WS2812FX library to control LEDs.

This backend provide a small ui with an html page based on [esp8266_webinterface](https://github.com/kitesurfer1404/WS2812FX/tree/master/examples/esp8266_webinterface).

But the benefit is on the API that can be used by any other frontend.

This backend can store his state and restore it after a controller reset.

## APIs

All examples are using `curl` command in a `GNU/Linux distribution` but you can use your browser to replace it or adapt for your operating system.

```bash
export IP=<YOUR ESP IP>
```

### Read settings

`Settings` are stored in EEPROM and restored after a reset.

`Settings` are used to store multiple parameters selected by the user.

When a user will update a setting, `Settings` will be stored on EEPROM after a 2 min timeout. This timeout is set to preserve write cycles on the controller flash memory as a user can change multiple settings in a short delay.

```bash
# Read settings
curl http://$IP/settings | jq

# will output
{
  "led_pin": 12,
  "led_count": 78,
  "color": 458858,
  "speed": 1000,
  "brightness": 6,
  "mode": 12,
  "auto_cycle": {
    "enable": false,
    "every_ms": 10000
  }
}
```

### Set

`Set *` APIs are boxed. That means that any value too low or too high will be corrected respectively to the lowest or highest supported value.

So, those APIs will return the real value used by the controller (The boxed value).

#### Set the color

The color value is calculated from 24bits RGB via this formule:

```
R * 65536 + G * 256 + B
```

```bash
# Set the color 458858 (R=7, G=0, B=106)
curl http://$IP/set?c=458858

# will output the boxed color
458858
```

#### Set the brightness

```bash
# Set the brightness to 40
curl http://$IP/set?b=40

# will output the boxed brightness
40
```

```bash
# Set the brightness to 500 (which is not possible as the max is 255 corrected to 254)
curl http://$IP/set?b=500

# will output the boxed brightness
254
```

```bash
# Increase the brightness
curl http://$IP/set?b=+

# Decrease the brightness
curl http://$IP/set?b=-
```

#### Set the mode

This call will disable auto cycle mode.

```bash
# Set the mode to 12 (Raimbow)
curl http://$IP/set?m=12

# will output the boxed mode
12
```

#### Set auto cycle mode

To provide a demo of all modes, you can use auto cycle to switch between modes.

```bash
# Enable the auto cycle mode
curl http://$IP/set?a=+

# will output
on
```

```bash
# Disable the auto cycle mode
curl http://$IP/set?a=-

# will output
off
```

#### Set the speed

```bash
# Set the speed to 1000
curl http://$IP/set?s=1000

# will output the boxed speed
1000
```

```bash
# Increase the speed
curl http://$IP/set?s=-

# Decrease the speed
curl http://$IP/set?s=+
```

### Power control

```bash
# Power off LEDs
curl http://$IP/power/off

# will output
off
```

```bash
# Power on LEDs
curl http://$IP/power/on

# will output
on
```

### Get a list of modes

Built-in list for the embedded html page but can be used to create your own list after reformating.

```bash
# list modes available
curl http://$IP/modes

# will output something like...
<li><a href='#'>Static</a></li><li><a href='#'>Blink</a></li><li><a href='#'>Breath</a></li> #...
```

## Embedded web page

You can connect to the page with your browser at location `http://<YOUR ESP IP>`

This page doesn't provide access to all APIs but most of them. This is the original page from [esp8266_webinterface](https://github.com/kitesurfer1404/WS2812FX/tree/master/examples/esp8266_webinterface).