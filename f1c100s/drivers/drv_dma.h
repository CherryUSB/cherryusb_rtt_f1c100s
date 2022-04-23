#ifndef __DRV_DMA_H__
#define __DRV_DMA_H__

#include <stdint.h>

/* DMA配置相关寄存器 */
struct tina_ndma
{
    volatile rt_uint32_t   cfg;             //0x00
    volatile rt_uint32_t   src_adr;         //0x04
    volatile rt_uint32_t   des_adr;         //0x08
    volatile rt_uint32_t   byte_cnt;        //0x0c
    volatile rt_uint32_t   reserved[4];
};

struct tina_ddma
{
    volatile rt_uint32_t   cfg;              //0x00
    volatile rt_uint32_t   src_adr;          //0x04
    volatile rt_uint32_t   des_adr;          //0x08
    volatile rt_uint32_t   byte_cnt;         //0x0c
    volatile rt_uint32_t   reserved[2];
    volatile rt_uint32_t   par;              //0x18
    volatile rt_uint32_t   gen_data;         //0x1c
};

struct tina_dma
{
    volatile rt_uint32_t   irq_ctrl;            //0x00
    volatile rt_uint32_t   irq_sta;             //0x04
    volatile rt_uint32_t   pty_cfg;             //0x08
    volatile rt_uint32_t   reserved11[61];
    struct tina_ndma       ndma_channel[4];     //0x100+n*0x20
    volatile rt_uint32_t   reserved22[96];
    struct tina_ddma       ddma_channel[4];     //0x300+n*0x20
};

typedef struct tina_dma *tina_dma_t;

#define R6_REG_DMA_BASE         (0x01c02000)

#define DMA ((tina_dma_t)R6_REG_DMA_BASE)

/* DMA intterrupt type */
#define DMA_IRQ_HALF 1
#define DMA_IRQ_FULL 2
#define DMA_IRQ_ALL  3

/************Normal DMA ******************************/
#define NDMA_CHANNEL_NUM  (4)

#define NDMA_CFG_SRC_DRQ_IR_RX    (0x00 << 0)
#define NDMA_CFG_SRC_DRQ_SPI0_RX  (0x04 << 0)
#define NDMA_CFG_SRC_DRQ_SPI1_RX  (0x05 << 0)
#define NDMA_CFG_SRC_DRQ_UART0_RX (0x08 << 0)
#define NDMA_CFG_SRC_DRQ_UART1_RX (0x09 << 0)
#define NDMA_CFG_SRC_DRQ_UART2_RX (0x0A << 0)
#define NDMA_CFG_SRC_DRQ_CODEC    (0x0c << 0)
#define NDMA_CFG_SRC_DRQ_TP_ADC   (0x0d << 0)
#define NDMA_CFG_SRC_DRQ_DAUDIO   (0x0e << 0)
#define NDMA_CFG_SRC_DRQ_SRAM     (0x10 << 0)
#define NDMA_CFG_SRC_DRQ_SDRAM    (0x11 << 0)
#define NDMA_CFG_SRC_DRQ_USB      (0x14 << 0)
#define NDMA_CFG_SRC_DRQ_USB_EP1  (0x15 << 0)
#define NDMA_CFG_SRC_DRQ_USB_EP2  (0x16 << 0)
#define NDMA_CFG_SRC_DRQ_USB_EP3  (0x17 << 0)

#define NDMA_CFG_SRC_LINEAR       (0x00 << 5)
#define NDMA_CFG_SRC_IO           (0x01 << 5)
#define NDMA_CFG_SRC_BST1         (0x00 << 7)
#define NDMA_CFG_SRC_BST4         (0x01 << 7)
#define NDMA_CFG_SRC_WIDTH8       (0x00 << 8)
#define NDMA_CFG_SRC_WIDTH16      (0x01 << 8)
#define NDMA_CFG_SRC_WIDTH32      (0x02 << 8)
#define NDMA_CFG_DMA_REMAIN_BYTE  (0x01 << 15)
#define NDMA_CFG_DST_DRQ_OWA_TX   (0x01 << 16)
#define NDMA_CFG_DST_DRQ_SPI0_TX  (0x04 << 16)
#define NDMA_CFG_DST_DRQ_SPI1_TX  (0x05 << 16)
#define NDMA_CFG_DST_DRQ_UART0_TX (0x08 << 16)
#define NDMA_CFG_DST_DRQ_UART1_TX (0x09 << 16)
#define NDMA_CFG_DST_DRQ_UART2_TX (0x0A << 16)
#define NDMA_CFG_DST_DRQ_CODEC    (0x0c << 16)
#define NDMA_CFG_DST_DRQ_DAUDIO   (0x0e << 16)
#define NDMA_CFG_DST_DRQ_SRAM     (0x10 << 16)
#define NDMA_CFG_DST_DRQ_SDRAM    (0x11 << 16)
#define NDMA_CFG_DST_DRQ_USB      (0x14 << 16)
#define NDMA_CFG_DST_DRQ_USB_EP1  (0x15 << 16)
#define NDMA_CFG_DST_DRQ_USB_EP2  (0x16 << 16)
#define NDMA_CFG_DST_DRQ_USB_EP3  (0x17 << 16)

#define NDMA_CFG_DST_LINEAR       (0x00 << 21)
#define NDMA_CFG_DST_IO           (0x01 << 21)
#define NDMA_CFG_DST_BST1         (0x00 << 23)
#define NDMA_CFG_DST_BST4         (0x01 << 23)
#define NDMA_CFG_DST_WIDTH8       (0x00 << 24)
#define NDMA_CFG_DST_WIDTH16      (0x01 << 24)
#define NDMA_CFG_DST_WIDTH32      (0x02 << 24)

