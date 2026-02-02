#include "myTime.h"

//Default constructor: starting time is 12:00:00AM
MyTime::MyTime()
{
  hourDigit1 = 1;
  hourDigit2 = 2;
  minuteDigit1 = 0;
  minuteDigit2 = 0;
  secondDigit1 = 0;
  secondDigit2 = 0;
  isPM = 0; //AM = 0, PM = 1
}

//Converts MyTime to string format: HH:MMam or HH:MMpm
string MyTime::toString()
{
  string timeString = ""; //std::__cxx11::string timeString
  timeString += char('0' + hourDigit1);
  timeString += char('0' + hourDigit2);

  //blinking affect to show passage of seconds
  if(secondDigit2 % 2 == 0){
    timeString += ":";
  }
  else {
    timeString += " ";
  }

  timeString += char('0' + minuteDigit1);
  timeString += char('0' + minuteDigit2);

  char meridiem[3] = "";
  if(isPM == 0) {
    meridiem[0] = 'A';
  }
  else {
    meridiem[0] = 'P';
  }
  meridiem[1] = 'M';

  timeString += meridiem[0];
  timeString += meridiem[1];

  return timeString;
} //end of MyTime::toString()

//Debugging code: returns the value of the second member variables
string MyTime::printSeconds()
{
  string secondsString = "";
  secondsString += char('0' + secondDigit1);
  secondsString += char('0' + secondDigit2);
  return secondsString;
}

//Increment the value of MyTime object by one second
void MyTime::incrementTime()
{
  //The main incrementing if-block
  //Increase the seconds by 1, if secondDigit2 reaches nine set it to 0 and increment the secondDigit1 by 1
  if(secondDigit2 == 9) {
    secondDigit2 = 0;
    secondDigit1 += 1;
  }
  else {
    secondDigit2 += 1;
  }
  
  //CHECK IF THIS IS CORRECT, doesn't follow same logic as the wx:yz:60
  //12:59:59 switch to 01:00:00
  if(hourDigit1 == 1 && hourDigit2 == 2 && minuteDigit1 == 5 && minuteDigit2 == 9 && secondDigit1 == 5 && secondDigit2 == 9) {
    secondDigit2 = 0;
    secondDigit1 = 0;
    minuteDigit2 = 0;
    minuteDigit1 = 0;
    hourDigit2 = 1;
    hourDigit1 = 0;
  }
  
  //CHECK IF THIS IS CORRECT, doesn't follow same logic as the wx:yz:60
  //11:59:59 switch AM-PM
  if(hourDigit1 == 1 && hourDigit2 == 1 && minuteDigit1 == 5 && minuteDigit2 == 9 && secondDigit1 == 5 && secondDigit2 == 9) {
    secondDigit2 = 0;
    secondDigit1 = 0;
    minuteDigit2 = 0;
    minuteDigit1 = 0;
    hourDigit2 = 2;
    hourDigit1 = 1;
    
    //AM = 0, PM = 1
    if(isPM == 0) {
      isPM = 1;
    }
    else {
      isPM = 0;
    }
  }
  
  //CHECK IF THIS IS CORRECT, doesn't follow same logic as the wx:yz:60
  //09:59:59 to 10:00:00
  if(hourDigit2 == 9 && minuteDigit1 == 5 && minuteDigit2 == 9 && secondDigit1 == 5 && secondDigit2 == 9) {
    secondDigit2 = 0;
    secondDigit1 = 0;
    minuteDigit2 = 0;
    minuteDigit1 = 0;
    hourDigit2 = 0;
    hourDigit1 += 1;
  }
  
  //CHECK IF THIS IS CORRECT, doesn't follow same logic as the wx:yz:60
  //wx:59:59 -> w(x+1):00:00
  if(minuteDigit1 == 5 && minuteDigit2 == 9 && secondDigit1 == 5 && secondDigit2 == 9) {
    secondDigit2 = 0;
    secondDigit1 = 0;
    minuteDigit2 = 0;
    minuteDigit1 = 0;
    hourDigit2 += 1;
  }
  
  //wx:y9:59 -> wx:y9:60 = wx:(y+1)0:00
  if(minuteDigit2 == 9 && secondDigit1 == 6 && secondDigit2 == 0) {
    secondDigit2 = 0;
    secondDigit1 = 0;
    minuteDigit2 = 0;
    minuteDigit1 += 1;
  }
  
  //wx:yz:59 -> wx:yz:60 = wx:y(z+1):00
  if(secondDigit1 == 6 && secondDigit2 == 0) {
    secondDigit2 = 0;
    secondDigit1 = 0;
    minuteDigit2 += 1;
  }
} //end of MyTime::incrementTime()

void MyTime::setTime(int newHourDigit1, int newHourDigit2, 
  int newMinuteDigit1, int newMinuteDigit2,
  int newSecondDigit1, int newSecondDigit2, 
  int newIsPM)
{
  hourDigit1 = newHourDigit1;
  hourDigit2 = newHourDigit2;
  minuteDigit1 = newMinuteDigit1;
  minuteDigit2 = newMinuteDigit2;
  secondDigit1 = newSecondDigit1;
  secondDigit2 = newSecondDigit2;
  isPM = newIsPM;
}