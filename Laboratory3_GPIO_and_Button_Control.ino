#include <Arduino.h>

const uint8_t BUTTON_PIN = 23;
const uint8_t LED1_PIN = 18;
const uint8_t LED2_PIN = 19;

void setup() {
  // Enables internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  
  // Set initial outputs matching "released" state
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED2_PIN, LOW);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  
  // Inverted logic with if/else structure
  if (buttonState == LOW) {
    // Button PRESSED
    digitalWrite(LED1_PIN, LOW);   // LED 1 turns OFF
    digitalWrite(LED2_PIN, HIGH);  // LED 2 turns ON
  } else {
    // Button RELEASED
    digitalWrite(LED1_PIN, HIGH);  // LED 1 turns ON
    digitalWrite(LED2_PIN, LOW);   // LED 2 turns OFF
  }
}