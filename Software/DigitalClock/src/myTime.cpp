#include "myTime.h"

//Converts MyTime to string format: HH:MMam or HH:MMpm
string MyTime::toString()
{
  string timeString = ""; //std::__cxx11::string timeString
  timeString += hourDigit1;
  timeString += hourDigit2;
  timeString += ":";
  timeString += minuteDigit1;
  timeString += minuteDigit2;

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

void MyTime::incrementTime()
{
  if(secondDigit2 == 9) {
    secondDigit2 = 0;
    secondDigit1 += 1;
  }
  else {
    secondDigit2 += 1;
  }
  
  //12:59:59 switch to 01:00:00
  if(hourDigit1 == 1 && hourDigit2 == 2 && minuteDigit1 == 5 && minuteDigit2 == 9 && secondDigit1 == 5 && secondDigit2 == 9) {
    secondDigit2 = 0;
    secondDigit1 = 0;
    minuteDigit2 = 0;
    minuteDigit1 = 0;
    hourDigit2 = 1;
    hourDigit1 = 0;
  }
  
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
  
  //09:59:59 to 10:00:00
  if(hourDigit2 == 9 && minuteDigit1 == 5 && minuteDigit2 == 9 && secondDigit1 == 5 && secondDigit2 == 9) {
    secondDigit2 = 0;
    secondDigit1 = 0;
    minuteDigit2 = 0;
    minuteDigit1 = 0;
    hourDigit2 = 0;
    hourDigit1 += 1;
  }
  
  if(minuteDigit1 == 5 && minuteDigit2 == 9 && secondDigit1 == 5 && secondDigit2 == 9) {
    secondDigit2 = 0;
    secondDigit1 = 0;
    minuteDigit2 = 0;
    minuteDigit1 = 0;
    hourDigit2 += 1;
  }
  
  if(minuteDigit2 == 9 && secondDigit1 == 6 && secondDigit2 == 0) {
    secondDigit2 = 0;
    secondDigit1 = 0;
    minuteDigit2 = 0;
    minuteDigit1 += 1;
  }
  
  if(secondDigit1 == 6 && secondDigit2 == 0) {
    secondDigit2 = 0;
    secondDigit1 = 0;
    minuteDigit2 += 1;
  }
} //end of MyTime::incrementTime()