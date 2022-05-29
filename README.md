# Friendship-Lamp
Two lamps that will communicate over internet. 
Communicate with friends over long distances.

In this project we will use the esp8266 and Node MCU. The esp8266 is a microcontroller; a Wi-Fi module that allows control to inputs/outputs similar to an Arduino. NodeMCU is a Firmware on ESP8266. It has Lua based firmware which is used to develop IoT based applications. 
At the time of this project each board is ~$7 dollars. It is a development board targeted for IoT based Applications with open-source Lua based firmware. Some specs include: 
    Microcontroller: Tensilica 32-bit RISC CPU Xtensa LX106
    Operating Voltage: 3.3V
    Input Voltage: 7-12V
    Digital I/O Pins (DIO): 16
    Analog Input Pins (ADC): 1
    UARTs: 1
    SPIs: 1
    I2Cs: 1
    Flash Memory: 4 MB
    SRAM: 64 KB
    Clock Speed: 80 MHz
    USB-TTL based on CP2102 is included onboard, Enabling Plug n Play
    PCB Antenna
    Small Sized module to fit smartly inside your IoT projects

	Note: refer to "NodeMCU_ESP8266_Pinout" for pinout info

The ESP8266 board can be programmed with the Arduino IDE 

Steps:
Programming with Arduino IDE
	1. Install Arduino IDE  from https://www.arduino.cc/en/software Or grab altest version.
	2. Go to File -> Preferences to open the below dialog box. In the “Additional Board managers URL” paste "http://arduino.esp8266.com/stable/package_esp8266com_index.json". Then press OK.
	3. go to Tool -> Boards -> Board Managers. Search for ESP8266 by esp8266 community and install
	4. go to Tools -> Boards -> ESP8266 Boards -> NodeMCU 1.0 (ESP-12E Module)
Using Blynk app to control esp8266
	1. Install Blynk App in the ios/android store
	2. But I find it easier to setup on Blynk's webpage so create an acount at https://blynk.io/ if you dso not have one and sign in
	3. make a new template (side tab -> template)
	4. under template, go to datastream and in the top right, click "+ New Datastream". Select virtual pin, since we will be using these virtual buttons on the app to control the lamp.
		a. for now, name the button based on what you want the button to do. In my case I have set buttons controlling led color. For example you can have "Red_Button" and assign it a unique pin. Set its range and defualt value. 
	5. Youc an connect blynk app to your esp8266 by powering on the esp8266. In the blynk app, go to "Add New Device". Follow instructions to pair.
	6. Once paired, select the template we just created and setup the onscreen button layout to your design. 
Setup Arduino IDE to operate blynk app
	The following snippet is an example layout/template of what is needed
		#define BLYNK_TEMPLATE_ID "TMPLGGD1XheI"
		#define BLYNK_DEVICE_NAME "RGB Button"
		#define BLYNK_AUTH_TOKEN "Sqa9ms-0zZV1HKWXG0mvrjq6bBpYRLHA"

		#define analogPin A0 //ESP8266 Analog Pin ADC0 = A0

		#define BLYNK_PRINT Serial

		#include <ESP8266WiFi.h>
		#include <BlynkSimpleEsp8266.h>

		char auth[] = BLYNK_AUTH_TOKEN;

		char ssid[] = ""; //WiFi Name
		char pass[] = ""; //WiFi Password

		#include <Adafruit_NeoPixel.h>
		
	The section:
		#define BLYNK_TEMPLATE_ID "TMPLGGD1XheI"
		#define BLYNK_DEVICE_NAME "RGB Button"
		#define BLYNK_AUTH_TOKEN "Sqa9ms-0zZV1HKWXG0mvrjq6bBpYRLHA"
	should be grabbed from blynk, under info tab in firmware configurations, when you created the template, 
	there will be a template ID and a device ID. Copy that info. 
	You can find the authentication token when you sync your esp8266 board with the blynk app. When this
	is done, the new esp8266 board will appear as one of the devices listed. Click into the device and go
	to the Device info tab. Under firmware configurations will be the authenticaton token. You can also grab
	the template and device id from here as well.
	
	The other important part here is:
		char ssid[] = ""; //WiFi Name
		char pass[] = ""; //WiFi Password
	fill out in the quotes the wifi name for ssid, and the wifi password for pass. This how blynk will connect to your wifi.
	
Notes for lamp code:
Implemented a touch sensor by using pieces of aluminum tape on the top cover plate of lamp. The aluminum tape is then wired to the analog pin A0. When you touch the tape, the value changes which is what we take advantage of to change the color of lamp on press
	adcValue = analogRead(analogPin); // Read the Analog Input value
	//Serial.print("ADC Value = ");
	//Serial.println(adcValue);
	if(adcValue>60){
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
	
blynk app works using this code like this:
	BLYNK_WRITE(V5)//Orange - button press
	{
	  if(param.asInt()==1){
		pixels.fill(pixels.Color(255, 140, 0));
		pixels.show();
	  }
	}
	
	Here we will have to set the virtual button (V5 in this case) to a button in the blynk app. When that virtual button is pressed on the app, this piece of code executes. I use this to set a specific color

This portion control the rgb selector on the app
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
	
	The virtual buttons V6, V7, V8 are mapped accordingly and the values are stored vars.

Notes:
Use mac_address to grab mac address of esp8266 board. This is useful if you need access from complex wide wifi or school wifi. You may need to add the board as a trusted device.