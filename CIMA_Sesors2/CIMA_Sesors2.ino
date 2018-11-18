#include "CimasWaterLevel.h"
#include "CimasWaterVolume.h"
#include "CimasDHT.h"
#include "CimasLight.h"
#include "CimasAirQ.h"

//Pines defectuosos: D5

unsigned long updateRate = 2500;
unsigned long previousMillis = updateRate;

CimasDHT dht;
CimasWaterLevel waterLevel;
CimasWaterVolume waterVolume;
CimasLight light;
CimasAirQ airQuality;


void setup() {
  Serial.begin(9600); 
 /* dht.add('A',1,14);
  dht.add('A',2,15);
  dht.add('B',1,16);
  dht.add('B',2,17);
  dht.add('C',1,18);
  dht.add('C',2,19);
  dht.add('D',1,20);
  dht.add('D',2,21);
  
  waterLevel.add('A',1, 2, true);
  waterLevel.add('A',2, 3, false);
  waterLevel.add('B',3, 4, true);
  waterLevel.add('B',4, 6, false);
  waterLevel.setPump('P', 7); */

  //waterVolume.add('V', 1, 11, 12, 24*24*PI); //1808.54
  light.add('L', 1, 1);
  airQuality.add('Q', 1, 0);
}
 
void loop() {
 updateSensors();
 serialRead();
}

void updateSensors() {
   if ((unsigned long)(millis() - previousMillis) >= updateRate) {
     // Serial.print("Updating "); Serial.print(millis()); Serial.print("\n");
      dht.updateAll();
      //dht.serialPrintData(); Serial.print("\n");
      //dht.serialPrint(); Serial.print("\n"); 
      waterLevel.updateAll();
      waterVolume.updateAll();
      waterLevel.updatePumpState();
      light.updateAll();
      airQuality.updateAll();
      
      //waterLevel.serialPrintData(); Serial.print("\n");
      //waterLevel.serialPrint(); Serial.print("\n");
      previousMillis = millis();
   }
}

void serialRead() {
    if (Serial.available() > 0) {
    char incomingByte = Serial.read();
    switch(incomingByte) {
    case 'A': 
    {
      Serial.print("Light Sensor Data"); Serial.print("\n"); light.serialPrint(); Serial.print("\n");
      Serial.print("Air Quality Sensor Data"); Serial.print("\n"); airQuality.serialPrint(); Serial.print("\n");
      Serial.print("DHT22 Data"); Serial.print("\n"); dht.serialPrint(); Serial.print("\n");
      Serial.print("Water Volume Data"); Serial.print("\n"); waterVolume.serialPrint(); Serial.print("\n");
      Serial.print("Water Level Data"); Serial.print("\n"); waterLevel.serialPrint(); Serial.print("\n");       
      break;
    }
    case 'D': Serial.print("DHT22 Data"); Serial.print("\n"); dht.serialPrint(); Serial.print("\n"); break;
    case 'L': Serial.print("Light Sensor Data"); Serial.print("\n"); light.serialPrint(); Serial.print("\n"); break;
    case 'Q': Serial.print("Air Quality Sensor Data"); Serial.print("\n"); airQuality.serialPrint(); Serial.print("\n"); break;
    case 'V': Serial.print("Water Volume Data"); Serial.print("\n"); waterVolume.serialPrint(); Serial.print("\n"); break; 
    case 'W': Serial.print("Water Level Data"); Serial.print("\n"); waterLevel.serialPrint(); Serial.print("\n"); break;   
    case 'a': printAllSensorsData();  break;
    case 'd': dht.serialPrintData(); break;
    case 'l': light.serialPrintData(); break;
    case 'q': airQuality.serialPrintData(); break;
    case 'v': waterVolume.serialPrintData(); break;
    case 'w': waterLevel.serialPrintData(); break;
    default: Serial.print("Error: Invalid input\n"); 
    }
  }
}

void printAllSensorsData() {
  int messageLenght =  dht.messageLenght()  + waterLevel.messageLenght() + waterVolume.messageLenght() + light.messageLenght() + airQuality.messageLenght();
  Serial.write('<');
  Serial.write(messageLenght + 1); // Se le suma 1 debido al simbolo < agregado para cerrar el mensaje.
  dht.serialPrintData();  
  light.serialPrintData();
  airQuality.serialPrintData();
  waterVolume.serialPrintData();
  waterLevel.serialPrintData();
  Serial.write('>');
}

