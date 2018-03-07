/*
  $Id: MAX3100Serial.h,v 1.6 2018/03/07 12:40:42 ewan Exp $
  Arduino MAX3100Serial library.
  MAX3100Serial.h (C) 2016 Ewan Parker.

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

  The author may be reached at https://www.ewan.cc/ for queries.


  A Maxim Integrated MAX3100 external USART/UART communication library for
  Arduino, built to be source code compatible with the Serial library, etc.

  https://datasheets.maximintegrated.com/en/ds/MAX3100.pdf


  Assemble the Arduino and MAX3100CPD circuit as follows.  This could be made 
  to work with the other MAX3100 packages with minor changes to the wiring.

Arduino                  MAX3100CPD
=======               ================             CH340/FTDI
MOSI 11 ----------> 1 DIN       Vcc 14 --- 5V      ==========
MISO 12 <---------- 2 DOUT       TX 13 ----------> RX
SCK  13 ----------> 3 SCLK       RX 12 <---------- TX
     ## ----------> 4 /CS      /RTS 11     GND --- GND
      2 <---------- 5 /IRQ     /CTS 10
             5V --- 6 /SHDN      X1  9 ----------- Crystal pin1 --- 22pF --- GND
            GND --- 7 GND        X2  8 ----------- Crystal pin2 --- 22pF --- GND

The Arduino pin used for the chip select signal is chosen in the calling code.
The crystal chosen above is either 1.8432 MHz or 3.6864 MHz and this is also
chosen by the calling code.
*/

#ifndef MAX3100SERIAL_H
#define MAX3100SERIAL_H

#include <Stream.h>

#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

class MAX3100Serial : public Stream
{
public:
  // public methods
  MAX3100Serial(uint32_t crystalFrequencykHz, uint8_t chipSelectPin);
  ~MAX3100Serial();
  void begin(uint32_t speed);
  void end();
  int peek();

  virtual size_t write(uint8_t byte);
  virtual int read();
  virtual int available();
  virtual void flush();

  using Print::write;

private:
  uint8_t _chipSelectPin;
  uint8_t _clockMultiplier;

  void _setChipSelectPin(uint8_t csPin);
  void _setClockMultiplier(uint32_t kHz);
  int _busy();
};

// Arduino 0012 workaround
#undef int
#undef char
#undef long
#undef byte
#undef float
#undef abs
#undef round

#endif
