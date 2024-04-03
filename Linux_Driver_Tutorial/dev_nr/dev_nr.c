#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

/* Meta  information*/

MODULE_LICENSE("GPL ");
MODULE_AUTHOR("Lalitha 4 GNU/Linux");
MODULE_DESCRIPTION("Registers a device nr and implements some callback functions");

/**
  * @brief This function is called, when the device file is opened
*/

static int driver_open(struct inode *device_file, struct file *instance) {
	printk("dev nr open was called! \n");
	return 0;
}

/**
 * @brief This function is called, when the device file is closed
*/

static int driver_closed(struct inode *device_file, struct file * instance) {
	printk("dev nr close was called!\n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_closed
};


#define MYMAJOR 90


/**
 * @brief This function is called, when the module is loaded into the kernel
*/

static int __init ModuleInit(void){
	int retval;
	printk("Hello, Kernel!\n");
	/* register device nr. */
	retval = register_chrdev(MYMAJOR, "my dev nr", &fops);
	if(retval == 0) {
		printk("dev nr - registered Device Number Major: %d, Minor: %d\n", MYMAJOR, 0);
	}
	else if(retval > 0) {
		printk("dev nr - registered Device Number Major: %d, Minor: %d\n", retval>>20, retval&0xfffff);
	}
	else {
		printk("could not register device number! \n");
		return -1;
	}

	return 0;
}

/**
 * @brief This funciton is called, when the module is removed from the kernel
*/

static void __exit ModuleExit(void) {
	unregister_chrdev(MYMAJOR, "my dev nr");
	printk("Goodbye, Kernel!\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);

