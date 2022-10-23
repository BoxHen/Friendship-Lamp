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
double brightness_percentage = 100;
int red_val   = 0;     // R
int green_val = 0;     // G
int blue_val  = 0;     // B
//--------------------------------------------------------------------------
const int neo = D2;     // ESP8266 pin connected to Neopixel's data pin
const int numLEDs = 24; // replace with the number of your LEDs
Adafruit_NeoPixel pixels(numLEDs, neo, NEO_GRB + NEO_KHZ800); //Initialize neopixel ring

/*--------------------------------------------------------------------------
sets up the virtual pins we will use with the blynk app
--------------------------------------------------------------------------*/
BLYNK_CONNECTED(){ Blynk.syncVirtual(V0); Blynk.syncVirtual(V1); Blynk.syncVirtual(V2); Blynk.syncVirtual(V3); Blynk.syncVirtual(V4); Blynk.syncVirtual(V5); Blynk.syncVirtual(V6); Blynk.syncVirtual(V7); Blynk.syncVirtual(V8); Blynk.syncVirtual(V9); }

/*--------------------------------------------------------------------------
Individual color buttons:
  These are the buttons on the blynk app that will change the color upon press
  Executes when the value of blynk virtual pins (V0-V9) changes (blynk server sends the current Virtual Pin 
  value as a parameter). We will update the rgb var so this way, the last press is stored. This is cool
  since when we update the brightness slider, the lamp will update colors immediately
--------------------------------------------------------------------------*/
BLYNK_WRITE(V0){                                 //Red    - button press 
  red_val = 255; green_val = 0; blue_val = 0; 
  AdjustBrightness(red_val, green_val, blue_val); 
}
BLYNK_WRITE(V1){                                 //Pink   - button press
  red_val = 255; green_val = 51; blue_val = 255; 
  AdjustBrightness(red_val, green_val, blue_val); 
}
BLYNK_WRITE(V2){                                 //Blue   - button press
  red_val = 0; green_val = 0; blue_val = 255; 
  AdjustBrightness(red_val, green_val, blue_val); 
}
BLYNK_WRITE(V3){                                 //Green  - button press
  red_val = 0; green_val = 255; blue_val = 0; 
  AdjustBrightness(red_val, green_val, blue_val); 
}
BLYNK_WRITE(V4){                                 //Yellow - button press
  red_val = 255; green_val = 255; blue_val = 0; 
  AdjustBrightness(red_val, green_val, blue_val); 
}
BLYNK_WRITE(V5){                                 //Orange - button press
  red_val = 255; green_val = 140; blue_val = 0; 
  AdjustBrightness(red_val, green_val, blue_val); 
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

/*--------------------------------------------------------------------------
Brightness control:
  This will adjust the brightness of the lamp upon the slider in the blynk app being changed. The slider has a 
  value from 0 to 100. This a percentage(stored as a deciaml), that we will multiply with the rgb value to 
  determine brightness.
  We will also update the lamp color at the end so that a change to the slider value immediately changes the 
  lamp color 
--------------------------------------------------------------------------*/
BLYNK_WRITE(V9){ 
  brightness_percentage = param.asDouble()/100.0; 
  AdjustBrightness(red_val, green_val, blue_val);
}

/*--------------------------------------------------------------------------
On/Off Button:
  clears the neopixel lights which will turn the lamp off
--------------------------------------------------------------------------*/
BLYNK_WRITE(V10){ //On/Off button
  red_val = 0; green_val = 0; blue_val = 0;
  pixels.clear();
  pixels.show() ; 
} 
                 
/*--------------------------------------------------------------------------
AdjustBrightness:
  Parameters:
            redValue   : represents the red value in rgb
            greenValue : represents the green value in rgb
            blueValue  : represents the blue value in rgb
  return:
            N/A (void return)
  Comments:
            Will fill the lamp with the known rgb value, but apply the set brightness level(percentage). Multiplies 
            the desired percentage of brightness by the rgb value
--------------------------------------------------------------------------*/
void AdjustBrightness(int redValue, int greenValue, int blueValue){
  pixels.fill(pixels.Color( (redValue*brightness_percentage), (greenValue*brightness_percentage), (blueValue*brightness_percentage) ));
  pixels.show();
}

//==========================================================================
void setup()
{ 
  Serial.begin(115200); // Initialize serial communication at 115200
  pixels.begin();
  pixels.setBrightness(100);
  pixels.show(); // Initialize all pixels to 'off'
  
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run(); 
}
