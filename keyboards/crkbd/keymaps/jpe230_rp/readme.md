# Jpe230's CRKBD (RP2040) Layout

## Layers
The four layers:
- BASE Layer: QWERTY
- LOWER Layer: Numbers + Arrows
- RAISE Layer: Symbols
- ADJUST Layer: Numpad + Media Keys + Fn keys

## OLED
- Master: Renders layer state + keylog + WPM
- Slave : Ocean Dream

## Changes vs my Pro Micro Board
- Updated `rules.mk`:
  - Set MCU to `RP2040`
  - WS2812 driver to `vendor`
  - Serial driver to `vendor`
  - Enable warnings
- Updated `config.h`:
  - Set the RP2040 pins for matrix, OLED and RGB
- Added `mcuconf.h` to use I2C1 (for OLED)
- Added `halconf.h` to enable I2C (for OLED)

## Flashing
Flash using `qmk compile -kb crkbd -km jpe230_rp` for Pro Micro
