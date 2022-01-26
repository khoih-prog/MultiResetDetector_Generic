/***********************************************************************************************************************************
  MultiResetDetector_Generic.h
  Arduino AVR, Teensy, SAM-DUE, SAMD21/SAMD51, STM32F/L/H/G/WB/MP1, nRF52, RASPBERRY_PI_PICO, etc. boards

  MultiResetDetector_Generic is a library for the Arduino AVR, Teensy, SAM-DUE, SAMD, STM32, nRF52, RASPBERRY_PI_PICO, etc. boards
  to enable trigger configure mode by resetting the boards twice within configurable timeout seconds.

  1) DataCute    https://github.com/datacute/DoubleResetDetector
  2) Khoi Hoang  https://github.com/khoih-prog/ESP_DoubleResetDetector
  3) Khoi Hoang  https://github.com/khoih-prog/ESP_MultiResetDetector
  4) Khoi Hoang  https://github.com/khoih-prog/DoubleResetDetector_Generic

  Built by Khoi Hoang https://github.com/khoih-prog/MultiResetDetector_Generic
  Licensed under MIT license
  
  Version: 1.8.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.3   K Hoang      30/12/2020 Initial coding to support Multiple Reset Detection. Sync with DoubleResetDetector_Generic v1.0.3
  1.1.0   K Hoang      27/04/2021 Use new FlashStorage_STM32 library. Add support to new STM32 core v2.0.0 and STM32L5
  1.2.0   K Hoang      12/05/2021 Add support to RASPBERRY_PI_PICO using Arduino-pico core
  1.3.0   K Hoang      28/05/2021 Add support to Nano_RP2040_Connect, RASPBERRY_PI_PICO using RP2040 Arduino mbed core
  1.4.0   K Hoang      05/06/2021 Permit more control over LittleFS for RP2040 Arduino mbed core
  1.5.0   K Hoang      07/08/2021 Add support to RTL8720DN, etc. using AmebaD core
  1.6.0   K Hoang      29/08/2021 Add support to MBED Nano_33_BLE, Nano_33_BLE_Sense, etc. using LittleFS
  1.7.0   K Hoang      10/09/2021 Add support to MBED Portenta_H7 using LittleFS
  1.7.1   K Hoang      13/09/2021 Select fix LittleFS size of 1024KB
  1.7.2   K Hoang      14/09/2021 Back to using auto LittleFS to fix bug
  1.7.3   K Hoang      10/10/2021 Update `platform.ini` and `library.json`
  1.8.0   K Hoang      26/01/2022 Update to be compatible with new FlashStorage libraries. Add support to more SAMD/STM32 boards
 ************************************************************************************************************************************/

#pragma once

#ifndef MultiResetDetector_Generic_H
#define MultiResetDetector_Generic_H

#ifndef MULTIRESETDETECTOR_GENERIC_VERSION
  #define MULTIRESETDETECTOR_GENERIC_VERSION            "MultiResetDetector_Generic v1.8.0"

  #define MULTIRESETDETECTOR_GENERIC_VERSION_MAJOR      1
  #define MULTIRESETDETECTOR_GENERIC_VERSION_MINOR      8
  #define MULTIRESETDETECTOR_GENERIC_VERSION_PATCH      0

#define MULTIRESETDETECTOR_GENERIC_VERSION_INT        1008000

#endif

#if ( defined(ESP32) || defined(ESP8266) )
  #error Please use ESP_MultiResetDetector library (https://github.com/khoih-prog/ESP_MultiResetDetector) for ESP8266 and ESP32!
#endif

// For AVR, Teensy, STM32 boards, use EEPROM
// For SAM DUE, use DueFlashStorage. For SAMD, use FlashStorage_SAMD

#define  MRD_FILENAME     "/mrd.dat"
#define  MRD_FLAG_OFFSET  0

#if defined(ARDUINO) && (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#define MRD_GENERIC_USE_EEPROM      true

///////////////////////////// 

#define MRD_GENERIC_USE_SAM_DUE     false
#define MRD_GENERIC_USE_SAMD        false
#define MRD_GENERIC_USE_STM32       false
#define MRD_GENERIC_USE_NRF52       false
#define MRD_GENERIC_USE_RP2040      false
#define MRD_GENERIC_USE_MBED_RP2040 false
#define MRD_GENERIC_USE_NANO33BLE   false
#define MRD_GENERIC_USE_RTL8720     false
#define MRD_GENERIC_USE_PORTENTA    false

/////////////////////////////
#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(MRD_GENERIC_USE_SAM_DUE)
    #undef MRD_GENERIC_USE_SAM_DUE
  #endif
  #define MRD_GENERIC_USE_SAM_DUE     true
  #if defined(MRD_GENERIC_USE_EEPROM)
    #undef MRD_GENERIC_USE_EEPROM
  #endif
  #define MRD_GENERIC_USE_EEPROM    false
  #warning Use SAM-DUE and DueFlashStorage
  
/////////////////////////////  
#elif ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD51__) || defined(__SAMD51J20A__) \
      || defined(__SAMD51J19A__) || defined(__SAMD51G19A__) || defined(__SAMD51P19A__)  \
      || defined(__SAMD21E15A__) || defined(__SAMD21E16A__) || defined(__SAMD21E17A__) || defined(__SAMD21E18A__) \
      || defined(__SAMD21G15A__) || defined(__SAMD21G16A__) || defined(__SAMD21G17A__) || defined(__SAMD21G18A__) \
      || defined(__SAMD21J15A__) || defined(__SAMD21J16A__) || defined(__SAMD21J17A__) || defined(__SAMD21J18A__) )
  #if defined(MRD_GENERIC_USE_SAMD)
    #undef MRD_GENERIC_USE_SAMD
  #endif
  #define MRD_GENERIC_USE_SAMD      true
  #if defined(MRD_GENERIC_USE_EEPROM)
    #undef MRD_GENERIC_USE_EEPROM
  #endif
  #define MRD_GENERIC_USE_EEPROM    false
  #warning Use SAMD and FlashStorage

///////////////////////////// 
#elif ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
        defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
        defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) | defined(NINA_B302_ublox) ) && \
        ! ( defined(ARDUINO_ARCH_MBED) )

  #if defined(MRD_GENERIC_USE_NRF52)
    #undef MRD_GENERIC_USE_NRF52
  #endif
  #define MRD_GENERIC_USE_NRF52      true
  #if defined(MRD_GENERIC_USE_EEPROM)
    #undef MRD_GENERIC_USE_EEPROM
  #endif
  #define MRD_GENERIC_USE_EEPROM    false
  #warning Use NRF52 and LittleFS / InternalFS

/////////////////////////////
#elif ( defined(ARDUINO_ARCH_RP2040) && !defined(ARDUINO_ARCH_MBED) )

  #if defined(MRD_GENERIC_USE_RP2040)
    #undef MRD_GENERIC_USE_RP2040
  #endif
  #define MRD_GENERIC_USE_RP2040      true
  
  #if defined(MRD_GENERIC_USE_EEPROM)
    #undef MRD_GENERIC_USE_EEPROM
  #endif
  #define MRD_GENERIC_USE_EEPROM    false
  
  #warning Use RP2040 (such as RASPBERRY_PI_PICO) and LittleFS

