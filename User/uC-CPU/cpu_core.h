

#ifndef __CPU_CORE_H__
#define __CPU_CORE_H__

#include "cpu.h"

#ifdef CPU_CORE_MODULE
#define CPU_CORE_EXT
#else
#define CPU_CORE_EXT	extern
#endif

typedef CPU_INT32U		CPU_TS32;
typedef CPU_INT32U		CPU_TS_TMR_FREQ;
typedef CPU_TS32		CPU_TS;
typedef CPU_INT32U		CPU_TS_TMR;

#if (CPU_CFG_TS_TMR_EN == DEF_EVABLED)
CPU_CORE_EXT	CPU_TS_TMR_FREQ		CPU_TS_TmrFreq_Hz;
#endif

#if ((CPU_CFG_TS_32_EN == DEF_ENABLED) || (CPU_CFG_TS_64_EN == DEF_ENABLED))
#define CPU_CFG_TS_EN				DEF_EVABLED
#else
#define CPU_CFG_TS_EN				DEF_DISABLED
#endif

#if ((CPU_CFG_TS_EN == DEF_ENABLED) || (defined(CPU_CFG_INT_DIS_MEAS_EN)))
#define CPU_CFG_TS_TMR_EN			DEF_ENABLED
#else
#define CPU_CFG_TS_TMR_EN			DEF_DISABLED
#endif


/*CPU时间戳初始化函数*/
void CPU_Init(void);
#if (CPU_CFG_TS_TMR_EN == DEF_ENABLE)
CPU_TS_TMR	CPU_TS_TmrRd(void);
#endif

/*
 ********************************************************
 *						时间戳配置
 **********************************************************
 */
/*启用时间戳*/
#define OS_CFG_TS_EN			1u

#if	OS_CFG_TS_EN == 1u
#define OS_TS_GET()			(CPU_TS)CPU_TS_TmrRd()
#else
#define OS_TS_GET()			(CPU_TS)0u
#endif







#endif
