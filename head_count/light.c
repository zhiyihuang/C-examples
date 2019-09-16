#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
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
int people = 0;
char ch;
struct timeval starttime, endtime;
long elapsetime;
float dp;
gettimeofday(&starttime ,0);
while(1)
{	
	light = getLight(fd);
if (light <= 3000){
	while(light <= 3000) light = getLight(fd);
	people = people + 1;
	gettimeofday(&endtime, 0);
	elapsetime = endtime.tv_sec*1000000+endtime.tv_usec - starttime.tv_sec*1000000 - starttime.tv_usec;
	elapsetime = (elapsetime / 60000000);
	dp = (float)people / elapsetime;
	printf("The count is %d and the popularity of the door is %f\n", people, dp);
}
	usleep(100000);
}

}

