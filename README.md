# repeater_utils-dev
Utilities for amateur repeaters. Will be converted to an appropriate library later.

## Contents
### Ptt
This class enables simple management of a RF Tx device control pin (AKA "RF On", or PTT pin), with transparent RF Kill management, and optionnal RF Kill state persistence, using Arduino's EEPROM.

Target footprint:
~approx 700 bytes of progmem, 6 bytes of ram, 0 or 1 byte of EEPROM

Example: in examples/ptt.ino
