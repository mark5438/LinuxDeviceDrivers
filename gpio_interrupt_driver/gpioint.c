#define MODULE
#define LINUX
#define __KERNEL__

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

#define GPIO_IN 17

static irqreturn_t interrupt_handler(int irq, void *ident)
{
    printk(KERN_INFO " Interrupt triggered");
    return IRQ_HANDLED;
}

static int __init module_start(void)
{
    int err;

    if ((err = gpio_request(GPIO_IN, THIS_MODULE->name)) != 0)
    {
        return err;
    }

    if ((err = gpio_direction_input(GPIO_IN)) != 0)
    {
        gpio_free(GPIO_IN);
        return err;
    }

    if ((err = request_irq(gpio_to_irq(GPIO_IN), interrupt_handler, IRQF_SHARED | IRQF_TRIGGER_FALLING, THIS_MODULE->name, THIS_MODULE->name)) != 0)
    {
        printk(KERN_INFO "Error %d: could not request irq: %d\n", err, GPIO_IN);
        gpio_free(GPIO_IN);
        return err;
    }

    printk(KERN_INFO " Loaded interrupt module\n");
    printk(KERN_INFO " Waiting for interrupts...\n");

    return 0;
}

static void __exit module_end(void)
{
    gpio_free(GPIO_IN);
    free_irq(gpio_to_irq(GPIO_IN), THIS_MODULE->name);
    printk(KERN_INFO " Unloaded interrupt module\n");
}

module_init(module_start);
module_exit(module_end);
MODULE_LICENSE("GPL");