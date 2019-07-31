#ifndef SLOT_H
#define SLOT_H

#include "Button.h"
#include "Led.h"

/**
 * A slot is an association of a Button and a Led.
 * A slot uses 2 pins : one for the button, one for the led
 * 
 * Basically, a Slot has 1 input and 1 output
 */

class Slot
{
  public:
    /**
     * The button
     */
    Button button;

    /**
     * The led
     */
    Led led;

    /**
     * Constructor
     * 
     * @param int input pin of the button
     * @param int output pin of the led
     */
    Slot(int input, int output);
};

#endif
