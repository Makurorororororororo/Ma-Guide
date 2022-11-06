/*
  ===========================================
       Copyright (c) 2018 Stefan Kremser
              github.com/spacehuhn
  ===========================================
*/
// O = wifi 
// - = programming mode
// ===== Settings ===== //
const uint8_t channels[] = {1, 6, 11}; // used Wi-Fi channels (available: 1-14)
const bool wpa2 = false; // WPA2 networks
const bool appendSpaces = true; // makes all SSIDs 32 characters long to improve performance

/*
  SSIDs:
  - don't forget the \n at the end of each SSID!
  - max. 32 characters per SSID
  - don't add duplicates! You have to change one character at least
*/
const char ssids[] PROGMEM = {
  "Ling Zhi Gei #0 \n" 
  "Ling Zhi Gei #1 \n"  
  "Ling Zhi Gei #2 \n"  
  "Ling Zhi Gei #3 \n"  
  "Ling Zhi Gei #4 \n"  
  "Ling Zhi Gei #5 \n"  
  "Ling Zhi Gei #6 \n"  
  "Ling Zhi Gei #7 \n"  
  "Ling Zhi Gei #8 \n"  
  "Ling Zhi Gei #9 \n"  
  "Ling Zhi Gei #10 \n" 
  "Ling Zhi Gei #11 \n" 
  "Ling Zhi Gei #12 \n" 
  "Ling Zhi Gei #13 \n" 
  "Ling Zhi Gei #14 \n" 
  "Ling Zhi Gei #15 \n" 
  "Ling Zhi Gei #16 \n" 
  "Ling Zhi Gei #17 \n"
  "Ling Zhi Gei #18 \n"
  "Ling Zhi Gei #19 \n"
  "Ling Zhi Gei #20 \n"
  "Ling Zhi Gei #21 \n"
  "Ling Zhi Gei #22 \n"
  "Ling Zhi Gei #23 \n"
  "Ling Zhi Gei #24 \n"
  "Ling Zhi Gei #25 \n"
  "Ling Zhi Gei #26 \n"
  "Ling Zhi Gei #27 \n"
  "Ling Zhi Gei #28 \n"
  "Ling Zhi Gei #29 \n"
  "Ling Zhi Gei #30 \n"
  "Ling Zhi Gei #31 \n"
  "Ling Zhi Gei #32 \n"
  "Ling Zhi Gei #33 \n"
  "Ling Zhi Gei #34 \n"
  "Ling Zhi Gei #35 \n"
  "Ling Zhi Gei #36 \n"
  "Ling Zhi Gei #37 \n"
  "Ling Zhi Gei #38 \n"
  "Ling Zhi Gei #39 \n"
  "Ling Zhi Gei #40 \n"
  "Ling Zhi Gei #41 \n"
  "Ling Zhi Gei #42 \n"
  "Ling Zhi Gei #43 \n"
  "Ling Zhi Gei #44 \n"
  "Ling Zhi Gei #45 \n"
  "Ling Zhi Gei #46 \n"
  "Ling Zhi Gei #47 \n"
  "Ling Zhi Gei #48 \n"
  "Ling Zhi Gei #49 \n"
  "Ling Zhi Gei #50 \n"
  "Ling Zhi Gei #51 \n"
  "Ling Zhi Gei #52 \n"
  "Ling Zhi Gei #53 \n"
  "Ling Zhi Gei #54 \n"
  "Ling Zhi Gei #55 \n"
  "Ling Zhi Gei #56 \n"
  "Ling Zhi Gei #57 \n"
  "Ling Zhi Gei #58 \n"
  "Ling Zhi Gei #59 \n"
  "Ling Zhi Gei #60 \n"
  "Ling Zhi Gei #61 \n"
  "Ling Zhi Gei #62 \n"
  "Ling Zhi Gei #63 \n"
  "Ling Zhi Gei #64 \n"
  "Ling Zhi Gei #65 \n"
  "Ling Zhi Gei #66 \n"
  "Ling Zhi Gei #67 \n"
  "Ling Zhi Gei #68 \n"
  "Ling Zhi Gei #69 \n"
  "Ling Zhi Gei #70 \n"
  "Ling Zhi Gei #71 \n"
  "Ling Zhi Gei #72 \n"
  "Ling Zhi Gei #73 \n"
  "Ling Zhi Gei #74 \n"
  "Ling Zhi Gei #75 \n"
  "Ling Zhi Gei #76 \n"
  "Ling Zhi Gei #77 \n"
};
// ==================== //

