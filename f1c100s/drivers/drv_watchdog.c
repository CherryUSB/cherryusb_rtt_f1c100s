/*
 * COPYRIGHT (C) 2012-2020, Shanghai Real-Thread Technology Co., Ltd
 * All rights reserved.
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

#include "drv_watchdog.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME  "[WDOG]"
#define DBG_LEVEL         DBG_LOG
#include <rtdbg.h>

#define ARR_LEN(__N)      (sizeof(__N) / sizeof(__N[0]))

#ifdef TINA_USING_WDT

static int timeout_map[] = {0, 1, 2, 3, 4, 5, 6, 8, 10, 12, 14, 16};
static struct rt_watchdog_device wdog_dev;

static rt_err_t tina_wdt_init(rt_watchdog_t *watchdog)
{
    return RT_EOK;
}

static rt_err_t tina_wdt_control(rt_watchdog_t *watchdog, int cmd, void *arg)
{
    rt_err_t err = RT_EOK;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_START:
    {
        WDOG_START();
        err = RT_EOK;
        break;
    }

    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
    {
        int *timeout =  (int *)arg;

        if (WDOG_GET_VALUE() > (ARR_LEN(timeout_map) - 1))
        {
            *timeout = timeout_map[ARR_LEN(timeout_map) - 1];
            break;
        }

        *timeout = timeout_map[WDOG_GET_VALUE()];
        err = RT_EOK;
        break;
    }

    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
    {
        int i = 0, timeout = *(int *)arg;
        
        dbg_log(DBG_LOG, "cmd:RT_DEVICE_CTRL_WDT_SET_TIMEOUT arg:%d\n", timeout);
        if (timeout > timeout_map[ARR_LEN(timeout_map) - 1])
        {
            timeout = timeout_map[ARR_LEN(timeout_map) - 1];
        }

        for(i = timeout / 2; (i < ARR_LEN(timeout_map)) && \
            (timeout_map[i] < timeout); i++);

        dbg_log(DBG_LOG, "wdog value:%d\n", i);
        WDOG_SET_VALUE(i);
        err = RT_EOK;
        break;
    }

    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
    {
        err = -RT_ERROR;
        break;
    }

    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
    {
        WDOG_KEEP_ALIVE();
        err = RT_EOK;
        break;
    }

    case RT_DEVICE_CTRL_WDT_STOP:
    {
        dbg_log(DBG_WARNING, "Watchdog can't stop\n");
        err = -RT_ERROR;
        break;
    }

    default:
    {
        err = -RT_ERROR;
        break;
    }

    }

    return err;
}

static struct rt_watchdog_ops _ops =
{
    tina_wdt_init,
    tina_wdt_control
};

int rt_hw_wdt_init(void)
{
    rt_err_t err;

    wdog_dev.ops = &_ops;
    WDOG_SET_MODE(RST_MODE);
    err = rt_hw_watchdog_register(&wdog_dev, "wdog", RT_DEVICE_FLAG_WRONLY, RT_NULL);

    return err;
}
INIT_DEVICE_EXPORT(rt_hw_wdt_init);

#endif