Author: Ben Jukus
##Timer A Blink
#Timer Interrupt
The difference between polling and interrupts starts here. The timer interrupts are enabled (TA0CCTL0 = CCIE) which later in the pragma vector tells the timer what to do while it is high. In this case XOR the LED to turn it off or on. 
#CCR
CCR is the Capture Compare Register. It controls how long the timer's cycles last; since we have been dealing with timers set to upmode whenever the counter in the timer reaches the CCR value they reset to zero. CCR acts as a cap value. This is the first step to creating a PWM as well. 
