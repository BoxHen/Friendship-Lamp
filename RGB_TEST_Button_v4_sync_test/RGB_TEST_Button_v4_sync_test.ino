/*************************************************************

  Control another device using Bridge widget!

  Bridge is initialized with the token of any (Blynk-enabled) device.
  After that, use the familiar functions to control it:
    bridge.digitalWrite(8, HIGH)
    bridge.digitalWrite("A0", LOW) // <- target needs to support "Named pins"
    bridge.analogWrite(3, 123)
    bridge.virtualWrite(V1, "hello")
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLGGD1XheI"
#define BLYNK_DEVICE_NAME "RGB Button"
#define BLYNK_AUTH_TOKEN "6vAVwP74Xh8h0CDlsmmdJXiZHRSu-ZWt"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "NETGEAR35";
char pass[] = "livelyviolet813";

#include <Adafruit_NeoPixel.h>
//--------------------------------------------------------------------------
bool RGB_Flag = false;
int red_val   = 0;
int green_val = 0;
int blue_val  = 0;
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
//--------------------------------------------------------------------------
BLYNK_WRITE(V6)//rgb control - R
{
  red_val = param.asInt();
  RGB_Flag = true;
}

BLYNK_WRITE(V7)//rgb control - G
{
  green_val = param.asInt();
  RGB_Flag = true;
}

BLYNK_WRITE(V8)//rgb control - B
{
  blue_val = param.asInt();
  RGB_Flag = true;
}
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
  pixels.begin();
  pixels.setBrightness(50);
  pixels.show(); // Initialize all pixels to 'off'
  
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  if(RGB_Flag){
    for(int i=0;i<numLEDs;i++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(red_val,green_val,blue_val)); // Moderately bright green color.
      delay(10);
    }  
    pixels.show();
    RGB_Flag = false;
  }
  
  Blynk.run();
  
}

//BLYNK_CONNECTED() {
//  bridge1.setAuthToken("Sqa9ms-0zZV1HKWXG0mvrjq6bBpYRLHA"); // Place the AuthToken of the second hardware here
//}
