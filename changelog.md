## MultiResetDetector_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/MultiResetDetector_Generic.svg?)](https://www.ardu-badge.com/MultiResetDetector_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/MultiResetDetector_Generic.svg)](https://github.com/khoih-prog/MultiResetDetector_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/MultiResetDetector_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/MultiResetDetector_Generic.svg)](http://github.com/khoih-prog/MultiResetDetector_Generic/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Major Releases v1.7.0](#major-releases-v170)
  * [Major Releases v1.6.0](#major-releases-v160)
  * [Major Releases v1.5.0](#major-releases-v150)
  * [Major Releases v1.4.0](#major-releases-v140)
  * [Major Releases v1.3.0](#major-releases-v130)
  * [Major Releases v1.2.0](#major-releases-v120)
  * [Major Releases v1.1.0](#major-releases-v110)
  * [Releases v1.0.3](#releases-v103)

---
---

## Changelog

### Major Releases v1.7.0

1. Add support to **Portenta_H7** using [**Arduino mbed_portenta core**](https://github.com/arduino/ArduinoCore-mbed).
2. Update `Packages' Patches` for **Portenta_H7**

### Major Releases v1.6.0

1. Add support to **MBED nRF52840-based boards such as Nano_33_BLE, Nano_33_BLE_Sense**, etc. using [**Arduino-mbed mbed_nano** core](https://github.com/arduino/ArduinoCore-mbed)

### Major Releases v1.5.0

1. Add support to Realtek RTL8720DN, RTL8722DM, RTL8722CSM, etc., using [`Arduino AmebaD core`](https://github.com/ambiot/ambd_arduino)

### Major Releases v1.4.0

1. Permit more control over LittleFS for RP2040 Arduino mbed core, such as `FORCE_REFORMAT`, `MBED_RP2040_INITIALIZED`, `MRD_MBED_LITTLEFS_NEED_INIT`.

### Major Releases v1.3.0

1. Add support to RP2040-based boards, such as **Nano RP2040 Connect**, using [**Arduino mbed OS for Nano boards**](https://github.com/arduino/ArduinoCore-mbed) and LittleFS.
1. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) and LittleFS.

### Major Releases v1.2.0

1. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [Earle Philhower's arduino-pico core](https://github.com/earlephilhower/arduino-pico) and LittleFS.

### Major Releases v1.1.0

1. Use new efficient [**FlashStorage_STM32** library](https://github.com/khoih-prog/FlashStorage_STM32). 
2. Add support to new **STM32 core v2.0.0** and **STM32L5**

### Releases v1.0.3

1. Initial coding to support Multiple Reset Detection.
2. Sync with DoubleResetDetector_Generic v1.0.3

