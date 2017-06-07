/*
  USB/UART bridge for Arduino Leonardo
  Originally written by Uli Koehler in 2015
  Published on techoverflow.net
  Updated by Louise Newberry to add baud rate support on STM32Duino (http://www.stm32duino.com/)

  Revision 1.0

  Published under the public domain (CC 1.0 Universal)
 */
#include <libmaple/usb_cdcacm.h>
#include <libmaple/usb.h>

int baudrate;

void setup() {
  // Adjust baudrate here
  baudrate = usb_cdcacm_get_baud();
  Serial.begin(baudrate);
  Serial1.begin(baudrate);
  //Wait until USB CDC port connects
  while (!Serial) {
  }
}

void loop() {
  // Reset baudrate on UART if it is changed on CDC.
  if (baudrate != usb_cdcacm_get_baud())
  {
    baudrate = usb_cdcacm_get_baud();
    Serial1.begin(baudrate);
  }
  
  //Copy byte incoming via TTL serial
  if (Serial1.available() > 0) {
    Serial.write(Serial1.read());
  }
  //Copy byte incoming via CDC serial
  if (Serial.available() > 0) {
    Serial1.write(Serial.read());
  }
}
