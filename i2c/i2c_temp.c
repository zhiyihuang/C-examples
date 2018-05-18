#include <stdio.h>
#include <stdlib.h>

#include "i2c_api.h"
#include "MPU9255.h"
#include "server_api.h"

float getTemperature(int fd)
{
return 0.0;
}

int main(int argc, char** argv)
{
	int fd, serversocket, clientsocket, n;
	float temperature;

	fd = open_i2c();
	
	temperature = getTemperature(fd);

	printf("The temperature is %f degrees.\n", temperature);
}

