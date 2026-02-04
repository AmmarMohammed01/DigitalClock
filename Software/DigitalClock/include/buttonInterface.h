#ifndef BUTTON_INTERFACE_H
#define BUTTON_INTERFACE_H
#include <Arduino.h>
using namespace std;
  
const int buttonOnePin = 15; //IO15
const int buttonTwoPin = 14; //IO14

//FUNCTION FOR attachInterrupt
//Load the MENU, 1. Set time, 2. Set alarm
//https://docs.arduino.cc/language-reference/en/functions/external-interrupts/attachInterrupt/
void loadMenu();
#endif