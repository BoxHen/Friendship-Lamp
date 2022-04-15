#define BLYNK_TEMPLATE_ID "TMPLGGD1XheI"
#define BLYNK_DEVICE_NAME "RGB Button"
#define BLYNK_AUTH_TOKEN "WUsujc4i59v0DjZlzG1yycONsxgcpUTn"

#define analogPin A0 //ESP8266 Analog Pin ADC0 = A0

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

//char ssid[] = "NETGEAR35";       //WiFi Name
//char pass[] = "livelyviolet813"; //WiFi Password
char ssid[] = "Single Digits - Residents"; //WiFi Name
char pass[] = ""; //WiFi Password

#include <Adafruit_NeoPixel.h>
//--------------------------------------------------------------------------
bool RGB_Flag = false; // flag for rgb lamp control - only executes rgb loop on true flag
int adcValue  = 0;     // Variable to store Output of ADC 
int colState  = 0;     // Variable to keep track of color state based on physical touch sensor
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
  Serial.begin(115200); // Initialize serial communication at 115200
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
    Serial.println("in rgb");
    RGB_Flag = false;
  }

  adcValue = analogRead(analogPin); // Read the Analog Input value
  Serial.print("ADC Value = ");
  Serial.println(adcValue);
  if(adcValue>35){
    colState += 1;
    //---------case statement to cycle through colors---------
    if(colState == 1){ // red
      pixels.fill(pixels.Color(255, 0, 0));
      pixels.show();
      delay(200);
    }
    if(colState == 2){ // pink
      pixels.fill(pixels.Color(255, 51, 255));
      pixels.show();
      delay(200);
    }
    if(colState == 3){ // blue
      pixels.fill(pixels.Color(0, 0, 255));
      pixels.show();
      delay(200);
    }
    if(colState == 4){ // Green
      pixels.fill(pixels.Color(0, 255, 0));
      pixels.show();
      delay(200);
    }
    if(colState == 5){ // Yellow
      pixels.fill(pixels.Color(255, 255, 0));
      pixels.show();
      delay(200);
    }
    if(colState == 6){ // orange
      pixels.fill(pixels.Color(255, 140, 0));
      pixels.show();
      delay(200);
    }
    if(colState == 7){ // off
      pixels.fill(pixels.Color(0, 0, 0));
      pixels.show();
      colState = 0; //reset color state val to restart cycle
      delay(200);
    }
    delay(150); // wait between colState counter increment
  }
  delay(100);
  
  Blynk.run();
  
}
