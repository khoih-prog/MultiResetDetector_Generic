/***********************************************************************************************************************************
   MultiResetDetector_Generic.h
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
 ************************************************************************************************************************************/

#pragma once

#ifndef MultiResetDetector_Generic_H
#define MultiResetDetector_Generic_H

#define MULTIRESETDETECTOR_GENERIC_VERSION       "MultiResetDetector_Generic v1.0.3"

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
#elif ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
   || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) \
   || defined(ARDUINO_SAMD_MKRWAN1310) || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) \
   || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) \
   || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) || defined(__SAMD51G19A__) )
  #if defined(MRD_GENERIC_USE_SAMD)
    #undef MRD_GENERIC_USE_SAMD
  #endif
  #define MRD_GENERIC_USE_SAMD      true
  #if defined(MRD_GENERIC_USE_EEPROM)
    #undef MRD_GENERIC_USE_EEPROM
  #endif
  #define MRD_GENERIC_USE_EEPROM    false
  #warning Use SAMD and FlashStorage
  
#elif ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
        defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
        defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) | defined(NINA_B302_ublox) )    

  #if defined(MRD_GENERIC_USE_NRF52)
    #undef MRD_GENERIC_USE_NRF52
  #endif
  #define MRD_GENERIC_USE_NRF52      true
  #if defined(MRD_GENERIC_USE_EEPROM)
    #undef MRD_GENERIC_USE_EEPROM
  #endif
  #define MRD_GENERIC_USE_EEPROM    false
  #warning Use NRF52 and LittleFS / InternalFS

#else
  #if defined(CORE_TEENSY)
    #warning Use TEENSY and EEPROM
  #elif ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) )
    #warning Use STM32 and EEPROM
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
 
//default to use EEPROM, otherwise, use DueFlashStorage or FlashStorage_SAMD
#if MRD_GENERIC_USE_EEPROM
  #include <EEPROM.h>

  #define  FLAG_DATA_SIZE     4

  #ifndef MRD_EEPROM_SIZE
    // Please change according to your application to avoid overwriting or being overwritten
    #define MRD_EEPROM_SIZE     (E2END + 1)
  #endif

#elif MRD_GENERIC_USE_SAMD
  // Include EEPROM-like API for FlashStorage
  //#include <FlashAsEEPROM.h>                //https://github.com/cmaglie/FlashStorage
  #include <FlashAsEEPROM_SAMD.h>             //https://github.com/khoih-prog/FlashStorage_SAMD
#elif MRD_GENERIC_USE_SAM_DUE
  //Use DueFlashStorage to simulate EEPROM
  #include <DueFlashStorage.h>                 //https://github.com/sebnil/DueFlashStorage
  DueFlashStorage dueFlashStorage;
  
#elif MRD_GENERIC_USE_NRF52
  // Include LittleFS similar to SPIFFS
  #include <Adafruit_LittleFS.h>
  #include <InternalFileSystem.h>
  using namespace Adafruit_LittleFS_Namespace;
  
  File MRD_file(InternalFS);
  
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

class MultiResetDetector_Generic
{
  public:
    MultiResetDetector_Generic(unsigned long timeout, int address)
    {
      mrd_times = MRD_TIMES;
      
      this->timeout = timeout * 1000;
      this->MRD_EEPROM_START = address;
      multiResetDetected = false;
      waitingForMultiReset = false;
          
#if MRD_GENERIC_USE_EEPROM
      EEPROM.begin();
  #if (MRD_GENERIC_DEBUG)
      Serial.print(F("\nEEPROM size = "));
      Serial.print(MRD_EEPROM_SIZE);
      Serial.print(F(", start = "));
      Serial.println(MRD_EEPROM_START);
  #endif
        
#elif MRD_GENERIC_USE_SAMD
      // Do something to init FlashStorage
#elif MRD_GENERIC_USE_SAM_DUE
      // Do something to init DueFlashStorage
      
#elif MRD_GENERIC_USE_NRF52
      // Do something to init LittleFS / InternalFS
      // Initialize Internal File System
      InternalFS.begin();
#else
      #error Un-identifiable board selected. Please check your Tools->Board setting.
#endif
    };

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

