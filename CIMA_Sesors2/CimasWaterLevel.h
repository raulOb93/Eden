/*
 * Cimas Library for Water Volume Sensors
 * Handles and formats signal from the sensors
 */
 #ifndef CimasWaterLevel
 #define CimasWaterLevel_h 
 #include <Arduino.h>
 #define maxSensors 5 //Maximum number of sensors
 #define pumpByteLenght 4
 #define sensorByteLenght 4

class CimasWaterLevel {
  public:
  CimasWaterLevel();
  void add(char identifier, int index, int pin, bool nc);
  void setPump(char identifier, int pin);
  void updatePumpState();
  void updateSensor(int index);
  void updateAll();
  void serialPrint();
  void serialPrintData();
  bool readOutput();
  int messageLenght();
  private:  
  char _identifier[maxSensors];
  int _index[maxSensors];
  byte _pin[maxSensors];
  bool _output[maxSensors];
  bool _nc[maxSensors];
  bool _pumpSet;
  char _pumpIdentifier;
  int _pumpPin;
  bool _pumpError;
  bool _pumpState;
  byte _count = 0;
};
#endif
