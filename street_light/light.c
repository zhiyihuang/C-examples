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

	fd = open_i2c();
	powerUp(fd);
	setup_io();
	setgpiofunc(8, 1);

while(1)
{	
	light = getLight(fd);

	printf("The reading from the light sensor is %u.\n", light);
	if(light < 1000) write_to_gpio(1, 8);
	if(light >= 20000) write_to_gpio(0, 8);
	usleep(1000000);
}
}

