#ifndef _PIRMOTION_H
#define _PIRMOTION_H

#define FILE_TO_READ "/sys/class/gpio/gpio13/value"

void initSetup();
void sleepForMs(long long delayInMs);
void Start_Detecting_Motion(void);
void Stop_Detecting_Motion(void);
int getMotionValue();
int readFromFileToScreen(char *fileName);

#endif