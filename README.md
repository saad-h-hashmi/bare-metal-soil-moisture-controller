# Bare-Metal Soil Moisture Controller (ATmega328P)

A small register-level AVR C project for an Arduino Uno / ATmega328P. It reads
a soil-moisture sensor through ADC0 and controls a relay output according to
a configurable threshold. The uploaded source used an explicit `main()`
function and AVR registers rather than the Arduino `setup()` / `loop()` API;
this repository preserves that bare-metal approach.

## Pin mapping

| Function | ATmega328P signal | Arduino Uno pin |
| --- | --- | --- |
| Soil sensor analog output | ADC0 / PC0 | A0 |
| Relay control signal | PB0 | D8 |
| ADC reference | AVcc | 5 V reference rail |

The current control rule activates PB0 when the ADC reading is below `500`.
Actual sensor polarity and calibration depend on the sensor module and soil
conditions. Some relay modules are active-low; verify the module's input logic
and change the output polarity if required.

## Build (standalone AVR-GCC)

Requires `avr-gcc` and `avr-objcopy` for the ATmega328P toolchain.

```bash
./scripts/build.sh
```

This is a standalone AVR program with its own `main()` entry point. It is not
intended to be compiled as a regular Arduino IDE `.ino` sketch alongside the
Arduino core, which supplies its own `main()`.

## Hardware safety and validation

- Confirm the sensor's analog range with the pump disconnected before setting
  `DRY_THRESHOLD`.
- Confirm whether the relay board is active-high or active-low.
- Use a correctly rated relay/driver and a suitable separate supply for the
  pump; do not power a pump directly from an MCU pin.
- Check wiring, isolation, common-ground requirements, and supply ratings for
  the specific modules before applying power.

The supplied archive contained only the firmware source, not a circuit diagram
or test evidence. Hardware operation has therefore not been verified as part
of this code review. The AVR toolchain was not installed in the review
environment, so an AVR binary build could not be run here.
