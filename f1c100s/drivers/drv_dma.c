#include <rtthread.h>
#include <drv_clock.h>
#include <string.h>
#include <board.h>
#include <rthw.h>
#include "drv_dma.h"
#include "interrupt.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME    "drv.dma"
#define DBG_LEVEL           DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

struct dma_channel_context
{
    void (*half_callback)(int channel, void * ctx);
    void * half_callback_ctx;
    void (*full_callback)(int channel, void * ctx);
    void * full_callback_ctx;
    int busy;
};

static struct dma_channel_context   ndma_channel_context[NDMA_CHANNEL_NUM];
static struct dma_channel_context   ddma_channel_context[DDMA_CHANNEL_NUM];

static void dma_irq_process(int irqno, void *param)
{
    int channel;
    uint32_t irq_pending;

    for(channel = 0; channel < NDMA_CHANNEL_NUM; channel++)
    {
        irq_pending = ndma_irq_get_status(channel);
        if(irq_pending & DMA_IRQ_HALF)
        {
            ndma_irq_clear_pending(channel, DMA_IRQ_HALF);
            if(ndma_channel_context[channel].half_callback)
            {
                ndma_channel_context[channel].half_callback(channel, ndma_channel_context[channel].half_callback_ctx);
            }
        }

        if(irq_pending & DMA_IRQ_FULL)
        {
            ndma_irq_clear_pending(channel, DMA_IRQ_FULL);
            if(ndma_channel_context[channel].full_callback)
            {
                ndma_channel_context[channel].full_callback(channel, ndma_channel_context[channel].full_callback_ctx);
            }
        }
    }

    for(channel = 0; channel < DDMA_CHANNEL_NUM; channel++)
    {
        irq_pending = ddma_irq_get_status(channel);
        if(irq_pending & DMA_IRQ_HALF)
        {
            ddma_irq_clear_pending(channel, DMA_IRQ_HALF);
            if(ddma_channel_context[channel].half_callback)
            {
                ddma_channel_context[channel].half_callback(channel, ddma_channel_context[channel].half_callback_ctx);
            }
        }

        if(irq_pending & DMA_IRQ_FULL)
        {
            ddma_irq_clear_pending(channel, DMA_IRQ_FULL);
            if(ddma_channel_context[channel].full_callback)
            {
                ddma_channel_context[channel].full_callback(channel, ddma_channel_context[channel].full_callback_ctx);
            }
        }
    }
}


static int dma_clock_open(void)
{
    /* 配置时钟 */
    CCU->bus_clk_gating0 |= (0x1 << 6); /* Enable AHB Gain */

    /* De-assert DMA software reset */
    CCU->bus_soft_rst0 |= (0x1 << 6);

    /* Enable Auto Clock Gain */
    DMA->pty_cfg |= (0x01 << 16);
    return 0;
}

static int dma_clock_close(void)
{
    /* Disable AHB Gain */
    CCU->bus_clk_gating0 |= (0x1 << 6); 
    return 0;
}

int dma_controller_init(void)
{
    memset(ndma_channel_context, 0, sizeof(ndma_channel_context));
    memset(ddma_channel_context, 0, sizeof(ddma_channel_context));
    dma_clock_open();
    /* disable all interrupt */
    DMA->irq_ctrl = 0;
    /* clear pending interrupt */
    DMA->irq_sta  = 0x00FF00FF;
    /* 安装中断处理函数 */
    rt_hw_interrupt_install(DMA_INTERRUPT, dma_irq_process, RT_NULL, "dma_irq");
    rt_hw_interrupt_umask(DMA_INTERRUPT);
    return 0;
}
INIT_BOARD_EXPORT(dma_controller_init);

int dma_controller_exit(void)
{
    dma_clock_close();
    rt_hw_interrupt_mask(DMA_INTERRUPT);
    return 0;
}

int ndma_request_channel(void)
{
    int channel;
    for(channel = 0; channel < NDMA_CHANNEL_NUM; channel++)
    {
        if(ndma_channel_context[channel].busy == 0)
        {
            ndma_channel_context[channel].busy = 1;
            return channel;
        }
    }
    return -1;
}

void ndma_release_channel(int channel)
{
    if (channel >= NDMA_CHANNEL_NUM)
    {
        return ;
    }
    memset(&ndma_channel_context[channel], 0, sizeof(ndma_channel_context[0]));
    ndma_stop(channel);
    ndma_irq_disable(channel, DMA_IRQ_ALL);
}

