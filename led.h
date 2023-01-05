#ifndef LED2_H
#define LED2_H

#define LED_Direc1 "/sys/class/gpio/gpio49/direction"  // green
#define LED_Value1 "/sys/class/gpio/gpio49/value"

#define LED_Direc2 "/sys/class/gpio/gpio66/direction" // red 
#define LED_Value2 "/sys/class/gpio/gpio66/value"

#define RELAY_Direc "/sys/class/gpio/gpio2/direction"
#define RELAY_Value "/sys/class/gpio/gpio2/value"

// create thread 
void Relay_Init(void);

void LED_ON(char *LED_low);
void LED_OFF(char *LED_high);

void LED_direction(char *LED_D);
void RELAY_direction(char *LED_D);

bool checkNightVision();

void Relay_Open(char *RELAY_high);
void Relay_Close(char *RELAY_low);

//void LED_direction(char *LED_D);

//join thread 
void Relay_clean(void);

#endif