#include <Adafruit_NeoPixel.h>
#include <DrumBean.h>
#include <AnimationPatterns.h>
#include <Direction.h>
#include <DrumType.h>

// NeoPattern Class - derived from the Adafruit_NeoPixel class
class DrumPatterns : public Adafruit_NeoPixel
{
public:
  struct DrumComponent myDrumComponent;

  // Member Variables:
  ANIMATION previousPattern;
  ANIMATION ActivePattern; // which pattern is running
  direction Direction;   // direction to run the pattern

  boolean bIsChaseSignal = true;
  boolean bForcingDrumBeat = false;

  unsigned long elapsedTimeInMilliSeconds = 0;
  unsigned long Interval = 0;   // milliseconds between updates
  unsigned long lastUpdate = 0; // last update of position

  uint32_t Color1, Color2; // What colors are in use
  uint16_t TotalSteps;     // total number of steps in the pattern
  uint16_t Index;          // current step within the pattern

  void (*OnComplete)(); // Callback on completion of pattern

  // Constructor - calls base-class constructor to initialize strip
  DrumPatterns(DrumComponent dc, void (*callback)()) : Adafruit_NeoPixel(dc.numPixelsOnDrum, dc.NEOPIXEL_STRIP_SIGNAL_PIN, dc.strip_type)
  {
    OnComplete = callback;
    myDrumComponent = dc;
  }

  void setDrumComponent(DrumComponent dc)
  {
    myDrumComponent = dc;
  }

  DrumComponent getDrumComponent(DrumComponent dc)
  {
    return dc;
  }

  void setChaseSignal(boolean b)
  {
    bIsChaseSignal = b;
  }

  // Update the pattern
  void Update()
  {

    ANIMATION p = ActivePattern;

    setChaseSignal(isChaseSignal());
    if (!bForcingDrumBeat && bIsChaseSignal && p != DRUMBEAT)
    {
      bForcingDrumBeat = true;
      previousPattern = p;
      Interval = 200;
      clearStrip();
    }

    if (bForcingDrumBeat)
    {
      DrumBeatUpdate();
    }

    elapsedTimeInMilliSeconds = (millis() - lastUpdate);

    if (elapsedTimeInMilliSeconds > Interval)
    {

      bForcingDrumBeat = false;

      lastUpdate = millis();

      switch (p)
      {
      case RAINBOW_CYCLE:
        Interval = 15;
        RainbowCycleUpdate();
        break;
      case COLOR_WIPE:
        ColorWipeUpdate();
        Interval = 25;
        break;
      case SCANNER:
        Interval = 25;
        ScannerUpdate();
        break;
      case DRUMBEAT:
        Interval = 0;
        DrumBeatUpdate();
        break;
      default:
        Interval = 0;
        DrumBeatUpdate();
        break;
      }
    }
  }

  void fadeInAndOut(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait)
  {

    for (uint8_t b = 0; b < 255; b++)
    {
      for (uint8_t i = 0; i < numPixels(); i++)
      {
        setPixelColor(i, red * b / 255, green * b / 255, blue * b / 255);
      }
      show();
      delay(wait);
    };

    for (uint8_t b = 255; b > 0; b--)
    {
      for (uint8_t i = 0; i < numPixels(); i++)
      {
        setPixelColor(i, red * b / 255, green * b / 255, blue * b / 255);
      }
      show();
      delay(wait);
    };
  };

  // Increment the Index and reset at the end
  void Increment()
  {
    if (Direction == FORWARD)
    {
      Index++;
      if (Index >= TotalSteps)
      {
        Index = 0;
        if (OnComplete != NULL)
        {
          OnComplete(); // call the comlpetion callback
        }
      }
    }
    else // Direction == REVERSE
    {
      --Index;
      if (Index <= 0)
      {
        Index = TotalSteps - 1;
        if (OnComplete != NULL)
        {
          OnComplete(); // call the comlpetion callback
        }
      }
    }
  }

  // Reverse pattern direction
  void Reverse()
  {
    if (Direction == FORWARD)
    {
      Direction = REVERSE;
      Index = TotalSteps - 1;
    }
    else
    {
      Direction = FORWARD;
      Index = 0;
    }
  }

  // Initialize for a RainbowCycle
  void RainbowCycle(uint8_t interval, direction dir = FORWARD)
  {
    ActivePattern = RAINBOW_CYCLE;
    Interval = interval;
    TotalSteps = 255;
    Index = 0;
    Direction = dir;
  }

  float mapf(long x, long in_min, long in_max, long out_min, long out_max)
  {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }

  // Update the Rainbow Cycle Pattern
  void RainbowCycleUpdate()
  {

    for (uint16_t i = 0; i < numPixels(); i++)
    {
      setPixelColor(i, Wheel(((i * 256 / numPixels()) + Index) & 255));
    }

    Increment();
  }

  // Initialize for a ColorWipe
  void ColorWipe(uint32_t color, uint8_t interval, direction dir = FORWARD)
  {
    ActivePattern = COLOR_WIPE;
    Interval = interval;
    TotalSteps = numPixels();
    Color1 = color;
    Index = 0;
    Direction = dir;
  }

