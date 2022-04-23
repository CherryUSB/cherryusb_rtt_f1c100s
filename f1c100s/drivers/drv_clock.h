/*
 * COPYRIGHT (C) 2012-2020, Shanghai Real-Thread Technology Co., Ltd
 * All rights reserved.
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */
#ifndef __DRV_CLOCK_H__
#define __DRV_CLOCK_H__

/* PLL state */
#define PLL_ENBALE              (0x1)
#define PLL_STABLE              (0x2)

/* Clock source selection */
#define CLK_LOSC_SRC            (0x00)
#define CLK_OSC24M_SRC          (0x01)
#define CLK_PLL_SRC             (0x02)
#define PRE_DIV_SRC             (0x03)

/*  */
#define TCON_PLL_VIDEO_X1       (0x000)
#define TCON_PLL_VIDEO_X2       (0x002)


#define PLL_CPU_ENABLE_STATE            (0x1<<31)
#define PLL_CPU_HAS_BEEN_STABLE         (0x1<<28)
#define PLL_CPU_DIV_P(reg)              ((reg>>16)&0x3)
#define PLL_CPU_FACTOR_N(reg)           ((reg>>8)&0x1f)
#define PLL_CPU_FACTOR_K(reg)           ((reg>>4)&0x3)
#define PLL_CPU_FACTOR_M(reg)           ((reg)&0x3)

#define PLL_AUDIO_ENABLE_STATE          (0x1<<31)
#define PLL_AUDIO_HAS_BEEN_STABLE       (0x1<<28)
#define PLL_AUDIO_FACTOR_N(reg)         ((reg>>8)&0x7f)
#define PLL_AUDIO_PREDIV_M(reg)         ((reg)&0x1f)

#define PLL_VIDEO_ENABLE_STATE          (0x1<<31)
#define PLL_VIDEO_MODE                  (0x1<<30)
#define PLL_VIDEO_HAS_BEEN_STABLE       (0x1<<28)
#define PLL_VIDEO_FRAC_CLK_OUT          (0x1<<25)
#define PLL_VIDEO_MODE_SEL              (0x1<<24)
#define PLL_VIDEO_SDM_EN                (0x1<<20)
#define PLL_VIDEO_FACTOR_N(reg)         ((reg>>8)&0x7f)
#define PLL_VIDEO_PREDIV_M(reg)         (reg&0xf)

#define PLL_VE_ENABLE_STATE             (0x1<<31)
#define PLL_VE_HAS_BEEN_STABLE          (0x1<<28)
#define PLL_VE_FRAC_CLK_OUT             (0x1<<25)
#define PLL_VE_MODE_SEL                 (0x1<<24)
#define PLL_VE_FACTOR_N(reg)            ((reg>>8)&0x7f)
#define PLL_VE_PREDIV_M(reg)            (reg&0xf)

#define PLL_DDR_ENABLE_STATE            (0x1<<31)
#define PLL_DDR_HAS_BEEN_STABLE         (0x1<<28)
#define SDRAM_SIGMA_DELTA_EN            (0x1<<24)
#define PLL_DDR_CFG_UPDATE              (0x1<<20)
#define PLL_DDR_FACTOR_N(reg)           ((reg>>8)&0x1f)
#define PLL_DDR_FACTOR_K(reg)           ((reg>>4)&0x3)
#define PLL_DDR_FACTOR_M(reg)           ((reg)&0x3)

#define PLL_PERIPH_ENABLE_STATE         (0x1<<31)
#define PLL_PERIPH_HAS_BEEN_STABLE      (0x1<<28)
#define PLL_PERIPH_24M_OUT_EN           (0x1<<18)
#define PLL_PERIPH_24M_POST_DIV(reg)    ((reg>>16)&0x3)
#define PLL_PERIPH_FACTOR_N(reg)        ((reg>>8)&0x1f)
#define PLL_PERIPH_FACTOR_K(reg)        ((reg>>4)&0x3)
#define PLL_PERIPH_FACTOR_M(reg)        (reg&0x3)

#define HCLKC_DIV(reg)                  ((reg>>16)&0x3)
#define AHB_SRC_SEL(reg)                ((reg>>12)&0x3)
#define AHB_CLK_DIV(reg)                ((reg>>4)&0x3)
#define AHB_PRE_DIV(reg)                ((reg>>6)&0x3)
#define APH_CLK_PATIO(reg)              ((reg>>8)&0x3)


#define CCM_MMC_CTRL_OSCM24             (0x00)
#define CCM_MMC_CTRL_PLL_PERIPH         (0x01)

#define CCU_BASE_ADDR      (0x01C20000)

#define _24MHZ_     (24000000U)
#define _32KHZ_     (32000U)

/* GATE */

#define BUS_GATE_OFFSET_BIT    (12)

enum bus_gate
{
    USB_OTG_GATING     = (0x18 | (0x0 << BUS_GATE_OFFSET_BIT)),
    SPI1_GATING        = (0x15 | (0x0 << BUS_GATE_OFFSET_BIT)),
    SPI0_GATING        = (0x14 | (0x0 << BUS_GATE_OFFSET_BIT)),
    SDRAM_GATING       = (0x0E | (0x0 << BUS_GATE_OFFSET_BIT)),
    SD1_GATING         = (0x09 | (0x0 << BUS_GATE_OFFSET_BIT)),
    SD0_GATING         = (0x08 | (0x0 << BUS_GATE_OFFSET_BIT)),
    DMA_GATING         = (0x06 | (0x0 << BUS_GATE_OFFSET_BIT)),

