# SFB Squareline Studio M5 Core2 Display Interface

This Arduino library contains an example of a display interface, designed with Squareline and implemented on a M5 Core2.

## Features
* Fully functional display interface.
* Modifiable values on the display.
* Slider with value feedback and 0.25 step value.
* Two modes with different appearances on the display.

## Installation
To install the Squareline Studio M5 Core2 Display Interface Library for the M5Core2 Development Kit, follow these steps:
* Download the latest release from the GitHub repository.
* Go to **`Sketch > Include Library > Add .ZIP Library`** and select the downloaded ZIP file.
* Install the 8.3.4 verion of the LVGL library.
* Install the M5 libraries and boards.

## Example
This library has an example file which initialises the interface and lists all functions to interact with the display.
To open this file go to **`File > Examples > M5Core2 Squareline Driver`** and select basic.

## Altering the UI
* Delete all files and folders in the src folder exept **`displayDriver.cpp`**, **`displayDriver.h`** and **`lv_conf.h`**.
* Open the Squareline Studio Project in the sourcefiles folder.
* After all the necessary changes export the UI files to the src folder.

## Driver Files
The driver files used to link LVGL to the M5 peripherals are **`displayDriver.cpp`** and **`displayDriver.h`**. This files contain all neccesarry code to link LVGL to the display and touchpad. **`lv_conf.h`** is the config file for LVGL.

*Note:* There is an implementation of the FMT library in the src folder. This library has different licencing than the rest of the project.

## Compatibility
This library is only compatible with the M5Core2 Development Kit, but it should be easy to convert it to a different M5 board.
