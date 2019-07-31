#include "Graphics.h"
#include "Timer.h"
#include "Slot.h"

Graphics graphics;

/**
 * Initialize Slots
 */
Slot slots[3] = {
  Slot(2, 5),
  Slot(3, 6),
  Slot(4, 7)
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

/**
 * Chronometer to measure the timeframe
 * of possible player action
 * 
 * When a light starts blinking, the player will have
 * a certain limit of time to react.
 */
Timer chronometer;

/**
 * Player has lost
 */
boolean gameOver = false;

int lengthOfControls = 2;

void setup() {
  if(!graphics.init()) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  timer.recordPreviousTime();
  chronometer.recordPreviousTime();
  
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

  if (gameOver) {
    reset();
    return;
  }
  
  checkState();
  
  if (isReadyToLaunch()) {
    graphics.liftOff();
    delay(600);

    reset();
    
    return;
  }

  // Make the current light blinking every 4th
  if (timer.tick()) {
    slots[index()].led.toggle();
  }
}

void reset()
{
  gameOver = false;
  
  // Put back timer to zero
  timer.reset();
  chronometer.reset();

  // We turn off the lights, and put all played slots to false
  for (int i = 0; i < lengthOfControls; i++) {
    slots[i].led.off();
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
  if (!slots[index()].button.action()) {
    if (chronometer.interval() > 3000) {
      gameOver = true;
    }
    return;
  }

  slots[index()].led.on();
  
  // Light is on, we give the player a break
  delay((rand() % 2000) + 1000);

  if (playingSlot <= lengthOfControls) {
    playedSlots[playingSlot] = true;
    playingSlot = playingSlot + 1;

    chronometer.recordPreviousTime();

    return;
  }

  randomizeIndexes();
}

/**
 * Returns the current playing slot index
 */
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