int ndma_config(int channel, rt_uint32_t src_addr, rt_uint32_t dest_addr, rt_uint32_t count)
{
    if (channel >= NDMA_CHANNEL_NUM)
    {
        LOG_E("ndma chanel %d (0-%d) error!", channel,  NDMA_CHANNEL_NUM-1);
        return -1;
    }
    DMA->ndma_channel[channel].src_adr  = src_addr;
    DMA->ndma_channel[channel].des_adr  = dest_addr;
    DMA->ndma_channel[channel].byte_cnt = count & 0x3FFFF;
    return 0;
}

void ndma_init(uint32_t channel , uint32_t config)
{
    struct tina_ndma * ndma;

    if (channel >= NDMA_CHANNEL_NUM)
    {
        LOG_E("ndma chanel %d (0-%d) error!", channel,  NDMA_CHANNEL_NUM-1);
        return ;
    }
    ndma = &DMA->ndma_channel[channel];

    ndma->cfg = config;

    /* Continue Mode 使能,剩余字节数可读使能 */
    ndma->cfg |= NDMA_CFG_DMA_REMAIN_BYTE;

}

int ndma_callback_register(int channel, uint32_t irq_type, void (*callback)(int channel, void * ctx), void * ctx)
{
    if (channel >= NDMA_CHANNEL_NUM)
    {
        LOG_E("ndma chanel %d (0-%d) error!", channel,  NDMA_CHANNEL_NUM-1);
        return -1;
    }

    if(irq_type & DMA_IRQ_HALF)
    {
        ndma_channel_context[channel].half_callback     = callback;
        ndma_channel_context[channel].half_callback_ctx = ctx;
    }

    if(irq_type & DMA_IRQ_FULL)
    {
        ndma_channel_context[channel].full_callback     = callback;
        ndma_channel_context[channel].full_callback_ctx = ctx;
    }
    return 0;
}

/****************************************************************************************/
int ddma_request_channel(void)
{
    int channel;
    for(channel = 0; channel < DDMA_CHANNEL_NUM; channel++)
    {
        if(ddma_channel_context[channel].busy == 0)
        {
            ddma_channel_context[channel].busy = 1;
            return channel;
        }
    }
    return -1;
}

void ddma_release_channel(int channel)
{
    if (channel >= DDMA_CHANNEL_NUM)
    {
        return ;
    }
    memset(&ddma_channel_context[channel], 0, sizeof(ddma_channel_context[0]));
    ddma_stop(channel);
    ddma_irq_disable(channel, DMA_IRQ_ALL);
}

int ddma_config(int channel, rt_uint32_t src_addr, rt_uint32_t dest_addr, rt_uint32_t count)
{
    if (channel >= DDMA_CHANNEL_NUM)
    {
        LOG_E("ddma chanel %d (0-%d) error!", channel,  DDMA_CHANNEL_NUM-1);
        return -1;
    }
    DMA->ddma_channel[channel].src_adr  = src_addr;
    DMA->ddma_channel[channel].des_adr  = dest_addr;
    DMA->ddma_channel[channel].byte_cnt = count & 0x3FFFF;
    return 0;
}

void ddma_init(uint32_t channel , uint32_t config)
{
    struct tina_ddma * ddma;

    if (channel >= DDMA_CHANNEL_NUM)
    {
        LOG_E("ddma chanel %d (0-%d) error!", channel,  DDMA_CHANNEL_NUM-1);
        return ;
    }
    ddma = &DMA->ddma_channel[channel];

    ddma->cfg = config;

    /* Continue Mode 使能,剩余字节数可读使能 */
    ddma->cfg |= DDMA_CFG_DMA_REMAIN_BYTE;
}

int ddma_callback_register(int channel, uint32_t irq_type, void (*callback)(int channel, void * ctx), void * ctx)
{
    if (channel >= DDMA_CHANNEL_NUM)
    {
        LOG_E("ddma chanel %d (0-%d) error!", channel,  DDMA_CHANNEL_NUM-1);
        return -1;
    }

    if(irq_type & DMA_IRQ_HALF)
    {
        ddma_channel_context[channel].half_callback     = callback;
        ddma_channel_context[channel].half_callback_ctx = ctx;
    }

    if(irq_type & DMA_IRQ_FULL)
    {
        ddma_channel_context[channel].full_callback     = callback;
        ddma_channel_context[channel].full_callback_ctx = ctx;
    }
    return 0;
}