  // Update the Color Wipe Pattern
  void ColorWipeUpdate()
  {
    setPixelColor(Index, Color1);
    show();
    Increment();
  }

  // Initialize for a SCANNNER
  void Scanner(uint32_t color1, uint8_t interval)
  {
    ActivePattern = SCANNER;
    Interval = interval;
    TotalSteps = (numPixels() - 1) * 2;
    Color1 = color1;
    Index = 0;
  }

  // Update the Scanner Pattern
  void ScannerUpdate()
  {
    for (uint16_t i = 0; i < numPixels(); i++)
    {
      if (i == Index) // Scan Pixel to the right
      {
        setPixelColor(i, Color1);
      }
      else if (i == TotalSteps - Index) // Scan Pixel to the left
      {
        setPixelColor(i, Color1);
      }
      else // Fading tail
      {
        setPixelColor(i, DimColor(getPixelColor(i)));
      }
    }
    show();
    Increment();
  }

  // Calculate 50% dimmed version of a color (used by ScannerUpdate)
  uint32_t DimColor(uint32_t color)
  {
    // Shift R, G and B components one bit to the right
    uint32_t dimColor = Color(Red(color) >> 1, Green(color) >> 1, Blue(color) >> 1);
    return dimColor;
  }

  // Returns the Red component of a 32-bit color
  uint8_t Red(uint32_t color)
  {
    return (color >> 16) & 0xFF;
  }

  // Returns the Green component of a 32-bit color
  uint8_t Green(uint32_t color)
  {
    return (color >> 8) & 0xFF;
  }

  // Returns the Blue component of a 32-bit color
  uint8_t Blue(uint32_t color)
  {
    return color & 0xFF;
  }

  // Input a value 0 to 255 to get a color value.
  // The colours are a transition r - g - b - back to r.
  uint32_t Wheel(byte WheelPos)
  {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
      return Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    else if (WheelPos < 170)
    {
      WheelPos -= 85;
      return Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    else
    {
      WheelPos -= 170;
      return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
  }

  //begin custom code
  void setCurrentPiezoThreshold(uint16_t t)
  {
    myDrumComponent.currentPiezoThreshold = t;
  }

  uint16_t getCurrentThresholdFromPiezo()
  {
    return analogRead(myDrumComponent.PIEZO_ANALOG_INPUT_PIN);
  }

  void setPixel(int Pixel, uint32_t color)
  {
    setPixelColor(Pixel, color);
  }

  void setPixel(int Pixel, byte red, byte green, byte blue)
  {
    setPixel(Pixel, Color(red, green, blue));
  }

  // Input a value 0 to 255 to get a color value.
  // The colours are a transition r - g - b - back to r.
  // This function adapted from Adafruit's demo code to add intensity.

  uint32_t Wheel(int pixel, float intensity)
  {
    static byte numLoops = 0;

    byte WheelPos = numLoops;

    byte red = 0;
    byte green = 0;
    byte blue = 0;

    WheelPos = (255 - WheelPos);

    if (WheelPos < 85)
    {

      red = (255 - WheelPos * 3) * intensity;
      green = 0;
      blue = (WheelPos * 3) * intensity;
    }
    else if (WheelPos < 170)
    {

      WheelPos -= 85;

      red = 0;
      green = (WheelPos * 3) * intensity;
      blue = (255 - WheelPos * 3) * intensity;
    }
    else
    {

      WheelPos -= 170;

      red = (WheelPos * 3) * intensity;
      green = (255 - WheelPos * 3) * intensity;
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

    red = constrain(red, 0, 255);
    green = constrain(green, 0, 255);
    blue = constrain(blue, 0, 255);

    return Color(red, green, blue);
  }

  void DrumBeatUpdate()
  {

    int pixel = 0;
    uint32_t color = Color(0, 0, 0);

    for (int i = numPixels(); i > 0; i--)
    {
      setPixel(i, getPixelColor(i - 1));
    }

    if (isChaseSignal())
    {
      float sensorValue = (float)map((analogRead(myDrumComponent.PIEZO_ANALOG_INPUT_PIN) / 1023.0 * 5.0), 0, 1023, 1, 255);
      color = Wheel(pixel, sensorValue);
    }

    setPixel(pixel, color);
  }

  void showStrip()
  {
    show();
  }

  void colorWipeAnimation(uint32_t stripColorValue, uint8_t wait)
  {

    for (uint16_t i = 0; i < numPixels(); i++)
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

  void colorWipe(uint32_t c, uint8_t wait)
  {
    ColorWipe(c, wait, FORWARD);
  }

  void clearStrip()
  {
    clear();
  }

  boolean isChaseSignal()
  {

    setCurrentPiezoThreshold(getCurrentThresholdFromPiezo());

    uint16_t potValue = constrain(map(int(analogRead(myDrumComponent.POT_PIN)), 0, 1023, int(myDrumComponent.minimumRequiredPiezoThreshold), 85), 0, 85);

    if (myDrumComponent.currentPiezoThreshold > potValue)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  //end custom code
};
