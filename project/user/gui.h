#ifndef _GUI_H_
#define _GUI_H_

#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"

extern lv_obj_t * background;
extern lv_obj_t *label_date;
extern lv_obj_t *label_week;
extern lv_obj_t *label_time;
extern lv_obj_t *label_weather;
extern lv_obj_t *label_tem;
extern lv_obj_t *label_hum;


extern void gGuiInit(void);


#endif