    DEFE_GATING        = (0x0E | (0x1 << BUS_GATE_OFFSET_BIT)),
    DEBE_GATING        = (0x0C | (0x1 << BUS_GATE_OFFSET_BIT)),
    TVE_GATING         = (0x0A | (0x1 << BUS_GATE_OFFSET_BIT)),
    TVD_GATING         = (0x09 | (0x1 << BUS_GATE_OFFSET_BIT)),
    CSI_GATING         = (0x08 | (0x1 << BUS_GATE_OFFSET_BIT)),
    DEINTERLACE_GATING = (0x05 | (0x1 << BUS_GATE_OFFSET_BIT)),
    LCD_GATING         = (0x04 | (0x1 << BUS_GATE_OFFSET_BIT)),
    VE_GATING          = (0x00 | (0x1 << BUS_GATE_OFFSET_BIT)),

    UART2_GATING       = (0x16 | (0x2 << BUS_GATE_OFFSET_BIT)),
    UART1_GATING       = (0x15 | (0x2 << BUS_GATE_OFFSET_BIT)),
    UART0_GATING       = (0x14 | (0x2 << BUS_GATE_OFFSET_BIT)),
    TWI2_GATING        = (0x12 | (0x2 << BUS_GATE_OFFSET_BIT)),
    TWI1_GATING        = (0x11 | (0x2 << BUS_GATE_OFFSET_BIT)),
    TWI0_GATING        = (0x10 | (0x2 << BUS_GATE_OFFSET_BIT)),
    DAUDIO_GATING      = (0x0C | (0x2 << BUS_GATE_OFFSET_BIT)),
    RSB_GATING         = (0x03 | (0x2 << BUS_GATE_OFFSET_BIT)),
    CIR_GATING         = (0x02 | (0x2 << BUS_GATE_OFFSET_BIT)),
    OWA_GATING         = (0x01 | (0x2 << BUS_GATE_OFFSET_BIT)),
    AUDIO_CODEC_GATING = (0x00 | (0x2 << BUS_GATE_OFFSET_BIT)),
};

enum bus_dram
{
    BE_GATING_DRAM           = 26,
    FE_GATING_DRAM           = 24,
    TVD_GATING_DRAM          = 3,
    DEINTERLACE_GATING_DRAM  = 2,
    CSI_GATING_DRAM          = 1,
    VE_GATING_DRAM           = 0,
};

enum mmc_clk_id
{
    SDMMC0,
    SDMMC1,
};
typedef struct
{                               //PLL1_CORE output freq = (24*N*K)/(M*P)
    volatile rt_uint32_t   FactorM:2;          //bit0,  PLL1 Factor M, M = FactorM+1
    volatile rt_uint32_t   reserved0:2;        //bit2, bit3 reserved
    volatile rt_uint32_t   FactorK:2;          //bit4,  PLL1 factor K, K = FactorK+1
    volatile rt_uint32_t   reserved1:2;        //bit6,  reserved
    volatile rt_uint32_t   FactorN:5;          //bit8,  PLL1 Factor N, N = FactorN+1
    volatile rt_uint32_t   reserved2:3;        //bit13, reserved
    volatile rt_uint32_t   PLLDivP:2;          //bit16, PLL1 output external divider P,P=PLLDivP+1
    volatile rt_uint32_t   reserved3:10;       //bit18, reserved
    volatile rt_uint32_t   IsLocked:1;         //bit28, it indicates that the PLL has been stable
    volatile rt_uint32_t   reserved4:2;        //bit18, reserved
    volatile rt_uint32_t   PLLEn:1;            //bit31, 0-disable, 1-enable, (24Mhz*N*K)/(M*P)
} __ccmu_pll1_core_reg0000_t;

typedef struct
{                               //PLL1_AUDIO output freq = (24*N*2)/M
    volatile rt_uint32_t   PreDivM:5;          //bit0,  Pre-div factor(M=Factor+1)
    volatile rt_uint32_t   reserved0:3;        //bit5,  reserved
    volatile rt_uint32_t   FactorN:7;          //bit8,  PLL2 factor N,
    volatile rt_uint32_t   reserved1:9;        //bit15, reserved
    volatile rt_uint32_t   PLLSdmEn:1;         //bit24, PLL_SDM_EN
    volatile rt_uint32_t   reserved2:3;        //bit25, reserved
    volatile rt_uint32_t   IsLocked:1;         //bit28, PLL2 is stable
    volatile rt_uint32_t   reserved3:2;        //bit29, reserved
    volatile rt_uint32_t   PLLEn:1;            //bit31, PLL2 enable
} __ccmu_pll2_audio_reg0008_t;

