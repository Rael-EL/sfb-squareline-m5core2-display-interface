/**
 ******************************************************************************
 * Dateiname           	: displayDriver.h
 * Projekt     		   	: M5Core2 display driver
 * Version				: V 1.0
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
#ifndef DISPLAY_DRIVER_H
#define DISPLAY_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif


/*********************
 *      DEFINES
 *********************/
#define LV_HOR_RES_MAX 320 		//Set screen resolution
#define LV_VER_RES_MAX 240

/*********************
 *      INCLUDES
 *********************/
#include "lv_conf.h"
#include <lvgl.h>
#include "ui.h"

/*********************
 *FUNCTION PROTOTYPES
 *********************/
void tft_lv_initialization();
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void init_disp_driver();
void my_touchpad_read(lv_indev_drv_t * drv, lv_indev_data_t * data);
void init_touch_driver();
void disp_init();
void disp_update();
void setTemp(float Val);
void setSollFlow(float Val);
void setIstFlow(float Val);
void setSollFlowManVal(float Val);
void setManFlowVal(float Val);
int getManFlowVal();
void setComStatus(bool State);

/*********************
 *VARIABLE PROTOTYPES
 *********************/
extern float ManFlowVal;

#ifdef __cplusplus
} /*extern "C"*/
#endif

extern int lpm_range;

#endif /*DISPLAY_DRIVER_H*/
