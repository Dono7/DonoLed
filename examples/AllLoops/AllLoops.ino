/*
  All Loops

  This example shows all the animation loops available in the library.
  Every loop is run 3 times for the example.
  Wait between each animation to see the next one.

  Some animations have parameters that can be changed to see different effects.

  Some animations may not look very well with a small number of LEDs.
*/

#include <DonoLed.h>

#define PIN 6
#define NUM_LEDS 50
#define PAUSE 1000

DonoLed led(PIN, NUM_LEDS);

void setup() {
  led.setup();
}

void loop() {
  led.FireLoop(55, 120, 3, 3);
  delay(PAUSE);

  led.RainbowLoop(20, 1, 255, 3);
  delay(PAUSE);

  led.ColorWipeLoop(0x66,0x22,0x22, 20, 3);
  delay(PAUSE);

  led.HeartPulseLoop(3, 1000, 0xff, 0x15, 0x00, 3);
  delay(PAUSE);
}
