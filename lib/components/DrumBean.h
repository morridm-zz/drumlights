typedef struct DrumComponent
{
  byte id;
  byte numPixelsOnDrum;
  uint16_t minimumRequiredPiezoThreshold;
  uint16_t currentPiezoThreshold;
  int NEOPIXEL_STRIP_SIGNAL_PIN;
  int PIEZO_ANALOG_INPUT_PIN;
  int PIEZO_DIGITAL_INPUT_PIN;
  int POT_PIN;  
};