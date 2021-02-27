#include "weather.h"


WEATHER weather;

unsigned char dayu[] = {0xE5, 0xA4, 0xA7, 0xE9, 0x9B, 0xA8};
unsigned char baoyu[] = {0xE6, 0x9A, 0xB4, 0xE9, 0x9B, 0xA8};
unsigned char zhenyu[] = {0xE9, 0x98, 0xB5, 0xE9, 0x9B, 0xA8};
unsigned char qing[] = {0xE6, 0x99, 0xB4};
unsigned char yintian[] = {0xE9, 0x98, 0xB4};
unsigned char dabaoyu[] = {0xE5, 0xA4, 0xA7, 0xE6, 0x9A, 0xB4, 0xE9, 0x9B, 0xA8};
unsigned char xiaoyu[] = {0xE5, 0xB0, 0x8F, 0xE9, 0x9B, 0xA8};
unsigned char zhongyu[] = {0xE4, 0xB8, 0xAD, 0xE9, 0x9B, 0xA8};
unsigned char leizhenyu[] = {0xE9, 0x9B, 0xB7, 0xE9, 0x98, 0xB5, 0xE9, 0x9B, 0xA8};

static struct rt_thread weather_thread;
static char WEATHER_LED_STACK[WEATHER_STACK_SIZE];

static void WeatherEntry(void *parameter);
void gWeatherInit(void)
{
	  rt_err_t result;
	
    result = rt_thread_init(&weather_thread, "weather", WeatherEntry, RT_NULL, WEATHER_LED_STACK, WEATHER_STACK_SIZE, WEATHER_PRIORITY, 0);
	  if(RT_EOK != result)  rt_kprintf("weather thread create failed\n");
	  else rt_thread_startup(&weather_thread);
}
static void WeatherEntry(void *parameter)
{
	  while(!(WIFI_CONN_CLOUD == bili.wifi_state))
		{
		    rt_thread_mdelay(200);
		}
		rt_kprintf("wifi connect intnet\n");
		rt_thread_mdelay(3000);
		mcu_open_weather();

    while(1)
		{
			  char str[320];
			  char len;
			  if(true == weather.update)
				{
					  weather.update = false;
					  
				    sprintf(str, "天气 %s ", weather.condition);
					  len = strlen(weather.condition);
					  len += 8;
					
						sprintf(str+len, "温度:%d℃ ", weather.temp);
					  
					  if(weather.temp <= -10) len += 14;
					  else if(weather.temp < 0) len += 13;
					  else if(weather.temp < 10) len += 12;
					  else len += 13;
					
						sprintf(str+len, "湿度:%d%% ", weather.humidity);
					  
					  if(weather.humidity < 10) len += 10;
					  else if(weather.humidity < 100) len += 11;
					  else len += 12;

					  sprintf(str+len, "PM2.5:%d ", weather.pm25);
					
					  lv_label_set_text(label_weather, str);
				}
		    rt_thread_mdelay(200);
		}
}

unsigned char gGetWeatherCondition(char *buff)
{
    if(0 == memcmp(dayu, buff, 6)) return 101;
	  else if(0 == memcmp(baoyu, buff, 6)) return 107;
		else if(0 == memcmp(qing, buff, 3)) return 120;
	  else if(0 == memcmp(zhenyu, buff, 6)) return 122;
	  else if(0 == memcmp(yintian, buff, 6)) return 132;
	  else if(0 == memcmp(dabaoyu, buff, 9)) return 134;
	  else if(0 == memcmp(xiaoyu, buff, 6)) return 139;
	  else if(0 == memcmp(zhongyu, buff, 6)) return 141;
	  else if(0 == memcmp(leizhenyu, buff, 9)) return 143;
	  else return 0;
}
extern const unsigned char gImage_baoxue[32768];
void gWeatherContitionDisplay(unsigned char state)
{
	  rt_kprintf("weather state %d\n", state);
    switch(state)
		{

		}
}

void gWeatherTempDisplay(uint32_t temp)
{
    lcd_show_string(128, 64, 32, "TEM:");
	  lcd_show_num(128+16*4, 64, temp, 4, 32);
}

void gWeatherHumidityDisplay(uint32_t humidity)
{
    lcd_show_string(128, 64+32, 32, "HUM:");
	  lcd_show_num(128+16*4, 64+32, humidity, 4, 32);
}

void gWeatherPm25Display(uint32_t pm25)
{
	  lcd_show_string(128, 64+64, 32, "PM25:");
	  lcd_show_num(128+16*5, 64+64, pm25, 4, 32);
}

