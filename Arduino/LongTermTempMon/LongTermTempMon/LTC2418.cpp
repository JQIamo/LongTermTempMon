/*
   LTC2418.cpp - Arduino library for interfacing with the LTC2481 ADC

   Created by Neal Pisenti, 2015
   JQI - Joint Quantum Institute

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


/*
class LTC2418 {

uint32_t read(dac_ch_t ch);
uint32_t read_update(dac_ch_t ch_next);

private:
    int _current_channel;
    

};



#endif*/

#include "LTC2418.h"
#include "SPI.h"

LTC2418::LTC2418(int cs, int clk_speed) :
_cs(cs)
 {
	pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);
    
    _spi_settings = SPISettings(clk_speed, MSBFIRST, SPI_MODE0);

}

void LTC2418::set_calibration(float lsb, int offset_code){
	_lsb = lsb;
	_offset_code = offset_code;
}

//int32_t LTC2418::read(dac_ch_t ch){
//  
//
//  
//    SPI.beginTransaction(_spi_settings);
//    digitalWrite(_cs, LOW);
//       
//    // write channel
//    int32_t command;
//    command = _ch_codes[ch] << 24;
//    SPI.transfer(command);
////    for (int i = 0; i < 4; i ++){
////    	SPI.transfer(_ch_codes[ch]);
////    }
//   
//
//   
//   //dump this result (because it is on an unknown channel) and start another conversion
//    digitalWrite(_cs, HIGH);
//    delayMicroseconds(1);  
//    
//    // now, read back voltage
//    digitalWrite(_cs, LOW);
//    // wait for EOC to go low, signalling end of conversion
//    while (digitalRead(MISO)){
//    	continue;
//    }
//    for (int i = 0; i < 4; i++){
//    	_data.bytes[i] = SPI.transfer(_ch_codes[ch]);
//    }
//	
//       digitalWrite(_cs, HIGH);
//       SPI.endTransaction();
//    
//    //Combine bytes:
//    _data.val = (_data.bytes[0] << 24) | (_data.bytes[1] << 16) | (_data.bytes[2] << 8) | (_data.bytes[3]);
//    Serial.println(_data.val);
//    // convert data to meaningful reading
//    // should eventually implement parity, bounds checking, etc. here??
//    
//    // using example code from Linduino
//    float adc_voltage;
//    int32_t adc_code;
//    // 1) Bit-shift ADC code to the right 6 bits
//  	adc_code = _data.val>>6;   
//  	// 2) Convert ADC code from offset binary to binary
//  	adc_code -= 8388608;      
//   	// 3) Calculate voltage from ADC code, lsb, offset.
//  	adc_voltage=((float)adc_code + _offset_code)*(_lsb); 
//        //Serial.println(adc_voltage);
//  	
//  	// dump voltage into reading for that channel
//  	_readings[ch].adc_code = adc_code;
//  	_readings[ch].value = adc_voltage;
//       
//       return adc_code;
//  	
//}

int32_t LTC2418::read(dac_ch_t ch){
  

  
    SPI.beginTransaction(_spi_settings);
    
    // now, read back voltage
    digitalWrite(_cs, LOW);
    // wait for EOC to go low, signalling end of conversion
    while (digitalRead(MISO)){
    	continue;
    }
    for (int i = 0; i < 4; i++){
    	_data.bytes[i] = SPI.transfer(_ch_codes[ch]);
    }
	
       digitalWrite(_cs, HIGH);
       SPI.endTransaction();
    
    //Combine bytes:
    _data.val = (_data.bytes[0] << 24) | (_data.bytes[1] << 16) | (_data.bytes[2] << 8) | (_data.bytes[3]);
    // convert data to meaningful reading
    // should eventually implement parity, bounds checking, etc. here??
    
    // using example code from Linduino
    float adc_voltage;
    int32_t adc_code;
    // 1) Bit-shift ADC code to the right 6 bits
  	adc_code = _data.val>>6;   
  	// 2) Convert ADC code from offset binary to binary
  	adc_code -= 8388608;      
   	// 3) Calculate voltage from ADC code, lsb, offset.
  	adc_voltage=((float)adc_code + _offset_code)*(_lsb); 
        //Serial.println(adc_voltage);
  	
  	// dump voltage into reading for that channel
  	_readings[ch].adc_code = adc_code;
  	_readings[ch].value = adc_voltage;
       
       return adc_code;
  	
}

int32_t LTC2418::readOnly(dac_ch_t ch){
  int32_t adc_code;
  this->read(ch);
  adc_code = this->read(ch);
  return adc_code;
}

