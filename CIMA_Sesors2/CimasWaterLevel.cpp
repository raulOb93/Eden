#include "Arduino.h"
#include "CimasWaterLevel.h"

CimasWaterLevel::CimasWaterLevel(){
  _pumpSet = false;
  _pumpError = false;
  _pumpState = false;
  }
void CimasWaterLevel::add(char identifier, int index, int pin, bool nc) { 
   pinMode(pin,INPUT_PULLUP);
  _identifier[_count] = identifier;
  _index[_count] = index;
  _pin[_count] = pin;
  _output[_count] = false;
  _nc[_count] = nc;
  _count++;
  
}
void CimasWaterLevel::updateSensor(int index)
{
  _output[index] = !digitalRead(_pin[index]);
}
void CimasWaterLevel::updateAll() {
  for(int i = 0; i<_count; i++) {
    updateSensor(i);
  }
}

void CimasWaterLevel::setPump(char identifier, int pin) {
  _pumpSet = true;
  _pumpIdentifier = identifier;
  _pumpPin = pin;
  pinMode(pin, OUTPUT);
}

void CimasWaterLevel::updatePumpState() {
 bool auxHighLevel = true;
 bool auxLowLevel = true;
 for(int i = 0; i<_count; i++) {
  if(_nc[i]) {
    auxLowLevel = auxLowLevel && _output[i];
  } else {
    auxHighLevel = auxHighLevel && _output[i];
  }
 }
 if(!auxLowLevel && auxHighLevel) {
  digitalWrite(_pumpPin, HIGH); //HIGH VALUE TO DEACTIVATE PUMP
  _pumpError = true;
  return;
 }
 if(!(auxLowLevel || auxHighLevel) || (auxLowLevel && !auxHighLevel && _pumpState)) {
  digitalWrite(_pumpPin, LOW); // LOW VALUE TO ACTIVATE PUMP
  _pumpState = true;
  _pumpError = false;
  return;
 } else {
  digitalWrite(_pumpPin, HIGH); //HIGH VALUE TO DEACTIVATE PUMP
  _pumpState = false;
  _pumpError = false;
  return;
 }
}

void CimasWaterLevel::serialPrint()
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
      Serial.print(" Output: ");
      Serial.print(_output[index]);
      Serial.print("\n");
     }

     Serial.print("Pump ");
     if(_pumpSet) {
      
      Serial.print(_pumpIdentifier);
      Serial.print(" State ");
      if(_pumpError) {
      Serial.print(" ERROR");  
      } else if(_pumpState) {
      Serial.print(" ON");
      } else {
      Serial.print(" OFF");
      }     
     } else {
      Serial.print(" NOT SET"); 
     }
}

void CimasWaterLevel::serialPrintData() {
  /* Exit function if there are no sensors added */
  if(_count == 0) {
    return;
  }
  /*Update all the sensors to receive new Data*/
  /*Sensor Type: 'W'*/
  Serial.write('W');
  /*Count: Number of sensors of this type*/
  Serial.write(_count);
  for(int index = 0; index<_count; index++) 
    {
    Serial.write(_identifier[index]);
    Serial.write(_index[index]);
    Serial.write(_pin[index]);
    Serial.write(_output[index]);
     }
   /*Close this sensor type data with its identifier W*/
 Serial.write('W');   
 Serial.write((byte)1); // Pump count. Hardcoded for 1 pump.
 if(_pumpSet) {
  Serial.write('P');     
  Serial.write(_pumpIdentifier);
  Serial.write(_pumpPin);
  Serial.write(_pumpState);
  Serial.write(_pumpError);
  Serial.write('P'); 
 }
}

int CimasWaterLevel:: messageLenght() {
  if(_count == 0) {
    return 0;
  }
  int lenght = _count * sensorByteLenght + 3;
  if(_pumpSet) {
    lenght += pumpByteLenght + 3;
  }
  return lenght;
}

