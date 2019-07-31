#ifndef BUTTONS_H
#define BUTTONS_H

#include "Control.h"

class Button : public Control
{

  public:
    /**
     * Constructor
     */
    Button();
    Button(int pinNumber);

    /**
     * True if button is pressed
     * 
     * @return boolean
     */
    boolean action();
};

#endif
