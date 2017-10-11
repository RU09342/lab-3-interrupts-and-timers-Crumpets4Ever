/* Ben Jukus
 * Button Based Delay 5994
 * Jess Wozniak made pretty much all this
 * I adjusted it, did some formatting. The functionality is all thanks to Jess.
 */
#include <msp430.h>

#define LED1 BIT0                               //Defines LED1 as BIT0
#define LED2 BIT1                               //Defines LED2 as BIT7
#define BUTTON BIT5                             //Defines BUTTON as BIT1

void main(void) {

    WDTCTL = WDTPW + WDTHOLD;                  // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

//LED Junk
    P1DIR |=   LED1;                             //sets the LED of pin 1 to output
    P1OUT &= ~(LED1);                          //sets output high

    P1DIR |=   LED2;                             //sets the LED of pin 4 to output
    P1OUT &= ~(LED2);                          //sets output high

//Button
    P5REN|=  BUTTON;                            //enable pull-up resistor on
    P5OUT|=  BUTTON;                            //Sets resistor to be pullup

//Button Interrupt
    P5IE  |=   BUTTON;                          //enable Button interrupt
    P5IES |=   BUTTON;                          //set as falling edge/ rising edge
    P5IFG &= ~(BUTTON);                         //clear interrupt flag

    TA0CCTL0 = CCIE;                            // sets timer on compare mode
    TA0CCR0 = 1600;
    TA0CTL= TASSEL_1+MC_1;                      // ACLK, UP MODE, DIV 2

   __bis_SR_register(LPM0_bits + GIE);         //enter LPM0 mode and enable global interrupt
}

//Port 2 ISR
#pragma vector=PORT5_VECTOR
__interrupt void PORT_5(void)
    {
        if (P2IES & BUTTON)                     //if button is not pressed
            {
                TA1CTL = TASSEL_1 + MC_2;           //SMCLK, CONT MODE, DIV 8
                P1OUT ^= LED2;                      //Toggles green led
                P5IES &= ~(BUTTON);                 //flips the edge of the clock the interrupt is enabled
            }
        else                                    //set TA1R to capture compare to timer a_0
            {                                     //button is pressed
                TA0CCR0 = TA1R;
                P1OUT &= ~(LED2);                   //turns off green led
                P5IES |= BUTTON;                    //flips the edge of the clock the interrupt is enabled
                TA1CTL = TACLR;                     //Clears the A1 Timer
            }
        P5IFG &= ~(BUTTON);                     //clears interrupt flag
        }

// Timer A0 ISR
#pragma vector= TIMER0_A0_VECTOR
    __interrupt void Timer_A0 (void)
    {
        P1OUT ^= LED1;                          //Toggles red led
    }
