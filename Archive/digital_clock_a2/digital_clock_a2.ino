/*
  Ammar Mohammed
  January 13, 2025.
  Digital Clock
  Version 0.2: Clock updates every second, you can set time as well.
  Made for Arduino Uno R3 and LiquidCrystalDisplay
  http://www.arduino.cc/en/Tutorial/LiquidCrystal
*/

#include <LiquidCrystal.h>

const int BUTTON_PIN = 13;

int arr[7] = {0, 0, 0, 0, 2, 1, 1}; //{S2, S1, M2, M1, H2, H1, isAM}
//bool isAM = true;

LiquidCrystal lcd_1(5, 4, 0, 2, 14, 12);

void setup()
{
  lcd_1.begin(16, 2); // Set up the number of columns and rows on the LCD.

  // Print a message to the LCD.
  lcd_1.setCursor(0, 0);
  //lcd_1.print("HH:MM:SS");
  
  pinMode(9, INPUT); //button
  Serial.begin(9600);
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
  
  Serial.print(digitalRead(BUTTON_PIN));
  Serial.print(", ");
  Serial.println(analogRead(A0)/146); //to get values 0-7
  
  if(digitalRead(BUTTON_PIN) == HIGH) {
  	setTime();
  }
  
  lcd_1.setCursor(9, 1);
  /*
  if(isAM) {
  	  lcd_1.print("AM");
  }
  else {
  	lcd_1.print("PM");
  }
  */
  if(arr[6] == 1) {
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
    
    /*
    if(isAM) {
    	isAM = false;
    }
    else {
    	isAM = true;
    }
    */
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

void setTime() {
  int option0 = 0;
  int option1 = 0;
  int option2 = 0;
  int option3 = 0;
  int option4 = 0;
  int option5 = 0;
  int option6 = 0;
  int option7 = 0;
  
  int cursorPositions[8] = {0, 1, 3, 4, 6, 7, 9, 12};
  int timeSetArr[7] = {0, 0, 0, 0, 0, 0, 1};
  
  lcd_1.setCursor(0, 0);
  lcd_1.print("Set Time");
  
  lcd_1.setCursor(0, 1);
  lcd_1.print(timeSetArr[5]);
  
  lcd_1.setCursor(1, 1);
  lcd_1.print(timeSetArr[4]);
  
  lcd_1.setCursor(3, 1);
  lcd_1.print(timeSetArr[3]);
  
  lcd_1.setCursor(4, 1);
  lcd_1.print(timeSetArr[2]);
  
  lcd_1.setCursor(6, 1);
  lcd_1.print(timeSetArr[1]);
  
  lcd_1.setCursor(7, 1);
  lcd_1.print(timeSetArr[0]);
  
  lcd_1.setCursor(9, 1);
  lcd_1.print("AM");
  
  lcd_1.setCursor(12, 1);
  lcd_1.print("ok");
   
  while(option7 == 0) {
    lcd_1.setCursor(cursorPositions[analogRead(A0)/146],1);
  	lcd_1.cursor();
    delay(500);
    
    if(digitalRead(BUTTON_PIN) == HIGH) {
      //if cursor on ok, exit menu
      if(analogRead(A0)/146 == 7) {
      	option7 = 1; //exit setTime menu
        if( !((timeSetArr[5] == 0) && (timeSetArr[4] == 0)) ) {
          for(int i = 0; i < 7; i++) {
          	arr[i] = timeSetArr[i];
          }
        }
      }
      
      //if cursor on first digit, either 0 or 1 can be selected
      if(analogRead(A0)/146 == 0) {
        if(timeSetArr[5] == 0) {
        	timeSetArr[5] = 1;
        }
        else {
        	timeSetArr[5] = 0;
        }
        lcd_1.setCursor(0, 1);
  		lcd_1.print(timeSetArr[5]);
      }
      
      //if cursor on second digit, either 0 to 9 can be selected
      //unless first digit is 1, in that case select 0 to 2
      if(analogRead(A0)/146 == 1) {
        if(timeSetArr[5] == 0) {
          if(timeSetArr[4] < 9) {
            timeSetArr[4] += 1;
          }
          else {
            timeSetArr[4] = 0;
          }
        }
        else if (timeSetArr[5] == 1){
       	  if(timeSetArr[4] < 2) {
            timeSetArr[4] += 1;
          }
          else {
            timeSetArr[4] = 0;
          }
          
        }
        lcd_1.setCursor(1, 1);
  		lcd_1.print(timeSetArr[4]);
      }
      
      //if cursor on third digit, either 0 to 5 can be selected
      if(analogRead(A0)/146 == 2) {
        if(timeSetArr[3] < 5) {
          timeSetArr[3] += 1;
        }
        else {
          timeSetArr[3] = 0;
        }
        
        lcd_1.setCursor(3, 1);
  		lcd_1.print(timeSetArr[3]);
      }
      
      //if cursor on fourth digit, either 0 to 9 can be selected
      if(analogRead(A0)/146 == 3) {
        if(timeSetArr[2] < 9) {
          timeSetArr[2] += 1;
        }
        else {
          timeSetArr[2] = 0;
        }
        
        lcd_1.setCursor(4, 1);
  		lcd_1.print(timeSetArr[2]);
      }
      
      //if cursor on fifth digit, either 0 to 5 can be selected
      if(analogRead(A0)/146 == 4) {
        if(timeSetArr[1] < 5) {
          timeSetArr[1] += 1;
        }
        else {
          timeSetArr[1] = 0;
        }
        
        lcd_1.setCursor(6, 1);
  		lcd_1.print(timeSetArr[1]);
      }
      
      //if cursor on sixth digit, either 0 to 9 can be selected
      if(analogRead(A0)/146 == 5) {
        if(timeSetArr[0] < 9) {
          timeSetArr[0] += 1;
        }
        else {
          timeSetArr[0] = 0;
        }
        
        lcd_1.setCursor(7, 1);
  		lcd_1.print(timeSetArr[0]);
      }
      
      //if cursor on AM/PM digit, either A or P can be selected
      if(analogRead(A0)/146 == 6) {
        if(timeSetArr[6] == 1) {
          timeSetArr[6] = 0;
        }
        else {
          timeSetArr[6] = 1;
        }
        
        lcd_1.setCursor(9, 1);
        if(timeSetArr[6] == 1) {
          lcd_1.print("A");
        }
        else {
          lcd_1.print("P");
        }
      }
      
    }
  }
  
  lcd_1.noCursor();
  lcd_1.clear();
}