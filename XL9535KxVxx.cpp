#include "XL9535KxVxx.h"


XL9535KxVxx::XL9535KxVxx(uint8_t SCL,uint8_t SDA,uint8_t I2CAddress)
{
	_XL9535KxVxxSCL=SCL;
	_XL9535KxVxxSDA=SDA;
	_XL9535KxVxxIIC_address=I2CAddress;
}


bool XL9535KxVxx::Init(void)
{
    #ifdef arduino
        Wire.begin();   // Initialization IIC
    #else
        Wire.begin(_XL9535KxVxxSCL, _XL9535KxVxxSDA);   // Initialization IIC
    #endif
    Wire.setClock(100000);  // Set frequency of 100KHZ
    
    int CheckData = 0x00;
    int InitializedEnableRegisterHighData = 0x00;
    
    Wire.beginTransmission(_XL9535KxVxxIIC_address);
    Wire.write(EnableRegisterHigh);
    if (Wire.endTransmission(false) != 0) {
        Serial.println("Error: endTransmission 1");
        return false;
    }
    // Adding a small delay to ensure the device is ready
    delay(10);
    Wire.requestFrom(_XL9535KxVxxIIC_address, 1, true);
    if (Wire.available()) {
        InitializedEnableRegisterHighData = Wire.read();
    } else {
        Serial.println("Error: No data available");
        return false;
    }
    Wire.beginTransmission(_XL9535KxVxxIIC_address);
    Wire.write(EnableRegisterHigh);
    Wire.write(0x80);
    if (Wire.endTransmission(true) != 0) {
        Serial.println("Error: endTransmission 2");
        return false;
    }
    Wire.beginTransmission(_XL9535KxVxxIIC_address);
    Wire.write(EnableRegisterHigh);
    if (Wire.endTransmission(false) != 0) {
        Serial.println("Error: endTransmission 3");
        return false;
    }
    delay(10);
    Wire.requestFrom(_XL9535KxVxxIIC_address, 1, true);
    if (Wire.available()) {
        CheckData = Wire.read();
    } else {
        return false;
    }
    Wire.beginTransmission(_XL9535KxVxxIIC_address);
    Wire.write(EnableRegisterHigh);
    Wire.write(InitializedEnableRegisterHighData);
    if (Wire.endTransmission(true) != 0) {
        Serial.println("Error: endTransmission 4");
        return false;
    }
    return (CheckData == 0x80);
}

void XL9535KxVxx::EnableRelay(int RelayLabel, bool EnableParameter)
{
    #ifdef arduino
        Wire.begin();   // Initialization IIC
    #else
        Wire.begin(_XL9535KxVxxSCL, _XL9535KxVxxSDA);   // Initialization IIC
    #endif
    Wire.setClock(100000);  // Set frequency of 100KHZ

    int InitializedEnableRegisterLowData = 0x00;
    int InitializedEnableRegisterHighData = 0x00;

    // Read the initial state of EnableRegisterLow
    Wire.beginTransmission(_XL9535KxVxxIIC_address);
    Wire.write(EnableRegisterLow);
    if (Wire.endTransmission(false) != 0) {
        Serial.println("Error: endTransmission on EnableRegisterLow read");
        return;
    }

    Wire.requestFrom(_XL9535KxVxxIIC_address, 1, true);
    if (Wire.available()) {
        InitializedEnableRegisterLowData = Wire.read();
    } else {
        Serial.println("Error: No data available on EnableRegisterLow read");
        return;
    }

    // Read the initial state of EnableRegisterHigh
    Wire.beginTransmission(_XL9535KxVxxIIC_address);
    Wire.write(EnableRegisterHigh);
    if (Wire.endTransmission(false) != 0) {
        Serial.println("Error: endTransmission on EnableRegisterHigh read");
        return;
    }

    Wire.requestFrom(_XL9535KxVxxIIC_address, 1, true);
    if (Wire.available()) {
        InitializedEnableRegisterHighData = Wire.read();
    } else {
        Serial.println("Error: No data available on EnableRegisterHigh read");
        return;
    }

    if (EnableParameter) {
        Wire.beginTransmission(_XL9535KxVxxIIC_address);
        Wire.write(EnableRegisterLow);
        Wire.write((~(RelayLabel & 0x00FF)) & InitializedEnableRegisterLowData);
        if (Wire.endTransmission(true) != 0) {
            Serial.println("Error: endTransmission on EnableRegisterLow write");
            return;
        }

        Wire.beginTransmission(_XL9535KxVxxIIC_address);
        Wire.write(EnableRegisterHigh);
        Wire.write((~((RelayLabel >> 8) & 0x00FF)) & InitializedEnableRegisterHighData);
        if (Wire.endTransmission(true) != 0) {
            Serial.println("Error: endTransmission on EnableRegisterHigh write");
            return;
        }
    } else {
        Wire.beginTransmission(_XL9535KxVxxIIC_address);
        Wire.write(EnableRegisterLow);
        Wire.write((RelayLabel & 0x00FF) | InitializedEnableRegisterLowData);
        if (Wire.endTransmission(true) != 0) {
            Serial.println("Error: endTransmission on EnableRegisterLow write (disable)");
            return;
        }

        Wire.beginTransmission(_XL9535KxVxxIIC_address);
        Wire.write(EnableRegisterHigh);
        Wire.write(((RelayLabel >> 8) & 0x00FF) | InitializedEnableRegisterHighData);
        if (Wire.endTransmission(true) != 0) {
            Serial.println("Error: endTransmission on EnableRegisterHigh write (disable)");
            return;
        }
    }

    Serial.println("Relay enabled/disabled successfully");
}

