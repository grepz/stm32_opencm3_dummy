#ifndef __BL_USB_H
#define __BL_USB_H

typedef struct cdcacm_func_descr {
    struct usb_cdc_header_descriptor header;
    struct usb_cdc_call_management_descriptor call_mgmt;
    struct usb_cdc_acm_descriptor acm;
    struct usb_cdc_union_descriptor cdc_union;
} __attribute__((packed)) cdcacm_func_descr_t;

static inline int usb_connect(void)
{
    return gpio_get(GPIOA, GPIO9);
}

void usb_gpio_init(void);
usbd_device *usbd_create(void);

#endif /* __BL_USB_H */
