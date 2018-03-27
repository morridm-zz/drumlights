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
#include <PixelDrumPatterns.h> //See https://github.com/morridm/drumlights/blob/master/lib/patterns/PixelDrumPatterns.h

#include <Button.h> //https://github.com/JChristensen/Button

static const int LED_STRIP_PIN_NUMBER = 4;     // The digital pin # for the neopixel output
static const int PIEZO_ANALOG_INPUT_PIN = 0;   // The analog alias pin # to the piezo input on PIEZO_DIGITAL_INPUT_PIN
static const int PIEZO_DIGITAL_INPUT_PIN = 14; // The digital pin # for the piezo input
static const int POTENTIOMETER_PIN = A1;
static const int PUSH_BUTTON_PIN = 12;

static const struct DrumComponent SNARE = {0, 65, 7, 0, LED_STRIP_PIN_NUMBER, PIEZO_ANALOG_INPUT_PIN, PIEZO_DIGITAL_INPUT_PIN, POTENTIOMETER_PIN, PUSH_BUTTON_PIN, NEO_GRB + NEO_KHZ800};
static const struct DrumComponent HI_TOM = {1, 50, 7, 0, LED_STRIP_PIN_NUMBER, PIEZO_ANALOG_INPUT_PIN, PIEZO_DIGITAL_INPUT_PIN, POTENTIOMETER_PIN, PUSH_BUTTON_PIN, NEO_GRB + NEO_KHZ800};
static const struct DrumComponent MIDDLE_TOM = {2, 65, 7, 0, LED_STRIP_PIN_NUMBER, PIEZO_ANALOG_INPUT_PIN, PIEZO_DIGITAL_INPUT_PIN, POTENTIOMETER_PIN, PUSH_BUTTON_PIN, NEO_GRB + NEO_KHZ800};
static const struct DrumComponent FLOOR_TOM = {3, 81, 7, 0, LED_STRIP_PIN_NUMBER, PIEZO_ANALOG_INPUT_PIN, PIEZO_DIGITAL_INPUT_PIN, POTENTIOMETER_PIN, PUSH_BUTTON_PIN, NEO_GRB + NEO_KHZ800};

static const struct DrumComponent KICK = {4, 106, 8, 0, LED_STRIP_PIN_NUMBER, PIEZO_ANALOG_INPUT_PIN, PIEZO_DIGITAL_INPUT_PIN, POTENTIOMETER_PIN, PUSH_BUTTON_PIN, NEO_GRB + NEO_KHZ800};

static const struct DrumComponent THIS_DRUM_COMPONENT = SNARE;

boolean PULLUP = true; //To keep things simple, we use the Arduino's internal pullup resistor.
boolean INVERT = true;
static const int DEBOUNCE_MS = 20;   //A debounce time of 20 milliseconds usually works well for tactile button switches.
static const int REPEAT_FIRST = 500; //ms required before repeating on long press
static const int REPEAT_INCR = 100;  //repeat interval for long press
static const int MIN_COUNT = 0;
static const int MAX_COUNT = 59;
Button btnUP(PUSH_BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);
enum
{
    WAIT,
    PRESSED,
    HELD,
    RELEASED
};                                //The possible states for the state machine
uint8_t STATE;                    //The current state machine state
int count;                        //The number that is adjusted
int lastCount = -1;               //Previous value of count (initialized to ensure it's different when the sketch starts)
unsigned long rpt = REPEAT_FIRST; //A variable time that is used to drive the repeats for long presses

void animationComplete();

DrumPatterns strip(THIS_DRUM_COMPONENT, &animationComplete);

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

bool wasButtonPressed()
{

    static bool oldState = HIGH;

    bool bReturn = false;

    // Get current button state.
    bool newState = digitalRead(PUSH_BUTTON_PIN);

    // Check if state changed from high to low (button press).
    if (newState == LOW && oldState == HIGH)
    {

        // Short delay to debounce button.
        delay(20);

        // Check if button is still low after debounce.
        newState = digitalRead(PUSH_BUTTON_PIN);

        if (newState == LOW)
        {
            bReturn = true;
        }
    }

    // Set the last button state to the old state.
    oldState = newState;

    return bReturn;
}

void setup()
{

    strip.begin();
    strip.setBrightness(255);

    strip.Scanner(strip.Color(0, 0, 255), 45);
    strip.ColorWipe(strip.Color(0, 0, 255), 30);

    strip.ActivePattern = DRUMBEAT;

    pinMode(PIEZO_DIGITAL_INPUT_PIN, INPUT);
    pinMode(PUSH_BUTTON_PIN, INPUT_PULLUP);

    strip.clearStrip();
    strip.colorWipeAnimation(strip.Color(0, 30, 0), 10); //show green color wipe to indicate it is ready to go
    strip.clearStrip();
}

void loop()
{

    static boolean brightnessWasAdjusted = false;

    if (!brightnessWasAdjusted)
    {
        strip.Update();
    }

    ANIMATION currentPattern = strip.ActivePattern;

    if (STATE == RELEASED && !brightnessWasAdjusted)
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
        case SCANNER:
            strip.ActivePattern = COLOR_WIPE;
            currentPattern = strip.ActivePattern;
            strip.clearStrip();
            strip.colorWipeAnimation(strip.Color(255, 75, 0), 10); //show green color wipe to indicate it is ready to go
            break;
        case COLOR_WIPE:
            strip.ActivePattern = DRUMBEAT;
            strip.TotalSteps = 255;
            currentPattern = strip.ActivePattern;
            strip.clearStrip();
            strip.colorWipeAnimation(strip.Color(0, 30, 0), 10); //show green color wipe to indicate it is ready to go
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

    btnUP.read();

    switch (STATE)
    {

    case WAIT: //wait for a button event
        if (btnUP.wasPressed())
        {
            STATE = PRESSED;
        }
        else if (btnUP.wasReleased())
        {
            STATE = RELEASED;
            rpt = REPEAT_FIRST;
        }
        else if (btnUP.pressedFor(rpt))
        {                       //check for long press
            rpt += REPEAT_INCR; //increment the long press interval
            STATE = HELD;
        }
        break;
    case HELD:
        strip.adjustBrightness();
        brightnessWasAdjusted = true;
        rpt += REPEAT_INCR; //increment the long press interval
        STATE = WAIT;
        break;
    case RELEASED:
        STATE = WAIT;
        brightnessWasAdjusted = false;
        break;
    case PRESSED:
        STATE = WAIT;
        break;
    }

    strip.showStrip();
}
