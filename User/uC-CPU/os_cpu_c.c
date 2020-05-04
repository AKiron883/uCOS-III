#include "ARMCM3.h"

#include "os_time.h"
#include "os_cpu_c.h"

#if 0
void OS_CPU_SysTickInit(CPU_INT32U ms)
{
	CPU_INT32U	prio;
	
	/*填写 SysTick 的重载计数值*/
	CPU_REG_NVIC_ST_RELOAD = cnts - 1u;
	
	/**/





}

#else
void OS_CPU_SysTickInit(CPU_INT32U ms)
{
	/*设置重装载寄存器的值*/
	SysTick->LOAD = ms * SystemCoreClock / 1000 - 1;
	
	/*配置中断优先级为最低*/
	NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);
	
	/*复位当前计数器的值*/
	SysTick->VAL = 0;
	
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | 
					SysTick_CTRL_TICKINT_Msk   |
					SysTick_CTRL_ENABLE_Msk;
}
#endif

/*SysTick 中断服务函数*/
void SysTick_Handler(void)
{
	OSTimeTick();
}


