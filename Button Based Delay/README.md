Author: Ben Jukus
## Button Based Delay
# Delay
In order to make the led blink at a rate determined by the user two timers must be used. The first time, TA0 is the blinker of the led, this timer is setup with an interrupt to toggle the led. Timer TA1 is used to take input. This timer counts as the user holds down button 2 and when released the cap on TA0 is set to this counted number. 
# Buttons
"Button 2" (varies by board, 2.1 on the 5529) is used to count the desired blink length, this is paired with Timer TA1 to determine the period of the LED.
5529 Only: Button 1 is used as a reset. This is simply done by setting the capture compare register to 10 hz, for A clock this is 1600 since it is divided by 2. 
