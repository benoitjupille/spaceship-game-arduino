#include "Control.h"

/**
 * Control implementation
 */

/**
 * Constructor
 */
Control::Control(int pinNumber): pin(pinNumber){}

/**
 * Get pin
 */
Control::getPin()
{
  return pin;
}
