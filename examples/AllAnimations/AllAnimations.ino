/*
  All Animations

  This example shows all the animations available in the library.
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
  led.NewKITT(0x66, 0x22, 0x22, 8, 10, 50);
  delay(PAUSE);

  led.Fire(55, 120, 3);
  delay(PAUSE);

  led.FadeInOut(0xff, 0x15, 0x00, 3, 800);
  delay(PAUSE);

  led.MeteorRain(0x66, 0x22, 0x22, 10, 64, true, 1);
  delay(PAUSE);

  led.Rainbow(20, 1, 255);
  delay(PAUSE);

  led.Sparkle(0x66, 0x22, 0x22, 3);
  delay(PAUSE);

  led.ColorWipe(0x66,0x22,0x22, 20);
  delay(PAUSE);

  led.HeartPulse(3);
  delay(PAUSE);
}
