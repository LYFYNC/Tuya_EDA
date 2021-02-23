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

#include "wifi_led.h"
#include "sht3x_update.h"
#include "button_control.h"
#include "time_update.h"

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
extern const unsigned char gImage_cloudy_sky[8192];
extern const unsigned char gImage_sunshine[8192];
extern const unsigned char gImage_rain[8192];

static void adc_demo(void);
int main(void)
{    
	
//    /* 清屏 */
    lcd_clear(WHITE);

//    /* 显示 RT-Thread logo */
//    lcd_show_image(0, 0, 240, 69, image_rttlogo);
	
//		lcd_show_image(0, 0, 64, 64, 	gImage_cloudy_sky);
//	  lcd_show_image(64, 0, 64, 64, 	gImage_sunshine);
//		lcd_show_image(128, 0, 64, 64, 	gImage_rain);
//    
//    /* 设置背景色和前景色 */
//    lcd_set_color(WHITE, BLACK);

//    /* 在 LCD 上显示字符 */
//    lcd_show_string(10, 69, 16, "Hello, RT-Thread!");
//    lcd_show_string(10, 69+16, 24, "RT-Thread");
//    lcd_show_string(10, 69+16+24, 32, "RT-Thread");
//    
//    /* 在 LCD 上画线 */
//    lcd_draw_line(0, 69+16+24+32, 240, 69+16+24+32);
//    
//    /* 在 LCD 上画一个同心圆 */
//    lcd_draw_point(120, 194);
//    for (int i = 0; i < 46; i += 4)
//    {
//        lcd_draw_circle(120, 194, i);
//    }
		
		serial_tuya = rt_device_find("uart1");
		rt_device_open(serial_tuya, RT_DEVICE_FLAG_INT_RX);
		rt_device_set_rx_indicate(serial_tuya, uartinput);
		
//        static char msg_pool[1024 * 5];
//        result = rt_mq_init(&rx_mq, "battery mq",
//                       msg_pool,                 /*  */
//                       RT_SERIAL_BATTERY_SIZE,   /*  */
//                       sizeof(msg_pool),         /*  */
//                       RT_IPC_FLAG_FIFO);        /*  */
//        if(RT_EOK != result) LOG_E("encoder message queue create failed");

    rt_pin_mode(PIN_BEEP, PIN_MODE_OUTPUT);
		rt_pin_write(PIN_BEEP, 1);
		rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
		rt_pin_write(LED_PIN, 0);
		rt_pin_mode(LEFT_PIN, PIN_MODE_INPUT);
		rt_pin_mode(RIGHT_PIN, PIN_MODE_INPUT);
		
		rt_pin_mode(PIN_USB_CHECK, PIN_MODE_INPUT);
		

    gWifiLedInit();
		gSht3xUpdateInit();
		gButtonControlInit();
		gTimeUpdateInit();
		
		rt_thread_mdelay(2000); //等待两秒涂鸦模块启动
		mcu_open_weather();
	  wifi_protocol_init();
		


		while(1)
		{
        wifi_uart_service();    //串口服务

			  Button_Process();
			  rt_thread_mdelay(20);
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
	
//	  len = rt_device_read(serial_tuya, 0, buff, 100);
//	  for(char i = 0; i < len; i++)
//	  {
//		    rt_kprintf("%X ", buff[i]);
//		}
//		rt_kprintf("\n");
//    msg.size = rt_device_read(serial_tuya, 0, msg.data, sizeof(msg.data)) + 4;    //
//    result = rt_mq_send(&rx_mq, &msg, msg.size);        //
//    if(result == -RT_EFULL)
//    {   /*  */
//        rt_kprintf("battery message queue full");
//    }
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

