/* Author: Ben Jukus
 * Button Based Delay 2553
 */

#include <msp430.h>
unsigned int speed[10] = {3200, 0, 1000, 1500, 2500, 5000, 10000, 15000, 25000, 40000, 55000}; //the different speeds the led blinks at. It's fine.
unsigned int i = 0;
int main(void)
{
            WDTCTL = WDTPW + WDTHOLD;                   // Stop WDT
            //PM5CTL0 &= ~LOCKLPM5;
//LED Junk
            P1DIR |= BIT0;                              //sets the direction of pin 1 to output
            P1OUT &= ~(BIT0);                           //sets output high

//Button Jazz

            P1DIR &= ~BIT1;                             //Sets button2, pin1.2 as an input
            P1REN |=  BIT1;                             //Enables the pullup/down resistor
            P1OUT |=  BIT1;                             //Set the resistor to be a pullup resistor

            P2DIR &= ~BIT1;                             //Sets button2, pin1.2 as an input
            P2OUT |=  BIT1;                             //Set the resistor to be a pullup resistor
            P2REN |=  BIT1;                             //Enables the pullup/down resistor

//Timer Junk
            TA0CCTL0 = CCIE;                            // CCR0 interrupt enabled
            TA0CCR0 = 3200;                             // Approximately 10 Hz, Aclk is like 32 kHz
            TA0CTL = TASSEL_1 + MC_1 + TACLR;           // ACLK, upmode, clear TAR

// Interrupt Enable Jawn
            P1IE |=BIT1;                                //enable the interrupt on Port 1.1
            P1IES |=BIT1;                               //set as falling edge
            P1IFG &=~(BIT1);                            //clear interrupt flag

            P2IE |=BIT1;                                //enable the interrupt on Port 2.1
            P2IES |=BIT1;                               //set as falling edge
            P2IFG &=~(BIT1);                            //clear interrupt flag


__bis_SR_register(LPM0_bits + GIE);                     // Enter LPM0
__no_operation();                                       // For debugger
}

#pragma vector = PORT1_VECTOR                           //Changes the blink rate
__interrupt void Port_1(void)
   {
        TA0CCR0 = speed[i];                             //LED blinks at speed of the array
        i++;                                            //Increments through the array
        if(i>10)                                        // Doesn't let it go outside the array
                   {
                       i=0;
                   }
        P1IFG &= ~(BIT1);                               //Clears interrupt flag
    }

#pragma vector = PORT2_VECTOR                           //Reset
__interrupt void Port_2(void)
    {
        TA0CCR0=3200;                                   //Resets the led to blink at 10 hz ish
        P2IFG &= ~(BIT1);                               //clears interrupt flag
    }
#pragma vector = TIMER0_A0_VECTOR                       //Timer counts
__interrupt void TA0_ISR(void)
{
  P1OUT ^= BIT0;                                        // Toggle LED 1.0
}
