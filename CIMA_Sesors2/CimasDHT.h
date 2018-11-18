/*
 * Cimas DHT Library for DHT22 Sensors.
 * Handles and formats signal from the sensors
 */
 #ifndef CimasDHT
 #define CimasDHT_h 
 #include <Arduino.h>
 #include <DHT.h>
 #define maxSensors 30 //Maximum number of sensors
 #define DHTTYPE DHT22   // DHT 22  (AM2302)
 #define sensorByteLenght 12
class CimasDHT {
  public:
  CimasDHT();
  void add(char identifier, int index, int pin);
  void updateSensor(int index);
  void updateAll();
  void serialPrint();
  void serialPrintData();
  int messageLenght();
  private:
  DHT* _sensor[maxSensors];
  char _identifier[maxSensors];
  int _index[maxSensors];
  byte _pin[maxSensors];
  float _humidity[maxSensors];
  float _temperature[maxSensors];
  byte _count = 0;
  typedef union {
   float f;
   byte b[4];
   } floatByte;
};
#endif
