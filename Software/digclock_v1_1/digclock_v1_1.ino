// Tools > BOARD: Select "ESP32 Dev Module", 115200 Baud Rate
// Tools > Upload Speed, 115200

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int timeFormat[7] = {0, 0, 0, 0, 2, 1, 1}; //{Seconds 2nd digit, Seconds 1st digit, Minutes 2, Minutes 1, Hours 2, Hours 1, isAM}

// Connect to Bluetooth device, use LightBlue to "write" a value to device.
// Format of Input Sent via Bluetooth: initially sent as UTF-8 String Value, converted to timeFormat[].
// Example: To set time to 5:54pm, type 0045500 
class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String value = pCharacteristic->getValue();

    if (value.length() > 0) {
      for (int i = 0; i < value.length(); i++) {
        Serial.print(value[i]);
        timeFormat[i] = value[i] - '0';
      }

    }
  }
};

// Name of Bluetooth Device: BlueLEDWrite
void setup()
{
  Serial.begin(115200);

  //BLE Setup
  BLEDevice::init("BlueLEDWrite");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic =
    pService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("Hello from AHM ESP32 via BLE");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

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

void displayTime(void) 
{
  for(;;) {
    char meridiem[3];
    
    if(timeFormat[6] == 1) {
      meridiem[0] = 'A';
    }
    else {
      meridiem[0] = 'P';
    }
    meridiem[1] = 'M';
    
    String timeStr = "";
    timeStr += timeFormat[5];
    timeStr += timeFormat[4];

    if(timeFormat[0] % 2 == 1)
    {
      timeStr += ':';
    }
    else {
      timeStr += ' ';
    }
    timeStr += timeFormat[3];
    timeStr += timeFormat[2];
    timeStr += meridiem[0]; 
    timeStr += meridiem[1];

    /*
    //DEV TESTING CODE
    Serial.print(timeStr);
    Serial.print(timeFormat[1]);
    Serial.println(timeFormat[0]);
    //END TESTING CODE
    */

    display.clearDisplay();
    display.setCursor(0,31);
    display.print(timeStr);
    display.display();
    delay(1000);

    if(timeFormat[0] == 9) {
      timeFormat[0] = 0;
      timeFormat[1] += 1;
    }
    else {
      timeFormat[0] += 1;
    }
    
    //12:59:59 switch to 01:00:00
    if(timeFormat[5] == 1 && timeFormat[4] == 2 && timeFormat[3] == 5 && timeFormat[2] == 9 && timeFormat[1] == 5 && timeFormat[0] == 9) {
      timeFormat[0] = 0;
      timeFormat[1] = 0;
      timeFormat[2] = 0;
      timeFormat[3] = 0;
      timeFormat[4] = 1;
      timeFormat[5] = 0;
    }
    
    //11:59:59 switch AM-PM
    if(timeFormat[5] == 1 && timeFormat[4] == 1 && timeFormat[3] == 5 && timeFormat[2] == 9 && timeFormat[1] == 5 && timeFormat[0] == 9) {
      timeFormat[0] = 0;
      timeFormat[1] = 0;
      timeFormat[2] = 0;
      timeFormat[3] = 0;
      timeFormat[4] = 2;
      timeFormat[5] = 1;
      
      //1 = AM, 0 = PM
      if(timeFormat[6] == 1) {
        timeFormat[6] = 0;
      }
      else {
        timeFormat[6] = 1;
      }
    }
    
    //09:59:59 to 10:00:00
    if(timeFormat[4] == 9 && timeFormat[3] == 5 && timeFormat[2] == 9 && timeFormat[1] == 5 && timeFormat[0] == 9) {
      timeFormat[0] = 0;
      timeFormat[1] = 0;
      timeFormat[2] = 0;
      timeFormat[3] = 0;
      timeFormat[4] = 0;
      timeFormat[5] += 1;
    }
    
    if(timeFormat[3] == 5 && timeFormat[2] == 9 && timeFormat[1] == 5 && timeFormat[0] == 9) {
      timeFormat[0] = 0;
      timeFormat[1] = 0;
      timeFormat[2] = 0;
      timeFormat[3] = 0;
      timeFormat[4] += 1;
    }
    
    if(timeFormat[2] == 9 && timeFormat[1] == 6 && timeFormat[0] == 0) {
      timeFormat[0] = 0;
      timeFormat[1] = 0;
      timeFormat[2] = 0;
      timeFormat[3] += 1;
    }
    
    if(timeFormat[1] == 6 && timeFormat[0] == 0) {
      timeFormat[0] = 0;
      timeFormat[1] = 0;
      timeFormat[2] += 1;
    }
  }
}
