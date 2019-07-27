#ifndef BUTTONS_H
#define BUTTONS_H

#include "Control.h"
//#include "Arduino.h"

class Button : public Control
{

  public:
    Button(int pinNumber);
    boolean action();
};

#endif
