#include "Arduino.h"
#include "CimasLight.h"

CimasLight::CimasLight() {}
void CimasLight::add(char identifier, int index, int analogPin) {
  _identifier[_count] = identifier;
  _index[_count] = index;
  _analogPin[_count] = analogPin;
  _count++;
}

void CimasLight::updateSensor(int index)
{
  _output[index] = analogRead(_analogPin[index]);
}
void CimasLight::updateAll() {
  for(int i = 0; i<_count; i++) {
    updateSensor(i);
  }
}

void CimasLight::serialPrint()
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
      Serial.print(" Analog Pin: ");
      Serial.print(_analogPin[index]);
      Serial.print(" Output: ");
      Serial.print(_output[index]);
       }
      Serial.print("\n");
}

void CimasLight::serialPrintData() {
   /* Exit function if there are no sensors added */
  if(_count == 0) {
    return;
  }
  /*Sensor Type: 'L*/
  Serial.write('L');
  /*Count: Number of sensors of this type*/
  Serial.write(_count);
  for(int index = 0; index<_count; index++) 
    {    
    Serial.write(_identifier[index]);
    Serial.write(_index[index]);
    Serial.write(_analogPin[index]);
    Serial.write((byte)0); // This place should be replaced by error handler 
    Serial.write(_output[index]);
    Serial.write(_output[index] >> 8);
     }
   /*Close this sensor type data with its identifier L*/
 Serial.write('L');   
}

int CimasLight:: messageLenght() {
  if(_count == 0) {
    return 0;
  }
  return _count * sensorByteLenght + 3;
}
