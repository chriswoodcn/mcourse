#include <linux/kernel.h>
#include <linux/module.h>
/*设备号 file_operations相关头文件*/
#include <linux/fs.h>
/*cdev相关头文件*/
#include <linux/cdev.h>

/*
 * 定义设备号变量
 * dev_major : 主设备号
 * dev_minor : 次设备号
 * dev_number: 设备数量
 */
static int dev_major = 300;
static int dev_minor = 0;
static int dev_number = 1;
/*定义cdev结构体变量*/
static struct cdev cdev;
// 在 file_operations 定义之前，添加 open 和 release 接口定义
int (*open)(struct inode *, struct file *);
int (*release)(struct inode *, struct file *);
/*open接口*/
static int fs_chrdev_open(struct inode *inode, struct file *file) {
  printk(KERN_INFO "fs_chrdev: fs_chrdev_open\n");
  /*具体功能实现*/
  return 0;
}
/*release接口*/
static int fs_chrdev_release(struct inode *inode, struct file *file) {
  printk(KERN_INFO "fs_chrdev: fs_chrdev_release\n");
  /*具体功能实现*/
  return 0;
}
// 使用 copy_to_user、copy_from_user实现用户数据和内核数据的交互而不是简单的通过
// mencpy 拷贝
/*定义数据缓存区*/
#define BUFF_SIZE 128
static char dev_data[BUFF_SIZE] = {'\0'};
static int current_size = 0;
/*write接口*/
static ssize_t fs_chrdev_write(struct file *file, const char __user *buff,
                               size_t size, loff_t *loff) {
  int count = 0;

  /*检查size的正确性*/
  if (size < 0) {
    return -EINVAL;
  } else if (size > BUFF_SIZE - 1) {
    count = BUFF_SIZE;
  } else {
    count = size;
  }

  /*将用户空间数据拷贝到内核空间*/
  if (copy_from_user(dev_data, buff, count)) {
    return -EFAULT;
  }

  dev_data[count] = '\0';
  current_size = count;

  return count;
}
/*read接口*/
static ssize_t fs_chrdev_read(struct file *file, char __user *buff, size_t size,
                              loff_t *loff) {
  int count = 0;

  /*检查size的正确性*/
  if (size < 0) {
    return -EINVAL;
  } else if (size > current_size) {
    count = current_size;
  } else {
    count = size;
  }

  /*将内核数据拷贝到用户空间*/
  if (copy_to_user(buff, dev_data, count)) {
    return -EFAULT;
  }

  current_size = 0;

  return count;
}
/*ioctl接口*/
static long fs_chrdev_unlocked_ioctl(struct file *inode, unsigned int cmd,
                                     unsigned long arg) {
  printk(KERN_INFO "fs_chrdev: fs_chrdev_unlocked_ioctl\n");

  switch (cmd) {
  case FS_CMD1:
    printk(KERN_INFO "fs_chrdev: FS_CMD1\n");
    break;
  case FS_CMD2:
    printk(KERN_INFO "fs_chrdev: FS_CMD2\n");
    break;
  default:
    printk(KERN_INFO "fs_chrdev: invalid argment\n");
  }

  return 0;
}

/*用户操作接口集合*/
static struct file_operations fs_chrdev_fops = {
    .owner = THIS_MODULE,
    .open = fs_chrdev_open,
    .release = fs_chrdev_release,
    .read = fs_chrdev_read,
    .write = fs_chrdev_write,
    .unlocked_ioctl = fs_chrdev_unlocked_ioctl,
};

/*加载函数*/
static int __init fs_chrdev_init(void) {
  int ret = 0;
  /*构建完整设备号*/
  dev_t devno = MKDEV(dev_major, dev_minor);

  printk(KERN_INFO "fs_chrdev: module enter\n");

  /*申请设备号*/
  ret = register_chrdev_region(devno, dev_number, "fs_chrdev");
  if (ret < 0) {
    printk(KERN_ERR "fs_chrdev: register_chrdev_region failed\n");
    goto err1;
  }

  /*cdev初始及注册*/
  cdev_init(&cdev, &fs_chrdev_fops);
  cdev.owner = THIS_MODULE;
  ret = cdev_add(&cdev, devno, 1);
  if (ret < 0) {
    printk(KERN_ERR "fs_chrdev: cdev_add");
    goto err2;
  }

  return 0;

err2:
  unregister_chrdev_region(devno, dev_minor);
err1:
  return ret;
}

/*卸载函数*/
static void __exit fs_chrdev_exit(void) {
  printk(KERN_INFO "fs_chrdev: module exit\n");

  /*cdev注销*/
  cdev_del(&cdev);
  dev_t devno = MKDEV(dev_major, dev_minor);
  /*释放设备号*/
  unregister_chrdev_region(devno, dev_number);
}

module_init(fs_chrdev_init);
module_exit(fs_chrdev_exit);

MODULE_LICENSE("GPL");