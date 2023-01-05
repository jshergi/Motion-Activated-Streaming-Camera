#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <time.h>
#include "i2c.h"


int initI2cBus(char* bus, int address)
{
	int i2cFileDesc = open(bus, O_RDWR);
	if (i2cFileDesc < 0) {
		printf("I2C DRV: Unable to open bus for read/write (%s)\n", bus);
		perror("Error is:");
		exit(-1);
	}

	int result = ioctl(i2cFileDesc, I2C_SLAVE, address);
	if (result < 0) {
		perror("Unable to set I2C device to slave address.");
		exit(-1);
	}
	return i2cFileDesc;
}

void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value)
{
	unsigned char buff[2];
	buff[0] = regAddr;
	buff[1] = value;
	int res = write(i2cFileDesc, buff, 2);
	if (res != 2) {
		perror("Unable to write i2c register");
		exit(-1);
	}
}

unsigned char readI2cReg(int i2cFileDesc, unsigned char regAddr)
{
	// To read a register, must first write the address
	int res = write(i2cFileDesc, &regAddr, sizeof(regAddr));
	if (res != sizeof(regAddr)) {
		perror("Unable to write i2c register.");
		exit(-1);
	}

	// Now read the value and return it
	char value = 0;
	res = read(i2cFileDesc, &value, sizeof(value));
	if (res != sizeof(value)) {
		perror("Unable to read i2c register");
		exit(-1);
	}
	return value;
}

static int* getDigits (int digitNumber){
	int* nums = malloc(7*sizeof(int));
	switch(digitNumber){
		case 0: 
			nums[0] = 0x00; nums[1] = 0x20; nums[2] = 0x30; nums[3] = 0x38; nums[4] = 0x38; nums[5] = 0x30; nums[6] = 0x20;
			break;
		case 1: 
			nums[0] = 0x00; nums[1] = 0x28; nums[2] = 0x28; nums[3] = 0x28; nums[4] = 0x28; nums[5] = 0x28; nums[6] = 0x28;
			break;
		
		case 2: 
			nums[0] = 0x00; nums[1] = 0x00; nums[2] = 0x00; nums[3] = 0x00; nums[4] = 0x00; nums[5] = 0x00; nums[6] = 0x00;
			break;
	}
	return nums; 
}


int displayMode(int mode)
{
	int* disp;

	if (mode == 0){
		disp = getDigits(1);
	}

	else if (mode == 1){
		disp = getDigits(0);
	}
	
	else if (mode == 2){
		disp = getDigits(2);
	}

	int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);
	
	writeI2cReg(i2cFileDesc, REG_DIRA, 0x00);
	writeI2cReg(i2cFileDesc, REG_DIRB, 0x00);

	writeI2cReg(i2cFileDesc, 0x0E, (disp[0]>>1));
	writeI2cReg(i2cFileDesc, 0x0C, (disp[1]>>1));
	writeI2cReg(i2cFileDesc, 0x0A, (disp[2]>>1));
	writeI2cReg(i2cFileDesc, 0x08, (disp[3]>>1));
	writeI2cReg(i2cFileDesc, 0x06, (disp[4]>>1));
	writeI2cReg(i2cFileDesc, 0x04, (disp[5]>>1));
	writeI2cReg(i2cFileDesc, 0x02, (disp[6]>>1));
	writeI2cReg(i2cFileDesc, 0x00, 0x00);
	
	free(disp);
	//free(RDigit);
	
	close(i2cFileDesc);
	return 0;

}