// ===== Includes ===== //
#include <ESP8266WiFi.h>

extern "C" {
#include "user_interface.h"
  typedef void (*freedom_outside_cb_t)(uint8 status);
  int wifi_register_send_pkt_freedom_cb(freedom_outside_cb_t cb);
  void wifi_unregister_send_pkt_freedom_cb(void);
  int wifi_send_pkt_freedom(uint8 *buf, int len, bool sys_seq);
}
// ==================== //

// run-time variables
char emptySSID[32];
uint8_t channelIndex = 0;
uint8_t macAddr[6];
uint8_t wifi_channel = 1;
uint32_t currentTime = 0;
uint32_t packetSize = 0;
uint32_t packetCounter = 0;
uint32_t attackTime = 0;
uint32_t packetRateTime = 0;

// beacon frame definition
uint8_t beaconPacket[109] = {
  /*  0 - 3  */ 0x80, 0x00, 0x00, 0x00,             // Type/Subtype: managment beacon frame
  /*  4 - 9  */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Destination: broadcast
  /* 10 - 15 */ 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, // Source
  /* 16 - 21 */ 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, // Source

  // Fixed parameters
  /* 22 - 23 */ 0x00, 0x00,                         // Fragment & sequence number (will be done by the SDK)
  /* 24 - 31 */ 0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00, // Timestamp
  /* 32 - 33 */ 0xe8, 0x03,                         // Interval: 0x64, 0x00 => every 100ms - 0xe8, 0x03 => every 1s
  /* 34 - 35 */ 0x31, 0x00,                         // capabilities Tnformation

  // Tagged parameters

  // SSID parameters
  /* 36 - 37 */ 0x00, 0x20,                         // Tag: Set SSID length, Tag length: 32
  /* 38 - 69 */ 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20,                           // SSID

  // Supported Rates
  /* 70 - 71 */ 0x01, 0x08,                         // Tag: Supported Rates, Tag length: 8
  /* 72 */ 0x82,                    // 1(B)
  /* 73 */ 0x84,                    // 2(B)
  /* 74 */ 0x8b,                    // 5.5(B)
  /* 75 */ 0x96,                    // 11(B)
  /* 76 */ 0x24,                    // 18
  /* 77 */ 0x30,                    // 24
  /* 78 */ 0x48,                    // 36
  /* 79 */ 0x6c,                    // 54

  // Current Channel
  /* 80 - 81 */ 0x03, 0x01,         // Channel set, length
  /* 82 */      0x01,               // Current Channel

  // RSN information
  /*  83 -  84 */ 0x30, 0x18,
  /*  85 -  86 */ 0x01, 0x00,
  /*  87 -  90 */ 0x00, 0x0f, 0xac, 0x02,
  /*  91 -  92 */ 0x02, 0x00,
  /*  93 - 100 */ 0x00, 0x0f, 0xac, 0x04, 0x00, 0x0f, 0xac, 0x04, /*Fix: changed 0x02(TKIP) to 0x04(CCMP) is default. WPA2 with TKIP not supported by many devices*/
  /* 101 - 102 */ 0x01, 0x00,
  /* 103 - 106 */ 0x00, 0x0f, 0xac, 0x02,
  /* 107 - 108 */ 0x00, 0x00
};