/////////////////////////////
#elif ( defined(ARDUINO_ARCH_RP2040) && defined(ARDUINO_ARCH_MBED) )

  // For Arduino' arduino-mbed core
  // To check and determine if we need to init LittleFS here
  #if MBED_RP2040_INITIALIZED
    #define MRD_MBED_LITTLEFS_NEED_INIT     false
    #warning MBED_RP2040_INITIALIZED in another place
  #else
    // Better to delay until init done
    #if defined(MBED_RP2040_INITIALIZED)
      #undef MBED_RP2040_INITIALIZED
    #endif
    #define MBED_RP2040_INITIALIZED           true
    
    #define MRD_MBED_LITTLEFS_NEED_INIT     true
  #endif
  
  #if defined(MRD_GENERIC_USE_MBED_RP2040)
    #undef MRD_GENERIC_USE_MBED_RP2040
  #endif
  #define MRD_GENERIC_USE_MBED_RP2040      true
  
  #if defined(MRD_GENERIC_USE_EEPROM)
    #undef MRD_GENERIC_USE_EEPROM
  #endif
  #define MRD_GENERIC_USE_EEPROM    false
  
  #warning Use MBED RP2040 (such as NANO_RP2040_CONNECT, RASPBERRY_PI_PICO) and LittleFS

///////////////////////////// 
#elif ( ( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) ) && defined(ARDUINO_ARCH_MBED) )

  #if defined(BOARD_NAME)
    #undef BOARD_NAME
  #endif

  #if defined(CORE_CM7)
    #warning Using Portenta H7 M7 core
    #define BOARD_NAME              "PORTENTA_H7_M7"
  #else
    #warning Using Portenta H7 M4 core
    #define BOARD_NAME              "PORTENTA_H7_M4"
  #endif
  
  // For Arduino' arduino-mbed core
  // To check and determine if we need to init LittleFS here
  #if MBED_PORTENTA_H7_INITIALIZED
    #define MRD_MBED_LITTLEFS_NEED_INIT     false
    #warning MBED_PORTENTA_H7_INITIALIZED in another place
  #else
    // Better to delay until init done
    #if defined(MBED_PORTENTA_H7_INITIALIZED)
      #undef MBED_PORTENTA_H7_INITIALIZED
    #endif
    #define MBED_PORTENTA_H7_INITIALIZED          true
    
    #define MRD_PORTENTA_LITTLEFS_NEED_INIT       true
  #endif
  
  #if defined(MRD_GENERIC_USE_MBED_PORTENTA)
    #undef MRD_GENERIC_USE_MBED_PORTENTA
  #endif
  #define MRD_GENERIC_USE_MBED_PORTENTA           true
   
  #if defined(MRD_GENERIC_USE_EEPROM)
    #undef MRD_GENERIC_USE_EEPROM
  #endif
  #define MRD_GENERIC_USE_EEPROM    false
  
  #warning Use MBED PORTENTA_H7 and LittleFS
  
///////////////////////////// 
#elif ( defined(ARDUINO_ARCH_NRF52840) && defined(ARDUINO_ARCH_MBED) && defined(ARDUINO_ARDUINO_NANO33BLE) )

  // For Arduino' arduino-mbed core
  // To check and determine if we need to init LittleFS here
  #if NANO33BLE_INITIALIZED
    #define MRD_NANO33BLE_NEED_INIT     false
    #warning NANO33BLE_INITIALIZED in another place
  #else
    // Better to delay until init done
    #if defined(NANO33BLE_INITIALIZED)
      #undef NANO33BLE_INITIALIZED
    #endif
    #define NANO33BLE_INITIALIZED           true
    
    #define MRD_NANO33BLE_NEED_INIT     true
  #endif
  
  #if defined(MRD_GENERIC_USE_NANO33BLE)
    #undef MRD_GENERIC_USE_NANO33BLE
  #endif
  #define MRD_GENERIC_USE_NANO33BLE      true
  
  #if defined(MRD_GENERIC_USE_EEPROM)
    #undef MRD_GENERIC_USE_EEPROM
  #endif
  #define MRD_GENERIC_USE_EEPROM    false
  
  #warning Use MBED nRF52840 (such as Nano_33_BLE, Nano_33_BLE_Sense) and LittleFS
  
/////////////////////////////  
#elif ( defined(STM32F0) || defined(STM32F1)  || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
        defined(STM32L0) || defined(STM32L1)  || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
        defined(STM32WB) || defined(STM32MP1) || defined(STM32L5) )
  #if defined(MRD_GENERIC_USE_STM32)
    #undef MRD_GENERIC_USE_STM32
  #endif
  #define MRD_GENERIC_USE_STM32      true
  #if defined(MRD_GENERIC_USE_EEPROM)
    #undef MRD_GENERIC_USE_EEPROM
  #endif
  #define MRD_GENERIC_USE_EEPROM    false
  #warning Use STM32 and FlashStorage_STM32

/////////////////////////////
#elif defined(CONFIG_PLATFORM_8721D)

  #if defined(MRD_GENERIC_USE_RTL8720)
    #undef MRD_GENERIC_USE_RTL8720
  #endif
  #define MRD_GENERIC_USE_RTL8720      true
  #if defined(MRD_GENERIC_USE_EEPROM)
    #undef MRD_GENERIC_USE_EEPROM
  #endif
  #define MRD_GENERIC_USE_EEPROM    false
  #warning Use RTL8720 and FlashStorage_RTL8720
  
/////////////////////////////  
#else
  #if defined(CORE_TEENSY)
    #warning Use TEENSY and EEPROM
  #elif ( defined(ARDUINO_AVR_ADK) || defined(ARDUINO_AVR_BT) || defined(ARDUINO_AVR_DUEMILANOVE) || defined(ARDUINO_AVR_ESPLORA) \
      || defined(ARDUINO_AVR_ETHERNET) || defined(ARDUINO_AVR_FIO) || defined(ARDUINO_AVR_GEMMA) || defined(ARDUINO_AVR_LEONARDO) \
      || defined(ARDUINO_AVR_LILYPAD) || defined(ARDUINO_AVR_LILYPAD_USB) || defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560) \
      || defined(ARDUINO_AVR_MICRO) || defined(ARDUINO_AVR_MINI) || defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_NG) \
      || defined(ARDUINO_AVR_PRO) || defined(ARDUINO_AVR_ROBOT_CONTROL) || defined(ARDUINO_AVR_ROBOT_MOTOR) || defined(ARDUINO_AVR_UNO) \
      || defined(ARDUINO_AVR_YUN) )        
    #warning Use AVR and EEPROM
  #else
    #warning Use Unknown board and EEPROM
  #endif  
#endif

/////////////////////////////
 
