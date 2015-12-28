#include "LTC2418.h"
#include "SPI.h"

const byte cs_pin(14);

LTC2418 adc(cs_pin, 100000);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  int res ;
  res = adc.read(CH3);
  Serial.println(res);
  delay(1000);

}
