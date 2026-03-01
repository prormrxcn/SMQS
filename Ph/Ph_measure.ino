// Arduino-specific code 

// ====== USER CONFIG ======
#define PH_ADC_PIN A0
#define ADC_SAMPLES 50      // Averaging for noise reduction
#define VREF_ADC 5.0        // ADC reference voltage (UNO = 5V)

// Calibration constants (REPLACE after calibration)
float CAL_A = 9.89;
float CAL_B = 106.44;

// =========================

void setup() {
  Serial.begin(9600);
  analogReference(DEFAULT); // Uses Vcc as reference
}

void loop() {

  // -------- ADC Averaging --------
  long adcSum = 0;
  for (int i = 0; i < ADC_SAMPLES; i++) {
    adcSum += analogRead(PH_ADC_PIN);
    delay(5);
  }
  float adcAvg = adcSum / (float)ADC_SAMPLES;

  // -------- Convert ADC to Voltage --------
  float voltage = (adcAvg / 1023.0) * VREF_ADC;

  // -------- Convert ADC to pH --------
  // Model from paper: pH = A - B * ADC_normalized
  float adcNorm = adcAvg / 1023.0;
  float pH = CAL_A - (CAL_B * adcNorm);

  // -------- Output --------
  Serial.print("ADC: ");
  Serial.print(adcAvg, 1);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V | pH: ");
  Serial.println(pH, 2);

  delay(1000);
}


// ESP-specific code

#include <esp_adc_cal.h>

// ================= USER CONFIG =================
#define PH_ADC_PIN       34        // ADC1 pin (GPIO 32–39 only)
#define ADC_SAMPLES      64
#define DEFAULT_VREF     1100      // mV (ESP32 typical)
#define ADC_ATTEN        ADC_ATTEN_DB_11  // up to ~3.6V
#define ADC_WIDTH        ADC_WIDTH_BIT_12 // 0–4095

// ---- Calibration constants (REPLACE AFTER BUFFER CAL) ----
float CAL_SLOPE = -3.25;   // pH per volt (example)
float CAL_OFFSET = 14.2;   // intercept
// ==========================================================

esp_adc_cal_characteristics_t adc_chars;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // ADC setup
  adc1_config_width(ADC_WIDTH);
  adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN); // GPIO34

  // ADC calibration
  esp_adc_cal_characterize(
    ADC_UNIT_1,
    ADC_ATTEN,
    ADC_WIDTH,
    DEFAULT_VREF,
    &adc_chars
  );

  Serial.println("ESP32 Soil pH Sensor Initialized");
}

void loop() {

  // -------- ADC Averaging --------
  uint32_t adc_sum = 0;
  for (int i = 0; i < ADC_SAMPLES; i++) {
    adc_sum += analogRead(PH_ADC_PIN);
    delay(3);
  }
  uint32_t adc_raw = adc_sum / ADC_SAMPLES;

  // -------- Convert ADC → millivolts --------
  uint32_t voltage_mv = esp_adc_cal_raw_to_voltage(adc_raw, &adc_chars);
  float voltage = voltage_mv / 1000.0;  // V

  // -------- Convert Voltage → pH --------
  // Model: pH = slope * V + offset
  float pH = (CAL_SLOPE * voltage) + CAL_OFFSET;

  // -------- Output --------
  Serial.print("ADC: ");
  Serial.print(adc_raw);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V | pH: ");
  Serial.println(pH, 2);

  delay(1000);
}
