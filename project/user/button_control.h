#ifndef _BUTTON_CONTROL_H_
#define _BUTTON_CONTROL_H_

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <stdbool.h>

#include "button.h"

/** 0:扫描按键 1:中断按键 **/
#define BUTTON_MODE 0
#ifndef BUTTON_MODE
#define BUTTON_MODE 0
#endif

#if 0 == BUTTON_MODE

typedef enum
{
    NO_KEY = 0,
	  LEFT_CLICK_KEY,
	  LEFT_DOUBLE_KEY,
	  LEFT_LONG_KEY,
	  RIGHT_CLICK_KEY,
	  RIGHT_DOUBLE_KEY,
	  RIGHT_LONG_KEY,
			
}KEY_STATE;

extern unsigned char gLeftKeyRead(void);
extern unsigned char gRightKeyRead(void);

#else

#define BUTTON_CONTROL_STACK_SIZE 512
#define BUTTON_CONTROL_PRIORITY 20

#endif

extern void gButtonControlInit(void);

#endif
