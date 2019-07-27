#include "Led.h"

/**
 * Constructor
 */
Led::Led(int pinNumber): pin(pinNumber)
{
  pinMode(pinNumber, OUTPUT);
  off();
};

/**
 * Determines if the light is on
 * 
 * @return boolean true if lighting, false if it's turned off
 */
boolean Led::isOn()
{
  return flag;
}

/**
 * Toggle the light. Ex : if the light is on, it will go off.
 */
void Led::toggle()
{
  flag != flag;

  if (flag) {
    on();
    return;
  }

  off();
}

/**
 * Turn on the light
 */
void Led::on()
{
  flag = true;
  writeFlag();
}

/**
 * Turn off the light
 */
void Led::off()
{
  flag = false;
  writeFlag();
}

/**
 * Execute the Arduino function to interacts with the pin
 */
void Led::writeFlag()
{
  digitalWrite(pin, flag);
}
