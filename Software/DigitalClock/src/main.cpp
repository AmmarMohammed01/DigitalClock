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
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

//My Code
#include "myTime.h"
#include "buttonInterface.h"

void displayTime(void); //2. Add function declarations for PlatformIO

MyTime currentTime; //Default constructor called
string timeStr = currentTime.toString();

// Name of Bluetooth Device: Digital Clock
// Connect to Bluetooth device, use LightBlue app to "write" a value to device.
// Format of Input Sent via Bluetooth: initially sent as UTF-8 String Value
// Example To set time to 8:05pm, type 0805001 --> (hours 08: minutes 05 : seconds 00 : isPM 1)
// INPUT FORMAT: HHMMSSI
class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String value = pCharacteristic->getValue().c_str();

    if (value.length() > 0) {
      currentTime.setTime(value[0] - '0', value[1] - '0', value[2] - '0', value[3] - '0', value[4] - '0', value[5] - '0', value[6] - '0');
    }
  }
};

void setup()
{
  Serial.begin(115200);

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

  //Button Interface
  pinMode(buttonOnePin, INPUT);
  pinMode(buttonTwoPin, INPUT);
  //attachInterrupt()

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

    /*
    //DEBUGGING CODE
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