typedef struct
{
    volatile rt_uint32_t   PreDivM:4;          //bit0,  Pre-div factor(M=Factor+1)
    volatile rt_uint32_t   reserved0:4;        //bit4, bit5,bit6,bit7 reserved
    volatile rt_uint32_t   FactorN:7;          //bit8,  PLL3 factor N,
    volatile rt_uint32_t   reserved1:5;        //bit15, reserved
    volatile rt_uint32_t   PLLSdmEn:1;         //bit20, PLL_SDM_EN
    volatile rt_uint32_t   reserved2:3;        //bit21, reserved
    volatile rt_uint32_t   ModeSel:1;          //bit24,
    volatile rt_uint32_t   FracClkOut:1;       //bit25,
    volatile rt_uint32_t   reserved3:2;        //bit26,bit27reserved
    volatile rt_uint32_t   IsLocked:1;         //bit28, PLL3 is stable
    volatile rt_uint32_t   reserved4:1;        //bit29, reserved
    volatile rt_uint32_t   PLLMode:1;          //bit30, PLL_MODE; 0:Manual Mode; 1:Auto mode
    volatile rt_uint32_t   PLLEn:1;            //bit31, PLL3 enable
} __ccmu_pll3_video_reg0010_t;

typedef struct
{
    volatile rt_uint32_t   PreDivM:4;          //bit0,  Pre-div factor(M=Factor+1)
    volatile rt_uint32_t   reserved0:4;        //bit4,  reserved
    volatile rt_uint32_t   FactorN:7;          //bit8,  PLL4 factor N,
    volatile rt_uint32_t   reserved1:9;        //bit15, reserved
    volatile rt_uint32_t   ModeSel:1;          //bit24,
    volatile rt_uint32_t   FracClkOut:1;       //bit25,
    volatile rt_uint32_t   reserved2:2;        //bit26,bit27
    volatile rt_uint32_t   IsLocked:1;         //bit28, PLL4 is stable
    volatile rt_uint32_t   reserved3:2;        //bit29, reserved
    volatile rt_uint32_t   PLLEn:1;            //bit31, PLL4 enable
} __ccmu_pll4_ve_reg0018_t;

typedef struct
{                               //PLLout = 24*N*K/M
    volatile rt_uint32_t   FactorM:2;          //bit0,  PLL5 factor M
    volatile rt_uint32_t   reserved0:2;        //bit1,  reserved
    volatile rt_uint32_t   FactorK:2;          //bit4,  PLL5 factor K
    volatile rt_uint32_t   reserved1:2;        //bit6,  reserved
    volatile rt_uint32_t   FactorN:5;          //bit8,  PLL5 factor N
    volatile rt_uint32_t   reserved2:7;         //bit13-bit19, reserved
    volatile rt_uint32_t   pll_ddr_cfg_update:1;//bit20, pll_ddr_cfg_update
    volatile rt_uint32_t   reserved3:3;         //bit21,bit22,bit23 reserved
    volatile rt_uint32_t   SigmaDeltaEn:1;     //bit24, Sdram sigma delta enable
    volatile rt_uint32_t   reserved4:3;         //bit25,  reserved
    volatile rt_uint32_t   IsLocked:1;         //bit28, PLL5 is stable
    volatile rt_uint32_t   reserved5:2;         //bit29, bit30, reserved
    volatile rt_uint32_t   PLLEn:1;            //bit31, PLL5 Enable
} __ccmu_pll5_ddr_reg0020_t;

typedef struct
{                               //PLL output = 24*N*K
    volatile rt_uint32_t   FactorM:2;          //bit0,  PLL6 factor M
    volatile rt_uint32_t   reserved0:2;        //bit2,  reserved
    volatile rt_uint32_t   FactorK:2;          //bit4,  PLL6 factor K
    volatile rt_uint32_t   reserved1:2;        //bit6,  reserved
    volatile rt_uint32_t   FactorN:5;          //bit8,  PLL6 factor N
    volatile rt_uint32_t   reserved2:3;        //bit13,  reserved
    volatile rt_uint32_t   PLL24MPostDiv:2;    //bit16
    volatile rt_uint32_t   PLL24MOutEn:1;      //bit18
    volatile rt_uint32_t   reserved3:9;        //bit19,  reserved
    volatile rt_uint32_t   IsLocked:1;         //bit28, PLL5 is stable
    volatile rt_uint32_t   reserved4:2;        //bit29,  reserved
    volatile rt_uint32_t   PLLEn:1;            //bit31, PLL6 enable
} __ccmu_pll6_periph_reg0028_t;

typedef struct
{
    volatile rt_uint32_t   reserved0:4;        //bit0,  reserved
    volatile rt_uint32_t   AHB1ClkRatio:2;     //bit4,  AHB1 clock divide ration,  00-1, 01-2, 10-4, 11-8
    volatile rt_uint32_t   AHB1PreClkDiv:2;    //bit6,  AHB1 pre-divide ratio,  00-1, 01-2, 10-3, 11-4
    volatile rt_uint32_t   APBClkRatio:2;      //bit8,  APB clock divide ration,  APB clock source is AHB1 clock, 00-2, 01-2, 10-4, 11-8
    volatile rt_uint32_t   reserved1:2;        //bit10, reserved
    volatile rt_uint32_t   AHB1ClkSrcSel:2;    //bit12, 00:LOSC; 01:OSC24M; 10:CPUCLK; 11:PLL_PERIPH/AHB1_PRE_DIV
    volatile rt_uint32_t   reserved2:2;        //bit14, reserved
    volatile rt_uint32_t   HCLK_C_DIV:2;       //bit16, HCLK_C clock divide ratio,the clock source is the cpuclk
    volatile rt_uint32_t   reserved3:14;       //bit18, reserved
} __ccmu_amba_clk_ratio_reg0054_t;

