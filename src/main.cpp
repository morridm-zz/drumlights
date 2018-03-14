/* David Morris 2018
  Thanks to:
      https://www.adafruit.com
      http://cassettepunk.com
      http://fastled.io
      https://beammyselfintothefuture.wordpress.com/
      http://moving-rainbow.readthedocs.io/en/latest/guide/color-wheel/
      https://www.instructables.com/id/Light-Up-Drum-Kit/
  for all the great tutorials.

  Note: If you are looking for the code I used for my Trinket 5v original see "https://github.com/morridm/drumlights/tree/master/archive/Trinket".
  This code assumes you are using an Adafruit Trinket Pro 5v not the regular Trinket 5v.
*/


#include <Arduino.h>
#include <DrumPatterns.h>

static const int NEOPIXEL_STRIP_SIGNAL_PIN = 4; // The digital pin # for the neopixel output
static const int PIEZO_ANALOG_INPUT_PIN = 0;    // The analog alias pin # to the piezo input on PIEZO_DIGITAL_INPUT_PIN
static const int PIEZO_DIGITAL_INPUT_PIN = 14;  // The digital pin # for the piezo input
static const int POT_PIN = A1;
static const int BUTTON_PIN = 12;

struct DrumComponent theDrum = {3, 81, 10, 0, NEOPIXEL_STRIP_SIGNAL_PIN, PIEZO_ANALOG_INPUT_PIN, PIEZO_DIGITAL_INPUT_PIN, POT_PIN};

void animationComplete();

DrumPatterns strip(theDrum, theDrum.numPixelsOnDrum, theDrum.NEOPIXEL_STRIP_SIGNAL_PIN, NEO_GRB + NEO_KHZ800, &animationComplete);

void setup()
{

    strip.begin();
    strip.setBrightness(255);

    strip.Scanner(strip.Color(0, 0, 255), 45);
    strip.ColorWipe(strip.Color(0, 0, 255), 30);

    strip.ActivePattern = DRUMBEAT;

    pinMode(theDrum.PIEZO_DIGITAL_INPUT_PIN, INPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    strip.clearStrip();
    strip.colorWipeAnimation(strip.Color(0, 30, 0), 10); //show green color wipe to indicate it is ready to go
    strip.clearStrip();
}

bool wasButtonPressed()
{

    static bool oldState = HIGH;

    bool bReturn = false;

    // Get current button state.
    bool newState = digitalRead(BUTTON_PIN);

    // Check if state changed from high to low (button press).
    if (newState == LOW && oldState == HIGH)
    {

        // Short delay to debounce button.
        delay(20);

        // Check if button is still low after debounce.
        newState = digitalRead(BUTTON_PIN);

        if (newState == LOW)
        {
            bReturn = true;
        }
    }

    // Set the last button state to the old state.
    oldState = newState;

    return bReturn;
}

void loop()
{
    strip.Update();

    pattern currentPattern = strip.ActivePattern;

    if (wasButtonPressed())
    {
        strip.Interval = 0;

        switch (currentPattern)
        {
        case DRUMBEAT:
            strip.ActivePattern = RAINBOW_CYCLE;
            strip.TotalSteps = 255;
            currentPattern = strip.ActivePattern;
            strip.clearStrip();
            strip.colorWipeAnimation(strip.Color(0, 0, 255), 10); //show green color wipe to indicate it is ready to go
            break;
        case RAINBOW_CYCLE:
            strip.ActivePattern = SCANNER;
            currentPattern = strip.ActivePattern;
            strip.clearStrip();
            strip.colorWipeAnimation(strip.Color(255, 0, 0), 10); //show green color wipe to indicate it is ready to go
            break;
        case COLOR_WIPE:
            strip.ActivePattern = DRUMBEAT;
            strip.TotalSteps = 255;
            currentPattern = strip.ActivePattern;
            strip.clearStrip();
            strip.colorWipeAnimation(strip.Color(0, 30, 0), 10); //show green color wipe to indicate it is ready to go
            break;
        case SCANNER:
            strip.ActivePattern = COLOR_WIPE;
            currentPattern = strip.ActivePattern;
            strip.clearStrip();
            strip.colorWipeAnimation(strip.Color(255, 75, 0), 10); //show green color wipe to indicate it is ready to go
            break;
        default:
            strip.ActivePattern = DRUMBEAT;
            strip.TotalSteps = 255;
            currentPattern = strip.ActivePattern;
            strip.clearStrip();
            strip.colorWipeAnimation(strip.Color(0, 30, 0), 10); //show green color wipe to indicate it is ready to go
            break;
        }
    }

    strip.showStrip();
}

// Strip  Completion Callback
void animationComplete()
{

    uint8_t red = random(0, 255);
    uint8_t green = random(0, 255);
    uint8_t blue = random(0, 255);

    if (strip.ActivePattern == RAINBOW_CYCLE)
    {
        strip.RainbowCycle(random(0, 10));
    }

    //  strip.Fade( 50, 255, 255, 30  );
    if (strip.ActivePattern == SCANNER)
    {

        if ((red + green + blue) <= 10)
        {
            red = 0;
            green = 0;
            blue = 255;
        }

        strip.Scanner(strip.Color(red, green, blue), 25);
    }

    if (strip.ActivePattern == COLOR_WIPE)
    {
        strip.ColorWipe(strip.Color(red, green, blue), 10);
    }
}