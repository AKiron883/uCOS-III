#include "app.h"
#include <stdint.h>
#include "os.h"

static OS_TCB	Task1TCB;	///< 任务1控制块
static OS_TCB	Task2TCB;	///< 任务2控制块





uint32_t flag1;
uint32_t flag2;

void delay(uint32_t count)
{
	for(; count != 0; count--)
	{}
}

/**
 *@breif 任务1
 */
void Task1(void *p_arg)
{
	for(;;)
	{
		flag1 = 1;
		delay(100);
		flag1 = 0;
		delay(100);
	}
}

/**
 *@brief 任务2
 */
void Task2(void *p_arg)
{
	for(;;)
	{
		flag2 = 1;
		delay(100);
		flag2 = 0;
		delay(100);
	}
}



int main(void)
{
	
	OSRdyList[0].HeadPtr = &Task1TCB;
	
	
	while(1)
	{
			flag1 = 1;
			delay(1000);
			flag1 = 0;
			delay(1000);
		
			flag2 = 1;
			delay(1000);
			flag2 = 0;
			delay(1000);
	}
}