typedef struct
{
    volatile rt_uint32_t   reserved0:6;        //bit0, reserved
    volatile rt_uint32_t   DmaGate:1;          //bit6,  gating AHB clock for DMA, 0-mask, 1-pass
    volatile rt_uint32_t   reserved1:1;        //bit7,  gating AHB clock for BIST, 0-mask, 1-pass
    volatile rt_uint32_t   Sdmmc0Gate:1;       //bit8,  gating AHB clock for SD/MMC0, 0-mask, 1-pass
    volatile rt_uint32_t   Sdmmc1Gate:1;       //bit9,  gating AHB clock for SD/MMC1, 0-mask, 1-pass
    volatile rt_uint32_t   reserved2:4;        //bit10, gating AHB clock for SD/MMC2, 0-mask, 1-pass
    volatile rt_uint32_t   SdramGate:1;        //bit14, gating AHB clock for SDRAM, 0-mask, 1-pass
    volatile rt_uint32_t   reserved3:5;        //bit15, reserved
    volatile rt_uint32_t   Spi0Gate:1;         //bit20, gating AHB clock for SPI0, 0-mask, 1-pass
    volatile rt_uint32_t   Spi1Gate:1;         //bit21, gating AHB clock for SPI1, 0-mask, 1-pass
    volatile rt_uint32_t   reserved4:2;        //bit22, reserved
    volatile rt_uint32_t   UsbOtgGate:1;       //bit24, gating AHB clock for PATA, 0-mask, 1-pass
    volatile rt_uint32_t   reserved5:7;        //bit25, reserved
} __ccmu_ahbclk_gate0_reg0060_t;

typedef struct
{
    volatile rt_uint32_t   VeGate:1;           //bit0,  gating AHB clock for VE, 0-mask, 1-pass
    volatile rt_uint32_t   reserved0:3;        //bit1,  reserved
    volatile rt_uint32_t   Lcd0Gate:1;         //bit4,  gating AHB clock for LCD0, 0-mask, 1-pass
    volatile rt_uint32_t   DeInterlaceGate:1;  //bit5,  gating AHB clock for deinterlace
    volatile rt_uint32_t   reserved1:2;        //bit6,  reserved
    volatile rt_uint32_t   Csi0Gate:1;         //bit8,  gating AHB clock for CSI0, 0-mask, 1-pass
    volatile rt_uint32_t   TvdGate:1;          //bit9,  gating AHB clock for TVD
    volatile rt_uint32_t   TveGate:1;          //bit10, reserved
    volatile rt_uint32_t   reserved2:1;        //bit11,  reserved
    volatile rt_uint32_t   DeBe0Gate:1;        //bit12, gating AHB clock for DE-BE0, 0-mask, 1-pass
    volatile rt_uint32_t   reserved3:1;        //bit13,  reserved
    volatile rt_uint32_t   DeFe0Gate:1;        //bit14, gating AHB clock for DE-FE0, 0-mask, 1-pass
    volatile rt_uint32_t   reserved4:17;       //bit15,
} __ccmu_ahbclk_gate1_reg0064_t;

typedef struct
{
    volatile rt_uint32_t   reserved0:16;       //bit0,  reserved
    volatile rt_uint32_t   CpuClkSrcSel:2;     //bit16
    volatile rt_uint32_t   reserved1:14;       //bit18,  reserved
} __ccmu_cpu_clk_sel_reg0050_t;

typedef struct
{
    volatile rt_uint32_t   AddaGate:1;         //bit0,  gating APB clock for audio codec, 0-mask, 1-pass
    volatile rt_uint32_t   SpdifGate:1;        //bit1,  gating APB clock for SPDIF, 0-mask, 1-pass
    volatile rt_uint32_t   CIRGate:1;          //bit2,  gating APB clock for CIR
    volatile rt_uint32_t   RSBGate:1;          //bit3,  gating APB clock for RSB, 0-mask, 1-pass
    volatile rt_uint32_t   reserved0:8;        //bit4,  reserved
    volatile rt_uint32_t   DAudioGate:1;       //bit12,  gating APB clock for DAUDIO, 0-mask, 1-pass
    volatile rt_uint32_t   reserved1:3;        //bit13,
    volatile rt_uint32_t   Twi0Gate:1;         //bit16,  gating APB clock for TWI0, 0-mask, 1-pass
    volatile rt_uint32_t   Twi1Gate:1;         //bit17,  twi1 gate
    volatile rt_uint32_t   Twi2Gate:1;         //bit18,  twi2 gate
    volatile rt_uint32_t   reserved2:1;        //bit19,  reserved
    volatile rt_uint32_t   Uart0Gate:1;        //bit20,  gating APB clock for uart0
    volatile rt_uint32_t   Uart1Gate:1;        //bit21,  gating APB clock for uart1
    volatile rt_uint32_t   Uart2Gate:1;        //bit22,  gating APB clock for uart1
    volatile rt_uint32_t   reserved3:9;       //bit23, reserved
} __ccmu_apb0clk_gate_reg0068_t;

