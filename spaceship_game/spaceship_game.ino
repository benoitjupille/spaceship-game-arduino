#include "Graphics.h"
#include "Button.h"

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
int leds[] = {
  5, 6, 7
};

boolean flags[] = {
  false, false, false
};

int lengthOfControls = 2;

void setup() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!graphics.init()) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  initLeds();

  graphics.erase();
  graphics.play();
 
  graphics.drawSpaceship(0);
}

void loop() {
  checkState();
  checkLights();
  delay(200);
 
  if (isReadyToLaunch()) {
    graphics.liftOff();
    delay(1000);

    for (int i = 0; i < lengthOfControls; i++) {
      flags[i] = false;
    }

    graphics.drawSpaceship(0);
  }
}

/*
 * Initialize the leds states
 */
void initLeds(void) {
  for (int i = 0; i < lengthOfControls; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

boolean isReadyToLaunch(void) {
  boolean flag = true;

  for (int i = 0; i < lengthOfControls; i++) {
    if (!flags[i]) {
      flag = false;
    }
  }

  return flag;
}

/**
 * Check the state of flags changed by pressing buttons
 */
void checkState(void) {
  for (int i=0; i<lengthOfControls; i++) {
    if (buttons[i].action()) {
      flags[i] = !flags[i];
    }
  }
}

/**
 * Change the led states according to flag states
 */
void checkLights(void) {
  for (int i=0; i<lengthOfControls; i++) {
    digitalWrite(leds[i], flags[i]);
  }
}
