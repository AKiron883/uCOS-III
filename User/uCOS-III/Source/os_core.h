#ifndef __OS_CORE_H__
#define __OS_CORE_H__

#include "os.h"

/**
 *@brief 初始化全局变量
 */
void OS_RdyListInit(void);
void OSInit(OS_ERR *p_err);
void OSStart(OS_ERR *p_err);

#endif
