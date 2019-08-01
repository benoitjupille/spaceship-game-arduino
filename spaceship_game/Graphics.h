#ifndef GRAPHICS_H
#define GRAPHICS_H

/**
 * Handles all graphics, bitmaps and animations
 * of the game
 */


/**
 * screen width
 */
extern int screenWidth;

/**
 * scren height
 */
extern int screenHeight;

/**
 * Output led reset for the screen
 */
extern int oledReset;

class Graphics
{
  private:
    /**
     * bitmap container width
     */
    int bitmapWidth = 16;
    
    /**
     * bitmap container height
     */
    int bitmapHeight = 16;
    
    /**
     * Speed of the animations
     */
    int animationSpeed = 15;

    /**
     * Declare the screen type
     */
    void declareScreen();

  public:
    /**
     * Init the display. Returns false if a problem occured
     * 
     * @return boolean
     */
    boolean init();

    /**
     * Clear the screen
     */
    void erase();

    /**
     * Display the screen cache
     */
    void play();

    /**
     * Draw the spaceship
     */
    void drawSpaceship(int altitude);

    /**
     * Animation of the spaceship flying
     */
    void liftOff();

    /**
     * Blink the screen to make "start fire" effect
     */
    void fireOn();

    /**
     * Draw a game over screen
     */
    void drawGameOver();
};
#endif
