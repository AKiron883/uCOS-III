#include "app.h"
#include <stdint.h>
#include "os.h"
#include "ARMCM3.h"
#include "os_core.h"
#include "os_task.h"
#include "os_cpu.h"
#include "os_cpu_c.h"
#include "cpu.h"
#include "os_time.h"
#include "cpu_core.h"

#define 	TASK1_STK_SIZE	20
#define 	TASK2_STK_SIZE	20

static CPU_STK	Task1Stk[TASK1_STK_SIZE];
static CPU_STK	Task2Stk[TASK2_STK_SIZE];

static OS_TCB	Task1TCB;	///< 任务1控制块
static OS_TCB	Task2TCB;	///< 任务2控制块

void Task1(void *p_arg);
void Task2(void *p_arg);
void dealy(uint32_t count);

uint32_t flag1;
uint32_t flag2;

uint32_t TimeStart;/*定义3个全局变量*/
uint32_t TimeEnd;
uint32_t TimeUse;

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
		TimeStart = OS_TS_GET();
		OSTimeDly(20);
		TimeEnd = OS_TS_GET();
		TimeUse = TimeEnd - TimeStart;
		flag1 = 0;
		OSTimeDly(2);
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
		OSTimeDly(2);
		flag2 = 0;
		OSTimeDly(2);
	}
}

int main(void)
{
	OS_ERR	err;
	
	/*CPU初始化,初始化时间戳*/
	CPU_Init();
	
	CPU_IntDis();	/**<关闭中断*/
	
	OS_CPU_SysTickInit(10);		/**<配置SysTick 10ms 中断一次*/
	
	/*初始化相关的全局变量*/
	OSInit(&err);

	OSInit(&err);
	
	OSTaskCreate((OS_TCB*)		&Task1TCB,
				 (OS_TASK_PTR)	Task1,
				 (void*)		0,
				 (CPU_STK*)		&Task1Stk[0],
				 (CPU_STK_SIZE)	TASK1_STK_SIZE,
				 (OS_ERR*)		&err);
	
	OSTaskCreate((OS_TCB*)		&Task2TCB,
				 (OS_TASK_PTR)  Task2,
				 (void*)        0,
				 (CPU_STK*)     &Task2Stk[0],
				 (CPU_STK_SIZE)	TASK2_STK_SIZE,
				 (OS_ERR*) 		&err);
				 
	OSRdyList[0].HeadPtr = &Task1TCB;
	OSRdyList[1].HeadPtr = &Task2TCB;
	
	OSStart(&err);				
}

