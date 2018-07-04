#include <Arduino.h>
#include <DallasTemperature.h>

#ifndef THERMOSTAT_H
#define THERMOSTAT_H

// States
#define OFF 0
#define HEAT 1
#define COOL 2
#define AUTO 3

class Thermostat {
private:
  int inputPin;
  int heatPin;
  int coolPin;
  int targetHeatingCoolingState;
  int currentHeatingCoolingState;
  float targetTemperature;
  float currentTemperature;
  void off();
  void cool();
  void heat();

public:
  Thermostat(int, int, int);
  float readCurrentTemperature();
  int getCurrentHeatingCoolingState();
  void setTargetHeatingCoolingState(int value);
  void setTargetTemperature(float value);
};

#endif
