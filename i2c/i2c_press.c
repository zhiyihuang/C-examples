#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "i2c_api.h"
#include "MPU9255.h"

float getTemperature(int fd)
{
        u8 byte1 = read_byte(fd, DEVICE_ADDRESS, TEMPERATURE_DATA_REG);
        u8 byte2 = read_byte(fd, DEVICE_ADDRESS, TEMPERATURE_DATA_REG + 1);

        if(byte1 < 0 || byte2 < 0)
        {
                printf("error reading temperature.\n");
                exit(1);
        }

        short result = (byte1 << 8) | byte2;

        return ((float) result - 21.0) / 333.87 + 21.0;
}

static uint16_t acal[8]; // for calibration of the altimeter; read from the PROM of the altimeter.

void getPressure(int fd)
{
uint32_t rp, rt, n;
uint8_t byte0, byte1, byte2;
uint8_t data[32];
double press, temp, dt, off, sen, off2, sen2, t2, altitude;

data[0]=data[1]=data[2]=0;

	write_quick(fd, ALTIMETER_ADDR, ALTIMETER_ADC_D1|ADC_8192);
	usleep(50000);

	n = read_bytes(fd, ALTIMETER_ADDR, ALTIMETER_ADC_READ, data);
/*
        byte0 = read_byte(fd, ALTIMETER_ADDR, ALTIMETER_ADC_READ);
        byte1 = read_byte(fd, ALTIMETER_ADDR, ALTIMETER_ADC_READ + 1);
	byte2 = read_byte(fd, ALTIMETER_ADDR, ALTIMETER_ADC_READ + 2);

        rp = (uint32_t)((uint32_t) byte0 << 16 | (uint32_t) byte1 << 8 | byte2);
*/
	rp = (uint32_t)((uint32_t) data[0] << 16 | (uint32_t) data[1] << 8 | data[2]);
printf("Raw pressure is %x num of bytes is %d\n", rp, n);

	write_quick(fd, ALTIMETER_ADDR, ALTIMETER_ADC_D2|ADC_8192);
        usleep(20000);

	n = read_bytes(fd, ALTIMETER_ADDR, ALTIMETER_ADC_READ, data);
/*
        byte0 = read_byte(fd, ALTIMETER_ADDR, ALTIMETER_ADC_READ);
        byte1 = read_byte(fd, ALTIMETER_ADDR, ALTIMETER_ADC_READ + 1);
        byte2 = read_byte(fd, ALTIMETER_ADDR, ALTIMETER_ADC_READ + 2);

        rt = (uint32_t)((uint32_t) byte0 << 16 | (uint32_t) byte1 << 8 | byte2);
*/

	rt = (uint32_t)((uint32_t) data[0] << 16 | (uint32_t) data[1] << 8 | data[2]);
printf("Raw temperature is %x num of bytes is %d\n", rt, n);

	dt = (float)rt - acal[5]*256.0;
	off = acal[2]*1024.0*128.0 + dt*acal[4]/64.0;
	sen = acal[1]*1024.0*64.0 + dt*acal[3]/128.0;
	temp = (2000 +(dt*acal[6])/(1024.0*1024.0*8.0))/100.0;
	if(temp > 20) {
	    t2 = 5*dt*dt/(1024.0*1024.0*1024.0*256.0);
	    off2 = 0.0;
	    sen2 = 0.0;
	}
	if(temp < 20) {
	    t2 = 3*dt*dt/(1024.0*1024.0*1024.0*8.0);
	    off2 = 61*(100*temp-2000)*(100*temp-2000)/16;
	    sen2 = 29*(100*temp-2000)*(100*temp-2000)/16;
	}
	if(temp < -15) {
	    off2 = off2 + 17*(100*temp+1500)*(100*temp+1500);
	    sen2 = sen2 + 9*(100*temp+1500)*(100*temp+1500);
	}
	temp = temp - t2/100;
	off = off - off2;
	sen = sen - sen2;

	press = (((rp*sen)/(1024.0*1024.0*2.0) - off)/(1024.0*32.0))/100.0;
	altitude = 145366.45*(1.0 - pow((press/1013.25), 0.190284));

        printf("The pressure is %f; the temperature is %f; and the altitude is %f\n", press, temp, altitude);
}

void reset(int fd)
{
	write_quick(fd, ALTIMETER_ADDR, ALTIMETER_RESET);
}


uint8_t checkcrc()
{
uint32_t r;
uint8_t b;
int i;

	acal[0] = acal[0] & 0x0FFF;
	acal[7] = 0;
	r = 0;
	for(i=0; i<16; i++){
	    if(i%2==1) r ^= (uint16_t) (acal[i>>1] & 0x00FF);
	    else r ^= (uint16_t) (acal[i>>1] >> 8);
	    for(b=8; b>0; b--) {
		if(r & 0x8000) r = (r << 1) ^ 0x3000;
		else r = r << 1;
	    }
	}
	r = (r >> 12) & 0x000F;
	return r^0x00;
}

void readCalData(int fd)
{
int i, raddr, n;
uint8_t oldcrc, crc;
uint16_t data;

	raddr = 0xA0;
	for(i=0; i<7; i++){
	    data = 0;
	    data = read_word(fd, ALTIMETER_ADDR, raddr);
	    acal[i] = ((data & 0xFF) << 8) | ((data & 0xFF00) >> 8);
	    raddr += 2;
	}
printf("The calibration data is: ");
for(i=0; i<7; i++) printf("%x ", acal[i]);
printf("\n");
oldcrc = acal[0] >> 12;
crc = checkcrc();
printf("The original CRC is %x while the calculated CRC is %x\n", oldcrc, crc);
}


int main(int argc, char** argv)
{
	int fd, serversocket, clientsocket, n;
	float temperature;

	fd = open_i2c();
	reset(fd);
	readCalData(fd);

	getPressure(fd);
	temperature = getTemperature(fd);

	printf("The temperature is %f degrees.\n", temperature);
}

