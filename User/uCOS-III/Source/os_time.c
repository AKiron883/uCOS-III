#include "os_time.h"

#include "os_cpu.h"

void OSSched(void)
{
#if 0
	if(OSTCBCurPtr == OSRdyList[0].HeadPtr)
		OSTCBHighRdyPtr = OSRdyList[1].HeadPtr;
	else
		OSTCBHighRdyPtr = OSRdyList[0].HeadPtr;
	
	OS_TASK_SW();
#endif
		
	/*如果当前任务是空闲任务,那么尝试执行任务1或者任务2,
	 *看看其延时时间是否结束,如果任务的延时时间均没有到期,
	 *就返回继续执行空闲任务*/
	if(OSTCBCurPtr == &OSIdleTaskTCB)
	{
		if(OSRdyList[0].HeadPtr->TaskDelayTicks == 0)
		{
			OSTCBHighRdyPtr = OSRdyList[0].HeadPtr;
		}
		else if(OSRdyList[1].HeadPtr->TaskDelayTicks == 0)
		{
			OSTCBHighRdyPtr = OSRdyList[1].HeadPtr;
		}
		else
		{
			return;
		}
	}
	else
	{
		if(OSTCBCurPtr == OSRdyList[0].HeadPtr)
		{
			if(OSRdyList[1].HeadPtr->TaskDelayTicks == 0)
			{
				OSTCBHighRdyPtr = OSRdyList[1].HeadPtr;
			}
			else if(OSTCBCurPtr->TaskDelayTicks != 0)
			{
				OSTCBHighRdyPtr = &OSIdleTaskTCB;
			}
			else
			{
				return;
			}
		}
		else if(OSTCBCurPtr == OSRdyList[1].HeadPtr)
		{
			if(OSRdyList[0].HeadPtr->TaskDelayTicks == 0)
			{
				OSTCBHighRdyPtr = OSRdyList[0].HeadPtr;
			}
			else if(OSTCBCurPtr->TaskDelayTicks != 0)
			{
				OSTCBHighRdyPtr = &OSIdleTaskTCB;
			}
			else
			{
				return;
			}
		}
	}

	/*任务切换*/
	OS_TASK_SW();
}


void OSTimeTick(void)
{
	unsigned int i;
	
	for(i = 0; i < OS_CFG_PRIO_MAX; i++)
	{
		if(OSRdyList[i].HeadPtr->TaskDelayTicks > 0)
		{
			OSRdyList[i].HeadPtr->TaskDelayTicks --;
		}
	
	}

	/*任务调度*/
	OSSched();
}

/*阻塞延时*/
void OSTimeDly(OS_TICK dly)
{
	/*设置延时时间*/
	OSTCBCurPtr->TaskDelayTicks = dly;
	
	/*进行任务调度*/
	OSSched();

}
