Author: Ben Jukus
## Button Interrupt
# Interrupt
The use of interrupts requires a greater understanding and takes a little more effort but is far more efficient. To understand interrupts there are a few steps: are enabled, what causes the interrupt, like a button, later in the interrupt service routine (ISR) what happens during the interrupt is outlined. This code simply turns on or off the LED if the button is pressed since the led is XOR'ed in the button interrupt. 

# Low Power Mode
One very useful feature of using interrupts instead of polling is that the board can go into low power mode (LPM). This will be useful for more complex operations and in times when the processor's power is key. For the scope we have already covered the LPM makes little difference, but will be useful in future applications, school and otherwise. 
