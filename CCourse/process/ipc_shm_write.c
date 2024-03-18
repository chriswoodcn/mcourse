#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  // 创建共享内存
  key_t key;
  key = ftok("./app", 'b');
  if (key < 0) {
    perror("ftok error");
    return -1;
  }
  printf("key_t = %#x\n", key);
  /// 创建
  int shmid = shmget(key, 128, IPC_CREAT | IPC_EXCL | 0666);
  if (shmid < 0) {
    if (errno == EEXIST)
      // 若存在 直接读取
      shmid = shmget(key, 128, 0666);
    else {
      perror("shmget error");
      return -1;
    }
  }
  printf("shmid = %d\n", shmid);
  char *p = NULL;
  /// 映射
  p = shmat(shmid, NULL, 0);
  if (p == (char *)-1) {
    perror("shmat error");
    return -1;
  }

  while (1) {
    if (strncmp(p, "quit", 4) == 0) {
      break;
    }
    printf("p = %s \n", p);
  }

  int shmdt_r = shmdt(p);
  if (shmdt_r == -1) {
    perror("shmdt error");
    return -1;
  }
  return 0;
}