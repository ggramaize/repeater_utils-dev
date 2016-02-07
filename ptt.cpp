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

#include <stdint.h>

#include <EEPROM.h>
#include "Arduino.h"

#include "ptt.h"

Ptt::Ptt( int pttPin, uint8_t activePttState, int eepromSettingAddr)
{
  this->pttPin = pttPin;
  this->activePttState = activePttState;
  this->eepromSettingAddr = eepromSettingAddr;

  if( this->eepromSettingAddr != PTT_NO_PERSIST )
  {
    // RF Kill state is persistent, and fetched from EEPROM
    this->rfKillState = EEPROM.read( this->eepromSettingAddr);
  }
  else
  {
    // RF Kill state is not persistent. We assume it is unset.
    this->rfKillState = 0;
  }
  
  // Set the PTT pin as an output pin
  pinMode( this->pttPin, OUTPUT);
  
  // Disable the PTT.
  this->disable_ptt();
}

uint8_t Ptt::enable_ptt( void) const
{
  // RF kill is active, we immediately return the RF Kill status.
  if( rfKillState != 0)
    return this->rfKillState;

  // Write the registered PTT Active state
  digitalWrite( this->pttPin, this->activePttState);

  return 0;
}

void Ptt::disable_ptt( void) const
{
  // Write the opposite state of the registered PTT active state.
  if( this->activePttState == LOW)
    digitalWrite( this->pttPin, HIGH);
    
  else
    digitalWrite( this->pttPin, LOW);
}

void Ptt::set_rf_kill( uint8_t rfKillState)
{
  // Update the runtime RF Kill state.
  this->rfKillState = rfKillState;

  // Update the EEPROM, if we manage RF Kill state persistence.
  if( this->eepromSettingAddr != PTT_NO_PERSIST)
    EEPROM.update( this->eepromSettingAddr, this->rfKillState);

  // If RF inhibition is set, immediately disable the PTT.
  if( rfKillState != 0 )
    this->disable_ptt();
}

uint8_t Ptt::get_rf_kill() const
{
  return this->rfKillState;
}

