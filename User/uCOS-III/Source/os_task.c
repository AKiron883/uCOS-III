#include "os_task.h"


/**
 *@brief 任务创建函数
 *
 *@param[in] p_tcb		任务栈控制块
 *@param[in] p_task 	任务名称(任务执行的实体)
 *@param[in] p_arg  	传给任务的参数
 *@param[in] p_stk_base	任务栈的地址
 *@param[in] stk_size 	任务栈的大小
 *@param[in] p_err		错误码
 *@return 无
 */
 void OSTaskCreate(OS_TCB			*p_tcb,
				   OS_TASK_PTR  	p_task,
				   void         	*p_arg,
				   CPU_STK			*p_stk_base,
				   CPU_STK_SIZE 	stk_size,
				   OS_ERR			*p_err)
{
	CPU_STK		*p_sp;
	
	p_sp = OSTaskStkInit(p_task,
						 p_arg,
						 p_stk_base,
						 stk_size);

	p_tcb->StkPtr = p_sp;
	p_tcb->StkSize = stk_size;

	*p_err = OS_ERR_NONE;
}

/**
 *@brief 任务栈初始化函数
 */
CPU_STK *OSTaskStkInit(OS_TASK_PTR	p_task,
					   void			*p_arg,
					   CPU_STK		*p_stk_base,
					   CPU_STK_SIZE stk_size)
{
	CPU_STK		*p_stk;

	p_stk = &p_stk_base[stk_size];
	/* 异常发生时自动保存的寄存器 */
	*--p_stk = (CPU_STK)0x01000000u;	/**< xPSR的位24必须置1		*/
	*--p_stk = (CPU_STK)p_task;			/**< R15(PC)任务的入口地址	*/
	*--p_stk = (CPU_STK)0x14141414u;	/**< R14(LR)				*/
	*--p_stk = (CPU_STK)0x12121212u;	/**< R12					*/
	*--p_stk = (CPU_STK)0x03030303u;	/**< R3						*/
	*--p_stk = (CPU_STK)0x02020202u;	/**< R2						*/
	*--p_stk = (CPU_STK)0x01010101u;	/**< R1						*/
	*--p_stk = (CPU_STK)p_arg;			/**< R0 :任务形参			*/
	/* 异常发生时需要手动保存的寄存器*/
	*--p_stk = (CPU_STK)0x11111111u;	/**< R11					*/
	*--p_stk = (CPU_STK)0x10101010u;	/**< R10					*/
	*--p_stk = (CPU_STK)0x09090909u;	/**< R9						*/
	*--p_stk = (CPU_STK)0x08080808u;	/**< R8						*/
	*--p_stk = (CPU_STK)0x07070707u;	/**< R7						*/
	*--p_stk = (CPU_STK)0x06060606u;	/**< R6						*/
	*--p_stk = (CPU_STK)0x05050505u;	/**< R5						*/
	*--p_stk = (CPU_STK)0x04040404u;	/**< R4						*/
		
	return (p_stk);
}