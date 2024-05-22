#ifndef _XL9535KXVX_H_
#define _XL9535KXVX_H_

#include <Arduino.h>
#include <Wire.h>

/*Define Module Register Address*/
#define ControlRegisterLow   0x02
#define ControlRegisterHigh   0x03
#define EnableRegisterLow   0x06
#define EnableRegisterHigh   0x07

/*Define relay labels*/
#define RelayA1  0x0001   //A1 relay
#define RelayA2  0x0002   //A2 relay
#define RelayA3  0x0004   //A3 relay
#define RelayA4  0x0008   //A4 relay
#define RelayA5  0x0010   //A5 relay
#define RelayA6  0x0020   //A6 relay
#define RelayA7  0x0040   //A7 relay
#define RelayA8  0x0080   //A8 relay

#define RelayB1  0x0100   //B1 relay
#define RelayB2  0x0200   //B2 relay
#define RelayB3  0x0400   //B3 relay
#define RelayB4  0x0800   //B4 relay
#define RelayB5  0x1000   //B5 relay
#define RelayB6  0x2000   //B6 relay
#define RelayB7  0x4000  //B7 relay
#define RelayB8  0x8000   //B8 relay

#define RelayALL  0xFFFF   //ALL relay

/*Define enabling parameters*/
#define Enable   true
#define DisEnable   false

/*Define switch parameters*/
#define Open   true
#define Close   false

/*If the value after # if is 1, then use the development board 
arduino UNO. If modified to 0, then use the development board ESP32*/
#if 0
  #define arduino
#else

#endif


class XL9535KxVxx
{
private:
		uint8_t _XL9535KxVxxSCL,_XL9535KxVxxSDA,_XL9535KxVxxIIC_address;
    
public:
	/*Define the pins used for SCL, SDA, and IIC device addresses.*/
	XL9535KxVxx(uint8_t SCL,uint8_t SDA,uint8_t I2CAddress);
	
	/*Initialization and power on judge whether the communication
	is normal by writing data to the enable register and then reading 
	data for verification.*/
	bool Init(void);
	
	/*
	Enable the relay, which only allows control of the relay. This 
	function does not control the relay, and the relay in the disabled 
	state will be in the disconnected state.
	parameter：
	RelayLabel optional RelayA1 ... RelayA16
	EnableParameter optional Enable or DisEnable
	*/
	void EnableRelay(int RelayLabel , bool EnableParameter);
	
	/*
	To control the relay switch, it is necessary to set the control 
	permission of the relay to allow before using this function.
	parameter：
	RelayLabel optional RelayA1 ... RelayA16
	SwitchParameter optional Open or Close
	*/
	void SwitchRelay(int RelayLabel , bool SwitchParameter);
	
};



#endif
