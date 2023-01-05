#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include "PIRmotion.h"
#include "led.h"
#include "i2c.h"



static pthread_t idRead; 
bool isDoneRunning = false;
int motionValue; 

void sleepForMs(long long delayInMs){
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 1000000000;
    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoSeconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoSeconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
}

static void runCommand(char* command){

    // Execute the shell command (output into pipe)
    FILE *pipe = popen(command, "r");

    // Ignore output of the command; but consume it 
    // so we don't get an error when closing the pipe. 
    char buffer[1024];
    while (!feof(pipe) && !ferror(pipe)) {
        if (fgets(buffer, sizeof(buffer), pipe) == NULL){
            break;
        }
        // printf("--> %s", buffer);
    }

    // Get the exit code from the pipe; non-zero is an error:
    int exitCode = WEXITSTATUS(pclose(pipe));
    if (exitCode != 0){
        perror("Unable to execute command:");
        printf(" command:   %s\n", command);
        printf(" exit code: %d\n", exitCode);
    }

}

void initSetup()
{
    runCommand("config-pin p9_19 gpio");
    runCommand("config-pin p8.43 gpio");
    runCommand("config-pin p9_18 i2c");
    runCommand("config-pin p9_17 i2c");
}

int readFromFileToScreen(char *fileName){
    FILE *pFile = fopen(fileName, "r");
    if (pFile == NULL){
        printf("ERROR: Unable to open file (%s) for read\n", fileName);
        exit(-1);
    }

    // Read string (line)
    const int MAX_LENGTH = 1024;
    char buff[MAX_LENGTH];
    fgets(buff, MAX_LENGTH, pFile);

    // Close
    fclose(pFile);
    return atoi(buff);
    // printf("Read: '%s\n", buff);
}


static void *CaptureThread (void *_) 
{
    int nightVisionStatus; 
    while(!isDoneRunning){
        int currentMotionValue = getMotionValue();
        if (currentMotionValue == 1){
            LED_ON(LED_Value1);
            LED_OFF(LED_Value2);
            nightVisionStatus = checkNightVision();
            if (nightVisionStatus == 1)
            {
                Relay_Close(RELAY_Value);
            }
            else {
                Relay_Open(RELAY_Value);
            }
        }
        else{
            LED_ON(LED_Value2);
            LED_OFF(LED_Value1);
            Relay_Open(RELAY_Value);
        } 
    }
    return NULL;
}

void Start_Detecting_Motion()
{
    pthread_create(&idRead, NULL, &CaptureThread, NULL);
}

void Stop_Detecting_Motion()
{
    isDoneRunning = true; 
    displayMode(2);
    LED_OFF(LED_Value1);
    LED_OFF(LED_Value2);
    printf("Thread exiting!\n");
    pthread_join(idRead, NULL);
    
}

int getMotionValue()
{
    motionValue = readFromFileToScreen(FILE_TO_READ);
    return motionValue;
}
