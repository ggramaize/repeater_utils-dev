/*
    Copyright (c) 2016 Geoffroy GRAMAIZE

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the Software
    is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef PTT_H
#define PTT_H

#include <stdint.h>

/* 
 * The PTT_NO_PERSIST constant can be customized if necessary.
 * It is used in class Ptt constructor to set the RF Kill state
 * persistence as unmanaged.
 */
#ifndef PTT_NO_PERSIST
#define PTT_NO_PERSIST    0xFFFF
#endif  // PTT_NO_PERSIST


/**
 * This class enables simple management of a RF Tx device control pin 
 * (AKA "RF On", or PTT pin), with transparent RF Kill management, 
 * and optionnal RF Kill state persistence, using Arduino EEPROM.
 */
class Ptt {
private:
  /**
   * Stores the RF Inhibition parameter. Value different from zero means 
   * we must inhibit the PTT pin output.
   */
  uint8_t rfKillState;

  /**
   * Used to tell which state enables the Tx RF function on the assigned pin.
   */
  uint8_t activePttState;

  /**
   * The pin assigned to control the Tx RF function.
   */
  int pttPin;

  /**
   * EEPROM Address used store the RF inhibition value. If eepromSettingAddr
   * is PTT_NO_PERSIST, we don't use EEPROM to get a persistent RFKill state.
   */
  int eepromSettingAddr;
  
public:
  /**
   * Construct a Ptt class, restores the RF inhibition setting, if
   * applicable, initializes the PTT pin, and sets it to disabled.
   * 
   * If you don't want to use EEPROM to manage a persistent RF Kill state,
   * set eepromSettingAddr to PTT_NO_PERSIST.
   * 
   * @param pttPin              The assigned RF transmit inhibition pin.
   * @param activePttState      The active PTT Pin State. Either HIGH or LOW           
   * @param eepromSettingAddr   The persistent RF Kill state EEPROM address. 
   */
  Ptt( int pttPin, uint8_t activePttState, int eepromSettingAddr);

  /**
   * Turns the RF control pin on, if RF Kill state is unset.
   * @return  The RF inhibition status. useful to skip code when RF is inhibited
   */
  uint8_t enable_ptt( void) const;

  /**
   * Turn the RF control pin off.
   */
  void disable_ptt( void) const;

  /**
   * Updates the RF Kill value. When inhibition is set, the functions immediately 
   * disables the PTT, and set the inhibition parameter to block any transmission 
   * until the inhibition parameter is unset.
   * @param rfKillState   The expected state. Disables the RF if different from 0
   */
  void set_rf_kill( uint8_t rfKillState);

  /**
   * Fetches the RF Kill state. RF Kill state is different from zero if inactive.
   * @return  The RF Kill State.
   */
  uint8_t get_rf_kill() const;
};

#endif  // PTT_H
