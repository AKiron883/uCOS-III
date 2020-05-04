#ifndef __OS_CPU_H__
#define __OS_CPU_H__

#ifndef NVIC_INT_CTRL
/*中断控制及状态寄存器 SCB_ICSR*/
#define NVIC_INT_CTRL				*((CPU_REG32*)0xE000ED04)
#endif

#ifndef NVIC_PENDSVSET
/*触发PendSV异常的值 Bit28: PENDSVSET*/
#define NVIC_PENDSVSET				0x10000000
#endif

/*触发PendSV异常*/
#define OS_TASK_SW()				NVIC_INT_CTRL = NVIC_PENDSVSET

/*触发PendSV异常*/
#define OSInitCtxSw()				NVIC_INT_CTRL = NVIC_PENDSVSET


void OSStartHighRdy(void);
void PendSV_Handler(void);

#endif
