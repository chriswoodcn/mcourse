#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main() {
  // 生产KEY值
  key_t key;
  key = ftok("./app", 'a');
  if (key < 0) {
    perror("ftok error");
    return -1;
  }
  printf("%#x\n", key);
  /// 创建共享内存
  int shmid = shmget(key, 128, IPC_CREAT | IPC_EXCL | 0666);
  if (shmid < 0) {
    if (errno == EEXIST)
      shmid = shmget(key, 128, 0666);
    else {
      perror("shmget error");
      return -1;
    }
  }
  printf("shmid = %d\n", shmid);
  char *p = NULL;
  /// 映射
  p = (char *)shmat(shmid, NULL, 0);
  if (p == (char *)-1) {
    perror("shmat error");
    return -1;
  }
  // sleep(1);
  fgets(p, 32, stdin);
  printf("%s \n", p);
  int shmdt_r = shmdt(p);
  if (shmdt_r == -1) {
    perror("shmdt error");
    return -1;
  }
  shmctl(shmid, IPC_RMID, NULL);

  system("ipcs -m");
  return 0;
}