#include "time_update.h"

static struct rt_thread time_update;
static char TIME_UPDATE_STACK[TIME_UPDATE_STACK_SIZE];

static time_config tuya_time;
static time_config last_time;

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
	  while(!(WIFI_CONN_CLOUD == bili.wifi_state))
		{
		    rt_thread_mdelay(200);
		}
	  rt_kprintf("wifi connect internet\n");
		rt_thread_mdelay(3000);
    while(1)
		{
		    mcu_get_green_time();
			  TimeUpdate(tuya_time);
			  rt_thread_mdelay(100);
		}
}

static void TimeUpdate(time_config time)
{
	  unsigned char days = 0;
	  if(1 == time.month || 3 == time.month || 5 == time.month || 7 == time.month || 8 == time.month || 10 == time.month || 12 == time.month)
		{
		    days = 31;
		}
		else if(4 == time.month || 6 == time.month || 9 == time.month || 11 == time.month)
		{
		    days = 30;
		}
		else if(2 == time.month)
		{
		    if((time.year % 400 == 0) || ((time.year % 4 == 0) && (time.year % 100 != 0)))
				{
				    days =29;
				}
				else
				{
				    days = 28;
				}
		}
		time.hour += 8;
		if(time.hour >= 24)
		{
		    time.hour -= 24;
			  time.day++;
			  if(time.day > days)
				{
				    time.day = 1;
					  time.month++;
					  if(time.month > 12)
						{
						    time.year++;
						}
				}
		}
		
		if(last_time.minuter != time.minuter)
		{
			  char str[5];
			  if(time.hour < 10) sprintf(str, "0%d", time.hour);
			  else sprintf(str, "%d", time.hour);
			
			  if(time.minuter < 10) sprintf(str+2, ":0%d", time.minuter);
			  else sprintf(str+2, ":%d", time.minuter);
					
		    lv_label_set_text(label_time, str);
		}
		
		if(last_time.day != time.day)
		{
		    char str[10];
			  if(time.year < 10) sprintf(str, "200%d.", time.year);
			  else sprintf(str, "20%d.", time.year);
			
				if(time.month < 10) sprintf(str+5, "0%d.", time.month);
			  else sprintf(str+5, "%d.", time.month);
			
				if(time.day < 10) sprintf(str+8, "0%d", time.day);
			  else sprintf(str+8, "%d", time.day);
			
				lv_label_set_text(label_date, str);
		}
		
		last_time.year = time.year;
		last_time.month = time.month;
		last_time.day = time.day;
		last_time.hour = time.hour;
		last_time.minuter = time.minuter;
		
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