typedef struct
{
    volatile rt_uint32_t   ClkDivRatioM:4;     //bit0 clock divide ratioM, divided by (m+1), 1~16 ex.
    volatile rt_uint32_t   reserved0:4;        //bit4, reserved
    volatile rt_uint32_t   OutClkPhaseCtr:3;   //bit8, output clock phase delay control.
    volatile rt_uint32_t   reserved1:5;        //bit11, reserved
    volatile rt_uint32_t   ClkDivRatioN:2;     //bit16  clock divide ratioN, divided by 2^N, the divider is 1,2,4,8
    volatile rt_uint32_t   reserved2:2;        //bit18, reserved
    volatile rt_uint32_t   SampleClkPhaseCtr:3;//bit20, sample clock phase delay control.
    volatile rt_uint32_t   reserved3:1;        //bit23, reserved
    volatile rt_uint32_t   ClkSrcSel:2;        //bit24, 00:OSC24M; 01 PLL_PERIPH;
    volatile rt_uint32_t   reserved4:5;        //bit26-bit30, reserved
    volatile rt_uint32_t   SpecialClkGate:1;   //bit31, the special clock = ClockSource/DividerN/DividerM
} __ccmu_sdmmc0_clk_reg0088_t;

typedef struct
{
    volatile rt_uint32_t   ClkDivRatioM:4;     //bit0 clock divide ratioM, divided by (m+1), 1~16 ex.
    volatile rt_uint32_t   reserved0:4;        //bit4, reserved
    volatile rt_uint32_t   OutClkPhaseCtr:3;   //bit8, output clock phase delay control.
    volatile rt_uint32_t   reserved1:5;        //bit11, reserved
    volatile rt_uint32_t   ClkDivRatioN:2;     //bit16  clock divide ratioN, divided by 2^N, the divider is 1,2,4,8
    volatile rt_uint32_t   reserved2:2;        //bit18, reserved
    volatile rt_uint32_t   SampleClkPhaseCtr:3;//bit20, sample clock phase delay control.
    volatile rt_uint32_t   reserved3:1;        //bit23, reserved
    volatile rt_uint32_t   ClkSrcSel:2;        //bit24, 00:OSC24M; 01 PLL_PERIPH;
    volatile rt_uint32_t   reserved4:5;        //bit26-bit30, reserved
    volatile rt_uint32_t   SpecialClkGate:1;   //bit31, the special clock = ClockSource/DividerN/DividerM
} __ccmu_sdmmc1_clk_reg008c_t;

typedef struct
{
    volatile rt_uint32_t   reserved0:16;       //bit0,  reserved
    volatile rt_uint32_t   ClkSrcSel:2;        //bit16, 00: PLL_AUDIO(8X); 01: PLL_AUDIO(8X)/2; 10:PLL_AUDIO(8X)/4; 11: PLL_AUDIO(8X)/8
    volatile rt_uint32_t   reserved1:13;       //bit18, reserved
    volatile rt_uint32_t   SpecialClkGate:1;   //bit31, reserved
} __ccmu_daudio_clk_reg00b0_t;

typedef struct
{
    volatile rt_uint32_t   reserved0:16;       //bit0,  reserved
    volatile rt_uint32_t   ClkSrcSel:2;        //bit16, 00: PLL_AUDIO(8X); 01: PLL_AUDIO(8X)/2; 10:PLL_AUDIO(8X)/4; 11: PLL_AUDIO(8X)/8
    volatile rt_uint32_t   reserved1:13;       //bit18, reserved
    volatile rt_uint32_t   SpecialClkGate:1;   //bit31, reserved
} __ccmu_spdif_clk_reg00b4_t;

typedef struct
{
    volatile rt_uint32_t   ClkDivRatioM:4;     //bit0 clock divide ratioM, divided by (m+1), 1~16 ex.
    volatile rt_uint32_t   reserved0:12;       //bit4, reserved
    volatile rt_uint32_t   ClkDivRatioN:2;     //bit16  clock divide ratioN, divided by 2^N, the divider is 1,2,4,8
    volatile rt_uint32_t   reserved1:6;        //bit18, reserved
    volatile rt_uint32_t   ClkSrcSel:2;        //bit24, 00:LOSC; 01 OSC24M;
    volatile rt_uint32_t   reserved2:5;        //bit26, reserved
    volatile rt_uint32_t   SpecialClkGate:1;   //bit31, the special clock = ClockSource/DividerN/DividerM
} __ccmu_cir_clk_reg00b8_t;

typedef struct
{
    volatile rt_uint32_t   UsbPhy0Rst:1;       //bit0,  USB PHY0 reset control, 0-reset valid, 1-reset invalid
    volatile rt_uint32_t   UsbSpecialClkGate:1;//bit1,  USBPHY 24MHZ Clock Gating
    volatile rt_uint32_t   reserved2:30;       //bit2,  reserved
} __ccmu_usb_clk_reg00cc_t;


