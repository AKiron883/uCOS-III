#include "os_cfg_app.h"

CPU_STK		OSCfg_IdleTaskStk[OS_CFG_IDLE_TASK_STK_SIZE];


/*空闲任务栈起始地址*/
CPU_STK* const OSCfg_IdleTaskStkBasePtr = (CPU_STK*)&OSCfg_IdleTaskStk[0];

/*空闲任务栈的大小*/
CPU_STK_SIZE const OSCfg_IdleTaskStkSize = (CPU_STK_SIZE)OS_CFG_IDLE_TASK_STK_SIZE;

/*空闲任务*/
void OS_IdleTask(void* p_arg)
{
	p_arg = p_arg;

	/*空闲任务什么都不做,只对全局变量执行OSIdleTaskCtr++操作*/
	for(;;)
	{
		OSIdleTaskCtr++;
	}
}

