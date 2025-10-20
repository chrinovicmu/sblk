#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/cred.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/blkdev.h> 
#include <linux/genhd.h>
#include <linux/spinlock.h> 
#include <include/sblk_dev.h> 
#include <include/utils.h> 

static int _init block_init(void)
{
    struct my_blk_dev dev; 

    status = register_blkdev(MY_BLOCK_MAJOR, MY_BLOKDEV_NAME); 
    if(status < 0)
    {
        pr_info("Unable to register mybdev block device");
        return -EBUSY; 
    }

    status = create_block_device(&dev); 
    if(status != 0)
    {
        pr_info("failed to create block device"); 
        return -1; 
    }
}

static void __exit block_exit(void)
{
    delete_block_device(&dev); 

}
