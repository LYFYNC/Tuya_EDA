#include "sht3x_update.h"

static struct rt_thread sht3x_update;
static char SHT3X_UPDATE_STACK[SHT3X_UPDATE_STACK_SIZE];

static sht3x_device_t dev;

static void WifiLedEntry(void *parameter);

void gSht3xUpdateInit(void)
{
	  rt_err_t result;
	
    result = rt_thread_init(&sht3x_update, "sht3x update", WifiLedEntry, RT_NULL, SHT3X_UPDATE_STACK, SHT3X_UPDATE_STACK_SIZE, SHT3X_UPDATE_PRIORITY, 0);
	  if(RT_EOK != result)  rt_kprintf("sht3x update thread create failed\n");
	  else rt_thread_startup(&sht3x_update);
	
		dev = sht3x_init("i2c1soft", SHT3X_ADDR_PD);
		if(!dev)
		{
				rt_kprintf("sht3x probe failed, check input args\n");
		}
		else
		{
			rt_kprintf("sht3x probed, addr:0x%x\n", SHT3X_ADDR_PD) ;
		}

}

static void sht3xguiupdate(signed char tem, unsigned char hum)
{
	  char str[13];
	
	  sprintf(str, "室内温度:%d℃ ", tem);
	  
    lv_label_set_text(label_tem, str);
	
	  sprintf(str, "室内湿度:%d%%", hum);
	  
    lv_label_set_text(label_hum, str);
}

extern unsigned char mcu_dp_value_update(unsigned char dpid,unsigned long value);
static void WifiLedEntry(void *parameter)
{
    while(1)
		{
			  sht3x_read_singleshot(dev);
			  mcu_dp_value_update(DPID_TEMP_CURRENT, dev->temperature);
			  mcu_dp_value_update(DPID_HUMIDITY_VALUE, dev->humidity);
			
			  sht3xguiupdate(dev->temperature, dev->humidity);
			  
		    rt_thread_mdelay(5000);
		}
}

