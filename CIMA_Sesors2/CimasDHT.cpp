#include "Arduino.h"
#include "CimasDHT.h"
#include <DHT.h>

CimasDHT::CimasDHT() {}
void CimasDHT::add(char identifier, int index, int pin) {
  _sensor[_count] = new DHT(pin, DHTTYPE);
  _identifier[_count] = identifier;
  _index[_count] = index;
  _pin[_count] = pin;
 // _nc[_count] = nc;
  _count++;
}

void CimasDHT::updateSensor(int index)
{
  _humidity[index] = _sensor[index]->readHumidity();
  _temperature[index] = _sensor[index]->readTemperature();
}
void CimasDHT::updateAll() {
  for(int i = 0; i<_count; i++) {
    updateSensor(i);
  }
}

void CimasDHT::serialPrint()
{
    if(_count == 0) {
      Serial.print("Not data available. Sensor _count = 0");
      return;
    }
    for(int index = 0; index<_count; index++) 
    {
      Serial.print("Sensor ");
      Serial.print(_identifier[index]);
      Serial.print(_index[index]);
      Serial.print(" Pin: ");
      Serial.print(_pin[index]);
      if (isnan(_temperature[index]) || isnan(_humidity[index])) {
      Serial.write(" Error");
      } else {
      Serial.print(" Temperature: ");
      Serial.print(_temperature[index]);
      Serial.print(" Humidity: ");
      Serial.print(_humidity[index]);
       }
      Serial.print("\n");
     }
}

void CimasDHT::serialPrintData() {
   /* Exit function if there are no sensors added */
  if(_count == 0) {
    return;
  }
  /*Sensor Type: 'D'*/
  Serial.write('D');
  /*Count: Number of sensors of this type*/
  Serial.write(_count);
  floatByte floatAux;
  for(int index = 0; index<_count; index++) 
    {    
    Serial.write(_identifier[index]);
    Serial.write(_index[index]);
    Serial.write(_pin[index]);
    if (isnan(_temperature[index]) || isnan(_humidity[index])) {
      Serial.write((byte)1);
    } else {
      Serial.write((byte)0);
    }
    floatAux.f = _temperature[index];    
    Serial.write(floatAux.b,4);
    floatAux.f = _humidity[index];
    Serial.write(floatAux.b,4);
     }
   /*Close this sensor type data with its identifier D*/
 Serial.write('D');   
}

int CimasDHT:: messageLenght() {
  if(_count == 0) {
    return 0;
  }
  return _count * sensorByteLenght + 3;
}

