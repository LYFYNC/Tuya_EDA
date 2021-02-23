#include "time_update.h"


static struct rt_thread time_update;
static char TIME_UPDATE_STACK[TIME_UPDATE_STACK_SIZE];

static time_config tuya_time;

static void TimeUpdateEntry(void *parameter);
static void TimeUpdate(time_config time);

void gTimeUpdateInit(void)
{
	  rt_err_t result;
	
    result = rt_thread_init(&time_update, "time update", TimeUpdateEntry, RT_NULL, TIME_UPDATE_STACK, TIME_UPDATE_STACK_SIZE, TIME_UPDATE_PRIORITY, 0);
	  if(RT_EOK != result)  rt_kprintf("time update thread create failed\n");
	  else rt_thread_startup(&time_update);
}
extern void mcu_get_green_time(void);
static void TimeUpdateEntry(void *parameter)
{
    while(1)
		{
		    mcu_get_green_time();
			  TimeUpdate(tuya_time);
			  rt_thread_mdelay(500);
		}
}

static void TimeUpdate(time_config time)
{
	  lcd_show_num(0, 64, 2000 + time.year, 4, 32);
	  lcd_show_string(16*4, 64, 32, ".");
	
	  if(time.month < 10) 
		{
			  lcd_show_num(16*5, 64, 0, 1, 32);
			  lcd_show_num(16*6, 64, time.month, 1, 32);
		}
		else
		{
				lcd_show_num(16*5, 64, time.month, 2, 32);
		}
	  lcd_show_string(16*7, 64, 32, ".");
		
		if(time.day < 10)
		{
        lcd_show_num(16*8, 64, 0, 1, 32);
			  lcd_show_num(16*9, 64, time.day, 1, 32);
		}
		else
		{
			  lcd_show_num(16*8, 64, time.day, 2, 32);
		}
	
		if(time.hour < 10)
		{
				lcd_show_num(0, 96, 0, 1, 32);
			  lcd_show_num(16, 96, time.hour, 1, 32);
		}
		else
		{
			  lcd_show_num(0, 96, time.hour, 2, 32);
		}
	  lcd_show_string(16*2, 96, 32, ":");
		
		if(time.minuter < 10)
		{
				lcd_show_num(16*3, 96, 0, 1, 32);
			  lcd_show_num(16*4, 96, time.minuter, 1, 32);
		}
		else
		{
			  lcd_show_num(16*3, 96, time.minuter, 2, 32);
		}
	  lcd_show_string(16*5, 96, 32, ":");
		
		if(time.second < 10)
		{
				lcd_show_num(16*6, 96, 0, 1, 32);
			  lcd_show_num(16*7, 96, time.second, 1, 32);
		}
		else
		{
			  lcd_show_num(16*6, 96, time.second, 2, 32);
		}
}

void gWriteTime(unsigned char *buff)
{
    tuya_time.year = buff[1];
	  tuya_time.month = buff[2];
	  tuya_time.day = buff[3];
	  tuya_time.hour = buff[4];
	  tuya_time.minuter = buff[5];
	  tuya_time.second = buff[6];
}

