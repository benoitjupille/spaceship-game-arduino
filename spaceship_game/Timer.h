#ifndef TIMER_H
#define TIMER_H

/**
 * Class to make time manipulation.
 * Calculation unit is Milliseconds.
 */
class Timer
{
  private:
    /**
     * The previous time in milliseconds recorded
     */
    unsigned long previousTime = 0;

    /**
     * Automatic saving every time you check
     */
    unsigned long autoSavedTime = 0;

    /**
     * The interval to consider as a tick
     */
    unsigned long clockTick = 1000;

  public:
    /**
     * The current time in milliseconds
     */
    unsigned long current();

    /**
     * The interval between the last recorder time and
     * the actual one
     */
    unsigned long interval();

    /**
     * Record a new previous time
     */
    void recordPreviousTime();

    /**
     * Is clock ticking ?
     */
    boolean tick();

    /**
     * this is a fourth time tick
     */
    boolean tickQuarter();

    /**
     * Reset everything to zero
     */
    void reset();
};

#endif
