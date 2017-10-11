/* Author: Ben Jukus
 * Button Interrupt 5994
 */

#include <msp430.h> 

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;
//Button Stuff
      P5DIR &= ~BIT6; //Sets button2, pin5.6 as an input
      P5REN |=  BIT6; //Enables the pullup/down resistor
      P5OUT |=  BIT6; //Set the resistor to be a pullup resistor

      //PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
//LED Junk
      P1DIR |= BIT0; //sets the direction of pin 1 to output
      P1OUT &= ~(BIT0); //sets output high

// Interrupt stuff
      P5IE |=BIT6;//enable the interrupt on Port 5.6
      P5IES |=BIT6;//set as falling edge
      P5IFG &=~(BIT6);//clear interrupt flag

      _BIS_SR(LPM4_bits + GIE);//enter LPM4 mode and enable global interrupt
}
//Port 1 ISR
#pragma vector=PORT5_VECTOR
__interrupt void PORT_5(void)
    {
        P1OUT ^= BIT0;
        P5IFG &=~(BIT6);
    }

