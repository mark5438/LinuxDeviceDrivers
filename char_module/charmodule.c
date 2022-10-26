#define MODULE
#define LINUX
#define __KERNEL__

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

// max Minor devices
#define MAX_DEV 2

#define DEVICE_NAME "rytter"
#define CLASS_NAME "ryt"

static int majorNumber;
static struct class *rytters_device_class = NULL;
static struct device *rytters_device = NULL;

static int device_open(struct inode *inode, struct file *file)
{
    printk("MYCHARDEV: Device open\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
    printk("MYCHARDEV: Device close\n");
    return 0;
}

static ssize_t device_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    printk("MYCHARDEV: Device read\n");
    return 0;
}

static ssize_t device_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
    printk("MYCHARDEV: Device write\n");
    return 0;
}

static const struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release};

struct mychar_device_data
{
    struct cdev cdev;
};

static int __init module_start(void)
{
    int err, i;

    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if (majorNumber < 0)
    {
        printk(KERN_ALERT "Error initializing Rytters Character Device: Couldn't obtain major number");
        return majorNumber;
    }

    rytters_device_class = class_create(THIS_MODULE, CLASS_NAME);

    if (IS_ERR(rytters_device_class))
    {
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(rytters_device_class);
    }

    rytters_device = device_create(rytters_device_class, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(rytters_device))
    {
        class_destroy(rytters_device_class);
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(rytters_device);
    }

    printk(KERN_INFO " Loaded character module\n");
    return 0;
}

static void __exit module_end(void)
{
    int i;

    for (i = 0; i < MAX_DEV; i++)
    {
        device_destroy(rytters_device_class, MKDEV(majorNumber, i));
    }

    class_unregister(rytters_device_class);
    class_destroy(rytters_device_class);

    unregister_chrdev_region(MKDEV(majorNumber, 0), MINORMASK);
    printk(KERN_INFO " Unloaded character module\n");
}

module_init(module_start);
module_exit(module_end);
MODULE_LICENSE("GPL");