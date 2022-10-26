# Linux Device Drivers

I have been experimenting with writing simple linux device drivers

All drivers can be compiled and loaded to the kernel, by using these commands in the driver directory:

```
$ make
$ sudo insmod drivername.ko
```

## Here is a list of the drivers

### hello

A simple hello world kernel module. Writes a kernel message when inserted into the kernel, and another one when removed

### char_module

Registers a char device driver as /dev/rytter. This file can be opened, closed, read from and written to. The readings and writings doesn't do anything except printing kernel messages.

### gpio_interrupt_driver

Prints a kernelmessage when a certain gpio pin goes from high to low