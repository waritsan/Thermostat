#include "Thermostat.h"

Thermostat::Thermostat(int inputPin, int heatPin, int coolPin) {
  this->inputPin = inputPin;
  this->heatPin = heatPin;
  this->coolPin = coolPin;
  pinMode(inputPin, INPUT);
  pinMode(heatPin, OUTPUT);
  pinMode(coolPin, OUTPUT);
}

float Thermostat::readCurrentTemperature() {
  OneWire oneWire(inputPin);
  DallasTemperature dallasTemperature(&oneWire);
  dallasTemperature.requestTemperatures();
  currentTemperature = dallasTemperature.getTempCByIndex(0);
  switch (targetHeatingCoolingState) {
    case HEAT: (currentTemperature < targetTemperature) ? heat() : off();
                break;
    case COOL: (currentTemperature < targetTemperature) ? off() : cool();
                break;
    case AUTO: (currentTemperature < targetTemperature) ? heat() : cool();
                break;
    default: off();
  }
  return currentTemperature;
}

int Thermostat::getCurrentHeatingCoolingState() {
  return currentHeatingCoolingState;
}

void Thermostat::setTargetHeatingCoolingState(int value) {
  targetHeatingCoolingState = value;
}

void Thermostat::setTargetTemperature(float value) {
  targetTemperature = value;
}

// Private

void Thermostat::off() {
  digitalWrite(coolPin, LOW);
  digitalWrite(heatPin, LOW);
  currentHeatingCoolingState = OFF;
}

void Thermostat::cool() {
  digitalWrite(coolPin, HIGH);
  digitalWrite(heatPin, LOW);
  currentHeatingCoolingState = COOL;
}

void Thermostat::heat() {
  digitalWrite(coolPin, LOW);
  digitalWrite(heatPin, HIGH);
  currentHeatingCoolingState = OFF;
}
