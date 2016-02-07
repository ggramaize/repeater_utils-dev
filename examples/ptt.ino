#include "ptt.h"

Ptt lePtt( 13, HIGH, PTT_NO_PERSIST);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  if( lePtt.get_rf_kill() != 0 )
    Serial.println( F("get_rf_kill() returned RF_KILLED while expecting otherwise."));
  
  if( lePtt.enable_ptt() != 0 )
    Serial.println( F("enable_ptt() returned RF_KILLED while expecting otherwise."));
  delay(1000);
  
  lePtt.disable_ptt();
  if( lePtt.get_rf_kill() != 0 )
    Serial.println( F("get_rf_kill() returned RF_KILLED while expecting otherwise."));
  delay(1000);

  if( lePtt.enable_ptt() != 0 )
    Serial.println( F("enable_ptt() returned RF_KILLED while expecting otherwise."));
  delay(500);

  lePtt.set_rf_kill( 2);
  delay(500);

  if( lePtt.enable_ptt() == 0 )
    Serial.println( F("enable_ptt() returned RF_ALLOWED while expecting otherwise."));
  lePtt.set_rf_kill( 0);
  delay(500);

  lePtt.disable_ptt();
  delay(500);

  if( lePtt.get_rf_kill() != 0 )
    Serial.println( F("get_rf_kill() returned RF_KILLED while expecting otherwise."));
  
  if( lePtt.enable_ptt() != 0 )
    Serial.println( F("enable_ptt() returned RF_KILLED while expecting otherwise."));
  delay(1000);

  lePtt.disable_ptt();
  delay(1000);
  
}

void loop() {
  
  // put your main code here, to run repeatedly:
  if( lePtt.enable_ptt() != 0 )
    Serial.println( F("enable_ptt() returned RF_KILLED while expecting otherwise."));
  delay(100);

  lePtt.disable_ptt();
  delay(900);
 
}
