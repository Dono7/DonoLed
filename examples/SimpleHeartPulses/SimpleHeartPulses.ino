/*
  Simple Heart Pulses

  Make all the LEDs pulse like a heart beat, then pause for a moment.
*/

#include <DonoLed.h>

#define PIN 6
#define NUM_LEDS 10

DonoLed led(PIN, NUM_LEDS);

void setup() {
  led.setup();
}

void loop() {
  led.HeartPulse(3);
  delay(3000);
}