//default to use EEPROM, otherwise, use DueFlashStorage or FlashStorage_SAMD
/////////////////////////////
#if MRD_GENERIC_USE_EEPROM
  #include <EEPROM.h>

  #define  FLAG_DATA_SIZE     4

  #ifndef MRD_EEPROM_SIZE
    // Please change according to your application to avoid overwriting or being overwritten
    #define MRD_EEPROM_SIZE     (E2END + 1)
  #endif

/////////////////////////////
#elif MRD_GENERIC_USE_SAMD
  // Include EEPROM-like API for FlashStorage
  #include <FlashStorage_SAMD.h>             //https://github.com/khoih-prog/FlashStorage_SAMD

/////////////////////////////  
#elif MRD_GENERIC_USE_SAM_DUE
  //Use DueFlashStorage to simulate EEPROM
  #include <DueFlashStorage.h>                 //https://github.com/sebnil/DueFlashStorage
  DueFlashStorage dueFlashStorage;

/////////////////////////////  
#elif MRD_GENERIC_USE_NRF52
  // Include LittleFS similar to SPIFFS
  #include <Adafruit_LittleFS.h>
  #include <InternalFileSystem.h>
  using namespace Adafruit_LittleFS_Namespace;
  
  File MRD_file(InternalFS);

/////////////////////////////
#elif MRD_GENERIC_USE_RP2040

  //Use LittleFS for RPI Pico
  #include <FS.h>
  #include <LittleFS.h>

  FS* filesystem =      &LittleFS;
  #define FileFS        LittleFS
  
/////////////////////////////
#elif (MRD_GENERIC_USE_MBED_RP2040 && MRD_MBED_LITTLEFS_NEED_INIT)

  //Use LittleFS for MBED RPI Pico
  #include "FlashIAPBlockDevice.h"
  #include "LittleFileSystem.h"
  #include "mbed.h"

  #include <stdio.h>
  #include <errno.h>
  #include <functional>

  #include "BlockDevice.h"

  #if !defined(RP2040_FLASH_SIZE)
    #define RP2040_FLASH_SIZE         (2 * 1024 * 1024)
  #endif

  #if !defined(RP2040_FS_LOCATION_END)
    #define RP2040_FS_LOCATION_END    RP2040_FLASH_SIZE
  #endif

  #if !defined(RP2040_FS_SIZE_KB)
    // Using default 64KB for LittleFS
    #define RP2040_FS_SIZE_KB       (64)
  #endif

  #if !defined(RP2040_FS_START)
    #define RP2040_FS_START           (RP2040_FLASH_SIZE - (RP2040_FS_SIZE_KB * 1024))
  #endif

  #if !defined(FORCE_REFORMAT)
    #define FORCE_REFORMAT            false
  #elif FORCE_REFORMAT
    #warning FORCE_REFORMAT enable. Are you sure ?
  #endif

  FlashIAPBlockDevice bd(XIP_BASE + RP2040_FS_START, (RP2040_FS_SIZE_KB * 1024));

  mbed::LittleFileSystem fs("fs");
  
  #if defined(MRD_FILENAME)
    #undef MRD_FILENAME
  #endif
  #define  MRD_FILENAME     "/fs/mrd.dat"  
  
  #warning MRD_MBED_LITTLEFS INITIALIZED locally in MultiResetDetector_Generic

/////////////////////////////
#elif (MRD_GENERIC_USE_MBED_PORTENTA && MRD_PORTENTA_LITTLEFS_NEED_INIT)

  //Use LittleFS for MBED Portenta
  #include "FlashIAPBlockDevice.h"
  #include "LittleFileSystem.h"
  #include "mbed.h"

  #include <stdio.h>
  #include <errno.h>
  #include <functional>

  #include "BlockDevice.h"
  
  #include "mbed_portenta/FlashIAPLimits.h"

  #if !defined(FORCE_REFORMAT)
    #define FORCE_REFORMAT            false
  #elif FORCE_REFORMAT
    #warning FORCE_REFORMAT enable. Are you sure ?
  #endif

  static FlashIAPBlockDevice* blockDevicePtr;

  mbed::LittleFileSystem fs("littlefs");
  
  struct FlashIAPLimits _flashIAPLimits;
  
  #if defined(MRD_FILENAME)
    #undef MRD_FILENAME
  #endif
  #define  MRD_FILENAME     "/littlefs/mrd.dat"
  
  #warning MRD_PORTENTA_LITTLEFS INITIALIZED locally in MultiResetDetector_Generic
  
/////////////////////////////
#elif (MRD_GENERIC_USE_NANO33BLE && MRD_NANO33BLE_NEED_INIT)

  //Use LittleFS for MBED Nano33BLE
  #include "FlashIAPBlockDevice.h"
  #include "LittleFileSystem.h"
  #include "mbed.h"

  #include <stdio.h>
  #include <errno.h>
  #include <functional>

  #include "BlockDevice.h"

  #if !defined(NANO33BLE_FLASH_SIZE)
    // Using max 512KB for FS
    #define NANO33BLE_FLASH_SIZE         (1 * 1024 * 1024)
  #endif

  #if !defined(NANO33BLE_FS_LOCATION_END)
    #define NANO33BLE_FS_LOCATION_END    NANO33BLE_FLASH_SIZE
  #endif

  #if !defined(NANO33BLE_FS_SIZE_KB)
    // Using default 64KB for FS
    #define NANO33BLE_FS_SIZE_KB       (64)
  #endif

  #if !defined(NANO33BLE_FS_START)
    #define NANO33BLE_FS_START           (NANO33BLE_FLASH_SIZE - (NANO33BLE_FS_SIZE_KB * 1024))
  #endif

  #if !defined(FORCE_REFORMAT)
    #define FORCE_REFORMAT            false
  #elif FORCE_REFORMAT
    #warning FORCE_REFORMAT enable. Are you sure ?
  #endif

  // nRF52840 flash address from 0, length 1MB.
  // Better to use max half of flash for LitleFS, must be 0x80000 (512KB)
  // FLASH_BASE must be 0x80000, or crash !!!????
  #define FLASH_BASE            0x80000

  FlashIAPBlockDevice wholeBD(FLASH_BASE, 0x80000);
  FlashIAPBlockDevice bd(FLASH_BASE, (NANO33BLE_FS_SIZE_KB * 1024));
  
  mbed::LittleFileSystem fs("littlefs");
  
  #if defined(MRD_FILENAME)
    #undef MRD_FILENAME
  #endif
  #define  MRD_FILENAME     "/littlefs/mrd.dat"
  
  #warning MRD_NANO33BLE_LITTLEFS INITIALIZED locally in MultiResetDetector_Generic
  
  
/////////////////////////////
#elif MRD_GENERIC_USE_STM32

