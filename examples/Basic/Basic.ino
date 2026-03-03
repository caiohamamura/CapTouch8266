#include <Arduino.h>
#include <CapTouch8266.h>

#define TOUCH_PIN D1

CapTouch8266 touch(TOUCH_PIN);

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\nCapTouch8266 - Basic Defaults Example");
  Serial.println("Do NOT touch the pad during calibration...");

  touch.begin();
  touch.calibrate();

  Serial.println("Calibration complete.");
  Serial.print("Baseline: ");
  Serial.println(touch.getBaseline());
}

void loop() {
  touch.update();

  if (touch.isTouched())
    Serial.println("Touch detected!");
  else
    Serial.println("No touch");

  delay(20);
}