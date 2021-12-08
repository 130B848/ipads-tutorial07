#include <linux/module.h>  /* Needed by all modules */
#include <linux/kernel.h>  /* Needed for KERN_INFO */
#include <linux/init.h>    /* Needed for the macros */
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>
#include <asm/io.h>
#include "ioctl-dev.h"

static volatile unsigned long *shared_mem = NULL;

static int tutorial_dev_mmap(struct file *file, struct vm_area_struct *vma)
{
    size_t size = vma->vm_end - vma->vm_start;
    void *mem = NULL;

    if (vma->vm_pgoff != 0)
        return -EINVAL;

    if (!(mem = kmalloc(size, GFP_KERNEL)))
        return -ENOMEM;
    memset(mem, 0, size);

    if (remap_pfn_range(vma, vma->vm_start, virt_to_phys(mem) >> PAGE_SHIFT,
                size, vma->vm_page_prot)) {
        kfree(mem);
        return -EAGAIN;
    }
    shared_mem = mem;

    return 0;
}

static long tutorial_dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    switch (cmd) {
        case TUTORIAL_TEST_PRINT: {
            pr_info("%s:%d shared_mem = %px, %lx\n", __func__, __LINE__,
                    shared_mem, shared_mem ? shared_mem[0] : 0xdead);
            break;
        }
        default:
            break;
    }
    return 0;
}

static int tutorial_dev_open(struct inode *inode, struct file *filep) {
    pr_info("%s:%d hello shared_mem: %px\n", __func__, __LINE__, shared_mem);
    return 0;  
}

static int tutorial_dev_release(struct inode *inode, struct file *filep) { 
    pr_info("%s:%d bye shared_mem: %px\n", __func__, __LINE__, shared_mem);
    shared_mem = NULL;
    return 0; 
}

static const struct file_operations tutorial_fops = {
    .owner              = THIS_MODULE,
    .read               = NULL,
    .write              = NULL,
    .mmap               = tutorial_dev_mmap,
    .unlocked_ioctl     = tutorial_dev_ioctl,
    .open               = tutorial_dev_open,
    .release            = tutorial_dev_release,
};

static struct miscdevice tutorial_dev = {
    .minor              = MISC_DYNAMIC_MINOR,
    .name               = "tutorial_dev",
    .fops               = &tutorial_fops,
};

static int __init ioctl_dev_init(void)
{
    int err;

    err = misc_register(&tutorial_dev);
    if (err != 0) {
        pr_err("%s:%d ERROR: %d\n", __func__, __LINE__, err);
        return err;
    }
    pr_info("%s:%d tutorial_dev installed\n", __func__, __LINE__);
    return 0;
}

static void __exit ioctl_dev_exit(void)
{
    misc_deregister(&tutorial_dev);
}

module_init(ioctl_dev_init);
module_exit(ioctl_dev_exit);

MODULE_LICENSE("GPL");
