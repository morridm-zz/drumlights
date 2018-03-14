/* David Morris 2018
  Thanks to:
      https://www.adafruit.com
      http://cassettepunk.com
      http://fastled.io
      https://beammyselfintothefuture.wordpress.com/
      http://moving-rainbow.readthedocs.io/en/latest/guide/color-wheel/
      https://www.instructables.com/id/Light-Up-Drum-Kit/
  for all the great tutorials on how to use neopixels and piezo sensors.
*/
#include <Adafruit_NeoPixel.h>

static const int NEOPIXEL_STRIP_SIGNAL_PIN = 4; // The digital pin # for the neopixel output
static const int PIEZO_ANALOG_INPUT_PIN    = 0; // The analog alias pin # to the piezo input on PIEZO_DIGITAL_INPUT_PIN
static const int PIEZO_DIGITAL_INPUT_PIN   = 14; // The digital pin # for the piezo input
static const int POT_PIN = A1;
static const int BUTTON_PIN = 12;

typedef struct DrumComponent {
  byte id;
  byte numPixelsOnDrum;
  uint16_t minimumRequiredPiezoThreshold;
  uint16_t currentPiezoThreshold;
};

//static const struct DrumComponent KICK         = { 0, 115, 65, 0 };

//static const struct DrumComponent SNARE        = { 1, 65, 65, 0 };

//static const struct DrumComponent MIDDLE_TOM   = { 2, 59, 65, 0 };
static const struct DrumComponent HI_TOM       = { 3, 50, 65, 0 };
//static const struct DrumComponent FLOOR_TOM    = { 4, 75, 65, 0 };

//static const struct DrumComponent CRASH        = { 5, 47, 65, 0 };
//static const struct DrumComponent RIDE         = { 6, 55, 65, 0 };
//static const struct DrumComponent HI_HAT       = { 7, 31, 65, 0 };

//static const struct DrumComponent BREADBOARD   = { 8, 65, 65, 0 };//temporary fake drum for neopixel strip when using breadboard for testing

static struct DrumComponent *myDrumComponent = &HI_TOM;//Pointer* to selected drum...

static Adafruit_NeoPixel strip = Adafruit_NeoPixel( myDrumComponent->numPixelsOnDrum, NEOPIXEL_STRIP_SIGNAL_PIN, NEO_GRB + NEO_KHZ800 );

void setup() { //runs once when powered on

  strip.begin();
  strip.setBrightness( 255 );

  clearStrip();

  colorWipeAnimation( strip.Color( 0, 30, 0 ), 10 );  //show green color wipe to indicate it is ready to go

  clearStrip();

  pinMode( PIEZO_DIGITAL_INPUT_PIN, INPUT );//initialze vibration sensor

  // Declare button pins as inputs
  pinMode(BUTTON_PIN, INPUT_PULLUP);


}

void loop() { //infinite loop

  static bool oldState = HIGH;
  static int showType = 0;

  // Get current button state.
  bool newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {

    // Short delay to debounce button.
    delay(20);

    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);

    if (newState == LOW) {

      showType++;

      if (showType > 3) {
        showType = 0;
      }

      if (showType > 0) {
        startShow(showType, 10);
      }

      if (showType == 0) {
        colorWipeAnimation( strip.Color( 0, 30, 0 ), 10 );  //show green color wipe to indicate it is ready to go
      }

    }

  }

  // Set the last button state to the old state.
  oldState = newState;

  //  if ( showType == 0 ) {
  startShow(0, 0);
  //  }


}

void setCurrentPiezoThreshold( uint16_t t ) {
  myDrumComponent->currentPiezoThreshold = t;
}

uint16_t getCurrentThresholdFromPiezo() {
  return analogRead( PIEZO_ANALOG_INPUT_PIN );
}

void runPixelChaseAnimation() {

  for ( int i = strip.numPixels(); i > 0; i-- ) {
    setPixel( i, strip.getPixelColor( i - 1 ) );
  }

  setCurrentPiezoThreshold( getCurrentThresholdFromPiezo() );

  if ( myDrumComponent->currentPiezoThreshold > map(analogRead( POT_PIN ), 0, 1023, 5, 1023) ) {

    setPixelStripColorBasedOnPiezoValue( 0 );

  } else {

    setPixel( 0, 0, 0, 0 );

  }

}

void showStrip() {

  strip.show();

}

void clearStrip() {
  strip.clear();
}

void setPixelStripColorBasedOnPiezoValue( int pixel ) {

  static byte numLoops = 0;

  byte WheelPos = numLoops;

  //  float intensity = map( ( ( ( float ) myDrumComponent->currentPiezoThreshold ) / 1024.0 ), 0, 1023, 1, 1023 );
  byte intensity = 1;

  byte red = 0;
  byte green = 0;
  byte blue = 0;

  WheelPos = ( 255 - WheelPos );

  if (WheelPos < 85) {

    red = ( 255 - WheelPos * 3) * intensity;
    green = 0;
    blue = ( WheelPos * 3 ) * intensity;

  } else if (WheelPos < 170) {

    WheelPos -= 85;

    red = 0;
    green = ( WheelPos * 3 ) * intensity;
    blue = ( 255 - WheelPos * 3 ) * intensity;

  } else {

    WheelPos -= 170;

    red = ( WheelPos * 3 ) * intensity;
    green = ( 255 - WheelPos * 3 ) * intensity;
    blue = 0;

  }

  if ( numLoops >= 0 && numLoops < 255 ) {
    numLoops++;
  } else {
    numLoops = 0;
  }

  setPixel( pixel, red, green, blue );

}

void colorWipeAnimation(uint32_t stripColorValue, uint8_t wait) {

  for ( uint16_t i = 0; i < strip.numPixels(); i++ ) {

    setPixel( i, stripColorValue );

    if ( wait > 0 ) {
      showStrip();
      delay(wait);
    }

  }

  if ( wait == 0 ) showStrip();

}

void setPixel(int Pixel, uint32_t color) {
  strip.setPixelColor( Pixel, color );
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
  setPixel( Pixel, strip.Color( red, green, blue ) );
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {

  WheelPos = 255 - WheelPos;

  //  float intensity = map( ( ( ( float ) myDrumComponent->currentPiezoThreshold ) / 1024.0 ), 0, 1023, 1, 1023 );
  byte intensity = 1;

  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3 * intensity, 0, WheelPos * 3 * intensity);
  }

  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3 * intensity, 255 - WheelPos * 3 * intensity);
  }

  WheelPos -= 170;

  return strip.Color(WheelPos * 3 * intensity, 255 - WheelPos * 3 * intensity, 0);

}

void startShow(int i, int waitTime) {

  switch (i) {
    case 0:
      runPixelChaseAnimation();
      break;
    case 1:
      rainbow(waitTime);
      colorWipe(strip.Color(0, 0, 0), 5);    // Black/off
      break;
    case 2:
      rainbowCycle(waitTime);
      colorWipe(strip.Color(0, 0, 0), 5);    // Black/off
      break;
    case 3:
      theaterChaseRainbow(waitTime);
      colorWipe(strip.Color(0, 0, 0), 5);    // Black/off
      break;

  }

  showStrip();

}
