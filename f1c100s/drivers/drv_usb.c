#include <rtthread.h>
#include <rthw.h>
#include "interrupt.h"
#include "usb_phy.h"

extern void USBD_IRQHandler(int, void *);
extern void USBH_IRQHandler(int, void *);

void usb_dc_low_level_init(void)
{
    usb_phy_open_clock();
	USBC_PhyConfig();
	USBC_ConfigFIFO_Base();
	USBC_EnableDpDmPullUp();
	USBC_EnableIdPullUp();
	USBC_ForceId(USBC_ID_TYPE_DEVICE);
	USBC_ForceVbusValid( USBC_VBUS_TYPE_HIGH);

    rt_hw_interrupt_install(USB_OTG_INTERRUPT, USBD_IRQHandler, NULL, "musb_irq");
	rt_hw_interrupt_umask(USB_OTG_INTERRUPT);
}

void usb_hc_low_level_init(void)
{
    usb_phy_open_clock();
	USBC_PhyConfig();
	USBC_ConfigFIFO_Base();
	USBC_EnableDpDmPullUp();
	USBC_EnableIdPullUp();
	USBC_ForceId(USBC_ID_TYPE_HOST);
	USBC_ForceVbusValid( USBC_VBUS_TYPE_HIGH);

    rt_hw_interrupt_install(USB_OTG_INTERRUPT, USBH_IRQHandler, NULL, "musb_irq");
	rt_hw_interrupt_umask(USB_OTG_INTERRUPT);
}