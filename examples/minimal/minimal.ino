/****************************************************************************************************************************
   minimal.ino
   Arduino AVR, Teensy, SAM-DUE, SAMD21/SAMD51, STM32F/L/H/G/WB/MP1, nRF52, etc. boards

   MultiResetDetector_Generic is a library for the Arduino AVR, Teensy, SAM-DUE, SAMD, STM32, nRF52, etc. boards
   to enable trigger configure mode by resetting the boards twice within configurable timeout seconds.
   
   1) DataCute    https://github.com/datacute/DoubleResetDetector
   2) Khoi Hoang  https://github.com/khoih-prog/ESP_DoubleResetDetector
   3) Khoi Hoang  https://github.com/khoih-prog/ESP_MultiResetDetector
   4) Khoi Hoang  https://github.com/khoih-prog/DoubleResetDetector_Generic

   Built by Khoi Hoang https://github.com/khoih-prog/MultiResetDetector_Generic
   Licensed under MIT license
   Version: 1.0.3

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
   1.0.3   K Hoang      30/12/2020 Initial coding to support Multiple Reset Detection. Sync with DoubleResetDetector_Generic v1.0.3
 *****************************************************************************************************************************/
/****************************************************************************************************************************
   This example will open a configuration portal when the reset button is pressed twice.
   This method works well on Wemos boards which have a single reset button on board. It avoids using a pin for launching the configuration portal.

   How It Works
   1) AVR Mega, Teensy, STM32
   Save data in EPPROM from address 1020, size 1024 bytes (both configurable)
   Note: Teensy 4.0 has only 1080 bytes of EEPROM-simulated Flash
   2) SAMD
   Save data in EEPROM-simulated FlashStorage from address 1020 (configurable to avoid conflict)
   3) SAM DUE
   Save data in DueFlashStorage from address 1020 (configurable to avoid conflict)
   3) Adafruit nRF52-based boards
   Save data in InternalFS, fle "/mrd.dat" location 0

   So when the device starts up it checks the InternalFS file "/mrd.dat", EEPROM or (Due)FlashStorage for a flag to see if it has been
   recently reset within the configurable timeout seconds
   It'll then set a flag, and display a message to signal if the DR is detected

   Settings
   There are values to be set in the sketch.

   MRD_TIMES   - Number of subsequent resets during MRD_TIMEOUT to activate
   MRD_TIMEOUT - Number of seconds to wait for the second reset. Set to 10 in the example.
   MRD_ADDRESS - The address in ESP8266 RTC RAM/EEPROM address to store the flag. Must not be used in the same sketch

   This example, originally relied on the Double Reset Detector library from https://github.com/datacute/DoubleResetDetector
   To support ESP32, use ESP_DoubleResetDetector library from https://github.com/khoih-prog/ESP_DoubleResetDetector
   To support AVR, Teensy, SAM DUE, SAMD and STM32, etc., use this MultiResetDetector_Generic from //https://github.com/khoih-prog/MultiResetDetector_Generic
 *****************************************************************************************************************************/

#define MRD_GENERIC_DEBUG       true  //false

// These definitions must be placed before #include <MultiResetDetector_Generic.h> to be used
// Otherwise, default values (MRD_TIMES = 3, MRD_TIMEOUT = 10 seconds and MRD_ADDRESS = 0) will be used
// Number of subsequent resets during MRD_TIMEOUT to activate
#define MRD_TIMES               5

// Number of seconds after reset during which a 
// subsequent reset will be considered a multi reset.
#define MRD_TIMEOUT             10

// RTC/EEPROM Memory Address for the MultiResetDetector to use
#define MRD_ADDRESS             0

#include <MultiResetDetector_Generic.h>

MultiResetDetector_Generic* mrd;

#ifndef LED_BUILTIN
#define LED_BUILTIN       13
#endif

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println(F("MultiResetDetector minimal Example Program"));
  Serial.println(MULTIRESETDETECTOR_GENERIC_VERSION);
  Serial.println(F("-----------------------------------"));

  mrd = new MultiResetDetector_Generic(MRD_TIMEOUT, MRD_ADDRESS);

  if (mrd->detectMultiReset()) 
  {
    Serial.println(F("Multi Reset Detected"));
    digitalWrite(LED_BUILTIN, LOW);
  } 
  else 
  {
    Serial.println(F("No Multi Reset Detected"));
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

void loop()
{
  // Call the multi reset detector loop method every so often,
  // so that it can recognise when the timeout expires.
  // You can also call mrd.stop() when you wish to no longer
  // consider the next reset as a multi reset.
  mrd->loop();
}