/////////////////////////////////////////////
      
  #if defined(DATA_EEPROM_BASE)
      // For STM32 devices having integrated EEPROM.
      #include <EEPROM.h>
      #warning STM32 devices have integrated EEPROM. Not using buffered API.   
  #else
      /**
       Most STM32 devices don't have an integrated EEPROM. To emulate a EEPROM, the STM32 Arduino core emulated
       the operation of an EEPROM with the help of the embedded flash.
       Writing to a flash is very expensive operation, since a whole flash page needs to be written, even if you only
       want to access the flash byte-wise.
       The STM32 Arduino core provides a buffered access API to the emulated EEPROM. The library has allocated the
       buffer even if you don't use the buffered API, so it's strongly suggested to use the buffered API anyhow.
       */
      #if ( defined(STM32F1xx) || defined(STM32F3xx) )
        #include <FlashStorage_STM32F1.h>       // https://github.com/khoih-prog/FlashStorage_STM32
        #warning STM32F1/F3 devices have no integrated EEPROM. Using buffered API with FlashStorage_STM32F1 library
      #else
        #include <FlashStorage_STM32.h>       // https://github.com/khoih-prog/FlashStorage_STM32
        #warning STM32 devices have no integrated EEPROM. Using buffered API with FlashStorage_STM32 library
      #endif
  #endif    // #if defined(DATA_EEPROM_BASE)

  //////////////////////////////////////////////
 
#elif MRD_GENERIC_USE_RTL8720
  // Include FlashStorage API for FlashStorage_RTL8720
  #include <FlashStorage_RTL8720.h>             //https://github.com/khoih-prog/FlashStorage_RTL8720

///////////////////////////// 
   
#endif    //#if MRD_GENERIC_USE_EEPROM

#ifndef MRD_GENERIC_DEBUG
  #define MRD_GENERIC_DEBUG       false
#endif

///////////////////
// Default values if not specified in sketch

#ifndef MRD_TIMES
  #define MRD_TIMES         3
#endif

#ifndef MRD_TIMEOUT
  #define MRD_TIMEOUT       10
#endif

#ifndef MRD_ADDRESS
  #define MRD_ADDRESS       0
#endif

///////////////////

// Flag clear to 0xFFFE0001 if no MRD within MRD_TIMEOUT. Flag will increase 1 for each reset within MRD_TIMEOUT
// So MULTIRESETDETECTOR_FLAG_SET is not necessary.
// Will use upper 2 bytes to verify if corrupted data. 

#define USING_INVERTED    true

#if USING_INVERTED
  #define MULTIRESETDETECTOR_GENERIC_FLAG_BEGIN  0xFFFE0001     // Used when beginning a new cycle
  #define MULTIRESETDETECTOR_GENERIC_FLAG_CLEAR  0xFFFF0000     // Used when data corrupted, such as reformat LittleFS/SPIFFS
#else
  #define MULTIRESETDETECTOR_GENERIC_FLAG_BEGIN  0x00010001     // Used when beginning a new cycle
  #define MULTIRESETDETECTOR_GENERIC_FLAG_CLEAR  0x00000000     // Used when data corrupted, such as reformat LittleFS/SPIFFS
#endif

/////////////////////////////////////////////

class MultiResetDetector_Generic
{
  public:
  
    /////////////////////////////////////////////
    
    MultiResetDetector_Generic(unsigned long timeout, int address)
    {
      mrd_times = MRD_TIMES;
      
      this->timeout = timeout * 1000;
      this->MRD_EEPROM_START = address;
      multiResetDetected = false;
      waitingForMultiReset = false;

/////////////////////////////          
#if MRD_GENERIC_USE_EEPROM

      EEPROM.begin();
      
  #if (MRD_GENERIC_DEBUG)
      Serial.print(F("\nEEPROM size = "));
      Serial.print(MRD_EEPROM_SIZE);
      Serial.print(F(", start = "));
      Serial.println(MRD_EEPROM_START);
  #endif

/////////////////////////////
#elif (MRD_GENERIC_USE_STM32)

  #if defined(DATA_EEPROM_BASE)      
      EEPROM.begin();
  #endif   
      
  #if (MRD_GENERIC_DEBUG)
      Serial.print("\n(Emulated-)EEPROM size = ");
      Serial.print(EEPROM.length());
      Serial.print(", start = ");
      Serial.println(MRD_EEPROM_START);
  #endif

/////////////////////////////          
#elif MRD_GENERIC_USE_SAMD
      // Do something to init FlashStorage
      
/////////////////////////////      
#elif MRD_GENERIC_USE_SAM_DUE
      // Do something to init DueFlashStorage

/////////////////////////////      
#elif MRD_GENERIC_USE_NRF52
      // Do something to init LittleFS / InternalFS
      // Initialize Internal File System
      InternalFS.begin();
      
/////////////////////////////      
#elif MRD_GENERIC_USE_RP2040

      bool beginOK = FileFS.begin();

  #if (MRD_GENERIC_DEBUG)      
      if (!beginOK)
      {
        Serial.println("\nLittleFS error");
      }
  #endif
  
/////////////////////////////
#elif (MRD_GENERIC_USE_MBED_RP2040 && MRD_MBED_LITTLEFS_NEED_INIT)

      Serial.print("LittleFS size (KB) = ");
      Serial.println(RP2040_FS_SIZE_KB);

#if FORCE_REFORMAT
      fs.reformat(&bd);
#endif
      
      int err = fs.mount(&bd);
      
  #if (MRD_GENERIC_DEBUG) 
      Serial.println(err ? "LittleFS Mount Fail" : "LittleFS Mount OK");
  #endif
  
      if (err)
      {
  #if (MRD_GENERIC_DEBUG)     
        // Reformat if we can't mount the filesystem
        Serial.println("Formatting... ");
        Serial.flush();
  #endif
  
        err = fs.reformat(&bd);
      }
  
      bool beginOK = (err == 0);

  #if (MRD_GENERIC_DEBUG)      
      if (!beginOK)
      {
        Serial.println("\nLittleFS error");
      }
  #endif


/////////////////////////////
#elif (MRD_GENERIC_USE_MBED_PORTENTA && MRD_PORTENTA_LITTLEFS_NEED_INIT)

      // Get limits of the the internal flash of the microcontroller
      _flashIAPLimits = getFlashIAPLimits();
      
      Serial.print("Flash Size: (KB) = "); Serial.println(_flashIAPLimits.flash_size / 1024.0);
      Serial.print("FlashIAP Start Address: = 0x"); Serial.println(_flashIAPLimits.start_address, HEX);
      Serial.print("LittleFS size (KB) = "); Serial.println(_flashIAPLimits.available_size / 1024.0);
            
      blockDevicePtr = new FlashIAPBlockDevice(_flashIAPLimits.start_address, _flashIAPLimits.available_size);
      
      if (!blockDevicePtr)
      {
  #if (MRD_GENERIC_DEBUG)       
        Serial.println("Error init FlashIAPBlockDevice");
  #endif      
        return;
      }
      
  #if FORCE_REFORMAT
      fs.reformat(blockDevicePtr);
  #endif

      int err = fs.mount(blockDevicePtr);
      
  #if (MRD_GENERIC_DEBUG) 
      Serial.println(err ? "LittleFS Mount Fail" : "LittleFS Mount OK");
  #endif
  
      if (err)
      {
  #if (MRD_GENERIC_DEBUG)     
        // Reformat if we can't mount the filesystem
        Serial.println("Formatting... ");
  #endif
  
        err = fs.reformat(blockDevicePtr);
      }
  
      bool beginOK = (err == 0);

  #if (MRD_GENERIC_DEBUG)      
      if (!beginOK)
      {
        Serial.println("\nLittleFS error");
      }
  #endif

  
/////////////////////////////
#elif (MRD_GENERIC_USE_NANO33BLE && MRD_NANO33BLE_NEED_INIT)

      Serial.print("LittleFS size (KB) = ");
      Serial.println(NANO33BLE_FS_SIZE_KB);
  
#if FORCE_REFORMAT
      mbed::LittleFileSystem::format(&bd);
#endif  
      
      int err = fs.mount(&bd);
      
  #if (MRD_GENERIC_DEBUG) 
      Serial.println(err ? "LittleFS Mount Fail" : "LittleFS Mount OK");
  #endif
  
      if (err)
      {
  #if (MRD_GENERIC_DEBUG)     
        // Reformat if we can't mount the filesystem
        Serial.println("Formatting... ");
  #endif
  
        err = mbed::LittleFileSystem::format(&bd);
      }
  
      bool beginOK = (err == 0);

  #if (MRD_GENERIC_DEBUG)      
      if (!beginOK)
      {
        Serial.println("\nLittleFS error");
      }
  #endif
    

/////////////////////////////        
#elif MRD_GENERIC_USE_RTL8720
      // Do something to init FlashStorage_RTL8720
      
/////////////////////////////    
#else
      #error Un-identifiable board selected. Please check your Tools->Board setting.
#endif
    };
    
