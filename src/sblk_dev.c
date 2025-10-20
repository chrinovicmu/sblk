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
#include <include/utils.h>
#include <include/sblk_dev.h> 

static int my_blk_open(struct block_device *bdev, fmode_t mode)
{
    return 0; 
}

static int my_blk_release(struct gendisk *gd, fmode_t mode)
{


    return 0; 
}

struct block_device_operations my_blk_ops = {
    .owner = THIS_MODULE, 
    .open = my_blk_open, 
    .release = my_blk_release 
}; 




static blk_status_t sblk_request(struct blk_mq_hw_ctx *hctx, const struct blk_mq_queue_data * bd)
{
    struct request *rq = bd->rq; 
    struct sblk_dev *dev = q->

}
static struct blk_mq_ops sblk_queue_ops = {
    .queue_rq = sblk_request, 
}; 

int create_block_device(struct sblk_dev *dev)
{
     if(!dev)
    {
        PR_ERR_LOG("Invalid dev\n"); 
        return 1; 
    } 

    dev->gd = alloc_disk(SBLK_MINORS); 
    if(!dev->gd)
    {
        PR_ERR_LOG("alloc_disk failed\n");
        return -ENOMEM; 
    }

    dev->gd->major = SBLK_MAJOR; 
    dev->gd->first_minor = SBLK_MINORS; 
    dev->gd->fops = &my_blk_ops;
    dev->gd->queue = dev->queue; 
    dev->gd->private_data = dev; 

    snprintf(dev->gd->disk_name, 32, SBLK_NAME; 

    set_capacity(dev->gd, NR_SECTORS);

    /*initialize tag set */ 
    dev->tag_set.ops = &sblk_queue_ops; 
    dev->tag_set.nr_hw_queues = SBLK_NUM_HW_QUEUE; 
    dev->tag_set.queue_depth = SBLK_MAX_REQUEST; 
    dev->tag_set.numa_node = NUMA_NO_NODE; 
    dev->tag_set.flags = BLK_MQ_F_SHOULD_MERGE | BLK_MQ_F_BLOCKING; 
    dev->tag_set.driver_data = dev; 

    int err; 

    err = blk_alloc_tag_set(&dev->tag_set); 
    if(err)
        goto out_err; 

    dev->queue = blk_init_queue(&tag_set); 
    if(IS_ERR(dev->queue))
    {
        blk_mq_free_tag_set(&tag_set); 
        return PTR_ERR(dev-.queue); 
    }

    add_disk(dev->gd); 

    return 0; 
}

void detroy_block_device(struct my_blk_dev *dev)
{
    if(!dev)
        return; 

    if(dev->gd)
    {
        dev_gendisk(dev->gd); 
        put_disk(dev->gd); 
        dev->gd = NULL; 
    }

    if(dev->queue)
    {
        blk_cleanup_queue(dev->queue); 
        dev->queue = NULL; 
    }
}
