#ifndef _BUTTON_CONTROL_H_
#define _BUTTON_CONTROL_H_

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <stdbool.h>

#include "button.h"

#define BUTTON_CONTROL_STACK_SIZE 512
#define BUTTON_CONTROL_PRIORITY 20

extern void gButtonControlInit(void);

#endif
