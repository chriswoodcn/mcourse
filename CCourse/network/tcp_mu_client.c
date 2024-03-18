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
  char buf[BUFFER_SIZE];
  struct sockaddr_in servaddr;

  if (argc < 3) {
    printf("Usage : %s <ip> <port>\n", argv[0]);
    exit(-1);
  }

  /*创建Socket*/
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(-1);
  }

  /*设置sockaddr_in 结构体中相关参数*/
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(atoi(argv[2]));
  servaddr.sin_addr.s_addr = inet_addr(argv[1]);

  /*调用connect()函数向服务器端建立TCP连接*/
  if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
    perror("connect");
    exit(-1);
  }

  /*循环从键盘输入*/
  while (1) {
    printf("input > ");
    fgets(buf, sizeof(buf), stdin);
    if (strcmp(buf, "quit\n") == 0)
      break; /*若输入input，跳出循环*/

    send(sockfd, buf, sizeof(buf), 0); /*发送消息给服务器端*/

    bzero(buf, sizeof(buf));

    recv(sockfd, buf, sizeof(buf), 0); /*接收服务器端发回的消息*/
    printf("recv from server : %s\n", buf);
  }
  printf("client exit\n");
  close(sockfd); /*关闭TCP连接*/
  exit(0);
}
