#include "server_api.h"

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <strings.h>

int setup_server_socket(int portno)
{
	int sockfd;
	struct sockaddr_in serv_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		printf("error opening socket.\n");
		exit(1);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
        portno = 7102;

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portno);

	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        {
                printf("error binding socket.\n");
                exit(1);
        }

        listen(sockfd, 5);

        printf("listening on port %i...\n", portno);

	return sockfd;
}

int accept_client_connection(int sockfd)
{
	int newsockfd, clilen;
	struct sockaddr_in cli_addr;

	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	if(newsockfd < 0)
	{
		printf("error accepting connection.\n");
		exit(1);
	}

	return newsockfd;
}

