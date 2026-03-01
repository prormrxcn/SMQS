#include <TroykaMQ.h> // https://github.com/amperka/TroykaMQ
#define SENSOR_PIN        34

MQ135 mq135(SENSOR_PIN);

void setup() {
   Serial.begin(9600);
   // before calibrating the sensor, warm it up for 60 seconds calibrate the sensor in clean air
   mq135.calibrate();
   // if you know the resistance of the sensor in clean air
   // you can specify it manually, eg: 160 mq135.calibrate(160);   
   Serial.print("Ro = ");
   Serial.println(mq135.getRo());
}

void loop() {
   // display gas values in ppm
   Serial.print(mq135.readCO2());
   Serial.println("ppm");
   delay(1000);
}
