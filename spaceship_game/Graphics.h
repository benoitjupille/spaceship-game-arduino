class Graphics
{
  private:
    /**
     * screen width
     */
    int screenWidth = 128;
    
    /**
     * scren height
     */
    int screenHeight = 32;
    
    /**
     * bitmap container width
     */
    int bitmapWidth = 22;
    
    /**
     * bitmap container height
     */
    int bitmapHeight = 16;
    
    /**
     * Speed of the animations
     */
    int animationSpeed = 15;
    
    /**
     * Output led reset for the screen
     */
    int oledReset = 4;
    
    /**
     * The bitmap of the spaceship
     */
    const unsigned char PROGMEM bitmap[] = 
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
};
