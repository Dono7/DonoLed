/*
  DonoLed.h - Library LED Strips animations.
  Created by Dono7, January 5, 2024.
*/


#ifndef DonoLed_h
#define DonoLed_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>


class DonoLed {
  public:
    DonoLed(int pin, int numLeds);

    // Core
    void setup();
    void showStrip();
    void setPixel(int Pixel, byte red, byte green, byte blue);
    void setAll(byte red, byte green, byte blue);
    void setPixelHeatColor (int Pixel, byte temperature);

    // Basics
    void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
    void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
    void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
    void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
    void FadeToBlack(int ledNo, byte fadeValue);
    void ColorWipeOneWay(byte red, byte green, byte blue, int SpeedDelay);

    // Pre-saved animations
    void NewKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int);
    void Fire(int Cooling, int Sparking, int SpeedDelay);
    void FireLoop(int Cooling, int Sparking, int SpeedDelay, int LoopsCount);
    void FadeInOut(byte red, byte green, byte blue, int waitTime, int);
    void MeteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay);
    void Rainbow(int wait, int repetition, int brightness);
    void RainbowLoop(int wait, int repetition, int brightness, int LoopsCount);
    void Sparkle(byte red, byte green, byte blue, int SpeedDelay);
    void ColorWipeLoop(byte red, byte green, byte blue, int SpeedDelay, int LoopsCount);
    void ColorWipe(byte red, byte green, byte blue, int SpeedDelay);
    void FadeOut(int delayTime);
    void HeartPulse(int pulses);

  private:
    int _pin;
    int _numLeds;
    Adafruit_NeoPixel strip;
}

#endif