    /////////////////////////////////////////////

    bool detectMultiReset()
    {
      multiResetDetected = detectRecentlyResetFlag();

      if (multiResetDetected)
      {
#if (MRD_GENERIC_DEBUG)
        Serial.print(F("multiResetDetected, number of times = "));
        Serial.println(MRD_TIMES);
#endif

        clearRecentlyResetFlag();
      }
      else
      {
#if (MRD_GENERIC_DEBUG)
        Serial.print(F("No multiResetDetected, number of times = "));
        Serial.println((uint16_t) (multiResetDetectorFlag & 0x0000FFFF));
#endif

        setRecentlyResetFlag();
        waitingForMultiReset = true;
      }

      return multiResetDetected;

    };
    
    /////////////////////////////////////////////

    void loop()
    {
      if ( waitingForMultiReset && (millis() > timeout) )
      {
#if (MRD_GENERIC_DEBUG)
        Serial.println(F("Stop multiResetDetecting"));
#endif

        stop();
      }
    };
    
    /////////////////////////////////////////////

    void stop()
    {
      clearRecentlyResetFlag();
      waitingForMultiReset = false;
    };
    
    /////////////////////////////////////////////

    bool multiResetDetected;
    
    /////////////////////////////////////////////


  private:
    uint32_t MULTIRESETDETECTOR_FLAG;
    
    unsigned long mrd_times;
    
    unsigned long timeout;
    int MRD_EEPROM_START;
    bool waitingForMultiReset;
    
    uint32_t multiResetDetectorFlag;

    /////////////////////////////////////////////////////////////////////
    
#if (MRD_GENERIC_USE_SAMD)   

    /////////////////////////////////////////////
     
    uint32_t readFlagSAMD(void)
    {        
      uint16_t offset   = MRD_EEPROM_START;               
      uint8_t* _pointer = (uint8_t *) &MULTIRESETDETECTOR_FLAG;
      
      for (unsigned int i = 0; i < sizeof(MULTIRESETDETECTOR_FLAG); i++, _pointer++, offset++)
      {              
        *_pointer = EEPROM.read(offset);
      }
      
      return MULTIRESETDETECTOR_FLAG;
    }
    
    /////////////////////////////////////////////
    
#elif (MRD_GENERIC_USE_SAM_DUE)

    /////////////////////////////////////////////
    
    uint32_t readFlagSAM_DUE(void)
    {           
      byte* dataPointer = (byte* ) dueFlashStorage.readAddress(MRD_EEPROM_START);
      
      memcpy(&MULTIRESETDETECTOR_FLAG, dataPointer, sizeof(MULTIRESETDETECTOR_FLAG));  
      
      return MULTIRESETDETECTOR_FLAG;
    }
    
    /////////////////////////////////////////////
    
#elif MRD_GENERIC_USE_NRF52

    /////////////////////////////////////////////

    uint32_t readFlagNRF52(void)
    {           
      MRD_file.open(MRD_FILENAME, FILE_O_READ);
      
      if (MRD_file)
      {
        MRD_file.seek(MRD_FLAG_OFFSET);
        MRD_file.read((char *) &MULTIRESETDETECTOR_FLAG, sizeof(MULTIRESETDETECTOR_FLAG));

  #if (MRD_GENERIC_DEBUG)
        Serial.print(F("LittleFS Flag read = 0x"));
        Serial.println(String(MULTIRESETDETECTOR_FLAG, HEX));
  #endif

        MRD_file.close(); 
      }
      else
      {
  #if (MRD_GENERIC_DEBUG)
        Serial.println(F("Loading MRD file failed"));
  #endif
      }
           
      return MULTIRESETDETECTOR_FLAG;
    }
    
    /////////////////////////////////////////////
    
#elif MRD_GENERIC_USE_RP2040

    /////////////////////////////////////////////

    uint32_t readFlagRP2040()
    {           
      File file = FileFS.open(MRD_FILENAME, "r");
      
      if (file)
      {
        file.seek(MRD_FLAG_OFFSET);
        file.read((uint8_t *) &MULTIRESETDETECTOR_FLAG, sizeof(MULTIRESETDETECTOR_FLAG));

  #if (MRD_GENERIC_DEBUG)
        Serial.println("LittleFS Flag read = 0x" + String(MULTIRESETDETECTOR_FLAG, HEX) );
  #endif

        file.close(); 
      }
      else
      {
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Loading MRD file failed");
  #endif
      }
           
      return MULTIRESETDETECTOR_FLAG;
    }
    
    /////////////////////////////////////////////

#elif MRD_GENERIC_USE_MBED_RP2040

    /////////////////////////////////////////////

    uint32_t readFlagMbedRP2040()
    {           
      FILE *file = fopen(MRD_FILENAME, "r");
      
      if (file)
      {
        fseek(file, MRD_FLAG_OFFSET, SEEK_SET);
        fread((uint8_t *) &MULTIRESETDETECTOR_FLAG, 1, sizeof(MULTIRESETDETECTOR_FLAG), file);

  #if (MRD_GENERIC_DEBUG)
        Serial.println("LittleFS Flag read = 0x" + String(MULTIRESETDETECTOR_FLAG, HEX) );
  #endif

        fclose(file);
      }
      else
      {
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Loading MRD file failed");
  #endif
      }
           
      return MULTIRESETDETECTOR_FLAG;
    }


