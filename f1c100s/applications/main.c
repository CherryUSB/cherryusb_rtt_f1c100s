/*
 * COPYRIGHT (C) 2012-2021, Shanghai Real-Thread Technology Co., Ltd
 * All rights reserved.
 * Change Logs
 * Date           Author       Notes
 * 2021-8-26      RT-Thread    the first version
 */

#include <rtthread.h>

int main(int argc, char **argv)
{
    rt_kprintf("Hello CherryUSB\n");
    return 0;
}
#ifdef PKG_CHERRYUSB_DEVICE
int usbd_cdc_start(void)
{
    extern void cdc_acm_init(void);

    cdc_acm_init();
    return 0;
}
MSH_CMD_EXPORT(usbd_cdc_start, usb device cdc demo);

int usbd_cdc_send(void)
{
    extern void cdc_acm_data_send_with_dtr_test(void);

    cdc_acm_data_send_with_dtr_test();
    return 0;
}
MSH_CMD_EXPORT(usbd_cdc_send, usb device cdc demo);
#endif
#ifdef PKG_CHERRYUSB_HOST
int usbh_start(void)
{
    extern int usbh_initialize(void);
    void usbh_class_test(void);

    usbh_initialize();
    usbh_class_test();
    return 0;
}
MSH_CMD_EXPORT(usbh_start, usb host demo);
#endif