#define NDMA_CFG_CONTINOUS_MODE   (0x01 << 29)
#define NDMA_CFG_BUSY_STATUS      (0x01 << 30)
#define NDMA_CFG_LOADING          (0x01 << 31)

/************Dedicated DMA ******************************/
#define DDMA_CHANNEL_NUM  (4)

#define DDMA_CFG_SRC_DRQ_SRAM     (0x00 << 0)
#define DDMA_CFG_SRC_DRQ_SDRAM    (0x01 << 0)
#define DDMA_CFG_SRC_DRQ_USB      (0x04 << 0)
#define DDMA_CFG_SRC_DRQ_AHB      (0x08 << 0)
#define DDMA_CFG_SRC_LINEAR       (0x00 << 5)
#define DDMA_CFG_SRC_IO           (0x01 << 5)
#define DDMA_CFG_SRC_BST1         (0x00 << 7)
#define DDMA_CFG_SRC_BST4         (0x01 << 7)
#define DDMA_CFG_SRC_WIDTH8       (0x00 << 8)
#define DDMA_CFG_SRC_WIDTH16      (0x01 << 8)
#define DDMA_CFG_SRC_WIDTH32      (0x02 << 8)
#define DDMA_CFG_DMA_REMAIN_BYTE  (0x01 << 15)
#define DDMA_CFG_DST_DRQ_SRAM     (0x00 << 16)
#define DDMA_CFG_DST_DRQ_SDRAM    (0x01 << 16)
#define DDMA_CFG_DST_DRQ_LCDC     (0x02 << 16)
#define DDMA_CFG_DST_DRQ_USB      (0x04 << 16)
#define DDMA_CFG_DST_DRQ_AHB      (0x09 << 16)
#define DDMA_CFG_DST_LINEAR       (0x00 << 21)
#define DDMA_CFG_DST_IO           (0x01 << 21)
#define DDMA_CFG_DST_BST1         (0x00 << 23)
#define DDMA_CFG_DST_BST4         (0x01 << 23)
#define DDMA_CFG_DST_WIDTH8       (0x00 << 24)
#define DDMA_CFG_DST_WIDTH16      (0x01 << 24)
#define DDMA_CFG_DST_WIDTH32      (0x02 << 24)
#define DDMA_CFG_MEMORY_SET_MODE  (0x01 << 28)
#define DDMA_CFG_CONTINOUS_MODE   (0x01 << 29)
#define DDMA_CFG_BUSY_STATUS      (0x01 << 30)
#define DDMA_CFG_LOADING          (0x01 << 31)
/*****************************************************************/

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/********************Normal DMA API **********************************/
inline void ndma_irq_enable(uint32_t channel, uint32_t irq_type)
{
    DMA->irq_ctrl |= (irq_type & 0x3) << (channel * 2);
}

inline void ndma_irq_disable(uint32_t channel, uint32_t irq_type)
{
    DMA->irq_ctrl &= ~((irq_type & 0x3)<< (channel * 2));
}

inline uint32_t ndma_irq_get_status(uint32_t channel)
{
    return (DMA->irq_sta >> (2 * channel)) & 0x03;
}

inline void ndma_irq_clear_pending(uint32_t channel, uint32_t irq_type)
{
    DMA->irq_sta = irq_type << (channel * 2);
}

inline uint32_t ndma_channel_get_remain_byte(uint32_t channel)
{
    return DMA->ndma_channel[channel].byte_cnt;
}

inline int ndma_start(int channel)
{
    DMA->ndma_channel[channel].cfg |= NDMA_CFG_LOADING;
    return 0;
}

inline int ndma_stop(int channel)
{
    DMA->ndma_channel[channel].cfg &= ~NDMA_CFG_LOADING;
    return 0;
}
int ndma_request_channel(void);
void ndma_release_channel(int channel);
int ndma_config(int channel, rt_uint32_t src_addr, rt_uint32_t dest_addr, rt_uint32_t count);
void ndma_init(uint32_t channel , uint32_t config);
int ndma_callback_register(int channel, uint32_t irq_type, void (*callback)(int channel, void * ctx), void * ctx);
/*************************************************************************/


/********************Dedicated DMA API **********************************/
inline void ddma_irq_enable(uint32_t channel, uint32_t irq_type)
{
    DMA->irq_ctrl |= (irq_type & 0x3) << (channel * 2 + 16);
}

inline void ddma_irq_disable(uint32_t channel, uint32_t irq_type)
{
    DMA->irq_ctrl &= ~((irq_type & 0x3)<< (channel * 2 + 16));
}

inline uint32_t ddma_irq_get_status(uint32_t channel)
{
    return (DMA->irq_sta >> (2 * channel + 16)) & 0x03;
}

inline void ddma_irq_clear_pending(uint32_t channel, uint32_t irq_type)
{
    DMA->irq_sta = irq_type << (channel * 2 + 16);
}

inline uint32_t ddma_channel_get_remain_byte(uint32_t channel)
{
    return DMA->ddma_channel[channel].byte_cnt;
}

inline int ddma_start(int channel)
{
    DMA->ddma_channel[channel].cfg |= DDMA_CFG_LOADING;
    return 0;
}

inline int ddma_stop(int channel)
{
    DMA->ddma_channel[channel].cfg &= ~DDMA_CFG_LOADING;
    return 0;
}
int ddma_request_channel(void);
void ddma_release_channel(int channel);
int  ddma_config(int channel, rt_uint32_t src_addr, rt_uint32_t dest_addr, rt_uint32_t count);
void ddma_init(uint32_t channel , uint32_t config);
int ddma_callback_register(int channel, uint32_t irq_type, void (*callback)(int channel, void * ctx), void * ctx);
/************************************************************************/
int dma_controller_init(void);
int dma_controller_exit(void);

#endif