typedef struct
{
    volatile rt_uint32_t   VeGate:1;           //bit0,  Gating dram clock for VE, 0-mask, 1-pass
    volatile rt_uint32_t   Csi0Gate:1;         //bit1,  Gating dram clock for CSI0, 0-mask, 1-pass
    volatile rt_uint32_t   DeInterlaceGate:1;  //bit2,  Gating dram clock for DeInterlace
    volatile rt_uint32_t   TvdGate:1;          //bit3,  Gating dram clock for TVD, 0-mask, 1-pass
    volatile rt_uint32_t   reserved0:20;       //bit4,  reserved
    volatile rt_uint32_t   DeFeGate:1;         //bit24, Gating dram clock for DE_FE0, 0-mask, 1-pass
    volatile rt_uint32_t   reserved1:1;        //bit25,  reserved
    volatile rt_uint32_t   DeBeGate:1;         //bit26, Gating dram clock for DE_BE0, 0-mask, 1-pass
    volatile rt_uint32_t   reserved2:5;        //bit27-bit31, reserved
} __ccmu_dram_clk_gate_reg0100_t;



typedef struct
{
    volatile rt_uint32_t   ClkDivRatioM:4;     //bit0,  clock divide ratioM, divied by (m+1), 1~16 ex.
    volatile rt_uint32_t   reserved0:20;       //bit4,  reserved
    volatile rt_uint32_t   ClkSrc:3;           //bit24, clock source select, 000-PLL_VIDEO, 001-Reserved, 010-PLL_PERIPH, others-reserved
    volatile rt_uint32_t   reserved1:4;        //bit27, reserved
    volatile rt_uint32_t   SpecialClkGate:1;   //bit31, gating special clock, 0-clock off, 1-clock on,special clock = clock source/DividerM
} __ccmu_debe_clk_reg0104_t;

typedef struct
{
    volatile rt_uint32_t   ClkDivRatioM:4;     //bit0,  clock divide ratioM, divied by (m+1), 1~16 ex.
    volatile rt_uint32_t   reserved0:20;       //bit4,  reserved
    volatile rt_uint32_t   ClkSrc:3;           //bit24, clock source select, 000-PLL_VIDEO, 001-Reserved, 010-PLL_PERIPH, others-reserved
    volatile rt_uint32_t   reserved1:4;        //bit27, reserved
    volatile rt_uint32_t   SpecialClkGate:1;   //bit31, gating special clock, 0-clock off, 1-clock on,special clock = clock source/DividerM
} __ccmu_defe_clk_reg010c_t;


typedef struct
{
    volatile rt_uint32_t   reserved0:24;       //bit0,  reserved
    volatile rt_uint32_t   ClkSrcSel:3;        //bit24, clock source select, 000-PLL_VIDEO(1x), 001-RESERVED, 010-PLL_VIDEO(2x), others:reserved
    volatile rt_uint32_t   reserved1:4;        //bit27, reserved
    volatile rt_uint32_t   SpecialClkGate:1;   //bit31, gating special clock, 0-clock off, 1-clock on
} __ccmu_lcd_clk_reg0118_t;


typedef struct
{
    volatile rt_uint32_t   ClkDivRatioM:4;     //bit0,  clock divide ratioM, divied by (m+1), 1~16 ex.
    volatile rt_uint32_t   reserved0:20;       //bit4,  reserved
    volatile rt_uint32_t   ClkSrcSel:3;        //bit24, clock source select, 000-PLL_VIDEO(1x), 001-RESERVED, 010-PLL_VIDEO(2x), others:reserved
    volatile rt_uint32_t   reserved1:4;        //bit27, reserved
    volatile rt_uint32_t   SpecialClkGate:1;   //bit31, gating special clock, 0-clock off, 1-clock on
} __ccmu_deinterlace_clk_reg011c_t;


typedef struct
{
    volatile rt_uint32_t   ClkDivRatioM:4;     //bit0,  clock divide ratio, divided by (m+1), 1~16 ex.
    volatile rt_uint32_t   reserved0:4;        //bit4,  reserved
    volatile rt_uint32_t   SpecClk1SrcSel:1;   //bit8,  special clock source select,0:tve_SCLK2; 1: tve_SCLK2_divide by2
    volatile rt_uint32_t   reserved1:1;        //bit9,  reserved
    volatile rt_uint32_t   reserved2:5;        //bit10-bit14,  reserved
    volatile rt_uint32_t   SpecClk1Gate:1;     //bit15, gating special clock, 0-clock off, 1-clock on
    volatile rt_uint32_t   reserved3:8;        //bit16-bit23, 8bits, reserved
    volatile rt_uint32_t   SpecClk2SrcSel:3;   //bit24, special clock source select,000:PLL_VIDEO(1X); 001:/; 010:PLL_VIDEO(2X)
    volatile rt_uint32_t   reserved4:4;        //bit27, reserved
    volatile rt_uint32_t   SpecClk2Gate:1;     //the special clock = clock/DividerM
} __ccmu_tve_clk_reg0120_t;

typedef struct
{
    volatile rt_uint32_t   ClkDivRatioM:4;     //bit0,  clock divide ratio, divided by (m+1), 1~16 ex.
    volatile rt_uint32_t   reserved0:20;       //bit4,  reserved
    volatile rt_uint32_t   ClkSrc:3;           //bit24, clock source select, 000-PLL_VIDEO(1X), 001:OSC24M; 010:PLL_VIDEO(2X)
    volatile rt_uint32_t   reserved1:4;        //bit27, reserved
    volatile rt_uint32_t   SpecClkGate:1;      //bit31, gating special clock, 0-clock off, 1-clock on
} __ccmu_tvd_clk_reg0124_t;

