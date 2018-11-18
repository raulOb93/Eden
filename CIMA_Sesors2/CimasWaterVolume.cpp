#include "Arduino.h"
#include "CimasWaterVolume.h"

CimasWaterVolume::CimasWaterVolume() {}

void CimasWaterVolume::add(char identifier, int index, int pinTrigger, int pinEcho, double area){ 
  pinMode(pinTrigger, OUTPUT); 
  pinMode(pinEcho, INPUT); 
  digitalWrite(pinTrigger, LOW);
  _identifier[_count] = identifier;
  _index[_count] = index;
  _pinTrigger[_count] = pinTrigger;
  _pinEcho[_count] = pinEcho;
  _area[_count] = area;
  _count++;
  
}
void CimasWaterVolume::updateSensor(int index)
{
  digitalWrite(_pinTrigger[index], HIGH);
  delayMicroseconds(10);      
  digitalWrite(_pinTrigger[index], LOW);  
  _pulseTime[index] = pulseIn(_pinEcho[index], HIGH);
  _height[index] = _pulseTime[index] / 59; 
  _volume[index] = _height[index] * _area[index];          
}
void CimasWaterVolume::updateAll() {
  for(int i = 0; i<_count; i++) {
    updateSensor(i);
  }
}

void CimasWaterVolume::serialPrint()
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
      Serial.print(" Trigger Pin: ");
      Serial.print(_pinTrigger[index]);
      Serial.print(" Echo Pin: ");
      Serial.print(_pinEcho[index]);
      Serial.print(" Height: ");
      Serial.print(_height[index]);
      Serial.print(" Volume: ");
      Serial.print(_volume[index]);
      Serial.print("\n");
     }
}

void CimasWaterVolume::serialPrintData() {
  /* Exit function if there are no sensors added */
  if(_count == 0) {
    return;
  }
  /*Update all the sensors to receive new Data*/
  /*Sensor Type: 'V'*/
  Serial.write('V');
  /*Count: Number of sensors of this type*/
  Serial.write(_count);
  floatByte floatAux;
  for(int index = 0; index<_count; index++) 
    {
    Serial.write(_identifier[index]);
    Serial.write(_index[index]);
    Serial.write(_pinTrigger[index]);
    Serial.write(_pinEcho[index]);
    Serial.write((byte)0); //Error Handling should be placed here
    floatAux.f = _height[index];
    Serial.write(floatAux.b,4);
    floatAux.f = _volume[index];
    Serial.write(floatAux.b,4);
     }
   /*Close this sensor type data with its identifier V*/
 Serial.write('V');   
}

int CimasWaterVolume:: messageLenght() {
  if(_count == 0) {
    return 0;
  }
  return _count * sensorByteLenght + 2;
}
