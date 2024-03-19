#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 128

int main(int argc, char *argv[]) {
  int sockfd;
  char buf[BUFFER_SIZE] = "Hello Server";
  struct sockaddr_in servaddr;

  if (argc < 3) {
    printf("Usage : %s <ip> <port>\n", argv[0]);
    exit(-1);
  }

  /*创建Socket*/
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("socket");
    exit(-1);
  }

  /*设置sockaddr_in 结构体中相关参数*/
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(atoi(argv[2]));
  servaddr.sin_addr.s_addr = inet_addr(argv[1]);

  /*发送消息给服务器端*/
  sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&servaddr,
         sizeof(servaddr));
  if (recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL) < 0) {
    perror("recvfrom");
    exit(-1);
  }
  printf("recv from server : %s\n", buf);
  close(sockfd);
  exit(0);
}
