/*
 * COPYRIGHT (C) 2012-2020, Shanghai Real-Thread Technology Co., Ltd
 * All rights reserved.
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */

#include <rtthread.h>
#include <rthw.h>

#include "drv_gpio.h"
#include "interrupt.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME  "[GPIO]"
#define DBG_LEVEL         DBG_WARNING
#include <rtdbg.h>


#define readl(addr)           (*(volatile unsigned int *)(addr))
#define writel(value,addr)    (*(volatile unsigned int *)(addr) = (value))

// Todo: add RT_ASSERT.

/*********************************************************
**   IO
*********************************************************/
int gpio_set_func(enum gpio_port port, enum gpio_pin pin, rt_uint8_t func)
{
    rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_A <= port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    if (func & 0x8)
    {
        dbg_log(DBG_WARNING, "[line]:%d There is a warning with parameter input\n", __LINE__);
        return RT_EINVAL;
    }

    addr = GPIOn_CFG_ADDR(port) + (pin / 8) * 4;
    offset = (pin % 8) * 4;

    data = readl(addr);
    data &= ~(0x7 << offset);
    data |= func << offset;
    writel(data, addr);

    dbg_log(DBG_LOG, "[line]:%d offset:%d addr:%08x data:%08x\n", __LINE__, offset, addr, *((rt_uint32_t *)addr));
    return RT_EOK;
}

int gpio_set_value(enum gpio_port port, enum gpio_pin pin, rt_uint8_t value)
{
    rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_A <= port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    if (value & 0xE)
    {
        dbg_log(DBG_WARNING, "[line]:%d There is a warning with parameter input\n", __LINE__);
        return RT_EINVAL;
    }

    addr = GPIOn_DATA_ADDR(port);
    offset = pin;

    data = readl(addr);
    data &= ~(0x1 << offset);
    data |= value << offset;
    writel(data, addr);

    dbg_log(DBG_LOG, "[line]:%d offset:%d addr:%08x data:%08x\n", __LINE__, offset, addr, *((rt_uint32_t *)addr));
    return RT_EOK;
}

int gpio_get_value(enum gpio_port port, enum gpio_pin pin)
{
    rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_A <= port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    addr = GPIOn_DATA_ADDR(port);
    offset = pin;

    data = readl(addr);

    dbg_log(DBG_LOG, "[line]:%d offset:%d addr:%08x data:%08x\n", __LINE__, offset, addr, *((rt_uint32_t *)addr));
    return (data >> offset) & 0x01;
}

int gpio_set_pull_mode(enum gpio_port port,  enum gpio_pin pin, enum gpio_pull pull)
{
    rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_A <= port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    if (pull & 0xC)
    {
        dbg_log(DBG_WARNING, "[line]:%d There is a warning with parameter input\n", __LINE__);
        return RT_EINVAL;
    }

    addr = GPIOn_PUL_ADDR(port);
    addr += pin > GPIO_PIN_15 ? 0x4 : 0x0;
    offset = (pin & 0xf) << 1;

    data = readl(addr);
    data &= ~(0x3 << offset);
    data |= pull << offset;
    writel(data, addr);

    dbg_log(DBG_LOG, "[line]:%d offset:%d addr:%08x data:%08x\n", __LINE__, offset, addr, *((rt_uint32_t *)addr));
    return RT_EOK;
}

int gpio_set_drive_level(enum gpio_port port, enum gpio_pin pin, enum gpio_drv_level level)
{
    volatile rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_A <= port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    if (level & 0xC)
    {
        dbg_log(DBG_WARNING, "[line]:%d There is a warning with parameter input\n", __LINE__);
        return RT_EINVAL;
    }

    addr = GPIOn_DRV_ADDR(port);
    addr += pin > GPIO_PIN_15 ? 0x4 : 0x0;
    offset = (pin & 0xf) << 1;

    data = readl(addr);
    data &= ~(0x3 << offset);
    data |= level << offset;
    writel(data, addr);

    dbg_log(DBG_LOG, "[line]:%d offset:%d addr:%08x data:%08x\n", __LINE__, offset, addr, *((rt_uint32_t *)addr));
    return RT_EOK;
}

