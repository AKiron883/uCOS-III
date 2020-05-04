#ifndef __OS_TIME_H__
#define __OS_TIME_H__

#include "os.h"

void OSTimeTick(void);
/*阻塞延时*/
void OSTimeDly(OS_TICK dly);
#endif