    /////////////////////////////////////////////
    
#elif (MRD_GENERIC_USE_MBED_PORTENTA)

    /////////////////////////////////////////////
    
    uint32_t readFlagMbedPortenta()
    {           
      FILE *file = fopen(MRD_FILENAME, "r");
      
      if (file)
      {
        fseek(file, MRD_FLAG_OFFSET, SEEK_SET);
        fread((uint8_t *) &MULTIRESETDETECTOR_FLAG, 1, sizeof(MULTIRESETDETECTOR_FLAG), file);

  #if (MRD_GENERIC_DEBUG)
        Serial.println("LittleFS Flag read = 0x" + String(MULTIRESETDETECTOR_FLAG, HEX) );
  #endif

        fclose(file);
      }
      else
      {
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Loading MRD file failed");
  #endif
      }
           
      return MULTIRESETDETECTOR_FLAG;
    } 
    
    
    /////////////////////////////////////////////

#elif MRD_GENERIC_USE_NANO33BLE

    /////////////////////////////////////////////

    uint32_t readFlagNano33BLE()
    {           
      FILE *file = fopen(MRD_FILENAME, "r");
      
      if (file)
      {
        fseek(file, MRD_FLAG_OFFSET, SEEK_SET);
        fread((uint8_t *) &MULTIRESETDETECTOR_FLAG, 1, sizeof(MULTIRESETDETECTOR_FLAG), file);

  #if (MRD_GENERIC_DEBUG)
        Serial.println("LittleFS Flag read = 0x" + String(MULTIRESETDETECTOR_FLAG, HEX) );
  #endif

        fclose(file);
      }
      else
      {
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Loading MRD file failed");
  #endif
      }
           
      return MULTIRESETDETECTOR_FLAG;
    }    
        
    /////////////////////////////////////////////

#elif (MRD_GENERIC_USE_RTL8720)

    /////////////////////////////////////////////

    uint32_t readFlagRTL8720()
    {             
      // Using name MRD_EEPROM_START, but actually FlashStorage not EEPROM
      FlashStorage.get(MRD_EEPROM_START, MULTIRESETDETECTOR_FLAG);
      
      return MULTIRESETDETECTOR_FLAG;
    }
    
    /////////////////////////////////////////////

#endif


    /////////////////////////////////////////////
       
    bool readRecentlyResetFlag()
    {
    
/////////////////////////////
#if (MRD_GENERIC_USE_EEPROM || MRD_GENERIC_USE_STM32)
      EEPROM.get(MRD_EEPROM_START, MULTIRESETDETECTOR_FLAG);
      multiResetDetectorFlag = MULTIRESETDETECTOR_FLAG;

/////////////////////////////
#elif (MRD_GENERIC_USE_SAMD)
      // SAMD code  
      multiResetDetectorFlag = readFlagSAMD();

/////////////////////////////         
#elif (MRD_GENERIC_USE_SAM_DUE)
      // SAM DUE code    
      multiResetDetectorFlag = readFlagSAM_DUE();

/////////////////////////////      
#elif MRD_GENERIC_USE_NRF52
      // nRF52 code    
      multiResetDetectorFlag = readFlagNRF52(); 

/////////////////////////////      
#elif MRD_GENERIC_USE_RP2040      
      // RP2040 code    
      multiResetDetectorFlag = readFlagRP2040(); 

///////////////////////////// 
#elif MRD_GENERIC_USE_MBED_RP2040

      // MBED RP2040 code    
      multiResetDetectorFlag = readFlagMbedRP2040();

/////////////////////////////
#elif (MRD_GENERIC_USE_MBED_PORTENTA)

      // MBED Portenta code    
      multiResetDetectorFlag = readFlagMbedPortenta();
    
/////////////////////////////
#elif MRD_GENERIC_USE_NANO33BLE

      // MBED Nano_33_BLE code    
      multiResetDetectorFlag = readFlagNano33BLE();
      
/////////////////////////////
#elif (MRD_GENERIC_USE_RTL8720)
      // RTL8720 code  
      multiResetDetectorFlag = readFlagRTL8720();
                          
#endif    //(MRD_GENERIC_USE_EEPROM || MRD_GENERIC_USE_STM32)

      return true;
    }
    
    /////////////////////////////////////////////////////////////////////
    
    bool detectRecentlyResetFlag()
    {

      if (!readRecentlyResetFlag())
        return false;
        
      /////////////////////////////////////////
      //multiResetDetected = (multiResetDetectorFlag == MULTIRESETDETECTOR_FLAG_SET);
      // Check lower 2 bytes is > 0 and upper 2 bytes agrees
           
#if USING_INVERTED      
      uint16_t upperBytes = ~(multiResetDetectorFlag >> 16);
#else
      uint16_t upperBytes = multiResetDetectorFlag >> 16;
#endif
     
      uint16_t lowerBytes = multiResetDetectorFlag & 0x0000FFFF;
      
#if (MRD_GENERIC_DEBUG)
      Serial.print(F("multiResetDetectorFlag = 0x"));
      Serial.println(String(MULTIRESETDETECTOR_FLAG, HEX));
      Serial.print(F("lowerBytes = 0x"));
      Serial.print(String(lowerBytes, HEX));
      Serial.print(F(", upperBytes = 0x"));
      Serial.println(String(upperBytes, HEX));
#endif

      if ( ( lowerBytes >= MRD_TIMES ) && ( lowerBytes == upperBytes )  )   
      {
        multiResetDetected = true;
      }
      else
      {
        multiResetDetected = false;
               
        if (lowerBytes != upperBytes)     
        {
#if (MRD_GENERIC_DEBUG)
          Serial.print(F("lowerBytes = 0x"));
          Serial.print(String(lowerBytes, HEX));
          Serial.print(F(", upperBytes = 0x"));
          Serial.println(String(upperBytes, HEX));
          Serial.println(F("detectRecentlyResetFlag: Data corrupted. Reset to 0"));
#endif
          // To reset flag to MULTIRESETDETECTOR_GENERIC_FLAG_CLEAR if data corrupted          
          clearRecentlyResetFlag(MULTIRESETDETECTOR_GENERIC_FLAG_CLEAR);
        }
      }

      /////////////////////////////////////////      
      
      
      return multiResetDetected;
    };

    /////////////////////////////////////////////////////////////////////
    
