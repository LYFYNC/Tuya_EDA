/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-07     yangjie      first implementation
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <drv_lcd.h>
#include <rttlogo.h>
#include <stdbool.h>
#include "global_conf.h"
#include "wifi_led.h"
#include "sht3x_update.h"
#include "button_control.h"
#include "time_update.h"
#include "weather.h"
#include "wm_timer.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_demo_benchmark.h"
#include "lv_demo_keypad_encoder.h"
#include "gui.h"

BILIBILI bili;

#define LED_PIN      PIN_LED_R
#define RIGHT_PIN    PIN_TOUCH_R
#define LEFT_PIN     PIN_TOUCH_L

struct wifi_rx_msg
{
    rt_size_t size;
    char data[1024 - 4];
};
rt_device_t serial_tuya; 
static rt_err_t uartinput(rt_device_t dev, rt_size_t size);

static bool led_status = false;
extern void wifi_uart_service(void);
extern void wifi_protocol_init(void);

extern void mcu_open_weather(void);
extern const unsigned char gImage_qingtian[32768];

static void adc_demo(void);
static int timer_demo(void);

int main(void)
{    
	
	  rt_thread_mdelay(2000);
//    /* 清屏 */
    lcd_clear(WHITE);
//    lcd_fill(0,0,320,240,RED);
//	  lcd_clear(WHITE);
		
		serial_tuya = rt_device_find("uart1");
		rt_device_open(serial_tuya, RT_DEVICE_FLAG_INT_RX);
		rt_device_set_rx_indicate(serial_tuya, uartinput);
		

    rt_pin_mode(PIN_BEEP, PIN_MODE_OUTPUT);
		rt_pin_write(PIN_BEEP, 1);
		rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
		rt_pin_write(LED_PIN, 0);
		rt_pin_mode(LEFT_PIN, PIN_MODE_INPUT);
		rt_pin_mode(RIGHT_PIN, PIN_MODE_INPUT);
		
		rt_pin_mode(PIN_USB_CHECK, PIN_MODE_INPUT);
		

		gSht3xUpdateInit();
		gButtonControlInit();
		gWifiLedInit();
		gTimeUpdateInit();
    gWeatherInit();		

	  wifi_protocol_init();
		
    timer_demo();
		
		lv_init();
		lv_port_disp_init();
    lv_port_indev_init();
#if 1		
		gGuiInit();
		#else
		lv_qm_ui_entry();
#endif
//		lv_demo_benchmark();
//    lv_demo_stress();
//    lv_demo_keypad_encoder();

		while(1)
		{
        wifi_uart_service();    //串口服务

//			  Button_Process();
//			  rt_thread_mdelay(20);
			
			lv_task_handler();
			rt_thread_mdelay(10);
		}
    return 0;
}
extern void uart_receive_input(unsigned char value);
extern void uart_receive_buff_input(unsigned char value[], unsigned short data_len);
static rt_err_t uartinput(rt_device_t dev, rt_size_t size)
{
    struct wifi_rx_msg msg;
    rt_err_t result;
    unsigned char buff[256];
	  char len;
	
	  len = rt_device_read(serial_tuya, 0, buff, 256);
	
	  if(1 == len)
		{
			  uart_receive_input(buff[0]);
		}
		else
		{
	      uart_receive_buff_input(buff, len);
		}
	
    return result;
}
#include "tls_common.h"
#include "wm_adc.h"
extern void wm_adc_config(u8 Channel);
#define ADC_DEMO_CHANNEL 1
static void adc_demo(void)
{
    char temperature[8] = {0};
    u32 temp;

    wm_adc_config(ADC_DEMO_CHANNEL);
    adc_get_offset();
    temp = adc_get_inputVolt(ADC_DEMO_CHANNEL);
    sprintf(temperature, "%d.%d", temp / 1000, (temp % 1000) / 100);
//    printf("VOL: %s", temperature);
    adc_get_inputVolt(ADC_DEMO_CHANNEL);
    adc_get_interVolt();  
}

static void demo_timer_irq(u8 *arg)
{
    lv_tick_inc(10);
}


static int timer_demo(void)
{

    u8 timer_id;
    struct tls_timer_cfg timer_cfg;

    timer_cfg.unit = TLS_TIMER_UNIT_MS;
    timer_cfg.timeout = 10;
    timer_cfg.is_repeat = 1;
    timer_cfg.callback = demo_timer_irq;
    timer_cfg.arg = NULL;
    timer_id = tls_timer_create(&timer_cfg, 1);
    tls_timer_start(timer_id);
    printf("timer start\n");

    return WM_SUCCESS;
}

