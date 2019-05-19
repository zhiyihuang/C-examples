#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "i2c_api.h"
#include "Grove_DLS.h"
#include "time.h"

#define LT 5000

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
	unsigned long t1, t2, t;

	fd = open_i2c();
	powerUp(fd);

	t1 = t2 = 0;
	while(1){	
	  light = getLight(fd);
	  if(light > LT) {
	    t1 = ustime();
	    while (light > LT) light = getLight(fd);
	    t2 = ustime();
	    t = t2 - t1;
	    //printf("The reading from the light sensor is %u. and over threshold time is %lu\n", light, t);
	    if(t > 1000000) printf("long %lu\n", t);
	    else printf("short\n");
	  } else {
	    t1 = ustime();
	    while(light <= LT) light = getLight(fd);
	    t2 = ustime();
	    t = t2 - t1;
	    //printf("The gap time is %lu\n", t);
	    if(t > 2000000 && t <= 4000000) printf("letter finished\n");
	    else if(t > 4000000) printf("space\n");
	
	  }
	//usleep(50000);
	}
}

