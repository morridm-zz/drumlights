#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

static const int NEOPIXEL_STRIP_SIGNAL_PIN = 0; // The digital pin # for the neopixel output
static const int PIEZO_ANALOG_INPUT_PIN    = 1; // The analog alias pin # to the piezo input on PIEZO_DIGITAL_INPUT_PIN
static const int PIEZO_DIGITAL_INPUT_PIN   = 2; // The digital pin # for the piezo input

static Adafruit_NeoPixel strip = Adafruit_NeoPixel( 97, NEOPIXEL_STRIP_SIGNAL_PIN, NEO_GRB + NEO_KHZ800 );

void setup() { //runs once when powered on

#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  strip.begin();
  strip.setBrightness( 255 );

  colorWipeAnimation( strip.Color( 0, 30, 0 ), 25 );  //show green color wipe to indicate it is ready to go

  strip.clear();

  pinMode( PIEZO_DIGITAL_INPUT_PIN, INPUT );//initialze vibration sensor

}

void loop() { //infinite loop

  for ( int i = strip.numPixels(); i > 0; i-- ) {
    setPixel( i, strip.getPixelColor( i - 1 ) );
  }

  if ( analogRead( PIEZO_ANALOG_INPUT_PIN ) > 65 ) {

    setPixelStripColorBasedOnPiezoValue( 0 );

  } else {

    setPixel( 0, 0, 0, 0 );

  }

  strip.show();

}

void setPixelStripColorBasedOnPiezoValue( int pixel ) {

  static byte numLoops = 0;

  byte WheelPos = numLoops;

  byte red = 0;
  byte green = 0;
  byte blue = 0;

  WheelPos = ( 255 - WheelPos );

  if (WheelPos < 85) {

    red = ( 255 - WheelPos * 3);
    green = 0;
    blue = ( WheelPos * 3 );

  } else if (WheelPos < 170) {

    WheelPos -= 85;

    red = 0;
    green = ( WheelPos * 3 );
    blue = ( 255 - WheelPos * 3 );

  } else {

    WheelPos -= 170;

    red = ( WheelPos * 3 );
    green = ( 255 - WheelPos * 3 );
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
      strip.show();
      delay(wait);
    }

  }

  if ( wait == 0 ) strip.show();

}

void setPixel(int Pixel, uint32_t color) {
  strip.setPixelColor( Pixel, color );
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
  setPixel( Pixel, strip.Color( red, green, blue ) );
}
