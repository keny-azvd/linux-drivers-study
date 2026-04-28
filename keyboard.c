#include <linux/module.h>
#include <linux/ioport.h>
#include <linux/io.h>

// README
// In Linux kernel programming, request_region() is a C function used to register a range of I/O ports for a device driver, 
// ensuring exclusive access to those resources. It prevents multiple drivers from using the same I/O memory region, which 
// could cause system instability. The function requires the start address, length, and owner name. 
// ex : !request_region(MY_PORT_BASE, MY_PORT_SIZE, "driver_name")

#define KBD_DATA_REG    0x60
#define KBD_STATUS_REG  0x64

static int __init keyboard_init(void) {
   
    if (!request_region(KBD_DATA_REG, 1, "keyboard_data")) { 
        pr_err("Erro ao reservar porta 0x60\n");
        return -EBUSY;
    }
    if (!request_region(KBD_STATUS_REG, 1, "keyboard_data")) {
        release_region(KBD_DATA_REG, 1);
        return -EBUSY;
    }

    pr_info("Keyboard driver PS/2 loaded!\n");
    
  
    unsigned char status = inb(KBD_STATUS_REG);
    pr_info("Status atual do controlador: 0x%x\n", status);

    return 0;
}

static void __exit keyboard_exit(void) {

    release_region(KBD_DATA_REG, 1);
    release_region(KBD_STATUS_REG, 1);
    pr_info("Driver removed!");

}

module_init(keyboard_init);
module_exit(keyboard_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anil Kumar Pugalia <email@sarika-pugs.com>");
MODULE_DESCRIPTION("Our First Character Driver");