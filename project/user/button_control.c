#include "button_control.h"

#define LEFT_PIN     PIN_TOUCH_L
#define RIGHT_PIN    PIN_TOUCH_R
#define BTN_TRIGGER 0

static struct rt_thread button_control;
static char BUTTON_CONTROL_STACK[BUTTON_CONTROL_STACK_SIZE];

static Button_t Button1;
static Button_t Button2;

static uint8_t time_count = 0;
static uint8_t wifi_reset_count = 0;

static uint8_t Read_Button1_Level(void);
static uint8_t Read_Button2_Level(void);
static void Btn1_Dowm_CallBack(void *btn);
static void Btn1_Double_CallBack(void *btn);
static void Btn1_Long_CallBack(void *btn);
static void Btn2_Dowm_CallBack(void *btn);
static void Btn2_Double_CallBack(void *btn);
static void Btn2_Long_CallBack(void *btn);
static void ButtonControlEntry(void *parameter);

void gButtonControlInit(void)
{
	  rt_err_t result;
	
		Button_Create("Button1",
							&Button1,
							Read_Button1_Level,
							BTN_TRIGGER);
	
	  Button_Attach(&Button1,BUTTON_DOWM,Btn1_Dowm_CallBack);
    Button_Attach(&Button1,BUTTON_DOUBLE,Btn1_Double_CallBack);
    Button_Attach(&Button1,BUTTON_LONG,Btn1_Long_CallBack);
	
		Button_Create("Button2",
						&Button2,
						Read_Button2_Level,
						BTN_TRIGGER);
	
	  Button_Attach(&Button2,BUTTON_DOWM,Btn2_Dowm_CallBack);
    Button_Attach(&Button2,BUTTON_DOUBLE,Btn2_Double_CallBack);
    Button_Attach(&Button2,BUTTON_LONG,Btn2_Long_CallBack);
	
	  Get_Button_Event(&Button1);

	result = rt_thread_init(&button_control, "button control", ButtonControlEntry, RT_NULL, BUTTON_CONTROL_STACK, BUTTON_CONTROL_STACK_SIZE, BUTTON_CONTROL_PRIORITY, 0);
	  if(RT_EOK != result)  rt_kprintf("wifi led thread create failed\n");
	  else rt_thread_startup(&button_control);	
	  
}

static uint8_t Read_Button1_Level(void)
{
  return rt_pin_read(LEFT_PIN);
}
static uint8_t Read_Button2_Level(void)
{
  return rt_pin_read(RIGHT_PIN);
}

static void Btn1_Dowm_CallBack(void *btn)
{
	  wifi_reset_count++;
	  time_count = 0;
	  rt_kprintf("count = %d\n", wifi_reset_count);
}

static void Btn1_Double_CallBack(void *btn)
{
    rt_kprintf("double click button\n");
}

static void Btn1_Long_CallBack(void *btn)
{
    if(3 == wifi_reset_count)
		{
			  wifi_reset_count = 0;
		    rt_kprintf("mcu reset tuya wifi\n");
		}
}
static bool beep = false;
static void Btn2_Dowm_CallBack(void *btn)
{
	  beep = !beep;
	  rt_pin_write(PIN_BEEP, beep);
	  rt_kprintf("click button\n");
}

static void Btn2_Double_CallBack(void *btn)
{
    rt_kprintf("double click button\n");
}

static void Btn2_Long_CallBack(void *btn)
{
    rt_kprintf("long click button\n");
}

static void ButtonControlEntry(void *parameter)
{

    while(1)
		{
		    time_count++;
			  if(time_count >= 30)
				{
				    time_count = 0;
					  wifi_reset_count = 0;
				}
			  rt_thread_mdelay(100);
		}
}


