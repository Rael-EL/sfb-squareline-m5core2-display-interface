/**
 ******************************************************************************
 * Dateiname    : basics.ino
 * Projekt     	: M5Core2 display driver
 * Version			: V 1.0
 * Autor				: R. Duque
 *
 * Versionsgeschichte:
 *
 * Ver:			Beschreibung:				Erscheinungsdatum:
 * V1.0			Erste Version				27.02.24
 ******************************************************************************
 *
 * Copyright (c) 2024 PSI
 * All rights reserved.
 *
 *
 ******************************************************************************
 */
int lpm_range = 0; //Set to 1 to set device range from 5 to 100, if 0, range will be 5-40

#include <M5Core2.h>
#include <displayDriver.h>

void setup() {
  M5.begin();     //Start M5 hardware
  disp_init(); //Start diplay and touch drivers
}

void loop() {
  M5.update();    //Collect information such as touch position
  disp_update();  //Execute actions according to new input data


  setTemp(50.5);  		//Set temperature value on screen, followed by °C
  setIstFlow(100);		//Set ist Flow value on screen, followed by lpm
  setSollFlow(77.5); 	//Set soll Flow value on screen, followed by lpm

  Serial.println(ManFlowVal);  //Read Userflow from screen and write it to the serial port

  setComStatus(true); //Set Com value to true or false->green or red
}
