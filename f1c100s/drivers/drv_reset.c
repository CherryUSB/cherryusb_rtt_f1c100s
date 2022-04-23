/*
 * COPYRIGHT (C) 2012-2020, Shanghai Real-Thread Technology Co., Ltd
 * All rights reserved.
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */

#include <rtthread.h>
#include <rthw.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#include "drv_reset.h"
#include "drv_watchdog.h"

void machine_reset(void)
{
    rt_hw_interrupt_disable();
    WDOG_SET_MODE(RST_MODE);
    WDOG_SET_VALUE(0);
    WDOG_START();
    WDOG_KEEP_ALIVE();
    while (1);
}

#ifdef RT_USING_FINSH
// MSH_CMD_EXPORT_ALIAS(machine_reset, __cmd_reboot, reboot the machine);
MSH_CMD_EXPORT_ALIAS(machine_reset, reboot, reboot the machine);
#endif

void machine_shutdown(void)
{
    while (1);
}

