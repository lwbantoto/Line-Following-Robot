#include "mte220.c"  // C functions needed for labs

/*
Description: 
The labhall code reads the Hall effect sensor ADC.  
The duty cycle of the LED is set based on the value.
*/

void main(void)
{
    uns8 analog_value1;  // current ADC value

    Initialization();

    while (1)  // loop forever
    {
        // get analog value from the Hall effect sensor
        analog_value1 = AnalogConvert(ADC_HALL_EFFECT);

        // Turn on LED for fraction of time corresponding to analog value
        OnLED
        Delay(analog_value);

        // Turn off LED
        OffLED
        analog_value = 255 - analog_value;
        Delay(analog_value);
    }
}
