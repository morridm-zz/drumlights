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
#ifdef __AVR__
#include <avr/power.h>
#endif

static const int NEOPIXEL_STRIP_SIGNAL_PIN = 0; // The digital pin # for the neopixel output
static const int PIEZO_ANALOG_INPUT_PIN = 1;    // The analog alias pin # to the piezo input on PIEZO_DIGITAL_INPUT_PIN
static const int PIEZO_DIGITAL_INPUT_PIN = 2;   // The digital pin # for the piezo input

typedef struct DrumComponent
{
    byte id;
    byte numPixelsOnDrum;
    uint16_t minimumRequiredPiezoThreshold;
    uint16_t currentPiezoThreshold;
};

//static const struct DrumComponent KICK         = { 0, 107, 65, 0 };

//static const struct DrumComponent SNARE        = { 1, 67, 65, 0 };

//static const struct DrumComponent MIDDLE_TOM   = { 2, 59, 65, 0 };
//static const struct DrumComponent HI_TOM       = { 3, 51, 65, 0 };
//static const struct DrumComponent FLOOR_TOM    = { 4, 75, 65, 0 };

//static const struct DrumComponent CRASH        = { 5, 47, 65, 0 };
//static const struct DrumComponent RIDE         = { 6, 55, 65, 0 };
//static const struct DrumComponent HI_HAT       = { 7, 31, 65, 0 };

static const struct DrumComponent BREADBOARD = {8, 25, 65, 0}; //temporary fake drum for neopixel strip when using breadboard for testing

static struct DrumComponent *myDrumComponent = &BREADBOARD; //Pointer* to selected drum...

static Adafruit_NeoPixel strip = Adafruit_NeoPixel(myDrumComponent->numPixelsOnDrum, NEOPIXEL_STRIP_SIGNAL_PIN, NEO_GRB + NEO_KHZ800);

void setPixel(int Pixel, uint32_t color)
{
    strip.setPixelColor(Pixel, color);
}

void setPixel(int Pixel, byte red, byte green, byte blue)
{
    setPixel(Pixel, strip.Color(red, green, blue));
}

void setCurrentPiezoThreshold(uint16_t t)
{
    myDrumComponent->currentPiezoThreshold = t;
}

uint16_t getCurrentThresholdFromPiezo()
{
    return analogRead(PIEZO_ANALOG_INPUT_PIN);
}

void runPixelChaseAnimation()
{

    for (int i = strip.numPixels(); i > 0; i--)
    {
        setPixel(i, strip.getPixelColor(i - 1));
    }
}

void showStrip()
{

    strip.show();
}

void clearStrip()
{
    strip.clear();
}

void setPixelStripColorBasedOnPiezoValue(int pixel)
{

    static byte numLoops = 0;

    byte WheelPos = numLoops;

    float intensity = (((float)myDrumComponent->currentPiezoThreshold) / 512.0);

    byte red = 0;
    byte green = 0;
    byte blue = 0;

    WheelPos = (255 - WheelPos);

    if (WheelPos < 85)
    {

        red = (255 - WheelPos * 3);
        green = 0;
        blue = (WheelPos * 3);
    }
    else if (WheelPos < 170)
    {

        WheelPos -= 85;

        red = 0;
        green = (WheelPos * 3);
        blue = (255 - WheelPos * 3);
    }
    else
    {

        WheelPos -= 170;

        red = (WheelPos * 3);
        green = (255 - WheelPos * 3);
        blue = 0;
    }

    if (numLoops >= 0 && numLoops < 255)
    {
        numLoops++;
    }
    else
    {
        numLoops = 0;
    }

    setPixel(pixel, red, green, blue);
}

void colorWipeAnimation(uint32_t stripColorValue, uint8_t wait)
{

    for (uint16_t i = 0; i < strip.numPixels(); i++)
    {

        setPixel(i, stripColorValue);

        if (wait > 0)
        {
            showStrip();
            delay(wait);
        }
    }

    if (wait == 0)
        showStrip();
}

void setup()
{ //runs once when powered on

#if defined(__AVR_ATtiny85__)
    if (F_CPU == 16000000)
        clock_prescale_set(clock_div_1);
#endif

    strip.begin();
    strip.setBrightness(255);

    clearStrip();

    colorWipeAnimation(strip.Color(0, 30, 0), 25); //show green color wipe to indicate it is ready to go

    clearStrip();

    pinMode(PIEZO_DIGITAL_INPUT_PIN, INPUT); //initialze vibration sensor
}

void loop()
{ //infinite loop

    int pixelNumbertoSet = 0;

    runPixelChaseAnimation();

    setCurrentPiezoThreshold(getCurrentThresholdFromPiezo());

    if (myDrumComponent->currentPiezoThreshold > myDrumComponent->minimumRequiredPiezoThreshold)
    {

        setPixelStripColorBasedOnPiezoValue(pixelNumbertoSet);
    }
    else
    {

        setPixel(pixelNumbertoSet, 0, 0, 0);
    }

    showStrip();
}
