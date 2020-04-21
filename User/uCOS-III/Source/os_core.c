#include "os_core.h"
#include "os.h"

void OSInit(OS_ERR *p_err)
{
	OSRunning = OS_STATE_OS_STOPPED;
	OSTCBCurPtr = (OS_TCB*)0;
	OSTCBHighRdyPtr = (OS_TCB*)0;

	OS_RdyListInit();
	
	*p_err = OS_ERR_NONE;
}

/**
 *@brief 初始化全局变量列表
 */
void OS_RdyListInit(void)
{
	OS_PRIO i;
	OS_RDY_LIST *p_rdy_list;
	
	for(i = 0u; i < OS_CFG_PRIO_MAX; i++)
	{
		p_rdy_list = &OSRdyList[i];
		p_rdy_list->HeadPtr = (OS_TCB*)0;
		p_rdy_list->TailPtr = (OS_TCB*)0;
	}
}



void OSStart(OS_ERR *p_err)
{
	if(OSRunning == OS_STATE_OS_STOPPED)
	{
		/*手动配置任务1先运行*/
		OSTCBHighRdyPtr = OSRdyList[0].HeadPtr;
		
		/*启动任务切换,不会返回*/
		OSStartHighRdy();
	
		/* 不会运行到这里,如果运行到这里,则表示发生了错误*/
		*p_err = OS_ERR_FATAL_RETURN;
	}
	else
	{
		*p_err = OS_STATE_OS_RUNNING;
	}


}