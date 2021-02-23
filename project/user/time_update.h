#ifndef _TIME_UPDATE_H_
#define _TIME_UPDATE_H_

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "drv_lcd.h"


#define TIME_UPDATE_STACK_SIZE 1024
#define TIME_UPDATE_PRIORITY   20

typedef struct 
{
    unsigned char year;
	  unsigned char month;
	  unsigned char day;
	  unsigned char hour;
	  unsigned char minuter;
	  unsigned char second;
}time_config;


extern void gTimeUpdateInit(void);
extern void gWriteTime(unsigned char *buff);

#endif
