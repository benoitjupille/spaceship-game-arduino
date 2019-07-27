#include "Button.h"
#include "Control.h"

Button::Button(int pinNumber): Control(pinNumber){}

boolean Button::action()
{
  return digitalRead(getPin()) == HIGH;
}
