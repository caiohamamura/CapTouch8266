#include <Arduino.h>
#include <CapTouch8266.h>

#define TOUCH_PIN D1

// Larger buffer for more stability
CapTouch8266 touch(TOUCH_PIN, 30);

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\nCapTouch8266 - Custom Tuned Example");
  Serial.println("Do NOT touch during calibration...");

  touch.begin();

  // Customize behavior
  touch.setThresholdOffset(12);   // Less sensitive
  touch.setVotePercentage(0.3);   // 30% of samples required
  touch.setTimeout(3000);         // Longer timeout

  touch.calibrate(80);            // More calibration samples

  Serial.println("Calibration complete.");
  Serial.print("Baseline: ");
  Serial.println(touch.getBaseline());
}


void loop() {
  touch.update();

  Serial.print("Raw: ");
  Serial.print(touch.getRaw());
  Serial.print(" | Baseline: ");
  Serial.print(touch.getBaseline());
  Serial.print(" | State: ");

  if (touch.isTouched())
    Serial.println("TOUCH");
  else
    Serial.println("NO");

  delay(20);
}