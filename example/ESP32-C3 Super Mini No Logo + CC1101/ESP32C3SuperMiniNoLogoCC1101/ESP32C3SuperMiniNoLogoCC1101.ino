#include <RadioLib.h>
#include <rtl_433_ESP.h>

/* WIRING FOR ESP32-C3 + CC1101:
  - SCK:  GPIO 4
  - MISO: GPIO 5
  - MOSI: GPIO 6
  - CS:   GPIO 7
  - GDO0: GPIO 1
  - GDO2: GPIO 2
*/

// Define pins
#define CS_PIN   7
#define GDO0_PIN 1 
#define GDO2_PIN 2

// 1. Setup SPI for ESP32-C3
SPIClass spi(FSPI);

// 2. Create the 'radio' object (Must be named 'radio' to match the library edit)
CC1101 radio = new Module(CS_PIN, GDO0_PIN, RADIOLIB_NC, GDO2_PIN, spi);

// 3. Initialize the rtl_433_ESP library
rtl_433_ESP rtl_device;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize the SPI bus for the C3
  spi.begin(4, 5, 6, 7); 

  Serial.println(F("Initializing rtl_433_ESP..."));
  
  // Initialize receiver on GDO0 at 433.92 MHz
  rtl_device.initReceiver(GDO0_PIN, 433.92);
  rtl_device.enableReceiver();

  Serial.println(F("Receiver is active. Waiting for signals..."));
}

void loop() {
  // Library background tasks
  rtl_device.loop();
}