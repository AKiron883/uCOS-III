#ifndef CPU_H
#define CPU_H

typedef unsigned short				CPU_INT16U;
typedef unsigned int				CPU_INT32U;
typedef unsigned char				CPU_INT08U;

typedef CPU_INT32U	CPU_ADDR;

/* 栈数据类型重定义 */
typedef CPU_INT32U					CPU_STK;
typedef CPU_ADDR					CPU_STK_SIZE;

typedef volatile CPU_INT32U	CPU_REG32;

void CPU_IntDis(void);
void CPU_IntEn(void);

#endif /*	CPU_H*/
