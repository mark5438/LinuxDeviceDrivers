#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

static int __init module_start(void) {
    printk(KERN_INFO " Loaded hello module\n");
    return 0;
}

static void __exit module_end(void) {
    printk(KERN_INFO " Unloaded hello module\n");
}

module_init(module_start)
module_exit(module_end)

MODULE_LICENSE("GPL");