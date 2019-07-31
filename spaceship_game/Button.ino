#include "Button.h"
#include "Control.h"

Button::Button(int pinNumber): Control(pinNumber){}

/**
 * True if button is pressed
 * 
 * @return boolean
 */
boolean Button::action()
{
  return digitalRead(getPin()) == HIGH;
}
