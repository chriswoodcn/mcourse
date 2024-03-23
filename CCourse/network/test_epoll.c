#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define EVENT_SIZE 10
#define BUF_SIZE 128

int main(int argc, char argv[]) {
  int serverfd;
  struct sockaddr_in servaddr, cliaddr;
  socklen_t peerlen = sizeof(cliaddr);

  if (argc < 3) {
    printf("Usage : %s <ip> <port>\n", argv[0]);
    exit(-1);
  }

  /*建立Socket连接*/
  if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(-1);
  }
  printf("serverfd = %d\n", serverfd);

  /*设置sockaddr_in 结构体中相关参数*/
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(atoi(argv[2]));
  servaddr.sin_addr.s_addr = inet_addr(argv[1]);

  /*绑定函数bind()*/
  if (bind(serverfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    perror("bind");
    exit(-1);
  }
  printf("bind success!\n");

  /*调用listen()函数，设置监听模式*/
  if (listen(serverfd, 10) == -1) {
    perror("listen");
    exit(-1);
  }
  printf("Listening....\n");

  struct epoll_event event;
  struct epoll_event events[EVENT_SIZE];
  int epfd, epct, i, readSize;
  epfd = epoll_create(1);

  event.data.fd = serverfd;
  event.events = EPOLLIN | EPOLLET;
  epoll_ctl(epfd, EPOLL_CTL_ADD, serverfd, &event);

  char buf[BUF_SIZE] = {0};
  while (1) {
    epct = epoll_wait(epfd, events, EVENT_SIZE, -1); // 阻塞等待事件到来
    for (i = 0; i < epct; i++) {
      if (events[i].data.fd == serverfd) {
        int acceptfd = accept(serverfd, (struct sockaddr *)&cliaddr, &peerlen);
        event.data.fd = serverfd;
        event.events = EPOLLIN | EPOLLET;
        epoll_ctl(epfd, EPOLL_CTL_ADD, acceptfd, &event);
      } else {
        memset(buf, 0, BUF_SIZE);
        readSize = read(events[i].data.fd, buf, BUF_SIZE);
        if (readSize <= 0) {
          epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, &event);
          close(events[i].data.fd);
          continue;
        }
        printf("fd: %d recv: %s\n", events[i].data.fd, buf);
      }
    }
  }

  close(epfd);
  close(serverfd);
  return 0;
}