    void setRecentlyResetFlag()
    {
      // Add 1 every time detecting a reset
      // To read first, increase and update 2 checking bytes
      readRecentlyResetFlag();
      
      MULTIRESETDETECTOR_FLAG = multiResetDetectorFlag;
      
#if USING_INVERTED
      // 2 lower bytes
      MULTIRESETDETECTOR_FLAG = (MULTIRESETDETECTOR_FLAG & 0x0000FFFF) + 1;
      
      // 2 upper bytes
      //uint16_t upperBytes = ~MULTIRESETDETECTOR_FLAG;
      uint32_t upperBytes = ~MULTIRESETDETECTOR_FLAG;
      MULTIRESETDETECTOR_FLAG = (upperBytes << 16) | MULTIRESETDETECTOR_FLAG;
#else   
      // 2 lower bytes
      MULTIRESETDETECTOR_FLAG = (MULTIRESETDETECTOR_FLAG & 0x0000FFFF) + 1;
      
      // 2 upper bytes
      MULTIRESETDETECTOR_FLAG = (MULTIRESETDETECTOR_FLAG << 16) | MULTIRESETDETECTOR_FLAG;
#endif

      multiResetDetectorFlag  = MULTIRESETDETECTOR_FLAG;

/////////////////////////////
#if (MRD_GENERIC_USE_EEPROM || MRD_GENERIC_USE_STM32)
      EEPROM.put(MRD_EEPROM_START, MULTIRESETDETECTOR_FLAG);

  #if (MRD_GENERIC_DEBUG)
      delay(1000);
      EEPROM.get(MRD_EEPROM_START, MULTIRESETDETECTOR_FLAG);
  #endif

/////////////////////////////
#elif (MRD_GENERIC_USE_SAMD)
      // SAMD code     
      uint16_t offset   = MRD_EEPROM_START;               
      uint8_t* _pointer = (uint8_t *) &MULTIRESETDETECTOR_FLAG;
      
      for (unsigned int i = 0; i < sizeof(MULTIRESETDETECTOR_FLAG); i++, _pointer++, offset++)
      {              
        EEPROM.write(offset, *_pointer);
      }
      
      EEPROM.commit();
      
  #if (MRD_GENERIC_DEBUG)
      delay(1000);
      readFlagSAMD();
  #endif      

/////////////////////////////
#elif (MRD_GENERIC_USE_SAM_DUE)
      // SAM DUE code           
      dueFlashStorage.write(MRD_EEPROM_START, (byte *) &MULTIRESETDETECTOR_FLAG, sizeof(MULTIRESETDETECTOR_FLAG));
      
  #if (MRD_GENERIC_DEBUG)
      delay(1000);
      readFlagSAM_DUE();
  #endif

/////////////////////////////
#elif MRD_GENERIC_USE_NRF52
      // nRF52 code
      MRD_file.open(MRD_FILENAME, FILE_O_WRITE);
      
  #if (MRD_GENERIC_DEBUG)
      Serial.print(F("Saving MULTIRESETDETECTOR_FLAG to MRD file : 0x"));
      Serial.println(String(MULTIRESETDETECTOR_FLAG, HEX));
  #endif

      if (MRD_file)
      {
        MRD_file.seek(MRD_FLAG_OFFSET);
        MRD_file.write((uint8_t *) &MULTIRESETDETECTOR_FLAG, sizeof(MULTIRESETDETECTOR_FLAG));
        MRD_file.close();
  #if (MRD_GENERIC_DEBUG)
        Serial.println(F("Saving MRD file OK"));
  #endif
      }
      else
      {
  #if (MRD_GENERIC_DEBUG)
        Serial.println(F("Saving MRD file failed"));
  #endif
      }
      
/////////////////////////////    
#elif MRD_GENERIC_USE_RP2040

      // RP2040 code
      File file = FileFS.open(MRD_FILENAME, "w");  
      
  #if (MRD_GENERIC_DEBUG)
      Serial.print("Saving MULTIRESETDETECTOR_FLAG to MRD file : 0x");
      Serial.println(String(MULTIRESETDETECTOR_FLAG, HEX));
  #endif

      if (file)
      {
        file.seek(MRD_FLAG_OFFSET);
        file.write((uint8_t *) &MULTIRESETDETECTOR_FLAG, sizeof(MULTIRESETDETECTOR_FLAG));
        file.close();
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Saving MRD file OK");
  #endif
      }
      else
      {
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Saving MRD file failed");
  #endif
      }

/////////////////////////////  
#elif MRD_GENERIC_USE_MBED_RP2040

      // Mbed RP2040 code
      FILE *file = fopen(MRD_FILENAME, "w");
      
  #if (MRD_GENERIC_DEBUG)
      Serial.print("Saving MULTIRESETDETECTOR_FLAG to MRD file : 0x");
      Serial.println(String(MULTIRESETDETECTOR_FLAG, HEX));
  #endif

      if (file)
      {
        fseek(file, MRD_FLAG_OFFSET, SEEK_SET);
        fwrite((uint8_t *) &MULTIRESETDETECTOR_FLAG, 1, sizeof(MULTIRESETDETECTOR_FLAG), file);
        
        fclose(file);
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Saving MRD file OK");
  #endif
      }
      else
      {
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Saving MRD file failed");
  #endif
      }


/////////////////////////////
#elif (MRD_GENERIC_USE_MBED_PORTENTA)

      // Mbed Portenta code
      FILE *file = fopen(MRD_FILENAME, "w");
      
  #if (MRD_GENERIC_DEBUG)
      Serial.print("Saving MULTIRESETDETECTOR_FLAG to MRD file : 0x");
      Serial.println(String(MULTIRESETDETECTOR_FLAG, HEX));
  #endif

      if (file)
      {
        fseek(file, MRD_FLAG_OFFSET, SEEK_SET);
        fwrite((uint8_t *) &MULTIRESETDETECTOR_FLAG, 1, sizeof(MULTIRESETDETECTOR_FLAG), file);
        
        fclose(file);
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Saving MRD file OK");
  #endif
      }
      else
      {
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Saving MRD file failed");
  #endif
      }
      
      
/////////////////////////////
#elif MRD_GENERIC_USE_NANO33BLE

      // Mbed Nano_33_BLE code
      FILE *file = fopen(MRD_FILENAME, "w");
      
  #if (MRD_GENERIC_DEBUG)
      Serial.print("Saving MULTIRESETDETECTOR_FLAG to MRD file : 0x");
      Serial.println(String(MULTIRESETDETECTOR_FLAG, HEX));
  #endif

      if (file)
      {
        fseek(file, MRD_FLAG_OFFSET, SEEK_SET);
        fwrite((uint8_t *) &MULTIRESETDETECTOR_FLAG, 1, sizeof(MULTIRESETDETECTOR_FLAG), file);
        
        fclose(file);
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Saving MRD file OK");
  #endif
      }
      else
      {
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Saving MRD file failed");
  #endif
      }
            
/////////////////////////////
#elif (MRD_GENERIC_USE_RTL8720)
      // RTL8720 code           
      FlashStorage.put(MRD_EEPROM_START, MULTIRESETDETECTOR_FLAG);
           
  #if (MRD_GENERIC_DEBUG)
      delay(1000);
      readFlagRTL8720();
  #endif
        
/////////////////////////////                  
#endif    //(MRD_GENERIC_USE_EEPROM || MRD_GENERIC_USE_STM32)

#if (MRD_GENERIC_DEBUG)
      Serial.print(F("SetFlag write = 0x"));
      Serial.println(String(MULTIRESETDETECTOR_FLAG, HEX));
#endif
    };

