#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/cdev.h>

MODULE_LICENSE("GPL");
// GPL license used by linux kernel developer..module stacking..some driver might not compatible with non GPL
MODULE_AUTHOR("DU");

	/*things need for char device
	* 1.device numbe:dev no. is used by linux to identify dev.
	* 2.cdev structure: kernel representation char device.
	* 2.1file operation:operations that can be done on device.
	*  /usr/src/<your version Linux kernel>/include/linux/fs.h
	*/

static dev_t devnum;    //device no. //static allocation of dev numb-register_chardev
static struct cdev _cdev;//represents char device.always after dev no. 

static int sample_open(struct inode *inode, struct file *filep)
{
	printk("Sample open function\n");
	return 0;
}

static int sample_close(struct inode *inode,struct file *filep)
{
	printk("sample close function \n");
	return 0;
}
struct file_operations fops= { //points to function
	.open = sample_open,
	.release = sample_close,	
};//Designated initialization of structture


static int __init sample_init(void){
	int ret;
	devnum =MKDEV(42,0);//used to create dev no.using major&minor no.
	ret=register_chrdev_region(devnum,1,"samlpe_dev");//request kernel..and if we use 3 instead of i.e. 3device acan access by 1 cdev struct

	if(ret){  //non zero meansnon successfull (error code in kernel)

		printk("kernel denied request for device number\n");
			// might be same device number is used other device
		return ret;
	}
	cdev_init(&_cdev,&fops);//Binds cdev with file operations
 
	ret = cdev_add(&_cdev,devnum,1);//after this device is Live 
	if(ret)
	{
		printk("unable to cdev to kernel\n");
		unregister_chrdev_region(devnum, 1);
		return ret;
	}

	printk("Done init\n");
	return 0;
}

static void __exit sample_exit(void){
	cdev_del(&_cdev);
	unregister_chrdev_region(devnum,1);
	printk("Good Byee\n");

}

module_init(sample_init);// on module init function to be executed is sample_init 
module_exit(sample_exit);
