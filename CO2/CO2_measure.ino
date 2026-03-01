/*
  MQ-135 CO2 Measurement Code (ppm)

  Preconditions (MANDATORY):
  1. RL replaced with 22kΩ on the sensor board
  2. Sensor preheated for 24 hours
  3. RLOAD, RZERO, and ATMOCO2 updated in MQ135.h
*/

#include "MQ135.h"

// -------- USER CONFIG --------
#define MQ135_PIN A0        // Analog pin connected to MQ-135
#define SAMPLE_COUNT 20     // Number of samples for averaging
#define SAMPLE_DELAY 50     // ms between samples
// -----------------------------

MQ135 gasSensor(MQ135_PIN);

void setup() {
  Serial.begin(9600);
  Serial.println("MQ-135 CO2 Measurement Started");
}

void loop() {

  // -------- ADC Averaging --------
  float ppmSum = 0.0;

  for (int i = 0; i < SAMPLE_COUNT; i++) {
    float ppm = gasSensor.getPPM();
    ppmSum += ppm;
    delay(SAMPLE_DELAY);
  }

  float avgPPM = ppmSum / SAMPLE_COUNT;

  // -------- Output --------
  Serial.print("CO2 Concentration: ");
  Serial.print(avgPPM, 2);
  Serial.println(" ppm");

  delay(2000);
}
