#include "Graphics.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>

/**
 * Declare the screen type
 */
void Graphics::declareScreen()
{
  Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, oledReset);
}

/**
 * Init the display. Returns false if a problem occured
 * SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
 * 
 * @return boolean
 */
boolean init()
{
  declareScreen();
  return display.begin(SSD1306_SWITCHCAPVCC, 0x3C)
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
    (display.height() - bitmapHeight) - altitude,
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
    drawSpaceShip(i);
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
