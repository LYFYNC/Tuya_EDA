#ifndef _WEATHER_H_
#define _WEATHER_H_

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <string.h>
#include <stdbool.h>
#include "global_conf.h"
#include "drv_lcd.h"
#include "wifi.h"
#include "gui.h"

#define WEATHER_STACK_SIZE  1024
#define WEATHER_PRIORITY  20

typedef struct
{
    signed int temp;
	  signed int humidity;
	  char condition[50];
	  signed int pm25;
	
	  bool update;
}WEATHER;
extern WEATHER weather;

extern void gWeatherInit(void);
extern unsigned char gGetWeatherCondition(char *buff);

#endif
