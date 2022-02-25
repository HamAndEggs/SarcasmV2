#include <iostream>
#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/bootrom.h"

// Use tinyUSB header to define USB descriptors
extern "C"
{
    #include "pio_usb.h"
    #include "device/usbd.h"
    #include "class/hid/hid_device.h"
}

static usb_device_t *usb_device = NULL;

void core1_main()
{
    sleep_ms(10);

    // To run USB SOF interrupt in core1, create alarm pool in core1.
    static pio_usb_configuration_t config = PIO_USB_DEFAULT_CONFIG;
    config.alarm_pool = (void*)alarm_pool_create(2, 1);
    usb_device = pio_usb_host_init(&config);

    //// Call pio_usb_host_add_port to use multi port
    // const uint8_t pin_dp2 = 8;
    // pio_usb_host_add_port(pin_dp2);

    while (true)
    {
        pio_usb_host_task();
    }
}

int main()
{
    // default 125MHz is not appropriate. Sysclock should be multiple of 12MHz.
    set_sys_clock_khz(120000, true);

    // Initialize chosen serial port
    stdio_init_all();

    sleep_ms(10);

    multicore_reset_core1();

    // all USB task run in core1
    multicore_launch_core1(core1_main);

    // wait for USB thread.
    while( usb_device == NULL )
    {
        sleep_ms(10);
    }

    // Loop forever
    while (true)
    {
        for (int dev_idx = 0; dev_idx < PIO_USB_DEVICE_CNT; dev_idx++)
        {
            usb_device_t *device = &usb_device[dev_idx];
            if( device->connected )
            {
                // Print received packet to EPs
                for (int ep_idx = 0; ep_idx < PIO_USB_DEV_EP_CNT; ep_idx++)
                {
                    endpoint_t *ep = pio_usb_get_endpoint(device, ep_idx);
                    if( ep )
                    {
/*                        uint8_t temp[64];
                        int len = pio_usb_get_in_data(ep, temp, sizeof(temp));
                        if (len > 0)
                        {
                            printf("%04x:%04x EP 0x%02x:\t", device->vid, device->pid,
                            ep->ep_num);
                            for (int i = 0; i < len; i++)
                            {
                                printf("%02x ", temp[i]);
                            }
                            printf("\n");
                        }*/
                        ep
                    }
                }
            }
        }
        sleep_us(10);
    }

    return 0;
}
