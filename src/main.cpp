#include <Arduino.h>

void setup() {
  Serial.begin(115200, true);
}

void loop() {
  Serial.print("tick... ");
  delay(500);
  Serial.println("tack!");
  delay(500);
}