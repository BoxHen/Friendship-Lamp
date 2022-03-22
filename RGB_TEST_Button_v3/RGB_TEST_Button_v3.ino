
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLGGD1XheI"
#define BLYNK_DEVICE_NAME "RGB Button"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define USE_NODE_MCU_BOARD

#include "BlynkEdgent.h"

#include <Adafruit_NeoPixel.h>

const int neo = D2; // ESP8266 pin connected to Neopixel's data pin
const int numLEDs = 12; // replace with the number of your LEDs
Adafruit_NeoPixel pixels(numLEDs, neo, NEO_GRB + NEO_KHZ800);

//--------------------------------------------------------------------------
BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);
  Blynk.syncVirtual(V1); 
  Blynk.syncVirtual(V2); 
  Blynk.syncVirtual(V3); 
}

BLYNK_WRITE(V0)//Red
{
  if(param.asInt()==1){
    for(int i=0;i<numLEDs;i++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(255,0,0)); // Moderately bright green color.
      //pixels.show(); // This sends the updated pixel color to the hardware.
    }
    //pixels.fill(pixels.Color(255, 0, 0));
    pixels.show();
  }
  else{
    //pixels.clear();
    for(int i=0;i<numLEDs;i++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
      //pixels.show(); // This sends the updated pixel color to the hardware.
    }
    pixels.show();
  }
}

BLYNK_WRITE(V1)//Green
{
  if(param.asInt()==1){
    pixels.fill(pixels.Color(0, 255, 0));
    pixels.show();
  }
  else{
    pixels.clear();
    pixels.show();
  }
}

BLYNK_WRITE(V2)//Blue
{
  if(param.asInt()==1){
    pixels.fill(pixels.Color(0, 0, 255));
    pixels.show();
  }
  else{
    pixels.clear();
    pixels.show();
  }
}

BLYNK_WRITE(V3)//Orange
{
  if(param.asInt()==1){
    pixels.fill(pixels.Color(255, 165, 0));
    pixels.show();
  }
  else{
    pixels.clear();
    pixels.show();
  }
}

//--------------------------------------------------------------------------

void setup()
{ 
  pixels.begin();
  pixels.setBrightness(255);
  pixels.show(); // Initialize all pixels to 'off'
  
  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
  
}
