#ifndef __OS_H__
#define __OS_H__

#include "cpu.h"
#include "os_cfg.h"

#define OS_STATE_OS_STOPPED			(OS_STATE)(0u)
#define OS_STATE_OS_RUNNING			(OS_STATE)(1u)

#ifdef OS_GLOBALS
#define OS_EXT
#else
#define OS_EXT extern
#endif

typedef struct os_tcb		OS_TCB;			///< 任务栈结构体
typedef struct os_rdy_list	OS_RDY_LIST;	///< 就绪任务列表

///任务栈控制块
struct os_tcb
{
	CPU_STK				*StkPtr;			///< 任务栈的地址
	CPU_STK_SIZE		StkSize;			///< 任务栈的大小
};

///就绪任务列表数据类型
struct os_rdy_list
{
	OS_TCB		*HeadPtr;
	OS_TCB		*TailPtr;
};

typedef CPU_INT08U		OS_STATE;			///< 系统运行状态
typedef CPU_INT08U		OS_PRIO;			///< 系统优先级	


typedef void (OS_TASK_PTR)(void *p_arg);	///< 任务的实体函数指针




///系统全局变量的定义
OS_EXT		OS_TCB			*OSTCBCurPtr;
OS_EXT		OS_TCB			*OSTCBHighRdyPtr;
OS_EXT		OS_RDY_LIST		OSRdyList[OS_CFG_PRIO_MAX];
OS_EXT		OS_STATE		OSRunning;


///错误类型
typedef enum os_err
{
	OS_ERR_NONE			=     	0u,
	OS_ERR_A			= 		10000u,
	OS_ERR_ACCEPT_ISR	=		10001u,
	
	OS_ERR_B			=       11000u,
	
	OS_ERR_C			=		12000u,
	OS_ERR_CHEATE_ISR   =		12001u,
	
	OS_ERR_FATAL_RETURN = 		15001u,
	
	OS_ERR_X			=		33000u,
	
	OS_ERR_Y			=		34000u,
	OS_ERR_YIELD_ISR	=		34001u,
	
	OS_ERR_Z			=		35000u,

}OS_ERR;




#endif
