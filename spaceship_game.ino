#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define ANIMATION_SPEED 15

// The spaceship drawing
#define LOGO_HEIGHT   22
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{
 B00000001, B10000000,
 B00000010, B01000000,
 B00000100, B00100000,
 B00000100, B00100000,
 B00001000, B00010000,
 B00001000, B00010000,
 B00001111, B11110000,
 B00001110, B01110000,
 B00001100, B00110000,
 B00001100, B00110000,
 B00001100, B00110000,
 B00001110, B01110000,
 B00001111, B11110000,
 B00001111, B11110000,
 B00001000, B00010000,
 B00001111, B11110000,
 B00001111, B11110000,
 B00011111, B11111000,
 B00111111, B11111100,
 B01111111, B11111110,
 B11111111, B11111111,
 B11111000, B00011111,
};

int buttons[] = {
  2, 3, 4
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
  //Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  initLeds();
  initButtons();

  display.clearDisplay();
  display.display();
 
  drawSpaceShip(0);
}

void loop() {
  checkState();
  checkLights();
  delay(200);
 
  if (isReadyToLaunch()) {
    liftOff();
    delay(1000);

    for (int i = 0; i < lengthOfControls; i++) {
      flags[i] = false;
    }

    drawSpaceShip(0);
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

/**
 * Initialize buttons
 *
 * This way, we avoid a use of resistors
 */
void initButtons(void) {
  for (int i = 0; i < lengthOfControls; i++) {
    pinMode(buttons[i], INPUT);
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
 * Check the state of flags changed by pressuring buttons
 */
void checkState(void) {
  for (int i=0; i<lengthOfControls; i++) {
    if (digitalRead(buttons[i]) == HIGH) {
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

/**
 * Returns the length of an array
 *
 * @param array
 */
int lengthOf(int a[]) {
  return sizeof(a) / sizeof(a[0]);
}


/**
 * Draw the spaceship
 *
 * @param altitude in pixels
 */
void drawSpaceShip(int altitude) {
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) - altitude,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1
  );
  display.display();
}

/**
 * Lift Off !
 */
void liftOff(void) {
  fireOn();
  for(int i=0; i<display.height() + 2; i+=2) {
    drawSpaceShip(i);
    delay(500 - (ANIMATION_SPEED * i));
  }
}

/**
 * Make the screen "blinking" when spaceship starts
 */
void fireOn(void) {
  display.invertDisplay(true);
  delay(300);
  display.invertDisplay(false);
  delay(100);
  display.invertDisplay(true);
  delay(100);
  display.invertDisplay(false);
  delay(50);
}
