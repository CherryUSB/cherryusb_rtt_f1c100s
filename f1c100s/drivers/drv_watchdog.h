/*
 * COPYRIGHT (C) 2012-2020, Shanghai Real-Thread Technology Co., Ltd
 * All rights reserved.
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */
#ifndef __DRV_WATCHDOG_H__
#define __DRV_WATCHDOG_H__

#define TIME_WATCH_DOG_ADDR    (0x01C20C00 + 0xA0)

struct tina_wdog
{
    volatile rt_uint32_t wdog_irq_en;
    volatile rt_uint32_t wdog_irq_sta;
    volatile rt_uint32_t reserved0[2];
    volatile rt_uint32_t wdog_ctrl;
    volatile rt_uint32_t wdog_cfg;
    volatile rt_uint32_t wdog_mode;
};

typedef struct tina_wdog tina_wdog_t;

#define WDOG ((tina_wdog_t *)TIME_WATCH_DOG_ADDR)

#define RST_MODE    (0x01)
#define IRQ_MODE    (0x02)

#define WDOG_GET_VALUE()         ((WDOG->wdog_mode >> 4) & 0xf)
#define WDOG_SET_VALUE(value)    (WDOG->wdog_mode = (value & 0xf) << 4)
#define WDOG_KEEP_ALIVE()        (WDOG->wdog_ctrl = (0x0A57 << 1) | 1)
#define WDOG_START()             (WDOG->wdog_mode |= 0x1)
#define WDOG_SET_MODE(mode)      (WDOG->wdog_cfg = (mode & 0x3))

#endif