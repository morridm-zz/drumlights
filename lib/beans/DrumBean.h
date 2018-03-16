struct DrumComponent
{
  byte id;
  byte numPixelsOnDrum;
  uint16_t minimumRequiredPiezoThreshold;
  uint16_t currentPiezoThreshold;
  int ledStripPinNumber;
  int piezoAnalogPinNumber;
  int piezoDigitalPinNumber;
  int potentiometerPinNumber;
  int buttonPinNumber;
  uint8_t strip_type;
};

