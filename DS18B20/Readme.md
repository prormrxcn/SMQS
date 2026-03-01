# DS18B20 Calibration & Verification Procedure

This document outlines the professional procedure for verifying a DS18B20 digital temperature sensor against known reference points and applying a single-point offset correction.

---

## 1. Ice Water Test (0 °C Reference)
The most reliable physical constant available for home calibration is the melting point of water.

1.  **Prepare the Bath:** Fill a glass with **crushed ice**.
2.  **Create Slush:** Add just enough distilled water to create a thick slush. The ice should be packed to the bottom, not floating.
3.  **Insert Sensor:** Place the DS18B20 into the center of the slush. 
    * *Note: Do not let the sensor touch the glass sides or bottom.*
4.  **Wait:** Allow ~2 minutes for the reading to stabilize.

### 📌 Expected Reading: 0.0 °C ± 0.5 °C

| If you read... | Your Offset is... |
| :--- | :--- |
| **+0.7 °C** | `-0.7` |
| **-0.4 °C** | `+0.4` |

---

## 2. Room Temperature Cross-check (~25 °C)
Verifies that the sensor behaves linearly under ambient conditions.

* **Stabilize:** Let the sensor sit in open air (away from heat sources or drafts) for 10 minutes.
* **Reference:** Measure room temperature using a secondary reliable thermometer or a calibrated weather station.
* **Tolerance:** The difference should remain within **±0.5 °C**.

---

## 3. Optional Hot Water Test (~50–60 °C)
Used only to detect rare manufacturing defects or gross non-linearity.

* **Heat Water:** Bring water to roughly 50 °C (well below boiling).
* **Compare:** Insert both the DS18B20 and a reference thermometer simultaneously.
* **Analysis:** If the error at 50 °C is significantly different from the error at 0 °C, the sensor may be a low-quality clone.

---

## 4. Apply Offset Correction
Once the offset is determined from Step 1, apply it directly to your code. No complex curve fitting or slope calculations are required for standard environmental monitoring.

```cpp
// Calibration Logic
#define TEMP_OFFSET -0.7  // Example: Adjust based on your Ice Water Test

void loop() {
  float rawTemp = sensors.getTempCByIndex(0);
  float calibratedTemp = rawTemp + TEMP_OFFSET;

  Serial.print("Calibrated Temp: ");
  Serial.println(calibratedTemp);
}
