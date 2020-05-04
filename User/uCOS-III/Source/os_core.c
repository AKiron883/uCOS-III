#include "os_core.h"
#include "os.h"
#include "os_cpu.h"
#include "os_task.h"
#include "os_cfg_app.h"

void OSInit(OS_ERR *p_err)
{
	/*配置操作系统初始状态为停止态*/
	OSRunning = OS_STATE_OS_STOPPED;
	
	/*初始化两个全局TCB,这两个TCB用于任务切换*/
	OSTCBCurPtr = (OS_TCB*)0;
	OSTCBHighRdyPtr = (OS_TCB*)0;

	/*初始化就绪列表*/
	OS_RdyListInit();
	
	/*初始化空闲任务*/
	OS_IdleTaskInit(p_err);
	if(*p_err != OS_ERR_NONE)
	{
		return;
	}
	
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

/**
 *@brief 初始化空闲任务
 **/
void OS_IdleTaskInit(OS_ERR* p_err)
{
	/*初始化空闲任务计数器*/
	OSIdleTaskCtr = (OS_IDLE_CTR)0;
	
	/*创建空闲任务*/
	OSTaskCreate((OS_TCB*)      &OSIdleTaskTCB,
				 (OS_TASK_PTR)  OS_IdleTask,
				 (void*)        0,
				 (CPU_STK*)	    OSCfg_IdleTaskStkBasePtr,
				 (CPU_STK_SIZE) OSCfg_IdleTaskStkSize,	                
				 (OS_ERR*)      p_err);
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



