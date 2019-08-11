#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "i2c_api.h"
#include "Grove_DLS.h"
#include "gpio.h"

unsigned short getLight(int fd)
{
        u8 byte1 = read_byte(fd, DEVICE_ADDRESS, DATA0HIGH);
        u8 byte2 = read_byte(fd, DEVICE_ADDRESS, DATA0LOW);

        if(byte1 < 0 || byte2 < 0)
        {
                printf("error reading light sensor.\n");
                exit(1);
        }

        unsigned short result = (byte1 << 8) | byte2;

        return result;
}

void powerUp(int fd)
{
	write_byte(fd, DEVICE_ADDRESS, CONTROL, 0x3);
}


int main(int argc, char** argv)
{
	int fd, i;
	unsigned short light;
	FILE *fp;
	int lightdata[200];

	fp = fopen("light.dat", "w");
	fd = open_i2c();
	powerUp(fd);
	setup_io();
	setgpiofunc(8, 1);

for(i=0;i<200;i++)
{	
	lightdata[i] = getLight(fd);

	printf("The reading from the light sensor is %u.\n", lightdata[i]);
	usleep(1000000);
}

fwrite(lightdata, 200, sizeof(int), fp);
fclose(fp);
}