// Shift out channels one by one
void nextChannel() {
  if (sizeof(channels) > 1) {
    uint8_t ch = channels[channelIndex];
    channelIndex++;
    if (channelIndex > sizeof(channels)) channelIndex = 0;

    if (ch != wifi_channel && ch >= 1 && ch <= 14) {
      wifi_channel = ch;
      wifi_set_channel(wifi_channel);
    }
  }
}

// Random MAC generator
void randomMac() {
  for (int i = 0; i < 6; i++){
     macAddr[i] = random(256);
  }
}

void setup() {
  // create empty SSID
  for (int i = 0; i < 32; i++)
    emptySSID[i] = ' ';

  // for random generator
  randomSeed(os_random());

  // set packetSize
  packetSize = sizeof(beaconPacket);
  if (wpa2) {
    beaconPacket[34] = 0x31;
  } else {
    beaconPacket[34] = 0x21;
    packetSize -= 26;
  }

  // generate random mac address
  randomMac();

  // start serial
  Serial.begin(115200);
  Serial.println();

  // get time
  currentTime = millis();

  // start WiFi
  WiFi.mode(WIFI_OFF);
  wifi_set_opmode(STATION_MODE);

  // Set to default WiFi channel
  wifi_set_channel(channels[0]);

  // Display all saved WiFi SSIDs
  Serial.println("SSIDs:");
  int i = 0;
  int len = sizeof(ssids);
  while (i < len) {
    Serial.print((char)pgm_read_byte(ssids + i));
    i++;
  }

  Serial.println();
  Serial.println("Started \\o/");
  Serial.println();
}

void loop() {
  currentTime = millis();

  // send out SSIDs
  if (currentTime - attackTime > 100) {
    attackTime = currentTime;

    // temp variables
    int i = 0;
    int j = 0;
    int ssidNum = 1;
    char tmp;
    int ssidsLen = strlen_P(ssids);
    bool sent = false;

    // Go to next channel
    nextChannel();

    while (i < ssidsLen) {
      // Get the next SSID
      j = 0;
      do {
        tmp = pgm_read_byte(ssids + i + j);
        j++;
      } while (tmp != '\n' && j <= 32 && i + j < ssidsLen);

      uint8_t ssidLen = j - 1;

      // set MAC address
      macAddr[5] = ssidNum;
      ssidNum++;

      // write MAC address into beacon frame
      memcpy(&beaconPacket[10], macAddr, 6);
      memcpy(&beaconPacket[16], macAddr, 6);

      // reset SSID
      memcpy(&beaconPacket[38], emptySSID, 32);

      // write new SSID into beacon frame
      memcpy_P(&beaconPacket[38], &ssids[i], ssidLen);

      // set channel for beacon frame
      beaconPacket[82] = wifi_channel;

      // send packet
      if (appendSpaces) {
        for (int k = 0; k < 3; k++) {
          packetCounter += wifi_send_pkt_freedom(beaconPacket, packetSize, 0) == 0;
          delay(1);
        }
      }

      // remove spaces
      else {

        uint16_t tmpPacketSize = (packetSize - 32) + ssidLen; // calc size
        uint8_t* tmpPacket = new uint8_t[tmpPacketSize]; // create packet buffer
        memcpy(&tmpPacket[0], &beaconPacket[0], 38 + ssidLen); // copy first half of packet into buffer
        tmpPacket[37] = ssidLen; // update SSID length byte
        memcpy(&tmpPacket[38 + ssidLen], &beaconPacket[70], wpa2 ? 39 : 13); // copy second half of packet into buffer

        // send packet
        for (int k = 0; k < 3; k++) {
          packetCounter += wifi_send_pkt_freedom(tmpPacket, tmpPacketSize, 0) == 0;
          delay(1);
        }

        delete tmpPacket; // free memory of allocated buffer
      }

      i += j;
    }
  }

  // show packet-rate each second
  if (currentTime - packetRateTime > 1000) {
    packetRateTime = currentTime;
    Serial.print("Packets/s: ");
    Serial.println(packetCounter);
    packetCounter = 0;
  }
}