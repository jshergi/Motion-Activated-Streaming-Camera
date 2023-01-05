#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

#include "led.h"
#include "photo.h"
#include "PIRmotion.h"

void Relay_Init(void)
{
    LED_direction(LED_Direc1);
    LED_direction(LED_Direc2);
    RELAY_direction(RELAY_Direc);
}

//------------------------------------------------------------------------------------------


FILE *openFile(char *file, char *type)
{
   FILE *f = fopen(file, type);
   if (!f)
   {
      printf("ERROR: Unable to open voltage input file. Cape loaded?\n");
      printf("       Check /boot/uEnv.txt for correct options.\n");
      exit(-1);
   }

   return f;
}



void LED_direction(char *LED_D)
{
 
    FILE *pLED_Direction = openFile(LED_D, "w");

    int charWritten1 = fprintf(pLED_Direction, "out");
    if (charWritten1 <= 0)
    {
        perror("ERROR WRITING DATA");
        exit(1);
    }
    fclose(pLED_Direction);
}

// led value --- active low will turn on LED
void LED_ON(char *LED_low)
{
    FILE *pLed_LowFile = openFile(LED_low, "w");

    int charWritten1 = fprintf(pLed_LowFile, "0");
    if (charWritten1 <= 0)
    {
        perror("ERROR WRITING DATA");
        exit(1);
    }

    fclose(pLed_LowFile);
}

// led value --- active low will turn on LED
void LED_OFF(char *LED_high)
{
    FILE *pLed_HighFile = openFile(LED_high, "w");

    int charWritten1 = fprintf(pLed_HighFile, "1");
    if (charWritten1 <= 0)
    {
        perror("ERROR WRITING DATA");
        exit(1);
    }

    fclose(pLed_HighFile);
}

//-------------------------------------------------------------------------------

void RELAY_direction(char *LED_D)
{

    FILE *pRELAY_Direction = openFile(LED_D, "w");

    int charWritten1 = fprintf(pRELAY_Direction, "out");
    if (charWritten1 <= 0)
    {
        // printf("ERROR WRITING DATA");
        perror("ERROR WRITING DATA");
        exit(1);
    }

    // Close the file using fclose():
    fclose(pRELAY_Direction);
}

// led value --- active low will turn on LED
void Relay_Close(char *RELAY_low)
{
    FILE *pRELAY_LowFile = openFile(RELAY_low, "w");

    int charWritten1 = fprintf(pRELAY_LowFile, "1");
    if (charWritten1 <= 0)
    {
        // printf("ERROR WRITING DATA");
        perror("ERROR WRITING DATA");
        exit(1);
    }

    fclose(pRELAY_LowFile);
}

// led value --- active low will turn on LED
void Relay_Open(char *RELAY_high)
{
    FILE *pRELAY_HighFile = openFile(RELAY_high, "w");

    int charWritten1 = fprintf(pRELAY_HighFile, "0");
    if (charWritten1 <= 0)
    {
        // printf("ERROR WRITING DATA");
        perror("ERROR WRITING DATA");
        exit(1);
    }

    fclose(pRELAY_HighFile);
}

bool checkNightVision()
{
    double voltage = getSampleVoltage();

    if (voltage <= 1){
        
        return 1;
    }
    else {
        Relay_Open(RELAY_Value);
        return 0;

    }
    
}