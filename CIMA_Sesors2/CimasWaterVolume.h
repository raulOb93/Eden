/*
 * Cimas Library for Water Level Sensors
 * Handles and formats signal from the sensors
 */
 #ifndef CimasWaterVolume
 #define CimasWaterLVolume_h 
 #include <Arduino.h>
 #define maxSensors 5 //Maximum number of sensors
 #define sensorByteLenght 13

class CimasWaterVolume {
  public:
  CimasWaterVolume();
  void add(char identifier, int index, int pinTrigger, int pinEcho, double area);
  void updateSensor(int index);
  void updateAll();
  void serialPrint();
  void serialPrintData();
  int messageLenght();
  private:  
  char _identifier[maxSensors];
  int _index[maxSensors];
  byte _pinTrigger[maxSensors];
  byte _pinEcho[maxSensors];
  float _pulseTime[maxSensors];
  float _height[maxSensors];
  float _area[maxSensors];
  float _volume[maxSensors];
  byte _count = 0;
  typedef union {
  float f;
  byte b[4];
  } floatByte;
};
#endif
