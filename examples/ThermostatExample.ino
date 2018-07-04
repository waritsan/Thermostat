/*
	ThermostatExample.ino

	This example demonstates how to use thermostat to read a temperature and operate various modes.

	The circuit:
	* Inputs
        D1 - Dallas temperature sensor (DS18B20)
	* Outputs
        D2 - output for heating
        D3 - output for cooling

	Created Jul 2, 2018
	By Warit Santaputra
	Modified Jul 3, 2018
	By Warit Santaputra

*/

#include <Arduino.h>
#include "Thermostat.h"

// User define
const int INPUT_PIN = D1;
const int HEAT_PIN = D2;
const int COOL_PIN = D3;
const int TARGET_MODE = AUTO;
const float TARGET_TEMPERATURE = 25; // Celsius

long lastMsg = 0;
Thermostat thermostat(INPUT_PIN, HEAT_PIN, COOL_PIN);

void setup() {
	Serial.begin(9600);
	thermostat.setTargetHeatingCoolingState(AUTO);
	thermostat.setTargetTemperature(25.0);
}

void loop() {
    long now = millis();
	if (now - lastMsg > 5000) {
		lastMsg = now;
		float currentTemperature = thermostat.readCurrentTemperature();
		Serial.print("Current temperature: ");
		Serial.print(currentTemperature);
		Serial.print(", current state: ");
		Serial.println(thermostat.getCurrentHeatingCoolingState());
	}
}