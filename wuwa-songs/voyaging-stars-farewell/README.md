# Voyaging-Star-Player

A physical audio-visualizer built with an Arduino Uno that plays "Voyaging Star's Farewell" (Wuthering Waves OST) alongside frame-synced lyrics and a procedural falling snow animation on an OLED display.

Built as a personal gift.

## Hardware Stack
* Arduino Uno R3
* 1.3" I2C OLED (SH1106, Address `0x3C`)
* DFPlayer Mini MP3 Module
* 4Ω 3W Speaker
* 1x Tactile Push Button
* 1x Micro SD Card (FAT32)
* 1x 1kΩ Resistor

## Wiring Reference

| Component | Pin | Arduino | Notes |
| :--- | :--- | :--- | :--- |
| **OLED** | VCC <br> GND <br> SDA <br> SCL | 5V <br> GND <br> A4 <br> A5 | |
| **Button** | Leg 1 <br> Leg 2 | A3 <br> GND | Using `INPUT_PULLUP`. Wire diagonally. |
| **DFPlayer** | VCC <br> GND <br> RX <br> TX <br> SPK_1/2 | 5V <br> GND <br> D10 <br> D11 <br> Speaker | **Requires 1kΩ resistor between Arduino D10 and DFPlayer RX.** |

## Dependencies
* `Adafruit_GFX`
* `Adafruit_SH110X`
* `DFRobotDFPlayerMini`

**Note on Audio:** Place the target track on the root of the SD card and rename it to `001.mp3`.

## Dev Notes & Workarounds

* **SRAM Overflow / OOM:** The Uno only has 2KB of SRAM, and the OLED frame buffer reserves 1KB on boot. Loading the lyrics string array and the timestamp `unsigned long` array into standard memory caused an immediate RAM overflow and a fatal null pointer dereference. **Fix:** Relocated the data structures to Flash memory using the `F()` macro and `PROGMEM`, reading timestamps on the fly with `pgm_read_dword()`.
* **SH1106 I2C Lockup:** Generic clone 1.3" OLEDs often crash if sent a soft-reset command during initialization. **Fix:** Booted the display with `display.begin(0x3C, false)` to bypass the reset sequence, then manually forced `display.setContrast(255)` to revive the charge pump.

## Disclaimer
This is a non-commercial, personal project. "Voyaging Star's Farewell", its lyrics, and the Wuthering Waves IP are the property of Kuro Games.
