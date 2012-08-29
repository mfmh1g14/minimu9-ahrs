#include "I2CBus.h"
#include "exceptions.h"
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <unistd.h>

I2CBus::I2CBus(const char * deviceName)
{
    fd = open(deviceName, O_RDWR);
    if (fd == -1)
    {
        throw posix_error();
    }
}

I2CBus::~I2CBus()
{
    close(fd);
}

void I2CBus::addressSet(uint8_t address)
{
    int result = ioctl(fd, I2C_SLAVE, address);
    if (result == -1)
    {
        throw posix_error();
    }
}

void I2CBus::writeByte(uint8_t command, uint8_t data)
{
    int result = i2c_smbus_write_byte_data(fd, command, data);
    if (result == -1)
    {
        throw posix_error();
    }
}

uint8_t I2CBus::readByte(uint8_t command)
{
    int result = i2c_smbus_read_byte_data(fd, command);
    if (result == -1)
    {
        throw posix_error();
    }
    return result;
}

void I2CBus::readBlock(uint8_t command, uint8_t size, uint8_t * data)
{
    int result = i2c_smbus_read_i2c_block_data(fd, command, size, data);
    if (result != size)
    {
        throw posix_error();
    }
}
