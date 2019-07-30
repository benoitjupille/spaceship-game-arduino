#include "Graphics.h"
#include "Button.h"
#include "Led.h"
#include "Timer.h"

Graphics graphics;

/**
 * Initialize buttons
 */
Button buttons[3] = {
  Button(2),
  Button(3),
  Button(4)
};

/**
 * LEDS for the output lights
 */
Led leds[3] = {
  Led(5),
  Led(6),
  Led(7)
};

/**
 * Already played slots
 */
boolean playedSlots[3] = {
  false,
  false,
  false
};

/**
 * This array will help to retain
 * a random order of triggering slots to be
 * activated.
 */
int indexes[3] = {
  0,
  1,
  2
};

/**
 * The index of the slot that is currently
 * requiring a user action
 */
int playingSlot = 0;

/**
 * Timer
 */
Timer timer;

int lengthOfControls = 2;

void setup() {
  if(!graphics.init()) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  graphics.erase();
  graphics.play();
 
  reset();
}

/**
 * If i dont put the delay, the Timer is not working.
 * 
 * That's probably because I can't set the Serial.begin().
 * If I put the begin, the compiler won't pass
 */
void loop() {
  delay(100); 
  checkState();
  
  if (isReadyToLaunch()) {
    graphics.liftOff();
    delay(1000);

    reset();
    
    return;
  }

  // Make the current light blinking every 4th
  if (timer.tick()) {
    leds[index()].toggle();
  }
}

void reset()
{
  // Put back timer to zero
  timer.reset();

  // We turn off the lights, and put all played slots to false
  for (int i = 0; i < lengthOfControls; i++) {
    leds[i].off();
    playedSlots[i] = false;
  }

  // playing slot put to first position
  playingSlot = 0;

  // Shuffle the indexes that give the order of execution
  randomizeIndexes();
  
  // Put the rocket back down
  graphics.drawSpaceship(0);
}

/**
 * Is the spaceship ready to be launch ?
 */
boolean isReadyToLaunch(void) {
  boolean flag = true;

  for (int i = 0; i < lengthOfControls; i++) {
    if (!playedSlots[i]) {
      flag = false;
    }
  }

  return flag;
}

/**
 * Check the state of flags changed by pressing buttons
 */
void checkState(void) {
  if (!buttons[index()].action()) {
    return;
  }

  leds[index()].on();
  
  // Light is on, we give the player a break
  delay((rand() % 2000) + 1000);

  if (playingSlot <= lengthOfControls) {
    playedSlots[playingSlot] = true;
    playingSlot = playingSlot + 1;
    return;
  }

  randomizeIndexes();
}

int index()
{
  return indexes[playingSlot];
}

/**
 * Randomize the indexes
 */
void randomizeIndexes(void) {
  for (int i=lengthOfControls - 1; i >= 0; i--) {
    int randomIndex = rand() % lengthOfControls;
    int old = indexes[i];
    indexes[i] = indexes[randomIndex];
    indexes[randomIndex] = old;
  }
}