/* CSI module clock type, used for CSI0/1 */
/* register address is 0x0134~0x0138 */
typedef struct
{
    volatile rt_uint32_t   MasterClkDivM:4;    //bit0,  clock divide ratio, divided by (m+1), 1~16, ex.
    volatile rt_uint32_t   reserved0:4;        //bit4,  reserved
    volatile rt_uint32_t   MasterClkSrc:3;     //bit8,  clock source select, 000:PLL_VIDEO(1X); 101:OSC24M; others:reserved
    volatile rt_uint32_t   reserved1:4;        //bit11-bit14, reserved
    volatile rt_uint32_t   MasterClkGate:1;    //bit15, Gating special clock, 0-clock off, 1-clock on
    volatile rt_uint32_t   reserved2:16;       //bit16, reserved
} __ccmu_csi_clk_reg0134_t;


typedef struct
{
    volatile rt_uint32_t   reserved0:31;       //bit1,  reserved
    volatile rt_uint32_t   SpecClkGate:1;      //bit31, gating special clock for VE, 0-mask, 1-pass
}__ccmu_ve_clk_reg013c_t;


typedef struct
{
    volatile rt_uint32_t   reserved0:31;       //bit0,  reserved
    volatile rt_uint32_t   SpecClkGate:1;      //bit31, Gating special clock, 0-clock off, 1-clock on
} __ccmu_adda_clk_reg0140_t;

typedef struct
{
    volatile rt_uint32_t   reserved0:31;       //bit0,  reserved
    volatile rt_uint32_t   SpecClkGate:1;      //bit31, Gating special clock, 0-clock off, 1-clock on
} __ccmu_avs_clk_reg0144_t;

typedef struct
{
    volatile rt_uint32_t   PllLockTime:16;     //bit0
    volatile rt_uint32_t   reserved0:16;       //bit16,  reserved
} __ccmu_pll_lock_time_reg0200_t;


typedef struct
{
    volatile rt_uint32_t   PllLockTime:16;     //bit0
    volatile rt_uint32_t   reserved0:16;       //bit16,  reserved
} __ccmu_pll_cpu_lock_time_reg0204_t;


typedef struct
{
    volatile rt_uint32_t   DampFactorCtrl:4;   //bit0
    volatile rt_uint32_t   reserved0:4;        //bit4,  reserved
    volatile rt_uint32_t   LockCtrl:3;         //bit8, pll lock time control
    volatile rt_uint32_t   reserved1:5;        //bit11
    volatile rt_uint32_t   BiasCurCtrl:5;      //bit16
    volatile rt_uint32_t   reserved2:3;        //bit21
    volatile rt_uint32_t   VcoBiasCtrl:4;      //bit24
    volatile rt_uint32_t   reserved3:3;        //bit28
    volatile rt_uint32_t   VcoReset:1;         //bit31  VCO reset in
} __ccmu_pll_bias_reg0220_t;


typedef struct
{
    volatile rt_uint32_t   reserved0:16;        //bit0, reserved
    volatile rt_uint32_t   BiasCur:5;           //bit16
    volatile rt_uint32_t   reserved1:3;        //bit121
    volatile rt_uint32_t   VcoBias:5;          //bit24
    volatile rt_uint32_t   reserved2:3;        //bit29
} __ccmu_pll_audio_bias_reg0224_t;

typedef struct
{
    volatile rt_uint32_t   DampFactorCtrl:3;    //bit0
    volatile rt_uint32_t   reserved0:13;        //bit3, reserved
    volatile rt_uint32_t   BiasCtrl:5;           //bit16
    volatile rt_uint32_t   reserved1:3;        //bit121
    volatile rt_uint32_t   VcoBiasCtrl:5;       //bit24
    volatile rt_uint32_t   reserved2:3;         //bit29
} __ccmu_pll_video_bias_reg0228_t;

typedef struct
{
    volatile rt_uint32_t   DampFactorCtrl:3;    //bit0
    volatile rt_uint32_t   reserved0:13;        //bit3, reserved
    volatile rt_uint32_t   BiasCtrl:5;          //bit16
    volatile rt_uint32_t   reserved1:3;         //bit21
    volatile rt_uint32_t   VcoBiasCtrl:5;       //bit24
    volatile rt_uint32_t   reserved2:3;         //bit29
} __ccmu_pll_ve_bias_reg022c_t;

enum tcon_clk
{
    TCON_VIDEO_X1,
    TCON_VIDEO_X2,
    TCON_VIDEO_DISABLE,
};

