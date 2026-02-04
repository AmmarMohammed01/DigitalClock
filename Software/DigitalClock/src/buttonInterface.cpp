#include "buttonInterface.h"

//Should attachInterrupt() be used? Once program is in the menu, what if I want to use button 1 again,
//can I detach a designated interrupt input? At least momentarilly, then re-enable it?

//Hold 1st button to enter MENU
//Use millis() to determine "click" vs "press"

void loadMenu() {
  /*
  MENU
  1. Set time
  2. Set alarm
  */

  //Stay in menu screen until user chooses an option.
  //Click either button 1 or 2 to access its respective option
  //Hold button 1 to exit MENU

  //Time selection: HH M M AorPm
}