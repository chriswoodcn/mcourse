#include <arpa/inet.h>
#include <dirent.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 128

void printUsage() {
  printf("usage:\n");
  printf("   list           list remote server files\n");
  printf("   put filename   upload file to remote server\n");
  printf("   get filename   download file from remote server\n");
  printf("   quit           close client\n");
}
void client_list(int sockfd);
void client_put(int sockfd, char buf[]);
void client_get(int sockfd);
void client_quit(int sockfd);

int main(int argc, char *argv[]) {
  int sockfd;
  char buf[BUFFER_SIZE] = {0};
  struct sockaddr_in servaddr;

  if (argc < 3) {
    printf("Usage : %s <ip> <port>\n", argv[0]);
    exit(-1);
  }

  /*创建Socket*/
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket error");
    exit(-1);
  }

  /*设置sockaddr_in 结构体中相关参数*/
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(atoi(argv[2]));
  servaddr.sin_addr.s_addr = inet_addr(argv[1]);

  /*调用connect()函数向服务器端建立TCP连接*/
  if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
    perror("connect error");
    exit(-1);
  }

  while (1) {
    printUsage();
    fgets(buf, sizeof(buf), stdin);
    if (buf[strlen(buf) - 1] == '\n') {
      buf[strlen(buf) - 1] = '\0';
    }
    switch (buf[0]) {
    case 'l' | 'L':
      printf("list command ======\n");
      client_list(sockfd);
      break;
    case 'p' | 'P':
      printf("put command ======\n");
      client_put(sockfd, buf + 4);
      break;
    case 'g' | 'G':
      printf("get command ======\n");
      client_get(sockfd);
      break;
    case 'q' | 'Q':
      printf("quit command ======\n");
      client_quit(sockfd);
      break;
    default:
      printf("Unknow command\n");
      break;
    }
  }
  // send(sockfd, buf, sizeof(buf), 0);
  // if (recv(sockfd, buf, sizeof(buf), 0) == -1) {
  //   perror("recv");
  //   exit(-1);
  // }
  // printf("recv from server : %s\n", buf);
  // close(sockfd);
}
void client_list(int sockfd) {
  char buf[BUFFER_SIZE] = {0};
  sprintf(buf, "%s", "L");
  send(sockfd, buf, sizeof(buf), 0);
  int i = 0;
  while (1) {
    if (recv(sockfd, buf, sizeof(buf), 0) == -1) {
      perror("list recv error");
      exit(-1);
    }
    if (strncmp(buf, "QUIT", 4) == 0) {
      break;
    }
    printf("%d.%s \n", ++i, buf);
  }
  printf("list command ====== OK\n");
}
void client_put(int sockfd, char *name) {
  char buf[BUFFER_SIZE] = {0};
  sprintf(buf, "P %s", name);
  send(sockfd, buf, sizeof(buf), 0);
  int fd = open(name, O_RDONLY);
  int readSize;
  while (1) {
    readSize = read(fd, buf, sizeof(buf));
    if (readSize == 0)
      break;
    send(sockfd, buf, readSize, 0);
    usleep(1000); //防止粘包
  }
  char finishFlag[10] = {0};
  sprintf(finishFlag, "%s", "FINISH");
  send(sockfd, finishFlag, sizeof(buf), 0);
  printf("put %s command ====== OK\n", name);
}
void client_get(int sockfd) {}
void client_quit(int sockfd) {
  close(sockfd);
  printf("quit command ====== OK\n");
  exit(0);
}