void gpio_direction_input(enum gpio_port port,  enum gpio_pin pin)
{
    volatile rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_A <= port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    addr = GPIOn_CFG_ADDR(port) + (pin / 8) * 4;
    offset = (pin % 8) * 4;

    data = readl(addr);
    data &= ~(0x7 << offset);
    data |= IO_INPUT << offset;
    writel(data, addr);

    dbg_log(DBG_LOG, "[line]:%d offset:%d addr:%08x data:%08x\n", __LINE__, offset, addr, *((rt_uint32_t *)addr));
}

void gpio_direction_output(enum gpio_port port, enum gpio_pin pin, int value)
{
    volatile rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_A <= port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    gpio_set_value(port, pin, value);
    addr = GPIOn_CFG_ADDR(port) + (pin / 8) * 4;
    offset = (pin % 8) * 4;

    data = readl(addr);
    data &= ~(0x7 << offset);
    data |= IO_OUTPUT << offset;
    writel(data, addr);

    dbg_log(DBG_LOG, "[line]:%d offset:%d addr:%08x data:%08x\n", __LINE__, offset, addr, *((rt_uint32_t *)addr));
}
/*********************************************************
**   IRQ
*********************************************************/
static void gpio_ack_irq(enum gpio_port port,  enum gpio_pin pin)
{
    rt_uint32_t addr;
    rt_uint32_t data;

    addr = GPIOn_INT_STA_ADDR(port);
    data = readl(addr);
    data |= 0x1 << pin;
    writel(data, addr);
}

void gpio_select_irq_clock(enum gpio_port port, enum gpio_irq_clock clock)
{
    rt_uint32_t addr;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_C < port) && (port < GPIO_PORT_NUM));

    addr = GPIOn_INT_DEB_ADDR(port - GPIO_PORT_D);

    data = readl(addr);
    data &= ~0x01;
    data |= clock;
    writel(data, addr);
    dbg_log(DBG_LOG, "[line]:%d addr:%08x data:%08x\n", __LINE__, addr, *((rt_uint32_t *)addr));
}

void gpio_set_debounce(enum gpio_port port, enum gpio_direction_type prescaler)
{
    rt_uint32_t addr;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_C < port) && (port < GPIO_PORT_NUM));

    addr = GPIOn_INT_DEB_ADDR(port - GPIO_PORT_D);

    data = readl(addr);
    data &= ~(0x07 << 4);
    data |= prescaler << 4;
    writel(data, addr);
    dbg_log(DBG_LOG, "[line]:%d addr:%08x data:%08x\n", __LINE__, addr, *((rt_uint32_t *)addr));
}

void gpio_irq_enable(enum gpio_port port,  enum gpio_pin pin)
{
    rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_C < port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    addr = GPIOn_INT_CTRL_ADDR(port - GPIO_PORT_D);
    offset = pin;

    data = readl(addr);
    data |= 0x1 << offset;
    writel(data, addr);
    gpio_select_irq_clock(port, GPIO_IRQ_HOSC_24MHZ);
    dbg_log(DBG_LOG, "[line]:%d offset:%d addr:%08x data:%08x\n", __LINE__, offset, addr, *((rt_uint32_t *)addr));
}

void gpio_irq_disable(enum gpio_port port,  enum gpio_pin pin)
{
    rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_C < port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    gpio_ack_irq(port - GPIO_PORT_D, pin);
    addr = GPIOn_INT_CTRL_ADDR(port - GPIO_PORT_D);
    offset = pin;

    data = readl(addr);
    data &= ~(0x1 << offset);

    writel(data, addr);
    dbg_log(DBG_LOG, "[line]:%d offset:%d addr:%08x data:%08x\n", __LINE__, offset, addr, *((rt_uint32_t *)addr));
}

