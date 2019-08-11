#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/i2c-dev.h>
//#include <i2c/smbus.h>
#include "i2c_api.h"

int open_i2c()
{
    int fd;

    fd = open("/dev/i2c-1", O_RDWR);
    if (fd < 0) {
        printf("can't open the i2c adaptor /dev/i2c-1\n");
        exit(1);
    }
    return fd;
}


int read_byte(int fd, u8 dev_addr, u8 reg_addr)
{
    if (ioctl(fd, I2C_SLAVE, dev_addr) < 0) {
        printf("No such device with address: %x\n", dev_addr);
        exit(1);
    }
    return (i2c_smbus_read_byte_data(fd, reg_addr));
}

int read_word(int fd, u8 dev_addr, u8 reg_addr)
{
    if (ioctl(fd, I2C_SLAVE, dev_addr) < 0) {
        printf("No such device with address: %x\n", dev_addr);
        exit(1);
    }
    return (i2c_smbus_read_word_data(fd, reg_addr));
}


int write_byte(int fd, u8 dev_addr, u8 reg_addr, u8 value)
{
    if (ioctl(fd, I2C_SLAVE, dev_addr) < 0) {
        printf("No such device with address: %x\n", dev_addr);
        exit(1);
    }
    return(i2c_smbus_write_byte_data(fd, reg_addr, value));
}

int write_word(int fd, u8 dev_addr, u8 reg_addr, uint16_t value)
{
    if (ioctl(fd, I2C_SLAVE, dev_addr) < 0) {
        printf("No such device with address: %x\n", dev_addr);
        exit(1);
    }
    return(i2c_smbus_write_word_data(fd, reg_addr, value));
}

int write_quick(int fd, u8 dev_addr, u8 reg_addr)
{
    if (ioctl(fd, I2C_SLAVE, dev_addr) < 0) {
        printf("No such device with address: %x\n", dev_addr);
        exit(1);
    }
    return(i2c_smbus_write_quick(fd, reg_addr));
}

int read_bytes(int fd, u8 dev_addr, u8 reg_addr, u8 *data)
{
    if (ioctl(fd, I2C_SLAVE, dev_addr) < 0) {
        printf("No such device with address: %x\n", dev_addr);
        exit(1);
    }
    return (i2c_smbus_read_block_data(fd, reg_addr, data));
}

