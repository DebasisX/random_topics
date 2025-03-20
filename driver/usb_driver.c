#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/kmod.h>  // user-space programs

#define USB_VENDOR_ID  0x0781  // SanDisk USB
#define USB_PRODUCT_ID 0x5567 // remember your vendor id maybe different 

static void execute_transfer_exe(void) {
    char *argv[] = { "/home/user/transfer", NULL };  // PATH to the compiled transfer executable where you compiled the transfer.c
    char *envp[] = { NULL };  // No need for PATH as no commands are required.

    int ret = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
    if (ret < 0) {
        printk(KERN_ERR "Failed to execute transfer executable: %d\n", ret);
    } else {
        printk(KERN_INFO "Transfer executable ran successfully.\n");
    }
}

// ALERT: Device is plugged in
static int usb_probe(struct usb_interface *interface, const struct usb_device_id *id) {
    printk(KERN_INFO "Debasis USB Device Connected: Vendor=%04X, Product=%04X\n", id->idVendor, id->idProduct);

    // calling the transfer executable
    execute_transfer_exe();

    return 0; // success
}

// USB removed
static void usb_disconnect(struct usb_interface *interface) {
    printk(KERN_INFO "Debasis USB Device Removed\n");
}

// Supported USB device list
static struct usb_device_id usb_table[] = {
    { USB_DEVICE(USB_VENDOR_ID, USB_PRODUCT_ID) },
    {}  // marks termination as there are no more devices we are trying to work with
};
MODULE_DEVICE_TABLE(usb, usb_table);

// register driver
static struct usb_driver usb_driver = {
    .name = "usb_gcc_driver",
    .id_table = usb_table,
    .probe = usb_probe,
    .disconnect = usb_disconnect,
};

static int __init usb_init(void) {
    return usb_register(&usb_driver);
}

static void __exit usb_exit(void) {
    usb_deregister(&usb_driver);
}

module_init(usb_init);
module_exit(usb_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Debasis");
MODULE_DESCRIPTION("USB Driver Calling Transfer Executable");
