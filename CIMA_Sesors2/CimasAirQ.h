/*
 * Cimas Library for Light Sensors (Simple fotoresistors)
 *  IMPORTANT: This sensors should be replaced for something more accurate
 * Handles and formats signal from the sensors
 */
 #ifndef CimasAirQ
 #define CimasAirQ_h 
 #include <Arduino.h>
 #define maxSensors 5 //Maximum number of sensors
 #define sensorByteLenght 6
class CimasAirQ {
  public:
  CimasAirQ();
  void add(char identifier, int index, int analogPin);
  void updateSensor(int index);
  void updateAll();
  void serialPrint();
  void serialPrintData();
  int messageLenght();
  private:
  char _identifier[maxSensors];
  int _index[maxSensors];
  byte _analogPin[maxSensors];
  int _output[maxSensors];
  byte _count = 0;
};
#endif
