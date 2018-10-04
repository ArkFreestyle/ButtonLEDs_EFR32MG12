#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"

#include "hal-config.h"

#define LED_PORT gpioPortF
#define LED_PIN1 4
#define LED_PIN2 5

#define BUTTON_PORT	gpioPortF
#define BUTTON_PIN1 6
#define BUTTON_PIN2 7

int main(void)
{
  /* Chip errata */
  CHIP_Init();
  //Always enable the clock relevant to what you're working with! This is the clock
  //for on-board components
  CMU_ClockEnable(cmuClock_GPIO, true);
  //Set buttons as Inputs first
  GPIO_PinModeSet(BUTTON_PORT, BUTTON_PIN1, gpioModeInput, 0);
  GPIO_PinModeSet(BUTTON_PORT, BUTTON_PIN2, gpioModeInput, 0);
  //Set bools for LED states
  bool LED1ON = false;
  bool LED2ON = false;
  /* Infinite loop */
  while (1) {
	  // Grab the state of the button, 1 for high voltage, 0 for low
	  bool live_button1_state = GPIO_PinInGet(BUTTON_PORT, BUTTON_PIN1);
	  bool live_button2_state = GPIO_PinInGet(BUTTON_PORT, BUTTON_PIN2);
	  if (live_button1_state == 0 && LED1ON == false) //when button1 is pressed
	  {
	  	  GPIO_PinModeSet(LED_PORT, LED_PIN1, gpioModePushPull, 1); //turn LED1 on
	  	  LED1ON = true;
	  }
	  else if(live_button1_state == 0 && LED1ON == true)
	  {
		  GPIO_PinModeSet(LED_PORT, LED_PIN1, gpioModePushPull, 0); //turn LED1 off
		  LED1ON = false;
	  }
	  if (live_button2_state == 0) //when button2 is pressed
	  {
		  GPIO_PinModeSet(LED_PORT, LED_PIN2, gpioModePushPull, 1); //turn LED2 on
	  }
	  else
	  {
		  GPIO_PinModeSet(LED_PORT, LED_PIN2, gpioModePushPull, 0); //turn LED2 off
	  }
  }
}
