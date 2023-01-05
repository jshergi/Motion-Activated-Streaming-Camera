#ifndef PHOTO_H
#define PHOTO_H

#define A2D_FILE_VOLTAGE1 "/sys/bus/iio/devices/iio:device0/in_voltage1_raw"
#define A2D_VOLTAGE_REF_VP 1.8
#define A2D_MAX_READING 4095

int readA2D();
double getSampleVoltage();

#endif