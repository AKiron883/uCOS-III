#ifndef __OS_CFG_APP_H__
#define __OS_CFG_APP_H__

#include "os.h"

/*空闲任务栈的大小*/
#define OS_CFG_IDLE_TASK_STK_SIZE	128u

void OS_IdleTask(void* p_arg);

#endif
