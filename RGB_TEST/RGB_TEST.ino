
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLGGD1XheI"
#define BLYNK_DEVICE_NAME "RGB Button"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
#define USE_NODE_MCU_BOARD

#include "BlynkEdgent.h"

#include <Adafruit_NeoPixel.h>

const int neo = D2; // ESP8266 pin connected to Neopixel's data pin
const int numLEDs = 12; // replace with the number of your LEDs

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLEDs, neo, NEO_GRB + NEO_KHZ800);

// initialize constants
int red_val = 255;
int green_val = 255;
int blue_val = 255;
//--------------------------------------------------------------------------

BLYNK_WRITE(V4)//Red
{
  red_val = param.asInt();
}

BLYNK_WRITE(V5)//Green
{
  green_val = param.asInt();
}

BLYNK_WRITE(V6)//Blue
{
  blue_val = param.asInt();
}

//--------------------------------------------------------------------------

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V4);  
  Blynk.syncVirtual(V5);  
  Blynk.syncVirtual(V6);  
}

void setup()
{
  int red_val = 255;
  int green_val = 255;
  int blue_val = 255;

  strip.begin(); 
  strip.show(); 
  strip.setBrightness(100);
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
}

void loop() {
  
  //uint32_t new_color = strip.Color(red_val, green_val, blue_val);
  //strip.fill(new_color);
  //strip.setPixelColor(0, red_val, green_val, blue_val);

  for(int i=0;i<numLEDs;i++){
    // strip.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(red_val,green_val,blue_val)); // Moderately bright green color.
    delay(500);
  }  
  strip.show();
  
  //Serial.print(red_val);
  //Serial.print(green_val);
  //Serial.print(blue_val);

  BlynkEdgent.run();
}
