#include "Timer.h"

/**
 * The current time in milliseconds
 */
unsigned long Timer::current()
{
  autoSavedTime = millis();
  return autoSavedTime;
}

/**
 * The interval between the last recorder time and
 * the actual one
 */
unsigned long Timer::interval()
{
  return current() - previousTime;
}

/**
 * Record a new previous time
 */
void Timer::recordPreviousTime()
{
  autoSavedTime = millis();
  previousTime = autoSavedTime;
}

/**
 * Is clock ticking ?
 */
boolean Timer::tick()
{
  return interval() >= clockTick;
}


/**
 * Is clock ticking a quarter ?
 */
boolean Timer::tickQuarter()
{
  return interval() >= clockTick / 4;
}

/**
 * Reset everything to zero
 */
void Timer::reset()
{
  previousTime = 0;
  autoSavedTime = 0;
  recordPreviousTime();
}
