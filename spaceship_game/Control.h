#ifndef CONTROL_H
#define CONTROL_H

/**
 * Handles the inputs of the game
 */
class Control
{
  private:
    /**
     * pin number
     */
     int pin;

  public:
    /**
     * constructor
     */
     Control();
     Control(int pinNumber);
    
    /**
     * return true if the control is actionned
     * 
     * @return boolean
     */
     virtual boolean action();

    /**
     * get pin
     */
     int getPin();
};

#endif