    /////////////////////////////////////////////////////////////////////
    
    void clearRecentlyResetFlag(uint32_t flagValue = MULTIRESETDETECTOR_GENERIC_FLAG_BEGIN)
    {      
      multiResetDetectorFlag  = flagValue;
      MULTIRESETDETECTOR_FLAG = flagValue;

/////////////////////////////
#if (MRD_GENERIC_USE_EEPROM || MRD_GENERIC_USE_STM32)
      EEPROM.put(MRD_EEPROM_START, MULTIRESETDETECTOR_FLAG);

  #if (MRD_GENERIC_DEBUG)
      delay(1000);
      EEPROM.get(MRD_EEPROM_START, MULTIRESETDETECTOR_FLAG);
  #endif

/////////////////////////////
#elif (MRD_GENERIC_USE_SAMD)
      // SAMD code     
      uint16_t offset   = MRD_EEPROM_START;               
      uint8_t* _pointer = (uint8_t *) &MULTIRESETDETECTOR_FLAG;
      
      for (unsigned int i = 0; i < sizeof(MULTIRESETDETECTOR_FLAG); i++, _pointer++, offset++)
      {              
        EEPROM.write(offset, *_pointer);
      }
      
      EEPROM.commit();
      
  #if (MRD_GENERIC_DEBUG)
      delay(1000);
      readFlagSAMD();
  #endif      

/////////////////////////////
#elif (MRD_GENERIC_USE_SAM_DUE)
      // SAM DUE code           
      dueFlashStorage.write(MRD_EEPROM_START, (byte *) &MULTIRESETDETECTOR_FLAG, sizeof(MULTIRESETDETECTOR_FLAG));
      
  #if (MRD_GENERIC_DEBUG)
      delay(1000);
      readFlagSAM_DUE();
  #endif

/////////////////////////////
#elif MRD_GENERIC_USE_NRF52

      // nRF52 code
      MRD_file.open(MRD_FILENAME, FILE_O_WRITE);
  #if (MRD_GENERIC_DEBUG)
      Serial.print(F("Saving to MRD file : 0x"));
      Serial.println(String(MULTIRESETDETECTOR_FLAG, HEX));
  #endif

      if (MRD_file)
      {
        MRD_file.seek(MRD_FLAG_OFFSET);
        MRD_file.write((uint8_t *) &MULTIRESETDETECTOR_FLAG, sizeof(MULTIRESETDETECTOR_FLAG)); 
   
        MRD_file.close();
  #if (MRD_GENERIC_DEBUG)
        Serial.println(F("Saving MRD file OK"));
  #endif
      }
      else
      {
  #if (MRD_GENERIC_DEBUG)
        Serial.println(F("Saving MRD file failed"));
  #endif
      }   
      
      delay(1000);
      readFlagNRF52();

/////////////////////////////
#elif MRD_GENERIC_USE_RP2040

      // RP2040 code
      File file = FileFS.open(MRD_FILENAME, "w");
      
  #if (MRD_GENERIC_DEBUG)
      Serial.print("Saving to MRD file : 0x");
      Serial.println(String(MULTIRESETDETECTOR_FLAG, HEX));
  #endif

      if (file)
      {
        file.seek(MRD_FLAG_OFFSET);
        file.write((uint8_t *) &MULTIRESETDETECTOR_FLAG, sizeof(MULTIRESETDETECTOR_FLAG)); 
   
        file.close();
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Saving MRD file OK");
  #endif
      }
      else
      {
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Saving MRD file failed");
  #endif
      }   
      
      delay(1000);
      readFlagRP2040();

/////////////////////////////

#elif MRD_GENERIC_USE_MBED_RP2040

      // Mbed RP2040 code
      FILE *file = fopen(MRD_FILENAME, "w");
      
  #if (MRD_GENERIC_DEBUG)
      Serial.print("Saving to MRD file : 0x");
      Serial.println(String(MULTIRESETDETECTOR_FLAG, HEX));
  #endif

      if (file)
      {       
        fseek(file, MRD_FLAG_OFFSET, SEEK_SET);
        fwrite((uint8_t *) &MULTIRESETDETECTOR_FLAG, 1, sizeof(MULTIRESETDETECTOR_FLAG), file);
        
        fclose(file);
        
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Saving MRD file OK");
  #endif
      }
      else
      {
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Saving MRD file failed");
  #endif
      }   
      
      delay(1000);
      readFlagMbedRP2040();


/////////////////////////////
#elif (MRD_GENERIC_USE_MBED_PORTENTA)

      // Mbed Portenta code
      FILE *file = fopen(MRD_FILENAME, "w");
      
  #if (MRD_GENERIC_DEBUG)
      Serial.print("Saving to MRD file : 0x");
      Serial.println(String(MULTIRESETDETECTOR_FLAG, HEX));
  #endif

      if (file)
      {       
        fseek(file, MRD_FLAG_OFFSET, SEEK_SET);
        fwrite((uint8_t *) &MULTIRESETDETECTOR_FLAG, 1, sizeof(MULTIRESETDETECTOR_FLAG), file);
        
        fclose(file);
        
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Saving MRD file OK");
  #endif
      }
      else
      {
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Saving MRD file failed");
  #endif
      }   
      
      delay(1000);
      readFlagMbedPortenta();


/////////////////////////////
#elif MRD_GENERIC_USE_NANO33BLE

      // Mbed Nano_33_BLE code
      FILE *file = fopen(MRD_FILENAME, "w");
      
  #if (MRD_GENERIC_DEBUG)
      Serial.print("Saving to MRD file : 0x");
      Serial.println(String(MULTIRESETDETECTOR_FLAG, HEX));
  #endif

      if (file)
      {       
        fseek(file, MRD_FLAG_OFFSET, SEEK_SET);
        fwrite((uint8_t *) &MULTIRESETDETECTOR_FLAG, 1, sizeof(MULTIRESETDETECTOR_FLAG), file);
        
        fclose(file);
        
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Saving MRD file OK");
  #endif
      }
      else
      {
  #if (MRD_GENERIC_DEBUG)
        Serial.println("Saving MRD file failed");
  #endif
      }   
      
      delay(1000);
      readFlagNano33BLE();
            
/////////////////////////////

#elif (MRD_GENERIC_USE_RTL8720)
     
      // RTL8720 code           
      FlashStorage.put(MRD_EEPROM_START, MULTIRESETDETECTOR_FLAG);
           
  #if (MRD_GENERIC_DEBUG)
      delay(1000);
      readFlagRTL8720();
  #endif  
      
/////////////////////////////
      
#endif    //(MRD_GENERIC_USE_EEPROM || MRD_GENERIC_USE_STM32)

#if (MRD_GENERIC_DEBUG)
      Serial.print(F("ClearFlag write = 0x"));
      Serial.println(String(MULTIRESETDETECTOR_FLAG, HEX));
#endif
    };

};
#endif // MultiResetDetector_Generic_H
