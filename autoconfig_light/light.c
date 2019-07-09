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
	int fd;
	unsigned short light;
	int threshold_1, threshold_2, samples[100];
	int i, j, mean[2], sum;

	fd = open_i2c();
	powerUp(fd);
	setup_io();
	setgpiofunc(8, 1);
    for(j=0;j<2;j++){
	printf("Press enter when you are ready (%d):", j+1);
	getchar();
	for(i=0;i<100;i++){
	    samples[i]=getLight(fd);
	    usleep(100000);
	}
	sum = 0;
	for(i=0;i<100;i++)sum = sum + samples[i];
	mean[j] = sum / 100;
	printf("The mean (%d) is %d\n", j+1, mean[j]);
    }

	printf("The means are %d %d\n", mean[0], mean[1]);
	threshold_1 = mean[0] + 200;
	threshold_2 = mean[1] - 200;

while(1)
{	
	light = getLight(fd);

	printf("The reading from the light sensor is %u.\n", light);
	if(light < threshold_1) write_to_gpio(1, 8);
	if(light >= threshold_2) write_to_gpio(0, 8);
	usleep(1000000);
}
}

