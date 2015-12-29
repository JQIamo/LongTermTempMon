#include "LTC2418.h"
#include "SPI.h"
#include <SerialCommand.h>

const byte cs_pin(14);
const float vref(5.1);
const double R_ref0(20000.0);
const double R_ref2(20000.0);

const double steinhart_A(1.1254e-3);
const double steinhart_B(2.3469e-4);
const double steinhart_C(0.8584e-7);

SerialCommand sCmd;

LTC2418 adc(cs_pin, 500000);

void readCh(int chNum) {
  int result;
  if (chNum == 0) {
    result = adc.read(CH0);
  } else if (chNum == 1) {
    result = adc.read(CH1);
  } else if (chNum == 2) {
    result = adc.read(CH2);
  } else if (chNum == 3) {
    result = adc.read(CH3);
  } else {
    return; //unexpected argument
  }
  double voltage = result*vref/8388608.0; //8388608 is 2^23
  double R_therm = R_ref0*result/(8388608.0-result);
  
  double T  = 1/(steinhart_A + steinhart_B*log(R_therm) + steinhart_C*pow(log(R_therm),3.0))-273.15;
  
  char lineToDisplay[100];
  //snprintf(lineToDisplay, 17,"Pgain  (%1s)    %2u",enc_set_pgain.step_size_label().c_str(),newPgain);
  snprintf(lineToDisplay, 100, "Ch:%u  %u  %7.6f %7.6f %7.6f", chNum,result,voltage,R_therm,T);
  Serial.println(lineToDisplay);
}


                    
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  //sCmd.addCommand("R", readTest); 

}

void loop() {
  // put your main code here, to run repeatedly:
  sCmd.readSerial();
  
  readCh(0);
  readCh(2);
  delay(1000);
  
  //int res ;
  //res = adc.read(CH0);
  //Serial.println(res);
  //delay(1000);

}
