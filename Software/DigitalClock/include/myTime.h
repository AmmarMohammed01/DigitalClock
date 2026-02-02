#ifndef MYTIME_H
#define MYTIME_H
#include <string> //what is the difference between C_11 string and Arduino String classes?
using namespace std;

class MyTime
{
  private:
    int hourDigit1;
    int hourDigit2;
    int minuteDigit1;
    int minuteDigit2;
    int secondDigit1;
    int secondDigit2;
    int isPM; //AM = 0, PM = 1
  public:
    MyTime(); //default constructor

    string toString();
    string printSeconds(); //debugging code
    void incrementTime();

    void setTime(int newHourDigit1, int newHourDigit2, int newMinuteDigit1, int newMinuteDigit2, int newSecondDigit1, int newSecondDigit2, int newIsPM);
};

#endif