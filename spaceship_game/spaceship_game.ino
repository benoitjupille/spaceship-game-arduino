#include "Graphics.h"
#include "Button.h"
#include "Led.h"

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

int lengthOfControls = 2;

void setup() {
  if(!graphics.init()) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  graphics.erase();
  graphics.play();
 
  graphics.drawSpaceship(0);
}

void loop() {
  checkState();
  delay(200);
 
  if (isReadyToLaunch()) {
    graphics.liftOff();
    delay(1000);

    for (int i = 0; i < lengthOfControls; i++) {
      leds[i].off();
    }

    graphics.drawSpaceship(0);
  }
}

/**
 * Is the spaceship ready to be launch ?
 */
boolean isReadyToLaunch(void) {
  boolean flag = true;

  for (int i = 0; i < lengthOfControls; i++) {
    if (!leds[i].isOn()) {
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
      leds[i].toggle();
    }
  }
}
