#include "button_control.h"

#define LEFT_PIN     PIN_TOUCH_L
#define RIGHT_PIN    PIN_TOUCH_R

#if 0 == BUTTON_MODE

#define KEY_TIME  10

#define LEFT_KEY rt_pin_read(LEFT_PIN)
#define RIGHT_KEY rt_pin_read(RIGHT_PIN)

static unsigned char left_key_state = 0; //0:初始状态 1:按键消抖 2:
static unsigned char left_key_state1 = 0;
static unsigned char left_time_count = 0;
static unsigned char left_time_count1 = 0;

static unsigned char right_key_state = 0; //0:初始状态 1:按键消抖 2:
static unsigned char right_key_state1 = 0;
static unsigned char right_time_count = 0;
static unsigned char right_time_count1 = 0;

void gButtonControlInit(void)
{
    rt_pin_mode(LEFT_PIN, PIN_MODE_INPUT);
	  rt_pin_mode(RIGHT_PIN, PIN_MODE_INPUT);
}

static unsigned char LeftKeyScan(void)
{
	  unsigned char rtn = 0;

    switch(left_key_state)
		{
		  case 0:
				if(0 == LEFT_KEY)
				{
					left_key_state = 1;    //
				}
				break;
			case 1:
				if(0 == LEFT_KEY)
				{
					  left_time_count = 0;
				    left_key_state = 2;    //消抖完成，按下计时开始
				}
				else
				{
				    left_key_state = 0;    //抖动
				}
				break;
			case 2:
				if(0 == LEFT_KEY)    //按键仍然被按下
				{
				    left_time_count++;
					  if(left_time_count >= KEY_TIME * 4)
						{
						    rtn = LEFT_LONG_KEY;
							  left_key_state = 3;    //等待长按释放
						}
				}
				else
				{
				    rtn = LEFT_CLICK_KEY;
					  left_key_state = 0;    //按键回到初始状态
				}
				break;
			case 3:
				if(1 == LEFT_KEY)
				{
				    left_key_state = 0;
				}
				break;
		}
		return rtn;
}
static unsigned char RightKeyScan(void)
{
	  unsigned char rtn = 0;

    switch(right_key_state)
		{
		  case 0:
				if(0 == RIGHT_KEY)
				{
					right_key_state = 1;    //
				}
				break;
			case 1:
				if(0 == RIGHT_KEY)
				{
					  right_time_count = 0;
				    right_key_state = 2;    //消抖完成，按下计时开始
				}
				else
				{
				    right_key_state = 0;    //抖动
				}
				break;
			case 2:
				if(0 == RIGHT_KEY)    //按键仍然被按下
				{
				    right_time_count++;
					  if(right_time_count >= KEY_TIME * 4)
						{
						    rtn = RIGHT_LONG_KEY;
							  right_key_state = 3;    //等待长按释放
						}
				}
				else
				{
				    rtn = RIGHT_CLICK_KEY;
					  right_key_state = 0;    //按键回到初始状态
				}
				break;
			case 3:
				if(1 == RIGHT_KEY)
				{
				    right_key_state = 0;
				}
				break;
		}
		return rtn;
}
unsigned char gLeftKeyRead(void)
{
	  unsigned char rtn = 0;
    unsigned char key = LeftKeyScan();
	
	  switch(left_key_state1)
		{
		  case 0:
				if(LEFT_CLICK_KEY == key)
				{
				    left_time_count1 = 0;
					  left_key_state1 = 1;
				}
				else
				{
				    rtn = key;
				}
				break;
			case 1:
				if(LEFT_CLICK_KEY == key)
				{
					  rtn = LEFT_DOUBLE_KEY;
				    left_key_state1 = 0;
				}
				else
				{
				    left_time_count1++;
					  if(left_time_count1 >= KEY_TIME)
						{
						    rtn = LEFT_CLICK_KEY;
							  left_key_state1 = 0;
						}
				}
				break;
		}
		return rtn;
}

unsigned char gRightKeyRead(void)
{
		unsigned char rtn = 0;
	
		unsigned char key = RightKeyScan();
		switch(right_key_state1)
		{
		  case 0:
				if(RIGHT_CLICK_KEY == key)
				{
				    right_time_count1 = 0;
					  right_key_state1 = 1;
				}
				else
				{
				    rtn = key;
				}
				break;
			case 1:
				if(RIGHT_CLICK_KEY == key)
				{
					  rtn = RIGHT_DOUBLE_KEY;
				    right_key_state1 = 0;
				}
				else
				{
				    right_time_count1++;
					  if(right_time_count1 >= KEY_TIME)
						{
						    rtn = RIGHT_CLICK_KEY;
							  right_key_state1 = 0;
						}
				}
				break;
		}
		
		return rtn;
}

#else

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
#endif