    void stop()
    {
      clearRecentlyResetFlag();
      waitingForMultiReset = false;
    };

    bool multiResetDetected;


  private:
    uint32_t MULTIRESETDETECTOR_FLAG;
    
    unsigned long mrd_times;
    
    unsigned long timeout;
    int MRD_EEPROM_START;
    bool waitingForMultiReset;
    
    uint32_t multiResetDetectorFlag;

    /////////////////////////////////////////////////////////////////////
    
#if (MRD_GENERIC_USE_SAMD)    
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
#elif (MRD_GENERIC_USE_SAM_DUE)
    uint32_t readFlagSAM_DUE(void)
    {           
      byte* dataPointer = (byte* ) dueFlashStorage.readAddress(MRD_EEPROM_START);
      
      memcpy(&MULTIRESETDETECTOR_FLAG, dataPointer, sizeof(MULTIRESETDETECTOR_FLAG));  
      
      return MULTIRESETDETECTOR_FLAG;
    }
#elif MRD_GENERIC_USE_NRF52
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
#endif
    
    /////////////////////////////////////////////////////////////////////
    
    bool readRecentlyResetFlag()
    {
#if (MRD_GENERIC_USE_EEPROM)
      EEPROM.get(MRD_EEPROM_START, MULTIRESETDETECTOR_FLAG);
      multiResetDetectorFlag = MULTIRESETDETECTOR_FLAG;

#elif (MRD_GENERIC_USE_SAMD)
      // SAMD code  
      multiResetDetectorFlag = readFlagSAMD();
         
#elif (MRD_GENERIC_USE_SAM_DUE)
      // SAM DUE code    
      multiResetDetectorFlag = readFlagSAM_DUE();
      
#elif MRD_GENERIC_USE_NRF52
      // nRF52 code    
      multiResetDetectorFlag = readFlagNRF52(); 
        
#endif    //(MRD_GENERIC_USE_EEPROM)

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

#if (MRD_GENERIC_USE_EEPROM)
      EEPROM.put(MRD_EEPROM_START, MULTIRESETDETECTOR_FLAG);

#if (MRD_GENERIC_DEBUG)
      delay(1000);
      EEPROM.get(MRD_EEPROM_START, MULTIRESETDETECTOR_FLAG);
#endif

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

#elif (MRD_GENERIC_USE_SAM_DUE)
      // SAM DUE code           
      dueFlashStorage.write(MRD_EEPROM_START, (byte *) &MULTIRESETDETECTOR_FLAG, sizeof(MULTIRESETDETECTOR_FLAG));
      
#if (MRD_GENERIC_DEBUG)
      delay(1000);
      readFlagSAM_DUE();
#endif

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
#endif    //(MRD_GENERIC_USE_EEPROM)

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

#if (MRD_GENERIC_USE_EEPROM)
      EEPROM.put(MRD_EEPROM_START, MULTIRESETDETECTOR_FLAG);

#if (MRD_GENERIC_DEBUG)
      delay(1000);
      EEPROM.get(MRD_EEPROM_START, MULTIRESETDETECTOR_FLAG);
#endif

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

#elif (MRD_GENERIC_USE_SAM_DUE)
      // SAM DUE code           
      dueFlashStorage.write(MRD_EEPROM_START, (byte *) &MULTIRESETDETECTOR_FLAG, sizeof(MULTIRESETDETECTOR_FLAG));
      
#if (MRD_GENERIC_DEBUG)
      delay(1000);
      readFlagSAM_DUE();
#endif

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
      
#endif    //(MRD_GENERIC_USE_EEPROM)

#if (MRD_GENERIC_DEBUG)
      Serial.print(F("ClearFlag write = 0x"));
      Serial.println(String(MULTIRESETDETECTOR_FLAG, HEX));
#endif

//#endif    //(MRD_GENERIC_USE_EEPROM)
    };

};
#endif // MultiResetDetector_Generic_H
