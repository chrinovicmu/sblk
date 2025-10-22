#ifndef SBLK_DEV_H
#define SBLK_DEV_H

#include <linux/genhd.h>       
#include <linux/blkdev.h>      
#include <linux/spinlock.h>    
#include <linux/errno.h>       
#include <linux/kernel.h>      
#include <linux/module.h>      

#define NR_SECTORS          1024
#define KERNEL_SECTOR_SIZE  512

#define SBLK_MAJOR      240 
#define SBLK_MINORS     1
#define SBLK_NAME       "sblkdev"

struct sblk_dev {
    int sec_size; 
    struct gendisk *gd;
    struct request_queue *queue;
    struct blk_mq_tag_set tag_set; 

    u8 data;
    spinlock_t lock;
};

int create_block_device(struct sblk_dev *dev);
void destroy_block_device(struct sblk_dev *dev);

#endif // SBLK_DEV_H
