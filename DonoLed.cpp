/*
  DonoLed.h - Library LED Strips animations.
  Created by Dono7, January 5, 2024.
*/

#include "Arduino.h"
#include "DonoLed.h"


#include <vector>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>
#endif


// Constructor
DonoLed::DonoLed(int pin, int numLeds) {
  _numLeds = numLeds;
  strip = Adafruit_NeoPixel(numLeds, pin, NEO_GRB + NEO_KHZ800);
}


// Core
void DonoLed::setup() {
  strip.begin();
  strip.show();
}

void DonoLed::showStrip() {
   strip.show();
}

void DonoLed::setPixel(int Pixel, byte red, byte green, byte blue) {
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
}

void DonoLed::setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < _numLeds; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

void DonoLed::setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    setPixel(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    setPixel(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}


// Basics
void DonoLed::CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i =((_numLeds-EyeSize)/2); i>=0; i--) {
    setAll(0,0,0);
   
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
   
    setPixel(_numLeds-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(_numLeds-i-j, red, green, blue);
    }
    setPixel(_numLeds-i-EyeSize-1, red/10, green/10, blue/10);
   
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void DonoLed::OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = 0; i<=((_numLeds-EyeSize)/2); i++) {
    setAll(0,0,0);
   
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
   
    setPixel(_numLeds-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(_numLeds-i-j, red, green, blue);
    }
    setPixel(_numLeds-i-EyeSize-1, red/10, green/10, blue/10);
   
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void DonoLed::LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = 0; i < _numLeds-EyeSize-2; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void DonoLed::RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = _numLeds-EyeSize-2; i > 0; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void DonoLed::FadeToBlack(int ledNo, byte fadeValue) {
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
   
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
   
    strip.setPixelColor(ledNo, r,g,b);
}

void DonoLed::ColorWipeOneWay(byte red, byte green, byte blue, int SpeedDelay) {
  for(uint16_t i=0; i<_numLeds; i++) {
      setPixel(i, red, green, blue);
      showStrip();
      delay(SpeedDelay);
  }
}


// Pre-saved animations
void DonoLed::NewKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){
  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
}

void DonoLed::Fire(int Cooling, int Sparking, int SpeedDelay) {
  static std::vector<byte> _heat(_numLeds);
  int cooldown;
 
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < _numLeds; i++) {
    cooldown = random(0, ((Cooling * 10) / _numLeds) + 2);
   
    if(cooldown>_heat[i]) {
      _heat[i]=0;
    } else {
      _heat[i]=_heat[i]-cooldown;
    }
  }
 
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= _numLeds - 1; k >= 2; k--) {
    _heat[k] = (_heat[k - 1] + _heat[k - 2] + _heat[k - 2]) / 3;
  }
   
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    _heat[y] = _heat[y] + random(160,255);
    //_heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < _numLeds; j++) {
    setPixelHeatColor(j, _heat[j] );
  }

  showStrip();
  delay(SpeedDelay);
}

void DonoLed::FireLoop(int Cooling, int Sparking, int SpeedDelay, int LoopsCount) {
  for (int i = 0; i < LoopsCount; i++) {
    Fire(Cooling, Sparking, SpeedDelay);
  }
}

void DonoLed::FadeInOut(byte red, byte green, byte blue, int waitTime, int pauseDelay){
  float r, g, b;
     
  for(int k = 0; k < 256; k=k+2) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
    delay(waitTime);
  }

  delay(pauseDelay);
     
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
    delay(waitTime);
  }
}

void DonoLed::MeteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  setAll(0,0,0);
 
  for(int i = 0; i < _numLeds+_numLeds; i++) {
   
    // fade brightness all LEDs one step
    for(int j=0; j<_numLeds; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        FadeToBlack(j, meteorTrailDecay );        
      }
    }
   
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <_numLeds) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      }
    }
   
    showStrip();
    delay(SpeedDelay);
  }
}

void DonoLed::Rainbow(int wait, int repetition, int brightness) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    strip.rainbow(firstPixelHue, repetition, brightness);
    strip.show();
    delay(wait);
  }
}

void DonoLed::RainbowLoop(int wait, int repetition, int brightness, int LoopsCount) {
  for (int i = 0; i < LoopsCount; i++) {
    Rainbow(wait, repetition, brightness);
  }
}

void DonoLed::Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(_numLeds);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
  setPixel(Pixel,0,0,0);
}

void DonoLed::ColorWipe(byte red, byte green, byte blue, int SpeedDelay) {
  ColorWipeOneWay(red,green,blue, SpeedDelay);
  ColorWipeOneWay(0x00,0x00,0x00, SpeedDelay);
}

void DonoLed::ColorWipeLoop(byte red, byte green, byte blue, int SpeedDelay, int LoopsCount) {
  for (int i = 0; i < LoopsCount; i++) {
    ColorWipe(red,green,blue,SpeedDelay);
  }
}

void DonoLed::FadeOut(int delayTime) {
  bool allBlack = false;
  
  while (!allBlack) {
    allBlack = true; // Assume all LEDs are black until proven otherwise
    
    for (int i = 0; i < _numLeds; i++) {
      uint32_t color = strip.getPixelColor(i);
      uint8_t r = (color >> 16) & 0xFF;
      uint8_t g = (color >> 8) & 0xFF;
      uint8_t b = color & 0xFF;
      
      if (r > 0 || g > 0 || b > 0) {
        allBlack = false; // At least one LED is not black
        r = (r > 1) ? r - 1 : 0;
        g = (g > 1) ? g - 1 : 0;
        b = (b > 1) ? b - 1 : 0;
        
        strip.setPixelColor(i, strip.Color(r, g, b));
      }
    }
    
    strip.show();
    delay(delayTime); // Adjust this delay as needed to control the fade speed
  }
}

void DonoLed::HeartPulse(int pulses, int delayTime, byte red, byte green, byte blue) {
  for (int i = 0; i < pulses; i++) {  
    FadeInOut(red, green, blue, 0, 50);
    FadeInOut(red, green, blue, 0, 50);
    delay(delayTime);
  }
}

void DonoLed::HeartPulseLoop(int pulses, int delayTime, byte red, byte green, byte blue, int LoopsCount) {
  for (int i = 0; i < LoopsCount; i++) {
    HeartPulse(pulses, delayTime, red, green, blue);
  }
}
