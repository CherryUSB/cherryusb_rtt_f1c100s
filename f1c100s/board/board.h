/*
 * COPYRIGHT (C) 2012-2020, Shanghai Real-Thread Technology Co., Ltd
 * All rights reserved.
 * Change Logs:
 * Date           Author       Notes
 * 2017-5-30      RT-Thread    the first version
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdint.h>

extern unsigned char __bss_start;
extern unsigned char __bss_end;

#define RT_HW_HEAP_BEGIN    (void*)&__bss_end
#define RT_HW_HEAP_END      (void*)(0x80000000 + 64 * 1024 * 1024)

void rt_hw_board_init(void);

#endif
