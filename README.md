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

	