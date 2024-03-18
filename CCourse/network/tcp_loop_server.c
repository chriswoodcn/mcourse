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
  int listenfd, connfd, n;
  struct sockaddr_in servaddr, cliaddr;
  socklen_t peerlen;
  char buf[BUFFER_SIZE];

  if (argc < 3) {
    printf("Usage : %s <ip> <port>\n", argv[0]);
    exit(-1);
  }

  /*建立Socket连接*/
  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(-1);
  }

  /*设置sockaddr_in 结构体中相关参数*/
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(atoi(argv[2]));
  servaddr.sin_addr.s_addr = inet_addr(argv[1]);

  /*绑定函数bind()*/
  if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    perror("bind");
    exit(-1);
  }

  /*调用listen()函数，设置监听模式*/
  if (listen(listenfd, 10) == -1) {
    perror("listen");
    exit(1);
  }

  /*调用accept()函数，等待客户端的连接*/
  peerlen = sizeof(cliaddr);
  while (1) {
    if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &peerlen)) <
        0) {
      perror("accept");
      exit(-1);
    }
    printf("connection from [%s:%d]\n", inet_ntoa(cliaddr.sin_addr),
           ntohs(cliaddr.sin_port));

    /*调用recv()函数接收客户端发送的数据*/
    while ((n = recv(connfd, buf, BUFFER_SIZE, 0)) > 0) {
      printf("echo : %s", buf);
      send(connfd, buf, n, 0);
    }
    printf("client is closed\n");
    close(connfd);
  }

  close(listenfd);
  exit(0);
}
