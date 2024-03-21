#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void select_sockfd(int sockfd);

int main() {
  int sockfd, acceptfd;
  struct sockaddr_in servaddr, cliaddr;
  socklen_t peerlen;
  char buf[BUFFER_SIZE];

  if (argc < 3) {
    printf("Usage : %s <ip> <port>\n", argv[0]);
    exit(-1);
  }

  /*建立Socket连接*/
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(-1);
  }
  printf("sockfd = %d\n", sockfd);

  /*设置sockaddr_in 结构体中相关参数*/
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(atoi(argv[2]));
  servaddr.sin_addr.s_addr = inet_addr(argv[1]);

  /*绑定函数bind()*/
  if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    perror("bind error");
    exit(-1);
  }
  printf("bind success!\n");

  /*调用listen()函数，设置监听模式*/
  if (listen(sockfd, 10) == -1) {
    perror("listen error");
    exit(-1);
  }
  printf("Listening....\n");

  select_sockfd(sockfd);

  // peerlen = sizeof(cliaddr);
  // while (1) {
  //   if ((acceptfd = accept(sockfd, (struct sockaddr *)&cliaddr,
  //   &peerlen)) <
  //       0) {
  //     perror("accept");
  //     exit(-1);
  //   }

  //   /*调用recv()函数接收客户端发送的数据*/
  //   memset(buf, 0, sizeof(buf));
  //   if (recv(acceptfd, buf, BUFFER_SIZE, 0) == -1) {
  //     perror("recv");
  //     exit(-1);
  //   }
  //   printf("Received a message: %s\n", buf);
  //   strcpy(buf, "Welcome to server");
  //   send(acceptfd, buf, BUFFER_SIZE, 0);
  //   close(acceptfd);
  // }

  close(sockfd);
  exit(0);
}
void select_sockfd(int sockfd) {
  fd_set readfds, tempfds;
  FD_ZERO(&readfds);
  FD_ZERO(&tempfds);
  struct timeval tv = {
      .tv_sec = 10,
      .tv_usec = 0,
  };

  FD_SET(0, &fs);
  FD_SET(sockfd, &fs);

  int maxfd = sockfd;
  int val;
  char buf[128] = {0};
  while (1) {
    tempfds = readfds;
    val = select(maxfd + 1, &tempfds, NULL, NULL, NULL);
    if (val < 0) {
      perror("select error");
      exit(-1);
    }
    for (int i = 0; i < maxfd + 1; i++) {
      if (i == 0 && FD_ISSET(0, &tempfds)) {
        fgets(buf, sizeof(buf), stdin);
        buf[strlen(buf) - 1] = '\0';
        printf("this is keyboard event\n");
        printf("buf = %s\n", buf);
      }
      if (i == sockfd && FD_ISSET(sockfd, &tempfds)) {
        printf("this is sockfd event\n");
        // accept阻塞等待客户端连接请求，如果有客户端连接返回一个用于通信的套接字文件描述符
        peerlen = sizeof(cliaddr);
        acceptfd = accept(sockfd, (struct sockaddr *)&cliaddr, &peerlen);
        printf("client_ip: %d client_port %d\n",
               inet_ntoa(cliaddr.sin_addr.s_addr), ntohs(cliaddr.sin_port));
      }
    }
  }