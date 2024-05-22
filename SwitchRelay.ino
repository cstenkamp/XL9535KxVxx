// datasheet: https://www.lcsc.com/datasheet/lcsc_datasheet_2205271545_XINLUDA-C3029626_C3029626.pdf (i²c address 0x20 for A0-A2=0, 0x27 for A1-A2=1
// from the zip-file mentioned in this issue: https://github.com/esphome/esphome/discussions/5710

/*
 * function:Open or close all relays every two seconds.
 * Author:JXL
 * 
   ESP32        XL9535KxVxx
    GND               GND
    3V3               VIN
    5V                5V
    21                SCL
    22                SDA
*/

#include "XL9535KxVxx.h"

/*
Open represents that the corresponding pad position of the pad 
is not short circuited, and the corresponding address bit is 0. 
Close represents that the corresponding pad position is short circuited, 
and the corresponding address bit is 1. Select the appropriate 
configuration to remove the annotation identification.
The default address is 0x20.
*/
#define XL9535_I2CAddr 0x20     //open:A0  A1  A2
// #define XL9535_I2CAddr 0x21   //open:A1  A2      close:A0
// #define XL9535_I2CAddr 0x22   //open:A0  A2      close:A1
// #define XL9535_I2CAddr 0x23   //open:A2          close:A0  A1
// #define XL9535_I2CAddr 0x24   //open:A0  A1      close:A2
// #define XL9535_I2CAddr 0x25   //open:A1          close:A0  A2
// #define XL9535_I2CAddr 0x26   //open:A0          close:A1  A2
// #define XL9535_I2CAddr 0x27   //                 close:A0  A1  A2


XL9535KxVxx XL9535KxVxx(22,21,XL9535_I2CAddr);


void setup() {
  Serial.begin(115200);
  Wire.begin();           //Initialization IIC
  Wire.setClock(100000);  //Set frequency of 100KHZ
  delay(100);
  Serial.println("Lets start");
  Serial.println(XL9535KxVxx.Init());
  XL9535KxVxx.EnableRelay(RelayALL,Enable);
  Serial.println("Started");
}

void loop() {
  
  XL9535KxVxx.SwitchRelay(RelayALL,Open);
  delay(2000);
  XL9535KxVxx.SwitchRelay(RelayALL,Close);
  delay(2000);

  XL9535KxVxx.SwitchRelay(RelayA1,Open);
  delay(1000);
  XL9535KxVxx.SwitchRelay(RelayA1,Close);
  delay(1000);
}
