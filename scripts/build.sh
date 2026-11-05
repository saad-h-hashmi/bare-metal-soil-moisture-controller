#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
mkdir -p "$ROOT/build"
avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -Os -std=gnu11 \
  -Wall -Wextra -Werror "$ROOT/src/main.c" \
  -o "$ROOT/build/soil-moisture-controller.elf"
avr-objcopy -O ihex -R .eeprom \
  "$ROOT/build/soil-moisture-controller.elf" \
  "$ROOT/build/soil-moisture-controller.hex"
echo "Build complete: build/soil-moisture-controller.hex"
