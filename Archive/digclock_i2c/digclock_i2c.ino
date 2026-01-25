#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int arr[7] = {0, 0, 0, 0, 2, 1, 1}; //{S2, S1, M2, M1, H2, H1, isAM}

void setup()
{
  Serial.begin(115200);

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

void loop()
{

}

void displayTime(void) 
{
  for(;;) {
    char meridiem[3];
    
    if(arr[6] == 1) {
      meridiem[0] = 'A';
    }
    else {
      meridiem[0] = 'P';
    }
    meridiem[1] = 'M';
    
    String timeStr = "";
    timeStr += arr[5];
    timeStr += arr[4];

    if(arr[0] % 2 == 1)
    {
      timeStr += ':';
    }
    else {
      timeStr += ' ';
    }
    timeStr += arr[3];
    timeStr += arr[2];
    timeStr += meridiem[0]; 
    timeStr += meridiem[1];

    //DEV TESTING CODE
    // Serial.print(timeStr);
    // Serial.print(arr[1]);
    // Serial.println(arr[0]);
    //END TESTING CODE

    display.clearDisplay();
    display.setCursor(0,31);
    display.print(timeStr);
    display.display();
    delay(1000);

    if(arr[0] == 9) {
      arr[0] = 0;
      arr[1] += 1;
    }
    else {
      arr[0] += 1;
    }
    
    //12:59:59 switch to 01:00:00
    if(arr[5] == 1 && arr[4] == 2 && arr[3] == 5 && arr[2] == 9 && arr[1] == 5 && arr[0] == 9) {
      arr[0] = 0;
      arr[1] = 0;
      arr[2] = 0;
      arr[3] = 0;
      arr[4] = 1;
      arr[5] = 0;
    }
    
    //11:59:59 switch AM-PM
    if(arr[5] == 1 && arr[4] == 1 && arr[3] == 5 && arr[2] == 9 && arr[1] == 5 && arr[0] == 9) {
      arr[0] = 0;
      arr[1] = 0;
      arr[2] = 0;
      arr[3] = 0;
      arr[4] = 2;
      arr[5] = 1;
      
      //1 = AM, 0 = PM
      if(arr[6] == 1) {
        arr[6] = 0;
      }
      else {
        arr[6] = 1;
      }
    }
    
    //09:59:59 to 10:00:00
    if(arr[4] == 9 && arr[3] == 5 && arr[2] == 9 && arr[1] == 5 && arr[0] == 9) {
      arr[0] = 0;
      arr[1] = 0;
      arr[2] = 0;
      arr[3] = 0;
      arr[4] = 0;
      arr[5] += 1;
    }
    
    if(arr[3] == 5 && arr[2] == 9 && arr[1] == 5 && arr[0] == 9) {
      arr[0] = 0;
      arr[1] = 0;
      arr[2] = 0;
      arr[3] = 0;
      arr[4] += 1;
    }
    
    if(arr[2] == 9 && arr[1] == 6 && arr[0] == 0) {
      arr[0] = 0;
      arr[1] = 0;
      arr[2] = 0;
      arr[3] += 1;
    }
    
    if(arr[1] == 6 && arr[0] == 0) {
      arr[0] = 0;
      arr[1] = 0;
      arr[2] += 1;
    }
  }
}
