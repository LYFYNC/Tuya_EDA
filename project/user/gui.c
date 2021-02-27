#include "gui.h"

lv_obj_t * background;
lv_obj_t *label_date;
lv_obj_t *label_week;
lv_obj_t *label_time;
lv_obj_t *label_weather;
lv_obj_t *label_tem;
lv_obj_t *label_hum;

LV_IMG_DECLARE(background_img);

static void guibackgroundinit(void)
{
    background = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(background, &background_img);
    static lv_style_t background_style;
    lv_style_init(&background_style);
    lv_obj_add_style(background,LV_IMG_PART_MAIN,&background_style);
    lv_obj_set_pos(background, 0, 0);
}
static void guitimecreate(void)
{
    label_time = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_long_mode(label_time, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
    lv_label_set_recolor(label_time, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_align(label_time, LV_LABEL_ALIGN_CENTER);       /*Center aligned lines*/
	
	  static lv_style_t style_date;
	  lv_style_init(&style_date);
	  lv_style_set_text_font(&style_date,LV_STATE_DEFAULT,&lv_font_montserrat_48);
	  lv_obj_add_style(label_time,LV_LABEL_PART_MAIN,&style_date);
	
	  lv_label_set_text(label_time, "12:00");
    lv_obj_set_size(label_time, 150, 50);
	  lv_obj_set_pos(label_time, 0, 30);
}
static void guidatecreate(void)
{
    label_date = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_long_mode(label_date, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
    lv_label_set_recolor(label_date, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_align(label_date, LV_LABEL_ALIGN_CENTER);       /*Center aligned lines*/
	
	  static lv_style_t style_date;
	  lv_style_init(&style_date);
	  lv_style_set_text_font(&style_date,LV_STATE_DEFAULT,&lv_font_montserrat_22);
	  lv_obj_add_style(label_date,LV_LABEL_PART_MAIN,&style_date);
	
	  lv_label_set_text(label_date, "2019.02.22");
    lv_obj_set_size(label_date, 200, 30);
	  lv_obj_set_pos(label_date, 140, 20);
}
static void guiweekcreate(void)
{
    label_week = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_long_mode(label_week, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
    lv_label_set_recolor(label_week, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_align(label_week, LV_LABEL_ALIGN_CENTER);       /*Center aligned lines*/
	
	  static lv_style_t style_date;
	  lv_style_init(&style_date);
	  lv_style_set_text_font(&style_date,LV_STATE_DEFAULT,&myFont15);
	  lv_obj_add_style(label_week,LV_LABEL_PART_MAIN,&style_date);
	
	  lv_label_set_text(label_week, "星期日 ");
    lv_obj_set_size(label_week, 172, 50);
	  lv_obj_set_pos(label_week, 148, 50);
}

static void guiweathercreate(void)
{
    label_weather = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_long_mode(label_weather, LV_LABEL_LONG_SROLL_CIRC);     /*Circular scroll*/
    lv_label_set_recolor(label_weather, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_align(label_weather, LV_LABEL_ALIGN_CENTER);       /*Center aligned lines*/
	
		static lv_style_t style_date;
	  lv_style_init(&style_date);
	  lv_style_set_text_font(&style_date,LV_STATE_DEFAULT,&myFont10);
	  lv_obj_add_style(label_weather,LV_LABEL_PART_MAIN,&style_date);
	
	  lv_label_set_text(label_weather, "今日天气 晴 温度:0℃ 湿度:0% PM2.5:0");
	  lv_obj_set_size(label_weather, 200, 40);
	  lv_obj_set_pos(label_weather, 60, 200);
}

static void guisht3xinit(void)
{
    label_tem = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_long_mode(label_tem, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
    lv_label_set_recolor(label_tem, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_align(label_tem, LV_LABEL_ALIGN_LEFT);       /*Center aligned lines*/
	
	  static lv_style_t style_date;
	  lv_style_init(&style_date);
	  lv_style_set_text_font(&style_date,LV_STATE_DEFAULT,&myFont15);
	  lv_obj_add_style(label_tem,LV_LABEL_PART_MAIN,&style_date);
	
	  lv_label_set_text(label_tem, "室内温度:25℃ ");
    lv_obj_set_size(label_tem, 200, 35);
	  lv_obj_set_pos(label_tem, 10, 100);
	
	  label_hum = lv_label_create(lv_scr_act(), label_tem);
	  lv_label_set_text(label_hum, "室内湿度:50%");
    lv_obj_set_size(label_hum, 200, 35);
	  lv_obj_set_pos(label_hum, 10, 135); 
}

void gGuiInit(void)
{
	  guibackgroundinit();
	  guitimecreate();
	  guidatecreate();
    guiweekcreate();
	  guiweathercreate();
	  guisht3xinit();
}


