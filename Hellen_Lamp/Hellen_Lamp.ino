#define BLYNK_TEMPLATE_ID ""
#define BLYNK_DEVICE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = ""; //WiFi Name
char pass[] = ""; //WiFi Password

#include <Adafruit_NeoPixel.h>
//--------------------------------------------------------------------------
bool RGB_Flag = false; // flag for rgb lamp control - only executes rgb loop on true flag
int red_val   = 0;     // R
int green_val = 0;     // G
int blue_val  = 0;     // B
//--------------------------------------------------------------------------
const int neo = D2; // ESP8266 pin connected to Neopixel's data pin
const int numLEDs = 24; // replace with the number of your LEDs
Adafruit_NeoPixel pixels(numLEDs, neo, NEO_GRB + NEO_KHZ800);

//==========================================================================
BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);  
  Blynk.syncVirtual(V1);  
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);     
  Blynk.syncVirtual(V4);  
  Blynk.syncVirtual(V5);  
  Blynk.syncVirtual(V6);  
  Blynk.syncVirtual(V7);  
  Blynk.syncVirtual(V8);  
  Blynk.syncVirtual(V9);  
}
//--------------------------------------------------------------------------
BLYNK_WRITE(V0)//Red - button press
{
  if(param.asInt()==1){
    pixels.fill(pixels.Color(255, 0, 0));
    pixels.show();
    Serial.println("in red");
  }
}

BLYNK_WRITE(V1)//Pink - button press
{
  if(param.asInt()==1){
    pixels.fill(pixels.Color(255, 51, 255));
    pixels.show();
  }
}

BLYNK_WRITE(V2)//Blue - button press
{
  if(param.asInt()==1){
    pixels.fill(pixels.Color(0, 0, 255));
    pixels.show();
  }
}


BLYNK_WRITE(V3)//Green - button press
{
  if(param.asInt()==1){
    pixels.fill(pixels.Color(0, 255, 0));
    pixels.show();
  }
}

BLYNK_WRITE(V4)//Yellow - button press
{
  if(param.asInt()==1){
    pixels.fill(pixels.Color(255, 255, 0));
    pixels.show();
  }
}

BLYNK_WRITE(V5)//Orange - button press
{
  if(param.asInt()==1){
    pixels.fill(pixels.Color(255, 140, 0));
    pixels.show();
  }
}
/*--------------------------------------------------------------------------
RGB custom control through blynk "zeRGBa":
  V6 is used for red value control
  V7 is used for green value control
  V8 is used for blue value control
  we used "zeRGBa" blynk app to control custom rgb setting for our lamp. the "zeRGBa" setting is set to SPLIT, 
  where each of the rgb values are sent separately. Upon using "zeRGBa" it will set and send Red, green, blue 
  values in that order. We will take advantage of blue being sent last and update the lamp color there. I did 
  this instead of using the MERGE version of "zeRGBa", where the message consists of a array of values because
  the neopixel does not update physically. There is documentation of the timing of the neopixel being strict 
  and my theory is that the MERGE option for "zeRGBa" is interfering with the timing of the neopixel.
--------------------------------------------------------------------------*/
BLYNK_WRITE(V6){ red_val   = param.asInt(); } //rgb control - Red
BLYNK_WRITE(V7){ green_val = param.asInt(); } //rgb control - Green
BLYNK_WRITE(V8){ blue_val  = param.asInt();   //rgb control - Blue
                 AdjustBrightness(red_val, green_val, blue_val);}
//--------------------------------------------------------------------------
BLYNK_WRITE(V9)//On/Off button
{
  if(param.asInt()==1){
    pixels.clear();
    pixels.show();
  }
}
//==========================================================================

void setup()
{ 
  Serial.begin(115200); // Initialize serial communication at 115200
  pixels.begin();
  pixels.setBrightness(50);
  pixels.show(); // Initialize all pixels to 'off'
  
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}
