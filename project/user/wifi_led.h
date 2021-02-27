#ifndef _WIFI_LED_H_
#define _WIFI_LED_H_

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <stdbool.h>
#include "global_conf.h"
#include "wifi.h"

#define WIFI_LED_STACK_SIZE  512
#define WIFI_LED_PRIORITY    20

extern void gWifiLedInit(void);

#endif
