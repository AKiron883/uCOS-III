#include "os_time.h"
#include "os.h"
#include "os_cpu.h"

void OSSched(void)
{
	if(OSTCBCurPtr == OSRdyList[0].HeadPtr)
		OSTCBHighRdyPtr = OSRdyList[1].HeadPtr;
	else
		OSTCBHighRdyPtr = OSRdyList[0].HeadPtr;
	
	OS_TASK_SW();
}


void OSTimeTick(void)
{
	/*任务调度*/
	OSSched();
}
