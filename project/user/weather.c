#include "weather.h"

extern const unsigned char gImage_cloudy_sky[8192];
extern const unsigned char gImage_sunshine[8192];
extern const unsigned char gImage_rain[8192];

unsigned char qing[] = {0xE6, 0x99, 0xB4};
unsigned char dabuqinglang[] = {0xE5, 0xA4, 0xA7, 0xE9, 0x83, 0xA8, 0xE6, 0x99, 0xB4, 0xE6, 0x9C, 0x97};
unsigned char duoyun[] = {0xE5, 0xA4, 0x9A, 0xE4, 0xBA, 0x91};
unsigned char yin[] = {0xE9, 0x98, 0xB4};
unsigned char xiaoyu[] = {0xE5, 0xB0, 0x8F, 0xE9, 0x9B, 0xA8};
unsigned char zhongyu[] = {0xE4, 0xB8, 0xAD, 0xE9, 0x9B, 0xA8};
unsigned char zhongdaodayu[] = {0xE4, 0xB8, 0xAD, 0xE5, 0x88, 0xB0, 0xE5, 0xA4, 0xA7, 0xE9, 0x9B, 0xA8};
unsigned char dayu[] = {0xE5, 0xA4, 0xA7, 0xE9, 0x9B, 0xA8};
	

unsigned char gGetWeatherCondition(char *buff)
{
    if(0 == memcmp(qing, buff, 3)) return 120;
	  else if(0 == memcmp(dabuqinglang, buff, 12)) return 119;
	  else if(0 == memcmp(duoyun, buff, 6)) return 142;
	  else if(0 == memcmp(yin, buff, 3)) return 132;
	  else if(0 == memcmp(xiaoyu, buff, 6)) return 139;
	  else if(0 == memcmp(zhongyu, buff, 6)) return 141;
	  else if(0 == memcmp(zhongdaodayu, buff, 12)) return 144;
	  else if(0 == memcmp(dayu, buff, 6)) return 101;
	  else return 0;
}

void gWeatherContitionDisplay(unsigned char state)
{
	  rt_kprintf("weather state %d\n", state);
    switch(state)
		{
			case 119:
						lcd_show_image(0, 0, 64, 64, 	gImage_sunshine);
				break;
			case 120:
				    lcd_show_image(0, 0, 64, 64, 	gImage_sunshine);
				break;
			
			default:
				break;
		}
}

void gWeatherTempDisplay(uint32_t temp)
{
    lcd_show_string(0, 128, 32, "temple:");
	  lcd_show_num(16*7, 128, temp, 4, 32);
}

void gWeatherHumidityDisplay(uint32_t humidity)
{
    lcd_show_string(0, 160, 32, "humidity:");
	  lcd_show_num(16*9, 160, humidity, 4, 32);
}

void gWeatherPm25Display(uint32_t pm25)
{
	  lcd_show_string(0, 192, 32, "pm25:");
	  lcd_show_num(16*5, 192, pm25, 4, 32);
}