void gpio_set_irq_type(enum gpio_port port,  enum gpio_pin pin, enum gpio_irq_type irq_type)
{
    rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_C < port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    addr = GPIOn_INT_CFG_ADDR(port - GPIO_PORT_D) + (pin / 8) * 4;
    offset = (pin % 8) * 4;

    data = readl(addr);
    data &= ~(0x7 << offset);
    data |= irq_type << offset;
    writel(data, addr);

    dbg_log(DBG_LOG, "[line]:%d offset:%d addr:%08x data:%08x\n", __LINE__, offset, addr, *((rt_uint32_t *)addr));
}

/*
PA0~PA3 : no-EINT
PB3     : no-EINT
PC0~PC3 : no-EINT
PD0~PD21: EINTD0~EINTD21
PE0~PE12: EINTE0~EINTE12
PF0~PF5 : EINTF0~EINTF5
*/
static struct gpio_irq_def _g_gpio_irq_tbl[GPIO_PORT_NUM - GPIO_PORT_D];

void gpio_set_irq_callback(enum gpio_port port, enum gpio_pin pin, void (*irq_cb)(void *), void *irq_arg)
{
    RT_ASSERT((GPIO_PORT_C < port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    _g_gpio_irq_tbl[port - GPIO_PORT_D].irq_cb[pin] = irq_cb;
    _g_gpio_irq_tbl[port - GPIO_PORT_D].irq_arg[pin] = irq_arg;
}

void gpio_clear_irq_callback(enum gpio_port port, enum gpio_pin pin)
{
    gpio_irq_disable(port, pin);

    _g_gpio_irq_tbl[port - GPIO_PORT_D].irq_cb[pin]    = RT_NULL;
    _g_gpio_irq_tbl[port - GPIO_PORT_D].irq_arg[pin]   = RT_NULL;
}

static void gpio_irq_handler(int irq, void *param)
{
    struct gpio_irq_def *irq_def = (struct gpio_irq_def *)param;
    rt_uint32_t pend, enable;
    int port, pin;
    rt_uint32_t addr;

    pin = 0;
    port = irq - PIOD_INTERRUPT;
    addr = GPIOn_INT_STA_ADDR(port);
    pend = readl(addr);
    addr = GPIOn_INT_CTRL_ADDR(port);
    enable = readl(addr);
    pend &= enable;

    while (pend)
    {
        if ((pend & 0x1) && (irq_def->irq_cb[pin] != RT_NULL))
        {
            dbg_log(DBG_LOG, "do irq callback...\n", port, pin);
            irq_def->irq_cb[pin](irq_def->irq_arg[pin]);
        }
        pin++;
        pend = pend >> 1;
        gpio_ack_irq(port, pin);
    }
}


#ifdef RT_USING_PIN
#include <rtdevice.h>

static void pin_mode(struct rt_device *dev, rt_base_t pin, rt_base_t mode)
{
    rt_base_t _mode, _pull;

    if (pin > PIN_NUM_MAX)
    {
        dbg_log(DBG_ERROR, "pin:%d value wrongful\n", pin);
        return;
    }

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        _mode = IO_OUTPUT;
        _pull = PULL_DISABLE;
        break;
    case PIN_MODE_INPUT:
        _mode = IO_INPUT;
        _pull = PULL_DISABLE;
        break;
    case PIN_MODE_INPUT_PULLUP:
        _mode = IO_INPUT;
        _pull = PULL_UP;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        _mode = IO_INPUT;
        _pull = PULL_DOWN;
        break;
    default:
        rt_kprintf("mode not support\n");
        _mode = IO_DISABLE;
        _pull = PULL_DISABLE;
        break;
    }

    gpio_set_pull_mode(GET_GPIO_PORT(pin), GET_GPIO_PIN(pin), _pull);
    gpio_set_func(GET_GPIO_PORT(pin), GET_GPIO_PIN(pin), _mode);
}

static void pin_write(struct rt_device *dev, rt_base_t pin, rt_base_t value)
{
    if (pin > PIN_NUM_MAX)
    {
        dbg_log(DBG_ERROR, "pin:%d value wrongful\n", pin);
        return;
    }

    gpio_set_value(GET_GPIO_PORT(pin), GET_GPIO_PIN(pin), value);
}

static int pin_read(struct rt_device *device, rt_base_t pin)
{
    if (pin > PIN_NUM_MAX)
    {
        dbg_log(DBG_ERROR, "pin:%d value wrongful\n", pin);
        return 0;
    }

    return gpio_get_value(GET_GPIO_PORT(pin), GET_GPIO_PIN(pin));
}

static rt_err_t pin_attach_irq(struct rt_device *device, rt_int32_t pin, rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t _mode;

    if (pin > PIN_NUM_MAX)
    {
        dbg_log(DBG_ERROR, "pin:%d value wrongful\n", pin);
        return RT_ERROR;
    }

    switch (mode)
    {
    case PIN_IRQ_MODE_RISING:
        _mode = POSITIVE;
        break;
    case PIN_IRQ_MODE_FALLING:
        _mode = NEGATIVE;
        break;
    case PIN_IRQ_MODE_RISING_FALLING:
        _mode = DOUBLE;
        break;
    case PIN_IRQ_MODE_HIGH_LEVEL:
        _mode = HIGH;
        break;
    case PIN_IRQ_MODE_LOW_LEVEL:
        _mode = LOW;
        break;
    default :
        dbg_log(DBG_ERROR, "irq mode err\n");
        return RT_ERROR;
    }

    gpio_set_irq_callback(GET_GPIO_PORT(pin), GET_GPIO_PIN(pin), hdr, args);
    gpio_set_irq_type(GET_GPIO_PORT(pin), GET_GPIO_PIN(pin), _mode);
    return RT_EOK;
}

static rt_err_t pin_dettach_irq(struct rt_device *device, rt_int32_t pin)
{
    if (pin > PIN_NUM_MAX)
    {
        dbg_log(DBG_ERROR, "pin:%d value wrongful\n", pin);
        return RT_ERROR;
    }

    gpio_clear_irq_callback(GET_GPIO_PORT(pin), GET_GPIO_PIN(pin));

    return RT_EOK;
}

rt_err_t pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint32_t enabled)
{
    if (pin > PIN_NUM_MAX)
    {
        dbg_log(DBG_ERROR, "pin:%d value wrongful\n", pin);
        return RT_ERROR;
    }

    if (enabled)
    {
        gpio_set_func(GET_GPIO_PORT(pin), GET_GPIO_PIN(pin), IO_FUN_5);
        gpio_irq_enable(GET_GPIO_PORT(pin), GET_GPIO_PIN(pin));
    }
    else
    {
        gpio_set_func(GET_GPIO_PORT(pin), GET_GPIO_PIN(pin), IO_DISABLE);
        gpio_irq_disable(GET_GPIO_PORT(pin), GET_GPIO_PIN(pin));
    }

    return RT_EOK;
}

static const struct rt_pin_ops ops =
{
    pin_mode,
    pin_write,
    pin_read,
    pin_attach_irq,
    pin_dettach_irq,
    pin_irq_enable,
};
#endif

int rt_hw_gpio_init(void)
{
#ifdef RT_USING_PIN
    rt_device_pin_register("gpio", &ops, RT_NULL);
#endif
    /* install ISR */
    rt_hw_interrupt_install(PIOD_INTERRUPT, gpio_irq_handler, &_g_gpio_irq_tbl[GPIO_PORT_D - GPIO_PORT_D], "gpiod_irq");
    rt_hw_interrupt_umask(PIOD_INTERRUPT);

    rt_hw_interrupt_install(PIOE_INTERRUPT, gpio_irq_handler, &_g_gpio_irq_tbl[GPIO_PORT_E - GPIO_PORT_D], "gpioe_irq");
    rt_hw_interrupt_umask(PIOE_INTERRUPT);

    rt_hw_interrupt_install(PIOF_INTERRUPT, gpio_irq_handler, &_g_gpio_irq_tbl[GPIO_PORT_F - GPIO_PORT_D], "gpiof_irq");
    rt_hw_interrupt_umask(PIOF_INTERRUPT);

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_gpio_init);
