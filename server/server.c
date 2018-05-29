#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include "server_api.h"

int main(int argc, char *argv[])
{
int port_num, sockfd, connfd;

  if(argc != 2) {
	fprintf(stderr, "Usage: %s <port_num>\n", argv[0]);
	exit(1);
  }

  port_num = atoi(argv[1]);
  if(port_num < 2048) {
	fprintf(stderr, "Invalid port number: %d\n", port_num);
	exit(1);
  }

  sockfd = setup_server_socket(port_num);
  connfd = accept_client_connection(sockfd);
  write(connfd, "Hello Client!\n", 15);
  sleep(1);
  close(connfd);
}
