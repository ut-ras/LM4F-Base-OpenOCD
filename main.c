#include <StellarisWare/hw_ints.h>
#include <StellarisWare/hw_memmap.h>
#include <StellarisWare/hw_types.h>
#include <driverlib/debug.h>
#include <driverlib/fpu.h>
#include <driverlib/i2c.h>
#include <driverlib/gpio.h>
#include <driverlib/interrupt.h>
#include <driverlib/pin_map.h>
#include <driverlib/sysctl.h>
#include <driverlib/timer.h>
#include <utils/uartstdio.h>
#include "blinky.h"
#include "line-sensors.h"

unsigned char led_state = 0;
unsigned char led_toggle = 0;

void BlinkyLedHandler(void){
  // clear Interrupt
  TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

  //toggle led
  if( led_toggle == 1){
    led_state += 2;
    led_state &= 15;}

  //write to led
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, led_state);}

int main(void){
  IntMasterDisable();
  FPULazyStackingEnable(); // minimize stack space used for fpu in an interrupt handlers

  //clock from the crystal
  SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

  //uart init
//  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
  UARTStdioInit(0);

  // enable the led GPIO port
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1);

  //configure timer 0
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
  TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()/3);

  //Enable Timer Interrupt
  IntMasterEnable();
  IntEnable(INT_TIMER0A);
  TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  TimerEnable(TIMER0_BASE, TIMER_A);

  while(1){
    unsigned long charic;
    UARTprintf("\r\nBlinkey Led demo!\r\n");
    UARTprintf("1 : toggle led \r\n");
    UARTprintf("2 : toggle led toggling via a timer =P\r\n");
    UARTprintf(">");
    UARTprintf("%c\n",(unsigned char) (charic = UARTgetc()));
    switch (charic){
    case '1':
      led_state += 2;
      led_state &= 15;
      //write to led
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, led_state);
      break;
    case '2':
      led_toggle ^= 1;
      break;
    default:
      UARTprintf("invalid input: %c", (unsigned char) charic);
      break;}}}
      

  

  
