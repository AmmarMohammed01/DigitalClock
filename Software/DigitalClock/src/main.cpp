// Tools > BOARD: Select "ESP32 Dev Module", 115200 Baud Rate
// Tools > Upload Speed, 115200

#include <Arduino.h> //1. Add for PlatformIO
#include <SPI.h>
#include <Wire.h>

//Display
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Bluetooth
/*
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
*/

//myTime
#include "myTime.h"

void displayTime(void); //2. Add function declarations for PlatformIO

//int timeFormat[7] = {0, 0, 0, 0, 2, 1, 1}; //{Seconds 2nd digit, Seconds 1st digit, Minutes 2, Minutes 1, Hours 2, Hours 1, isAM}
MyTime currentTime;
string timeStr = currentTime.toString();

/*
// Connect to Bluetooth device, use LightBlue to "write" a value to device.
// Format of Input Sent via Bluetooth: initially sent as UTF-8 String Value, converted to timeFormat[].
// Example: To set time to 5:54pm, type 0045500 
class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String value = pCharacteristic->getValue().c_str();

    if (value.length() > 0) {
      for (int i = 0; i < value.length(); i++) {
        Serial.print(value[i]);
        timeFormat[i] = value[i] - '0';
      }

    }
  }
};
*/

// Name of Bluetooth Device: Digital Clock
void setup()
{
  Serial.begin(115200);

  /*
  //BLE Setup
  BLEDevice::init("Digital Clock");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic =
    pService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("Hello from AHM ESP32 via BLE");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  */

  //DISPLAY SETUP
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(2000);
  display.clearDisplay();

  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,31);
  display.cp437(true); //Code Page 437 font

  displayTime();
}

void loop(){}

//runs forever
void displayTime(void) 
{
  for(;;) {
    timeStr = currentTime.toString();

    //DEBUGGING CODE
    /*
    Serial.print(timeStr.c_str());
    Serial.print(currentTime.printSeconds().c_str());
    Serial.println();
    */ 

    display.clearDisplay();
    display.setCursor(0,31);
    display.print(timeStr.c_str()); //Adafruit_SSD1306::print does not take argument std::__cxx11::string, converted it to c_string
    display.display();
    delay(1000);

    currentTime.incrementTime();
  }
}