struct tina_ccu
{
    volatile rt_uint32_t pll_cpu_ctrl;         /* 0x000 */
    volatile rt_uint32_t reserved0;
    volatile rt_uint32_t pll_audio_ctrl;       /* 0x008 */
    volatile rt_uint32_t reserved1;
    volatile rt_uint32_t pll_video_ctrl;       /* 0x010 */
    volatile rt_uint32_t reserved2;
    volatile rt_uint32_t pll_ve_ctrl;          /* 0x018 */
    volatile rt_uint32_t reserved3;
    volatile rt_uint32_t pll_ddr_ctrl;         /* 0x020 */
    volatile rt_uint32_t reserved4;
    volatile rt_uint32_t pll_periph_ctrl;      /* 0x028 */
    volatile rt_uint32_t reserved5[9];
    volatile rt_uint32_t cpu_clk_src;          /* 0x050 */
    volatile rt_uint32_t ahb_apb_hclkc_cfg;    /* 0x054 */
    volatile rt_uint32_t reserved6[2];
    volatile rt_uint32_t bus_clk_gating0;      /* 0x060 */
    volatile rt_uint32_t bus_clk_gating1;      /* 0x064 */
    volatile rt_uint32_t bus_clk_gating2;      /* 0x068 */
    volatile rt_uint32_t reserved7[7];
    volatile rt_uint32_t sdmmc0_clk;           /* 0x088 */
    volatile rt_uint32_t sdmmc1_clk;           /* 0x08C */
    volatile rt_uint32_t reserved8[8];
    volatile rt_uint32_t daudio_clk;           /* 0x0B0 */
    volatile rt_uint32_t owa_clk;              /* 0x0B4 */
    volatile rt_uint32_t cir_clk;              /* 0x0B8 */
    volatile rt_uint32_t reserved9[4];
    volatile rt_uint32_t usbphy_clk;           /* 0x0CC */
    volatile rt_uint32_t reserved10[12];
    volatile rt_uint32_t dram_gating;          /* 0x100 */
    volatile rt_uint32_t be_clk;               /* 0x104 */
    volatile rt_uint32_t reserved11;
    volatile rt_uint32_t fe_clk;               /* 0x10C */
    volatile rt_uint32_t reserved12[2];
    volatile rt_uint32_t tcon_clk;             /* 0x118*/
    volatile rt_uint32_t di_clk;               /* 0x11C */
    volatile rt_uint32_t tve_clk;              /* 0x120 */
    volatile rt_uint32_t tvd_clk;              /* 0x124 */
    volatile rt_uint32_t reserved13[3];
    volatile rt_uint32_t csi_clk;              /* 0x134 */
    volatile rt_uint32_t reserved14;
    volatile __ccmu_ve_clk_reg013c_t ve_clk;               /* 0x13C */
    volatile rt_uint32_t audio_codec_clk;      /* 0x140 */
    volatile rt_uint32_t avs_clk;              /* 0x144 */
    volatile rt_uint32_t reserved15[46];
    volatile rt_uint32_t pll_stable_time0;     /* 0x200 */
    volatile rt_uint32_t pll_stable_time1;     /* 0x204 */
    volatile rt_uint32_t reserved16[6];
    volatile rt_uint32_t pll_cpu_bias;         /* 0x220 */
    volatile rt_uint32_t pll_audio_bias;       /* 0x224 */
    volatile rt_uint32_t pll_video_bias;       /* 0x228 */
    volatile rt_uint32_t pll_ve_bias;          /* 0x22C */
    volatile rt_uint32_t pll_ddr_bias;         /* 0x230 */
    volatile rt_uint32_t pll_periph_bias;      /* 0x234 */
    volatile rt_uint32_t reserved17[6];
    volatile rt_uint32_t pll_cpu_tun;          /* 0x250 */
    volatile rt_uint32_t reserved18[3];
    volatile rt_uint32_t pll_ddr_tun;          /* 0x260 */
    volatile rt_uint32_t reserved19[8];
    volatile rt_uint32_t pll_audio_pat_ctrl;   /* 0x284 */
    volatile rt_uint32_t pll_video_pat_ctrl;   /* 0x288 */
    volatile rt_uint32_t reserved20;
    volatile rt_uint32_t pll_ddr_pat_ctrl;     /* 0x290 */
    volatile rt_uint32_t reserved21[11];
    volatile rt_uint32_t bus_soft_rst0;        /* 0x2C0 */
    volatile rt_uint32_t bus_soft_rst1;        /* 0x2C4 */
    volatile rt_uint32_t reserved22[2];
    volatile rt_uint32_t bus_soft_rst2;        /* 0x2D0 */
};
typedef struct tina_ccu *tina_ccu_t;

#define CCU ((tina_ccu_t) CCU_BASE_ADDR)

int cpu_get_pll_clk(void);
int audio_get_pll_clk(void);
int video_get_pll_clk(void);
int ve_get_pll_clk(void);
int ddr_get_pll_clk(void);
int periph_get_pll_clk(void);
int cpu_get_clk(void);
int ahb_get_clk(void);
int apb_get_clk(void);

rt_err_t cpu_set_pll_clk(int clk);
rt_err_t audio_set_pll_clk(int clk);
rt_err_t video_set_pll_clk(int clk);
rt_err_t ve_set_pll_clk(int clk);
rt_err_t periph_set_pll_clk(int clk);

rt_err_t cpu_set_clk(int clk);

rt_err_t bus_gate_clk_enable(enum bus_gate bus);
rt_err_t bus_gate_clk_disable(enum bus_gate bus);
rt_err_t bus_software_reset_enable(enum bus_gate bus);
rt_err_t bus_software_reset_disable(enum bus_gate bus);
rt_err_t bus_gate_dram_enalbe(enum bus_dram bus);
rt_err_t bus_gate_dram_disable(enum bus_dram bus);

rt_err_t mmc_set_clk(enum mmc_clk_id clk_id, int hz);

rt_err_t debe_set_clk(int clk);
rt_err_t defe_set_clk(int clk);
rt_err_t tcon_set_clk(enum tcon_clk clk);
int debe_get_clk(void);
int defe_get_clk(void);
int tcon_get_clk(void);
#endif