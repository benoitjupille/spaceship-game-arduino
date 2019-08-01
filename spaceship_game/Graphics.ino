#include "Graphics.h"

#include <Wire.h>
#include <Adafruit_SSD1306.h>

/**
 * screen width
 */
int screenWidth = 128;

/**
 * scren height
 */
int screenHeight = 32;

/**
 * Output led reset for the screen
 */
int oledReset = 4;

Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, oledReset);

/**
 * The bitmap of the spaceship
 */
static const unsigned char PROGMEM bitmap[] = 
{
  B00000001, B10000000,
 B00000010, B01000000,
 B00000100, B00100000,
 B00000111, B11100000,
 B00000111, B11100000,
 B00000111, B11100000,
 B00000110, B01100000,
 B00000110, B01100000,
 B00000111, B11100000,
 B00000111, B11100000,
 B00000111, B11100000,
 B00001111, B11110000,
 B00010111, B11101000,
 B00100100, B00100100,
 B01000111, B11100010,
 B01111000, B00011110,
};

/**
 * Init the display. Returns false if a problem occured
 * SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
 * 
 * @return boolean
 */
boolean Graphics::init()
{
  return display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

/**
 * Clear the screen
 */
void Graphics::erase()
{
  display.clearDisplay();  
}

/**
 * Display the screen cache
 */
void Graphics::play()
{
  display.display();
}

/**
 * Draw the spaceship
 */
void Graphics::drawSpaceship(int altitude)
{
  erase();

  display.drawBitmap(
    (display.width()  - bitmapWidth) / 2,
    display.height() - bitmapHeight - altitude,
    bitmap,
    bitmapWidth,
    bitmapHeight,
    1
  );
  play();
}

/**
 * Animation of the spaceship flying
 */
void Graphics::liftOff()
{
  fireOn();
  for(int i=0; i<display.height() + 2; i+=2) {
    drawSpaceship(i);
    delay(500 - (animationSpeed * i));
  }
}

/**
 * Blink the screen to make "start fire" effect
 */
void Graphics::fireOn()
{
  display.invertDisplay(true);
  delay(300);
  display.invertDisplay(false);
  delay(100);
  display.invertDisplay(true);
  delay(100);
  display.invertDisplay(false);
  delay(50);
}

/**
 * Draw a game over screen
 */
void Graphics::drawGameOver()
{
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.clearDisplay(); 
  display.println(F("GAME OVER"));
  display.display();
}
