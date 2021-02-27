#include "wifi_led.h"

#define LED_PIN     PIN_LED_R
static bool led_status = false;

static struct rt_thread wifi_led;
static char WIFI_LED_STACK[WIFI_LED_STACK_SIZE];

static void WifiLedEntry(void *parameter);

void gWifiLedInit(void)
{
	  rt_err_t result;
	
    result = rt_thread_init(&wifi_led, "wifi led", WifiLedEntry, RT_NULL, WIFI_LED_STACK, WIFI_LED_STACK_SIZE, WIFI_LED_PRIORITY, 0);
	  if(RT_EOK != result)  rt_kprintf("wifi led thread create failed\n");
	  else rt_thread_startup(&wifi_led);
}

unsigned char mcu_get_wifi_work_state(void);
static void WifiLedEntry(void *parameter)
{
	  static unsigned char state;
	  state = mcu_get_wifi_work_state();
	  rt_kprintf("wifi state %d\n", state);
    while(1)
		{
        state = mcu_get_wifi_work_state();
			  switch(state)
				{
					case SMART_CONFIG_STATE:
						rt_pin_write(LED_PIN, led_status);
					  led_status = ! led_status;
					  rt_thread_mdelay(250);
						break;
					case AP_STATE:
						rt_pin_write(LED_PIN, led_status);
					  led_status = ! led_status;
					  rt_thread_mdelay(1500);
						break;
					case WIFI_NOT_CONNECTED:
						rt_pin_write(LED_PIN, 1);
					  rt_thread_mdelay(1000);
						break;
					case WIFI_CONNECTED:
						rt_pin_write(LED_PIN, 0);
					  rt_thread_mdelay(1000);
						break;
					case WIFI_CONN_CLOUD:
						rt_pin_write(LED_PIN, 0);
					  rt_thread_mdelay(1000);
						break;
					case WIFI_LOW_POWER:
						rt_pin_write(LED_PIN, 1);
					  rt_thread_mdelay(1000);
						break;
					case SMART_AND_AP_STATE:
						rt_pin_write(LED_PIN, led_status);
					  led_status = ! led_status;
					  rt_thread_mdelay(250);
						break;
					default: 
						rt_thread_mdelay(1000);
						break;
				}
				bili.wifi_state = state;
		}
}

