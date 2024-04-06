#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/**
 * open 设备文件的时候可能出现的错误
 * 1）No such file or directory：没有文件或目录
 * 错误原因：打开的设备文件不存在，检查设备文件是否存在，文件名是否正确
 * 2）Permission denied：权限问题
 * 错误原因：设备打开需要超级用户权限，修改设备文件权限或使用 sudo 执行应用程序
 * 3）No such device or address：没有设备或地址
 * 错误原因：驱动未加载或创建设备文件的时候设备号与驱动中设备号不一致
 */
int main(int argc, const char *argv[]) {
  int fd;

  fd = open("/dev/fs_chrdev", O_RDWR);
  if (fd < 0) {
    perror("open");
    return -1;
  }
  char buf[128] = "Hello World";
  while (1) {
    memset(buf, 0, sizeof(buf));
    scanf("%s", buf);
    /*写入键盘数据的数据*/
    nbyte = write(fd, buf, strlen(buf));
    if (nbyte < 0) {
      perror("write");
      return -1;
    }
    printf("write: nbyte = %d\n", nbyte);
    /*清空buf，读取数据存放在buf中*/
    memset(buf, 0, sizeof(buf));
    nbyte = read(fd, buf, sizeof(buf));
    if (nbyte < 0) {
      perror("read");
      return -1;
    }
    printf("read: nbyte = %d, buf = %s\n", nbyte, buf);
  }
  close(fd);

  return 0;
}