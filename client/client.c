#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include "client_api.h"


int main(int argc, char *argv[])
{
  int sockfd, port_num;
  char buf[1000];

  if(argc != 3){
        printf("Usage: %s <ip of server> <port number> \n",argv[0]);
        exit(1);
  }

  port_num = atoi(argv[2]);
  if(port_num < 2048) {
        printf("Invalid port number: %d\n", port_num);
        exit(1);
  }

  memset(buf, '0', 1000);

  sockfd = connect_server(argv[1], port_num);

  n = read(sockfd, buf, 999);
  if(n > 0) printf("%s\n", buf);

  close(sockfd);
  return 0;
}

