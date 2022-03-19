
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

BLYNK_WRITE(V4) // Widget WRITEs to Virtual Pin V1
{   
  red_val = param[0].asInt();
  green_val = param[1].asInt();
  blue_val = param[2].asInt();
}

//--------------------------------------------------------------------------

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V4);  
}

void setup()
{
  int red_val = 255;
  int green_val = 255;
  int blue_val = 255;
  
  Serial.begin(115200);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(50);
  
  BlynkEdgent.begin();
}

void loop() {
  Serial.println(red_val);
  Serial.println(green_val);
  Serial.println(blue_val);
  
  for(int i=0;i<numLEDs;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(red_val,green_val,blue_val)); // Moderately bright green color.
    strip.show(); // This sends the updated pixel color to the hardware.
    Serial.println("in2");
  }
  Serial.println("out2");
  
  BlynkEdgent.run();
  
}
