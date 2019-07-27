#ifndef LED_H
#define LED_H

/**
 * Handles led state, and embedd a flag to know
 * if the led is on or off
 */
class Led
{
  private:
    /**
     * the pin number
     */
    int pin;

    /**
     * the flag to determine is the light is on or not
     */
    boolean flag;

    /**
     * Execute the Arduino function to interacts with the pin
     */
    void writeFlag();

  public:
    /**
     * Constructor
     */
    Led(int pinNumber);
    
    /**
     * Determines if the light is on
     * 
     * @return boolean true if lighting, false if it's turned off
     */
    boolean isOn();

    /**
     * Toggle the light. Ex : if the light is on, it will go off.
     */
    void toggle();

    /**
     * Turn on the light
     */
    void on();

    /**
     * Turn off the light
     */
    void off();
};

#endif
