/*
  Ammar Mohammed
  January 13, 2025.
  Digital Clock
  Version 0.1: Starts at 12:00 AM and updates every one second.
  http://www.arduino.cc/en/Tutorial/LiquidCrystal
*/

#include <LiquidCrystal.h>

int arr[6] = {0, 0, 0, 0, 2, 1};
bool isAM = true;

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

void setup()
{
  lcd_1.begin(16, 2); // Set up the number of columns and rows on the LCD.

  // Print a message to the LCD.
  lcd_1.print("HH:MM:SS");
}

void loop()
{
  lcd_1.setCursor(0, 1);
  lcd_1.print(arr[5]);
  
  lcd_1.setCursor(1, 1);
  lcd_1.print(arr[4]);
  
  lcd_1.setCursor(3, 1);
  lcd_1.print(arr[3]);
  
  lcd_1.setCursor(4, 1);
  lcd_1.print(arr[2]);
  
  lcd_1.setCursor(6, 1);
  lcd_1.print(arr[1]);
  
  lcd_1.setCursor(7, 1);
  lcd_1.print(arr[0]);
  delay(1000); // Wait for 1000 millisecond(s)
  //delayMicroseconds(1);
  
  lcd_1.setCursor(9, 1);
  if(isAM) {
  	  lcd_1.print("AM");
  }
  else {
  	lcd_1.print("PM");
  }
  
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
    
    if(isAM) {
    	isAM = false;
    }
    else {
    	isAM = true;
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
  
  if(arr[2] == 9 && arr[1] == 5 && arr[0] == 9) {
  	arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;
    arr[3] += 1;
  }
  
  if(arr[1] == 5 && arr[0] == 9) {
    arr[0] = 0;
    arr[1] = 0;
    arr[2] += 1;
  }
  
  
  
}