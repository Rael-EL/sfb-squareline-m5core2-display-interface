/**
 ******************************************************************************
 * Dateiname           	: displayDriver.cpp
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
#include "displayDriver.h"
#include <M5Core2.h>
#include <string.h>
#include "fmt/fmt.h"

static lv_disp_draw_buf_t draw_buf;
M5Display *tft;

float ManFlowVal = 0;

void disp_init() {	//Initalize display and touch sensors in the correct order
	lv_init();
	tft_lv_initialization();
	init_disp_driver();
	init_touch_driver();
	ui_init();
	lv_slider_set_range(ui_ManFlowSlider, 0, lpm_range ? 380:140);
}

void disp_update(){
	lv_task_handler();
	float RawVal =  getManFlowVal();
	ManFlowVal = 0.25 * RawVal + 5.0;
	setSollFlowManVal(ManFlowVal);
	setManFlowVal(ManFlowVal);
}

void tft_lv_initialization() {
	static lv_color_t buf1[(LV_HOR_RES_MAX * LV_VER_RES_MAX) / 10]; // Declare a buffer for 1/10 screen size
	static lv_color_t buf2[(LV_HOR_RES_MAX * LV_VER_RES_MAX) / 10]; // second buffer is optionnal

	// Initialize `disp_buf` display buffer with the buffer(s).
	lv_disp_draw_buf_init(&draw_buf, buf1, buf2,
			(LV_HOR_RES_MAX * LV_VER_RES_MAX) / 10);

	tft = &M5.Lcd;
}

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area,
		lv_color_t *color_p) {
	uint32_t w = (area->x2 - area->x1 + 1);
	uint32_t h = (area->y2 - area->y1 + 1);

	tft->startWrite();
	tft->setAddrWindow(area->x1, area->y1, w, h);
	tft->pushColors((uint16_t*) &color_p->full, w * h, true);
	tft->endWrite();

	lv_disp_flush_ready(disp);
}

void init_disp_driver() {
	// Initialize the display
	static lv_disp_drv_t disp_drv;	// Descriptor of a display driver

	lv_disp_drv_init(&disp_drv);	// Basic initialization

	disp_drv.flush_cb = my_disp_flush; // Set your driver function
	disp_drv.draw_buf = &draw_buf;     // Assign the buffer to the display
	disp_drv.hor_res = LV_HOR_RES_MAX; // Set the horizontal resolution of the display
	disp_drv.ver_res = LV_VER_RES_MAX; // Set the vertical resolution of the display

	lv_disp_drv_register(&disp_drv);					// Finally register the driver
	lv_disp_set_bg_color(NULL, lv_color_hex3(0x000));	// Set default background color to black
}

void my_touchpad_read(lv_indev_drv_t *drv, lv_indev_data_t *data) {		//Initialize the touchpad
	TouchPoint_t pos = M5.Touch.getPressPoint();	//Copy the touchpad information into the pos struct
	bool touched = (pos.x == -1) ? false : true;	//Detect if the touchpad was touched

	if (!touched) {
		data->state = LV_INDEV_STATE_REL;	//Set the state to released
	} else {
		data->state = LV_INDEV_STATE_PR;	//Set the state to pressed
		data->point.x = pos.x;				//set the x and y coordinates
		data->point.y = pos.y;
	}
}

void init_touch_driver() {
	static lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = my_touchpad_read;
	lv_indev_t *my_indev = lv_indev_drv_register(&indev_drv);
}

void setTemp(float Val){									//Write temperature to display
	std::string str_number = fmt::format("{0:.1f}°C", Val);	//Convert float to string and strip appended zeroes
	const char* char_ptr = str_number.c_str();				//Create a pointer to the string
	lv_label_set_text(ui_TempVal, char_ptr);				//Write Char array at pointer address to screen
}

void setSollFlow(float Val){								//Write SollFlow to display
	std::string str_number = fmt::format("{0:.2f}lpm", Val);	//Convert float to string and strip appended zeroes
	const char* char_ptr = str_number.c_str();				//Create a pointer to the string
	lv_label_set_text(ui_SollFlowVal, char_ptr);			//Write Char array at pointer address to screen
}

void setIstFlow(float Val){									//Write IstFlow to display
	std::string str_number = fmt::format("{0:.2f}lpm", Val);	//Convert float to string and strip appended zeroes
	const char* char_ptr = str_number.c_str();				//Create a pointer to the string
	lv_label_set_text(ui_IstFlowVal, char_ptr);			//Write Char array at pointer address to screen
}

void setSollFlowManVal(float Val){							//Write Manual Flow to display
	std::string str_number = fmt::format("{0:.2f}lpm", Val);	//Convert float to string and strip appended zeroes
	const char* char_ptr = str_number.c_str();				//Create a pointer to the string
	lv_label_set_text(ui_SollFlowManVal, char_ptr);			//Write Char array at pointer address to screen
}

void setManFlowVal(float Val){								//Write Manual Flow to second screen
	std::string str_number = fmt::format("{0:.2f}lpm", Val);	//Convert float to string and strip appended zeroes
	const char* char_ptr = str_number.c_str();				//Create a pointer to the string
	lv_label_set_text(ui_ManFlowVal, char_ptr);				//Write Char array at pointer address to screen
}

int getManFlowVal(){									//Get Manual Flow
	return lv_slider_get_value(ui_ManFlowSlider);
}

void setComStatus(bool State){							//Set the system in Remote Control mode
	State == 1 ? lv_obj_add_state(ui_RCmode, LV_STATE_CHECKED) : lv_obj_clear_state(ui_RCmode, LV_STATE_CHECKED);
	lv_event_send(ui_RCmode, LV_EVENT_VALUE_CHANGED, NULL);

}
