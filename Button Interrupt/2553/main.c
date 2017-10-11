/* Author: Ben Jukus
 * Button Interrupt 2311
 */

#include <msp430.h> 

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;
//Button Stuff
      P1DIR &= ~BIT3; //Sets button2, pin1.2 as an input
      P1REN |=  BIT3; //Enables the pullup/down resistor
      P1OUT |=  BIT3; //Set the resistor to be a pullup resistor

      //PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
//LED Junk
      P1DIR |= BIT0; //sets the direction of pin 1 to output
      P1OUT &= ~(BIT0); //sets output high

// Interrupt stuff
      P1IE |=BIT3;//enable the interrupt on Port 1.1
      P1IES |=BIT3;//set as falling edge
      P1IFG &=~(BIT3);//clear interrupt flag

      _BIS_SR(LPM4_bits + GIE);//enter LPM4 mode and enable global interrupt
}
//Port 1 ISR
#pragma vector=PORT1_VECTOR
__interrupt void PORT_1(void)
    {
        P1OUT ^= BIT0;
        P1IFG &=~(BIT3);
    }

