//Only for the purpose of testing the motion sensor

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include "PIRmotion.h"
#include "led.h"
#include "capture.h"
#include "i2c.h"

#define USER_BUTTON_VALUE_FILE "/sys/class/gpio/gpio72/value"

int main()
{
    //initDisplay();     
    initSetup();
    Relay_Init();
    Start_Detecting_Motion();
    cameraSetup();

    //printf("Press the user button to quit.\n");
    //int userButtonState = readFromFileToScreen(USER_BUTTON_VALUE_FILE);

    printf("Enter 'Q' to quit.\n");
    while (true) {
        // Quit?
        if (toupper(getchar()) == 'Q') {
            break;
        }
    }

    cameraCleanup();
    Stop_Detecting_Motion();

    return 0;
}