#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include "photo.h"


FILE *openVFile(char *voltageFile, char *type)
{
   FILE *f = fopen(voltageFile, type);
   if (!f)
   {
      printf("ERROR: Unable to open voltage input file. Cape loaded?\n");
      printf("       Check /boot/uEnv.txt for correct options.\n");
      exit(-1);
   }

   return f;
}

int readA2D()
{
   FILE *f = openVFile(A2D_FILE_VOLTAGE1, "r");
   int a2dReadingX = 0;
   int itemsReadX = fscanf(f, "%d", &a2dReadingX);
   if (itemsReadX <= 0)
   {
      printf("ERROR: Unable to read values from voltage input file.\n");
      exit(-1);
   }

   // Close file
   fclose(f);

   return a2dReadingX;
}

double getSampleVoltage()
{
   int A2DReading = readA2D();
   double voltage = ((double)A2DReading / A2D_MAX_READING) * A2D_VOLTAGE_REF_VP;
   return voltage;
}