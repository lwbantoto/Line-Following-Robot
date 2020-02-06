#include "mte220.c"  // C functions needed for labs

/*
Description:
Once the button is pushed, this code will turn on both servos and
leave them on for about 2 seconds, then turn the motors off.
*/

//;**********************************************************************
void main(void)
{
    Initialization();

    // both servos are turned on
    UseServos         // (syntax of "call" is correct without () or ;)


    while (1)
    {
        WaitForButton();  // wait until the button is pushed

        // turn on the servos
        BothServosOn

        // wait for 2 second
        LongDelay(16);

        // turn off servos
        BothServosOff
       
    }
}
