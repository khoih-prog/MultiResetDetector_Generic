## MultiResetDetector_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/MultiResetDetector_Generic.svg?)](https://www.ardu-badge.com/MultiResetDetector_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/MultiResetDetector_Generic.svg)](https://github.com/khoih-prog/MultiResetDetector_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/MultiResetDetector_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/MultiResetDetector_Generic.svg)](http://github.com/khoih-prog/MultiResetDetector_Generic/issues)

---
---

## Table of Contents

* [Why do we need this MultiResetDetector_Generic library](#why-do-we-need-this-multiresetdetector_generic-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](#changelog)
  * [Releases v1.0.3](#releases-v103)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards) 
* [Purpose](#purpose)
* [How It Works](#how-it-works)
* [Examples](#examples)
  * [ 1. minimal](examples/minimal)
  * [Many other libraries are depending on this library's DRD and MRD feature](#many-other-libraries-are-depending-on-this-librarys-drd-and-mrd-feature)
    * [ 1. BlynkEthernet_WM](https://github.com/khoih-prog/BlynkEthernet_WM)
    * [ 2. Blynk_Esp8266AT_WM](https://github.com/khoih-prog/Blynk_Esp8266AT_WM)
    * [ 3. Blynk_WiFiNINA_WM](https://github.com/khoih-prog/Blynk_WiFiNINA_WM)
    * [ 4. WiFiManager_NINA_Lite](https://github.com/khoih-prog/WiFiManager_NINA_Lite)
    * [ 5. BlynkEthernet_STM32_WM](https://github.com/khoih-prog/BlynkEthernet_STM32_WM)
    * [ 6. ESP_AT_WM_Lite](https://github.com/khoih-prog/ESP_AT_WM_Lite)
    * [ 7. WIOTerminal_WiFiManager](https://github.com/khoih-prog/WIOTerminal_WiFiManager)
    * [ 8. Ethernet_Manager](https://github.com/khoih-prog/Ethernet_Manager)
    * [ 9. Ethernet_Manager_STM32](https://github.com/khoih-prog/Ethernet_Manager_STM32)
* [Example minimal](#example-minimal)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. minimal on Adafruit Itsy-Bitsy nRF52840 Express using LittleFS](#1-minimal-on-adafruit-itsy-bitsy-nrf52840-express-using-littlefs)
    * [ 1.1 Data Corrupted => reset to 0](#11-data-corrupted--reset-to-0)
    * [ 1.2 Reset Detected => Reporting 1](#12-reset-detected--reporting-1)
    * [ 1.3 Reset Detected => Reporting 2](#13-reset-detected--reporting-2)
    * [ 1.4 Reset Detected => Reporting 3](#14-reset-detected--reporting-3)
    * [ 1.5 Reset Detected => Reporting 4](#15-reset-detected--reporting-4)
    * [ 1.6 Reset Detected => Reporting 5. Multi Reset Detected](#16-reset-detected--reporting-5-multi-reset-detected)
  * [2. minimal on Teensy 4.0 using EEPROM](#2-minimal-on-Teensy-40-using-eeprom)
    * [ 2.1 Data Corrupted => reset to 0](#21-data-corrupted--reset-to-0)
    * [ 2.2 Reset Detected => Reporting 1](#22-reset-detected--reporting-1)
    * [ 2.3 Reset Detected => Reporting 2](#23-reset-detected--reporting-2)
    * [ 2.4 Reset Detected => Reporting 3](#24-reset-detected--reporting-3)
    * [ 2.5 Reset Detected => Reporting 4](#25-reset-detected--reporting-4)
    * [ 2.6 Reset Detected => Reporting 5. Multi Reset Detected](#26-reset-detected--reporting-5-multi-reset-detected)
  * [3. minimal on SAM DUE using DueFlashStorage](#3-minimal-on-sam-due-using-dueflashstorage)
    * [ 3.1 Data Corrupted => reset to 0](#31-data-corrupted--reset-to-0)
    * [ 3.2 Reset Detected => Reporting 1](#32-reset-detected--reporting-1)
    * [ 3.3 Reset Detected => Reporting 2](#33-reset-detected--reporting-2)
    * [ 3.4 Reset Detected => Reporting 3](#34-reset-detected--reporting-3)
    * [ 3.5 Reset Detected => Reporting 4](#35-reset-detected--reporting-4)
    * [ 3.8 Reset Detected => Reporting 1](#38-reset-detected--reporting-1)
  * [4. minimal on minimal on Arduino SAMD21 Nano-33-IoT using FlashStorage_SAMD](#4-minimal-on-arduino-samd21-nano-33-iot-using-flashstorage_samd)
    * [ 4.1 Data Corrupted => reset to 0](#41-data-corrupted--reset-to-0)
    * [ 4.2 Reset Detected => Reporting 1](#42-reset-detected--reporting-1)
    * [ 4.3 Reset Detected => Reporting 2](#43-reset-detected--reporting-2)
    * [ 4.4 Reset Detected => Reporting 3](#44-reset-detected--reporting-3)
    * [ 4.5 Reset Detected => Reporting 4](#45-reset-detected--reporting-4)
    * [ 4.6 Reset Detected => Reporting 5. Multi Reset Detected](#46-reset-detected--reporting-5-multi-reset-detected)
* [Libraries using ESP_DoubleResetDetector or DoubleResetDetector_Generic library](#libraries-using-esp_doubleresetdetector-or-doubleresetdetector_generic-library)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Releases](#releases)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)
---
---

### Why do we need this [MultiResetDetector_Generic library](https://github.com/khoih-prog/MultiResetDetector_Generic)

#### Features

[**MultiResetDetector_Generic**](https://github.com/khoih-prog/MultiResetDetector_Generic) is a library for the **Arduino AVR, Teensy, SAM DUE, SAMD21, SAMD51, STM32F/L/H/G/WB/MP1, nRF52, etc.** boards to detects a **multi reset, within configurable timeout (default 10s) seconds**, so that an alternative start-up mode can be used. Example use cases are to allow re-configuration of a device's WiFi / MQTT / Blynk credentials or to count the number of resets within a pre-determined timed.

This library is based on, modified, bug-fixed and improved from 

1. [`Stephen Denne's DoubleResetDetector`](https://github.com/datacute/DoubleResetDetector)
2. [`Khoi Hoang's ESP_DoubleResetDetector`](https://github.com/khoih-prog/ESP_DoubleResetDetector)
3. [`Khoi Hoang's ESP_MultiResetDetector`](https://github.com/khoih-prog/ESP_MultiResetDetector)
4. [`Khoi Hoang's DoubleResetDetector_Generic`](https://github.com/khoih-prog/DoubleResetDetector_Generic) 

to add support for AVR, Teensy, SAM DUE, SAMD, STM32, nRF52, etc. boards.

Currently, [`DoubleResetDetector`](https://github.com/datacute/DoubleResetDetector) only supports ESP8266 using RTC memory,  [`ESP_DoubleResetDetector`](https://github.com/khoih-prog/ESP_DoubleResetDetector) and [`ESP_MultiResetDetector`](https://github.com/khoih-prog/ESP_MultiResetDetector) only ESP8266 and ESP32, [`DoubleResetDetector_Generic`](https://github.com/khoih-prog/DoubleResetDetector_Generic) only for double reset detection.
 
This library can be used to detect a multi reset within a predetermined time to force the program to enter a special operation such as Config Portal, Clear Default Data, etc., using :

1. EEPROM for AVR, Teensy, STM32F/L/H/G/WB/MP1 boards.
2. [`FlashStorage_SAMD library v1.0.0`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, **NANO_33_IOT**, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.)
3. [`DueFlashStorage library`](https://github.com/sebnil/DueFlashStorage) for SAM DUE
4. [`Adafruit's LittleFS/InternalFS`](www.adafruit.com) for nRF52


#### Currently supported Boards

This [**MultiResetDetector_Generic** library](https://github.com/khoih-prog/MultiResetDetector_Generic) currently supports these following boards:

 1. **nRF52 boards**, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**
 
 2. **SAM DUE**
 
 3. **SAMD21**
  - Arduino SAMD21: ZERO, MKRs, NANO_33_IOT, etc.
  - Adafruit SAMD21 (M0): ItsyBitsy M0, Feather M0, Feather M0 Express, Metro M0 Express, Circuit Playground Express, Trinket M0, PIRkey, Hallowing M0, Crickit M0, etc.
  - Seeeduino:  LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, etc.
  
 4. **SAMD51**
  - Adafruit SAMD51 (M4): Metro M4, Grand Central M4, ItsyBitsy M4, Feather M4 Express, Trellis M4, Metro M4 AirLift Lite, MONSTER M4SK Express, Hallowing M4, etc.
  - Seeeduino: Wio Terminal, Grove UI Wireless
  
 5. **Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC)**
 
 6. **AVR Mega1280, 2560, ADK.**
 
 7. **STM32F/L/H/G/WB/MP1 boards**

- Nucleo-144
- Nucleo-64
- Discovery
- Generic STM32F0, STM32F1, STM32F2, STM32F3, STM32F4, STM32F7 (with 64+K Flash): x8 and up
- STM32L0, STM32L1, STM32L4
- STM32G0, STM32G4
- STM32H7
- STM32WB
- STM32MP1
- LoRa boards
- 3-D printer boards
- Generic Flight Controllers
- Midatronics boards

---

## Changelog

### Releases v1.0.3

1. Initial coding to support Multiple Reset Detection.
2. Sync with DoubleResetDetector_Generic v1.0.3

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.13+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Teensy core 1.53+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC) boards
 3. [`Arduino SAM DUE core 1.6.12+`](https://www.arduino.cc/en/Guide/ArduinoDue) for SAM DUE ARM Cortex-M3 boards
 4. [`Arduino SAMD core 1.8.11+`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards
 5. [`Adafruit SAMD core 1.6.4+`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.)
 6. [`Seeeduino SAMD core 1.8.1+`](https://www.seeedstudio.com/) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.).
 7. [`Adafruit nRF52 v0.21.0+`](www.adafruit.com) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox, NINA_B112_ublox**, etc.
 8. [`Arduino Core for STM32 v1.9.0+`](https://github.com/khoih-prog/Arduino_Core_STM32) for STM32 boards
 9. [`FlashStorage_SAMD library v1.0.0+`](https://github.com/khoih-prog/FlashStorage_SAMD) or [`Platform.io FlashStorage_SAMD library v1.0.0+`](https://platformio.org/lib/show/11242/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.)
10. [`DueFlashStorage library`](https://github.com/sebnil/DueFlashStorage) for SAM DUE
11. [`Adafruit's LittleFS/InternalFS`](https://www.adafruit.com) for nRF52. Already included if you already installed Adafruit **nRF52 board package** from Boards Manager.

---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for `MultiResetDetector_Generic`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/MultiResetDetector_Generic.svg?)](https://www.ardu-badge.com/MultiResetDetector_Generic) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [MultiResetDetector_Generic](https://github.com/khoih-prog/MultiResetDetector_Generic) page.
2. Download the latest release `MultiResetDetector_Generic-master.zip`.
3. Extract the zip file to `MultiResetDetector_Generic-master` directory 
4. Copy whole `MultiResetDetector_Generic-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install **MultiResetDetector_Generic** library by using [Library Manager](https://docs.platformio.org/en/latest/librarymanager/). Search for MultiResetDetector_Generic in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
3. Install [**MultiResetDetector_Generic** library](https://platformio.org/lib/show/xxxxx/MultiResetDetector_Generic) by using [Library Manager](https://platformio.org/lib/show/xxxxx/MultiResetDetector_Generic/installation). Search for **MultiResetDetector_Generic** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 0.21.0](Packages_Patches/adafruit/hardware/nrf52/0.21.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0). 

Supposing the Adafruit nRF52 version is 0.21.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the file [Teensy boards.txt](Packages_Patches/hardware/teensy/avr/boards.txt) into Teensy hardware directory (./arduino-1.8.12/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.12. This file must be copied into the directory:

- `./arduino-1.8.12/hardware/teensy/avr/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile without error and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD cores 1.8.10](Packages_Patches/arduino/hardware/samd/1.8.10) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.10).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.11. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.11/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the file [Adafruit SAMD platform.txt](Packages_Patches/adafruit/hardware/samd/1.6.4) into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.6.4). 

Supposing the Adafruit SAMD core version is 1.6.4. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.6.4/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the file [Seeeduino SAMD platform.txt](Packages_Patches/Seeeduino/hardware/samd/1.8.1) into Adafruit samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1). 

Supposing the Seeeduino SAMD core version is 1.8.1. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`

#### 7. For STM32 boards

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/1.9.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/1.9.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 1.9.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_L053R8/variant.h`

---
---

### Purpose

Detects a multi reset so that an alternative start-up mode can be used. One example use is to allow re-configuration of a device's WiFi or Blynk Credentials or to count the number of resets within a pre-determined timed.

### How It Works
  
   When the device starts up it checks the EEPROM, (Due)FlashStorage or LittleFS file `/mrd.dat` for a flag to see if it has been recently reset within the configurable timeout seconds
   
---
   
### Examples: 

 1. [minimal](examples/minimal)


#### Many other libraries are depending on this library's DRD and MRD feature

  All examples of these following libraries are using DRD/MRD feature of this [MultiResetDetector_Generic Library](https://github.com/khoih-prog/MultiResetDetector_Generic)
   
* [ 1. BlynkEthernet_WM](https://github.com/khoih-prog/BlynkEthernet_WM)
* [ 2. Blynk_Esp8266AT_WM](https://github.com/khoih-prog/Blynk_Esp8266AT_WM)
* [ 3. Blynk_WiFiNINA_WM](https://github.com/khoih-prog/Blynk_WiFiNINA_WM)
* [ 4. WiFiManager_NINA_Lite](https://github.com/khoih-prog/WiFiManager_NINA_Lite)
* [ 5. BlynkEthernet_STM32_WM](https://github.com/khoih-prog/BlynkEthernet_STM32_WM)
* [ 6. ESP_AT_WM_Lite](https://github.com/khoih-prog/ESP_AT_WM_Lite)
* [ 7. WIOTerminal_WiFiManager](https://github.com/khoih-prog/WIOTerminal_WiFiManager)
* [ 8. Ethernet_Manager](https://github.com/khoih-prog/Ethernet_Manager)
* [ 9. Ethernet_Manager_STM32](https://github.com/khoih-prog/Ethernet_Manager_STM32)

  
---
   
#### Example [minimal](examples/minimal)

```cpp
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
```

---

### Debug Terminal Output Samples

#### 1. minimal on Adafruit Itsy-Bitsy nRF52840 Express using LittleFS

This is terminal debug output when running [minimal](examples/minimal) on ***Adafruit Itsy-Bitsy nRF52840 Express using LittleFS.***. MRD_TIMES is set at 5 and MRD_TIMEOUT at 10 seconds.


#### 1.1 Data Corrupted => reset to 0

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
LittleFS Flag read = 0xfffe0001
multiResetDetectorFlag = 0xfffe0001
lowerBytes = 0x1, upperBytes = 0x1
No multiResetDetected, number of times = 1
LittleFS Flag read = 0xfffe0001
Saving MULTIRESETDETECTOR_FLAG to MRD file : 0xfffd0002
Saving MRD file OK
SetFlag write = 0xfffd0002
No Multi Reset Detected
Stop multiResetDetecting
Saving to MRD file : 0xfffe0001
Saving MRD file OK
LittleFS Flag read = 0xfffe0001
ClearFlag write = 0xfffe0001
```

#### 1.2 Reset Detected => Reporting 1

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
LittleFS Flag read = 0xfffe0001
multiResetDetectorFlag = 0xfffe0001
lowerBytes = 0x1, upperBytes = 0x1
No multiResetDetected, number of times = 1
LittleFS Flag read = 0xfffe0001
Saving MULTIRESETDETECTOR_FLAG to MRD file : 0xfffd0002
Saving MRD file OK
SetFlag write = 0xfffd0002
No Multi Reset Detected
```

#### 1.3 Reset Detected => Reporting 2

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
LittleFS Flag read = 0xfffd0002
multiResetDetectorFlag = 0xfffd0002
lowerBytes = 0x2, upperBytes = 0x2
No multiResetDetected, number of times = 2
LittleFS Flag read = 0xfffd0002
Saving MULTIRESETDETECTOR_FLAG to MRD file : 0xfffc0003
Saving MRD file OK
SetFlag write = 0xfffc0003
No Multi Reset Detected
```

#### 1.4 Reset Detected => Reporting 3

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
LittleFS Flag read = 0xfffc0003
multiResetDetectorFlag = 0xfffc0003
lowerBytes = 0x3, upperBytes = 0x3
No multiResetDetected, number of times = 3
LittleFS Flag read = 0xfffc0003
Saving MULTIRESETDETECTOR_FLAG to MRD file : 0xfffb0004
Saving MRD file OK
SetFlag write = 0xfffb0004
No Multi Reset Detected
```

#### 1.5 Reset Detected => Reporting 4

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
LittleFS Flag read = 0xfffb0004
multiResetDetectorFlag = 0xfffb0004
lowerBytes = 0x4, upperBytes = 0x4
No multiResetDetected, number of times = 4
LittleFS Flag read = 0xfffb0004
Saving MULTIRESETDETECTOR_FLAG to MRD file : 0xfffa0005
Saving MRD file OK
SetFlag write = 0xfffa0005
No Multi Reset Detected
```

#### 1.6 Reset Detected => Reporting 5. Multi Reset Detected

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
LittleFS Flag read = 0xfffa0005
multiResetDetectorFlag = 0xfffa0005
lowerBytes = 0x5, upperBytes = 0x5
multiResetDetected, number of times = 5
Saving to MRD file : 0xfffe0001
Saving MRD file OK
LittleFS Flag read = 0xfffe0001
ClearFlag write = 0xfffe0001
Multi Reset Detected
```

---

#### 2. minimal on Teensy 4.0 using EEPROM

This is terminal debug output when running [minimal](examples/minimal) on ***Teensy 4.0 using EEPROM.***. MRD_TIMES is set at 5 and MRD_TIMEOUT at 10 seconds.


#### 2.1 Data Corrupted => reset to 0

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------

EEPROM size = 1080, start = 0
multiResetDetectorFlag = 0xD0D04321
lowerBytes = 0x4321, upperBytes = 0x2f2f
lowerBytes = 0x4321, upperBytes = 0x2f2f
detectRecentlyResetFlag: Data corrupted. Reset to 0
ClearFlag write = 0xFFFF0000
No multiResetDetected, number of times = 0
SetFlag write = 0xFFFE0001
No Multi Reset Detected
```

#### 2.2 Reset Detected => Reporting 1

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------

EEPROM size = 1080, start = 0
multiResetDetectorFlag = 0xFFFE0001
lowerBytes = 0x1, upperBytes = 0x1
No multiResetDetected, number of times = 1
SetFlag write = 0xFFFD0002
No Multi Reset Detected
```

#### 2.3 Reset Detected => Reporting 2

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------

EEPROM size = 1080, start = 0
multiResetDetectorFlag = 0xFFFD0002
lowerBytes = 0x2, upperBytes = 0x2
No multiResetDetected, number of times = 2
SetFlag write = 0xFFFC0003
No Multi Reset Detected
```

#### 2.4 Reset Detected => Reporting 3

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------

EEPROM size = 1080, start = 0
multiResetDetectorFlag = 0xFFFC0003
lowerBytes = 0x3, upperBytes = 0x3
No multiResetDetected, number of times = 3
SetFlag write = 0xFFFB0004
No Multi Reset Detected
```

#### 2.5 Reset Detected => Reporting 4

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------

EEPROM size = 1080, start = 0
multiResetDetectorFlag = 0xFFFB0004
lowerBytes = 0x4, upperBytes = 0x4
No multiResetDetected, number of times = 4
SetFlag write = 0xFFFA0005
No Multi Reset Detected
```

#### 2.6 Reset Detected => Reporting 5. Multi Reset Detected

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------

EEPROM size = 1080, start = 0
multiResetDetectorFlag = 0xFFFA0005
lowerBytes = 0x5, upperBytes = 0x5
multiResetDetected, number of times = 5
ClearFlag write = 0xFFFE0001
Multi Reset Detected
```

---

#### 3. minimal on SAM DUE using DueFlashStorage

This is terminal debug output when running [minimal](examples/minimal) on ***SAM DUE using DueFlashStorage.***. MRD_TIMES is set at 5 and MRD_TIMEOUT at 10 seconds.


#### 3.1 Data Corrupted => reset to 0

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
multiResetDetectorFlag = 0xffff0000
lowerBytes = 0x0, upperBytes = 0x0
No multiResetDetected, number of times = 0
SetFlag write = 0xfffe0001
No Multi Reset Detected
Stop multiResetDetecting
ClearFlag write = 0xfffe0001
```

#### 3.2 Reset Detected => Reporting 1

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
multiResetDetectorFlag = 0xfffe0001
lowerBytes = 0x1, upperBytes = 0x1
No multiResetDetected, number of times = 1
SetFlag write = 0xfffd0002
No Multi Reset Detected
```

#### 3.3 Reset Detected => Reporting 2

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
multiResetDetectorFlag = 0xfffd0002
lowerBytes = 0x2, upperBytes = 0x2
No multiResetDetected, number of times = 2
SetFlag write = 0xfffc0003
No Multi Reset Detected
```

#### 3.4 Reset Detected => Reporting 3

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
multiResetDetectorFlag = 0xfffc0003
lowerBytes = 0x3, upperBytes = 0x3
No multiResetDetected, number of times = 3
SetFlag write = 0xfffb0004
No Multi Reset Detected
```

#### 3.5 Reset Detected => Reporting 4

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
multiResetDetectorFlag = 0xfffb0004
lowerBytes = 0x4, upperBytes = 0x4
No multiResetDetected, number of times = 4
SetFlag write = 0xfffa0005
No Multi Reset Detected
```

#### 3.6 Reset Detected => Reporting 5. Multi Reset Detected

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
multiResetDetectorFlag = 0xfffa0005
lowerBytes = 0x5, upperBytes = 0x5
multiResetDetected, number of times = 5
ClearFlag write = 0xfffe0001
Multi Reset Detected
```

---

#### 4. minimal on Arduino SAMD21 Nano-33-IoT using FlashStorage_SAMD

This is terminal debug output when running [minimal](examples/minimal) on ***Arduino SAMD21 Nano-33-IoT using FlashStorage_SAMD***. MRD_TIMES is set at 5 and MRD_TIMEOUT at 10 seconds.


#### 4.1 Data Corrupted => reset to 0

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
multiResetDetectorFlag = 0xffffffff
lowerBytes = 0xffff, upperBytes = 0x0
lowerBytes = 0xffff, upperBytes = 0x0
detectRecentlyResetFlag: Data corrupted. Reset to 0
ClearFlag write = 0xffff0000
No multiResetDetected, number of times = 0
SetFlag write = 0xfffe0001
No Multi Reset Detected
```

#### 4.2 Reset Detected => Reporting 1

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
multiResetDetectorFlag = 0xfffe0001
lowerBytes = 0x1, upperBytes = 0x1
No multiResetDetected, number of times = 1
SetFlag write = 0xfffd0002
No Multi Reset Detected
```

#### 4.3 Reset Detected => Reporting 2

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
multiResetDetectorFlag = 0xfffd0002
lowerBytes = 0x2, upperBytes = 0x2
No multiResetDetected, number of times = 2
SetFlag write = 0xfffc0003
No Multi Reset Detected
```

#### 4.4 Reset Detected => Reporting 3

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
multiResetDetectorFlag = 0xfffc0003
lowerBytes = 0x3, upperBytes = 0x3
No multiResetDetected, number of times = 3
SetFlag write = 0xfffb0004
No Multi Reset Detected
```

#### 4.5 Reset Detected => Reporting 4

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
multiResetDetectorFlag = 0xfffb0004
lowerBytes = 0x4, upperBytes = 0x4
No multiResetDetected, number of times = 4
SetFlag write = 0xfffa0005
No Multi Reset Detected
```

#### 4.6 Reset Detected => Reporting 5. Multi Reset Detected

```
MultiResetDetector minimal Example Program
MultiResetDetector_Generic v1.0.3
-----------------------------------
multiResetDetectorFlag = 0xfffa0005
lowerBytes = 0x5, upperBytes = 0x5
multiResetDetected, number of times = 5
ClearFlag write = 0xfffe0001
Multi Reset Detected
```

---
---

### Libraries using ESP_DoubleResetDetector or DoubleResetDetector_Generic library

You can also see how [`ESP_DoubleResetDetector`](https://github.com/khoih-prog/ESP_DoubleResetDetector) and [`DoubleResetDetector_Generic`](https://github.com/khoih-prog/DoubleResetDetector_Generic) are applied in many other libraries, such as:

 1. [Blynk_WM](https://github.com/khoih-prog/Blynk_WM)
 2. [BlynkEthernet_WM](https://github.com/khoih-prog/BlynkEthernet_WM)
 3. [WiFiManager_NINA_Lite](https://github.com/khoih-prog/WiFiManager_NINA_Lite)
 4. [BlynkESP32_BT_WF](https://github.com/khoih-prog/BlynkESP32_BT_WF), 
 5. [Blynk_GSM_Manager](https://github.com/khoih-prog/Blynk_GSM_Manager),
 6. [Blynk_Esp8266AT_WM](https://github.com/khoih-prog/Blynk_Esp8266AT_WM), 
 7. [Blynk_WiFiNINA_WM](https://github.com/khoih-prog/Blynk_WiFiNINA_WM), 
 8. [Blynk_Async_WM](https://github.com/khoih-prog/Blynk_Async_WM),
 9. [Blynk_Async_ESP32_BT_WF](https://github.com/khoih-prog/Blynk_Async_ESP32_BT_WF), 
10. [Blynk_Async_GSM_Manager](https://github.com/khoih-prog/Blynk_Async_GSM_Manager),
11. [ESP_WiFiManager](https://github.com/khoih-prog/ESP_WiFiManager)
12. [ESPAsync_WiFiManager](https://github.com/khoih-prog/ESPAsync_WiFiManager)
13. [WiFiManager_NINA_Lite](https://github.com/khoih-prog/WiFiManager_NINA_Lite)
14. [BlynkEthernet_STM32_WM](https://github.com/khoih-prog/BlynkEthernet_STM32_WM),
15. [ESP_AT_WM_Lite](https://github.com/khoih-prog/ESP_AT_WM_Lite)
16. [WIOTerminal_WiFiManager](https://github.com/khoih-prog/WIOTerminal_WiFiManager)
17. [Ethernet_Manager](https://github.com/khoih-prog/Ethernet_Manager)
18. [Ethernet_Manager_STM32](https://github.com/khoih-prog/Ethernet_Manager_STM32)

and the list is growing fast.

---
---

### Debug

Debug is disabled by default. To enable debug:

```cpp
// Use this to output debug msgs to Serial
#define MRD_GENERIC_DEBUG       true
```

---

## Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, applying Packages' Patches or this library latest version.


---
---

### Releases

### Releases v1.0.3

1. Initial coding to support Multiple Reset Detection.
2. Sync with DoubleResetDetector_Generic v1.0.3

---
---

### Issues

Submit issues to: [MultiResetDetector_Generic issues](https://github.com/khoih-prog/MultiResetDetector_Generic/issues)

---

### TO DO

1. Search for bug and improvement.
2. More examples and more supported boards.

### DONE

 1. Add support to **Arduino SAMD21 (ZERO, MKR, NANO_33_IOT, etc.)** using FlashStorage_SAMD.
 2. Add support to **Adafruit SAMD21 (Itsy-Bitsy M0, Metro M0, Feather M0 Express, etc.)**  using FlashStorage_SAMD.
 3. Add support to **Adafruit SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)**  using FlashStorage_SAMD.
 4. Add support to **Adafruit nRF52 ( Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.** using LittleFS.
 5. Add support to SAM DUE using DueFlashStorage.
 6. Add support to Seeeduino SAMD21/SAMD51: LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, Wio Terminal, Grove UI Wireless  using FlashStorage_SAMD.
 7. Add support to STM32F/L/H/G/WB/MP1 boards using EEPROM.
 8. Add support to Teensy boards using EEPROM.
 8. Add support to AVR Mega, Nano, UNO, etc boards using EEPROM.

---
---

### Contributions and thanks

1. Thanks to [Stephen Denne](https://github.com/datacute) for the [`DoubleResetDetector library`](https://github.com/datacute/DoubleResetDetector) this library is based upon.


<table>
  <tr>
    <td align="center"><a href="https://github.com/datacute"><img src="https://github.com/datacute.png" width="100px;" alt="datacute"/><br /><sub><b>⭐️ Stephen Denne</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/MultiResetDetector_Generic/blob/master/LICENSE)

---

### Copyright

Copyright 2020- Khoi Hoang