void XL9535KxVxx::SwitchRelay(int RelayLabel, bool SwitchParameter)
{
    #ifdef arduino
        Wire.begin();   // Initialization IIC
    #else
        Wire.begin(_XL9535KxVxxSCL, _XL9535KxVxxSDA);   // Initialization IIC
    #endif
    Wire.setClock(100000);  // Set frequency of 100KHZ

    int InitializedControlRegisterLowData = 0x00;
    int InitializedControlRegisterHighData = 0x00;

    // Read the initial state of ControlRegisterLow
    Wire.beginTransmission(_XL9535KxVxxIIC_address);
    Wire.write(ControlRegisterLow);
    if (Wire.endTransmission(false) != 0) {
        Serial.println("Error: endTransmission on ControlRegisterLow read");
        return;
    }

    Wire.requestFrom(_XL9535KxVxxIIC_address, 1, true);
    if (Wire.available()) {
        InitializedControlRegisterLowData = Wire.read();
    } else {
        Serial.println("Error: No data available on ControlRegisterLow read");
        return;
    }

    // Read the initial state of ControlRegisterHigh
    Wire.beginTransmission(_XL9535KxVxxIIC_address);
    Wire.write(ControlRegisterHigh);
    if (Wire.endTransmission(false) != 0) {
        Serial.println("Error: endTransmission on ControlRegisterHigh read");
        return;
    }

    Wire.requestFrom(_XL9535KxVxxIIC_address, 1, true);
    if (Wire.available()) {
        InitializedControlRegisterHighData = Wire.read();
    } else {
        Serial.println("Error: No data available on ControlRegisterHigh read");
        return;
    }

    if (SwitchParameter) {
        Wire.beginTransmission(_XL9535KxVxxIIC_address);
        Wire.write(ControlRegisterLow);
        Wire.write((RelayLabel & 0x00FF) | InitializedControlRegisterLowData);
        if (Wire.endTransmission(true) != 0) {
            Serial.println("Error: endTransmission on ControlRegisterLow write");
            return;
        }

        Wire.beginTransmission(_XL9535KxVxxIIC_address);
        Wire.write(ControlRegisterHigh);
        Wire.write(((RelayLabel >> 8) & 0x00FF) | InitializedControlRegisterHighData);
        if (Wire.endTransmission(true) != 0) {
            Serial.println("Error: endTransmission on ControlRegisterHigh write");
            return;
        }
    } else {
        Wire.beginTransmission(_XL9535KxVxxIIC_address);
        Wire.write(ControlRegisterLow);
        Wire.write(~(RelayLabel & 0x00FF) & InitializedControlRegisterLowData);
        if (Wire.endTransmission(true) != 0) {
            Serial.println("Error: endTransmission on ControlRegisterLow write (close)");
            return;
        }

        Wire.beginTransmission(_XL9535KxVxxIIC_address);
        Wire.write(ControlRegisterHigh);
        Wire.write(~((RelayLabel >> 8) & 0x00FF) & InitializedControlRegisterHighData);
        if (Wire.endTransmission(true) != 0) {
            Serial.println("Error: endTransmission on ControlRegisterHigh write (close)");
            return;
        }
    }

    Serial.println("Relay switched successfully");
}


