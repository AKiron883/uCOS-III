#define CPU_CORE_MODULE
#include "cpu_core.h"
/*
******************************************************************
*						寄存器定义
******************************************************************
*/
#define BSP_REG_DEM_CR		(*(CPU_REG32*)0xE000EDFC)
#define BSP_REG_DWT_CR		(*(CPU_REG32*)0xE0001000)
#define BSP_REG_DWT_CYCCNT	(*(CPU_REG32*)0xE0001004)
#define BSP_REG_DBGMCU_CR	(*(CPU_REG32*)0xE0042004)

/*
********************************************************************
*						寄存器位定义
********************************************************************
*/
#define BSP_DBGMCU_CR_TRACE_IOEN_MASK		0x10
#define BSP_DBGMCU_CR_TRACE_MODE_ASYNC		0x00
#define BSP_DBGMCU_CR_TRACE_MODE_SYNC_01	0x40
#define BSP_DBGMCU_CR_TRACE_MODE_SYNC_02	0x80
#define BSP_DBGMCU_CR_TRACE_MODE_SYNC_04	0xC0
#define BSP_DBGMCU_CR_TRACE_MODE_MASK		0xC0

#define BSP_BIT_DEM_CR_TRCENA				(1 << 24)

#define BSP_BIT_DWT_CR_CYCCNTENA			(1 << 0)

/*获取CPU的HCLK时钟
 *与硬件相关,目前是软件仿真,所以暂时屏蔽了与硬件相关的代码
 *直接手动设备CPU的HCLK时钟
 */
CPU_INT32U BSP_CPU_ClkFreq(void)
{
#if 0
	RCC_ClocksTypeDef	rcc_clocks;
	
	RCC_GetClocksFreq(&rcc_clocks);
	return ((CPU_INT32U)rcc_clocks.HCLK_Frequency);
#else
	CPU_INT32U		CPU_HCLK;
	
	CPU_HCLK = 25000000;
	
	return  CPU_HCLK;
#endif
}

/*初始化CPU_TS_TmrFreq_Hz,这就是系统的时钟,单位为Hz*/
#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
void CPU_TS_TmrFreqSet(CPU_TS_TMR_FREQ freq_hz)
{
	CPU_TS_TmrFreq_Hz = freq_hz;
}
#endif



#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
void CPU_TS_TmrInit(void)
{
	CPU_INT32U	fclk_freq;
	
	fclk_freq = BSP_CPU_ClkFreq();

	/*启用DWT外设*/
	BSP_REG_DEM_CR	|=	(CPU_INT32U)BSP_BIT_DEM_CR_TRCENA; 
	/*DWT CYCCNT 寄存器计数清零*/
	BSP_REG_DWT_CYCCNT = (CPU_INT32U)0u;
	/*软件仿真会停在此处,需要手动跳过,硬件仿真不会出现此问题*/
	BSP_REG_DWT_CR	|= (CPU_INT32U)BSP_BIT_DWT_CR_CYCCNTENA;
	
	CPU_TS_TmrFreqSet((CPU_TS_TMR_FREQ)fclk_freq);
}
#endif

#if ((CPU_CFG_TS_EN == DEF_ENABLED) || (CPU_CFG_TS_TMR_EN == DEF_ENABLED))
static void CPU_TS_Init(void)
{
	#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
		CPU_TS_TmrFreq_Hz = 0u;
		CPU_TS_TmrInit();
	#endif
}
#endif


/*CPU初始化函数*/
void CPU_Init(void)
{
	#if ((CPU_CFG_TS_EN == DEF_ENABLED) || (CPU_CFG_TS_TMR_EN == DEF_EVABLED))
		CPU_TS_Init();
	#endif
}

/*用于获取时间戳的值*/
#if (CPU_CFG_TS_TMR_EN == DEF_ENABLE)
CPU_TS_TMR	CPU_TS_TmrRd(void)
{	
	CPU_TS_TMR	ts_tmr_cnts;
	
	ts_tmr_cnts = (CPU_TS_TMR)BSP_REG_DWT_CYCCNT;

	return ts_tmr_cnts;
}
#endif
