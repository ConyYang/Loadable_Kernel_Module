#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = { .read = device_read,
        .write = device_write,
        .open = device_open,
        .release = device_release
};

char msg_buf[20], ctr = 0; // buffer to store message from user space
char msg1[7]="CE3003"; // message to be send to the user space
int errorno, msg1len =6;

static int device_open(struct inode *inode, struct file *file)
{ printk(KERN_ALERT "Someone opened modIO\n");
    return 0; }

static int device_release(struct inode *inode, struct file *file)
{ printk(KERN_ALERT "Someone closed modIO\n");
    return 0; }

static ssize_t device_read(struct file *filp, char *buf, size_t len,
                           loff_t *off)
{ printk(KERN_ALERT "reading the device 101\n");
    if (ctr==0)
        return 0; /* nothing to return to userland*/
    errorno = copy_to_user(buf, msg1, msg1len); /* write to user space */
    ctr=0;
    return msg1len; /* return size of message */
}

static ssize_t device_write(struct file *filp, const char *buf, size_t len,
                            loff_t *off)
{ printk(KERN_ALERT "writing to device 101\n");
    if (ctr>0)
        return 0; /* no space to accept another char */
    errorno = copy_from_user(msg_buf, buf, 12); /* retrieve value from user space*/
    ctr=1;
    return 1; /* 1 message read from buffer*/
}
char msg, count=0;

static int __init ce3003_init(void)
{ printk(KERN_ALERT "Loading ce3003\n");
    register_chrdev(105, "ce3003", &fops);
    return(0);
}
static void __exit ce3003_cleanup(void)
{
    unregister_chrdev(105,"ce3003");
    printk(KERN_ALERT "Unloading ce3003\n");
}
module_init(ce3003_init);
module_exit(ce3003_cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CE3003");
MODULE_DESCRIPTION("Simple I/O module");
MODULE_VERSION("V1"); #include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = { .read = device_read,
        .write = device_write,
        .open = device_open,
        .release = device_release
};

char msg_buf[20], ctr = 0; // buffer to store message from user space
char msg1[7]="CE3003"; // message to be send to the user space
int errorno, msg1len =6;

static int device_open(struct inode *inode, struct file *file)
{ printk(KERN_ALERT "Someone opened modIO\n");
    return 0; }

static int device_release(struct inode *inode, struct file *file)
{ printk(KERN_ALERT "Someone closed modIO\n");
    return 0; }

static ssize_t device_read(struct file *filp, char *buf, size_t len,
                           loff_t *off)
{ printk(KERN_ALERT "reading the device 101\n");
    if (ctr==0)
        return 0; /* nothing to return to userland*/
    errorno = copy_to_user(buf, msg1, msg1len); /* write to user space */
    ctr=0;
    return msg1len; /* return size of message */
}

static ssize_t device_write(struct file *filp, const char *buf, size_t len,
                            loff_t *off)
{ printk(KERN_ALERT "writing to device 101\n");
    if (ctr>0)
        return 0; /* no space to accept another char */
    errorno = copy_from_user(msg_buf, buf, 12); /* retrieve value from user space*/
    ctr=1;
    return 1; /* 1 message read from buffer*/
}
char msg, count=0;

static int __init ce3003_init(void)
{ printk(KERN_ALERT "Loading ce3003\n");
    register_chrdev(105, "ce3003", &fops);
    return(0);
}

static void __exit ce3003_cleanup(void)
{
    unregister_chrdev(105,"ce3003");
    printk(KERN_ALERT "Unloading ce3003\n");
}

module_init(ce3003_init);
module_exit(ce3003_cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CE3003");
MODULE_DESCRIPTION("Simple I/O module");
MODULE_VERSION("V1");