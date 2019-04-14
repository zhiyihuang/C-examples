#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "i2c_api.h"
#include "Grove_DLS.h"
#include "time.h"

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
	unsigned long t1, t2;

	fd = open_i2c();
	powerUp(fd);

	t1 = t2 = 0;
	while(1){	
	  light = getLight(fd);
	  if(light > 2000) {
	    t1 = ustime();
	    while (light > 2000) light = getLight(fd);
	    t2 = ustime();
	    printf("The reading from the light sensor is %u. and over threshold time is %lu\n", light, t2-t1);
	  }
	//usleep(50000);
	}
}

