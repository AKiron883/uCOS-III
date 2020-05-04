#ifndef __OS_TASK_H__
#define __OS_TASK_H__

#include "os.h"

/**
 *@brief 任务栈初始化函数
 */
CPU_STK *OSTaskStkInit(OS_TASK_PTR	p_task,
					   void			*p_arg,
					   CPU_STK		*p_stk_base,
					   CPU_STK_SIZE stk_size);
					   
void OSTaskCreate(OS_TCB			*p_tcb,
				   OS_TASK_PTR  	p_task,
				   void         	*p_arg,
				   CPU_STK			*p_stk_base,
				   CPU_STK_SIZE 	stk_size,
				   OS_ERR			*p_err);

#endif
