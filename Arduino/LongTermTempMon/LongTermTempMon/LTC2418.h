/*
   LTC2418.h - Arduino library for interfacing with the LTC2481 ADC

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



Portions of this code were taken from the Linduino library, provided by Linear Technologies. The following copyright notice applies:

http://www.linear.com/product/LTC2418

http://www.linear.com/product/LTC2418#demoboards

REVISION HISTORY
$Revision: 1853 $
$Date: 2013-08-08 17:01:29 -0700 (Thu, 08 Aug 2013) $

Copyright (c) 2013, Linear Technology Corp.(LTC)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of Linear Technology Corp.

The Linear Technology Linduino is not affiliated with the official Arduino team.
However, the Linduino is only possible because of the Arduino team's commitment
to the open-source community.  Please, visit http://www.arduino.cc and
http://store.arduino.cc , and consider a purchase that will help fund their
ongoing work.

*/


#include "Arduino.h"
#include "SPI.h"

#ifndef LTC2418_h
#define LTC2418_h

#define REF_VOLTAGE 2.5

// from LTC2418.h, provided by Linear Technologies.

//! @name LTC2418 Single-Ended configuration bytes
//! @{
//! Address bytes with enable sequence prepended
#define LTC2418_CH0            0xB0
#define LTC2418_CH1            0xB8
#define LTC2418_CH2            0xB1
#define LTC2418_CH3            0xB9
#define LTC2418_CH4            0xB2
#define LTC2418_CH5            0xBA
#define LTC2418_CH6            0xB3
#define LTC2418_CH7            0xBB
#define LTC2418_CH8            0xB4
#define LTC2418_CH9            0xBC
#define LTC2418_CH10           0xB5
#define LTC2418_CH11           0xBD
#define LTC2418_CH12           0xB6
#define LTC2418_CH13           0xBE
#define LTC2418_CH14           0xB7
#define LTC2418_CH15           0xBF
//! @}

//! @name LTC2418 Differential configuration bytes
//! @{
//! Address bytes with enable sequence prepended
#define LTC2418_P0_N1          0xA0
#define LTC2418_P1_N0          0xA8

#define LTC2418_P2_N3          0xA1
#define LTC2418_P3_N2          0xA9

#define LTC2418_P4_N5          0xA2
#define LTC2418_P5_N4          0xAA

#define LTC2418_P6_N7          0xA3
#define LTC2418_P7_N6          0xAB

#define LTC2418_P8_N9          0xA4
#define LTC2418_P9_N8          0xAC

#define LTC2418_P10_N11        0xA5
#define LTC2418_P11_N10        0xAD

#define LTC2418_P12_N13        0xA6
#define LTC2418_P13_N12        0xAE

#define LTC2418_P14_N15        0xA7
#define LTC2418_P15_N14        0xAF
//! @}

// End portion taken from Linduino library

//#define LTC2418_MEAS_TIME	250000	// 250ms allowed for reading

// enum for dac addressing codes 

//! @name enum for LTC2418 addressing codes.
//! @{
//! CH0..CH15 are single-ended measurements.
//! PCH0..PCH7 are differential measurements positive-oriented.
//! NCH0..NCH7 are differential measurements negative-oriented.

enum  dac_ch_t { CH0, CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8, CH9, CH10, CH11, CH12, CH13, CH14, CH15, PCH0, NCH0, PCH1, NCH1, PCH2, NCH2, PCH3, NCH3, PCH4, NCH4, PCH5, NCH5, PCH6, NCH6, PCH7, NCH7, CH_COUNT };

/*enum { 	CH0 = LTC2418_CH0, 
		CH1 = LTC2418_CH1, 
		CH2 = LTC2418_CH2,
		CH3 = LTC2418_CH3, 
		CH4 = LTC2418_CH4, 
		CH5 = LTC2418_CH5,
		CH6 = LTC2418_CH6, 
		CH7 = LTC2418_CH7,
		CH8 = LTC2418_CH8, 
		CH9 = LTC2418_CH9, 
		CH10 = LTC2418_CH10,
		CH11 = LTC2418_CH11, 
		CH12 = LTC2418_CH12, 
		CH13 = LTC2418_CH13,
		CH14 = LTC2418_CH14, 
		CH15 = LTC2418_CH15,
		
		PCH0 = LTC2418_P0_N1,
		NCH0 = LTC2418_P1_N0,
		
		PCH1 = LTC2418_P2_N3,
		NCH1 = LTC2418_P3_N2,
		
		PCH2 = LTC2418_P4_N5,
		NCH2 = LTC2418_P5_N4,
		
		PCH3 = LTC2418_P6_N7,
		NCH3 = LTC2418_P7_N6,
		
		PCH4 = LTC2418_P8_N9,
		NCH4 = LTC2418_P9_N8,
		
		PCH5 = LTC2418_P10_N11,
		NCH5 = LTC2418_P11_N10,
		
		PCH6 = LTC2418_P12_N13,
		NCH6 = LTC2418_P13_N12,
		
		PCH7 = LTC2418_P14_N15,
		NCH7 = LTC2418_P15_N14	} dac_ch_t;
		*/
		
		

//! @}

class LTC2418 {
  
  public:

    LTC2418(int cs, int clk_speed = 1000000);

    //! read given channel.
    int32_t read(dac_ch_t ch);
    
    //! @name read_continuous
    //! @{ 
    //!	continuous polling of channels given by ch_spec.
    //! currently only supports single-ended mode.
    //! ch_spec is a 16-bit number where the nth bit says whether that channel 
    //! should be polled or not. eg, 0x0003 -> read channel 0 & 1. 
    //! (= 0b0000000000000011)
    
    // not yet implemented...
    //void read_continuous(uint16_t ch_spec);
    
    void set_calibration(float lsb, int offset_code);
    
    //! @}

private:
    SPISettings _spi_settings;
    
    int _cs;
    int _offset_code = 0;
    float _lsb = REF_VOLTAGE/(2^24);
    
	byte _ch_codes[CH_COUNT] = { LTC2418_CH0, LTC2418_CH1, LTC2418_CH2, LTC2418_CH3, LTC2418_CH4, LTC2418_CH5, LTC2418_CH6, LTC2418_CH7, LTC2418_CH8,  LTC2418_CH9, LTC2418_CH10, LTC2418_CH11, LTC2418_CH12, LTC2418_CH13, LTC2418_CH14, LTC2418_CH15, LTC2418_P0_N1, LTC2418_P1_N0, LTC2418_P2_N3, LTC2418_P3_N2, LTC2418_P4_N5, LTC2418_P5_N4, LTC2418_P6_N7, LTC2418_P7_N6, LTC2418_P8_N9, LTC2418_P9_N8, LTC2418_P10_N11, LTC2418_P11_N10, LTC2418_P12_N13, LTC2418_P13_N12, LTC2418_P14_N15, LTC2418_P15_N14 };
	
	    
    struct LTC2481_measurement {
    	bool valid;
    	int32_t adc_code;
    	float value;
    } _readings[CH_COUNT];
    	
    
	union {
		bool bits[32];
		int32_t val;
		byte bytes[4];
	} _data;
	

};



#endif
