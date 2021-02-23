#ifndef _SHT3X_UPDATE_H_
#define _SHT3X_UPDATE_H_

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "sht3x.h"
#include "protocol.h"

#define SHT3X_UPDATE_STACK_SIZE  1024
#define SHT3X_UPDATE_PRIORITY    20


extern void gSht3xUpdateInit(void);

#endif
