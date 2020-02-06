#include "mte220.c" 

/*
Lance and Cole
November 29, 2016
*/

// Constant declarations
#define HALL_LOW 0x3E // 62
#define HALL_HIGH 0xAB // 171
#define LOW_THRESH 0x70 // 112
#define NOMNOMNOM 0x7A  // 122
#define HIGH_THRESH 0x84 // 132
#define RIGHT_THRESH 0x66 // 0x66 is 2V for 10-bit ADC with 2 LSB dropped
#define LEFT_THRESH 0x99 // 0x99 is 3V for 10-bit ADC with 2 LSB dropped
#define LEFT_START 2500 
#define RIGHT_START 5000
#define LEFT_STOP 3350
#define RIGHT_STOP 3500

void LineFollow(void)
{
	uns8 irValue;
	irValue = AnalogConvert(ADC_IR_SENSOR);
	if ( irValue < RIGHT_THRESH )
	    {
	        LeftServoOn
	        RightServoOff
	    }

	else if ( irValue > LEFT_THRESH ) 
	{
        RightServoOn
        LeftServoOff
    }

    else
        BothServosOn
}

void Blink(void)
{
	for (i = 0; i < 4; i++) // Loop 4 times
	{
		OnLED
		LongDelay(7); // 0.875 seconds
		OffLED
		LongDelay(7);
	}
}

void SlowStart(void)
{
	uns8 leftInterval, rightInterval, leftInc, rightInc;
	char i;

	leftInterval = LEFT_STOP - LEFT_START; 
	leftInterval = leftInterval / 5;
	rightInterval = RIGHT_START - RIGHT_STOP;
	rightInterval = rightInterval / 5;

	for ( i = 1; i < 6; i++ )
	{
		leftInc = i * leftInterval;
		rightInc = i * rightInterval;
		SetLeft(LEFT_STOP - leftInc);  
		SetRight(RIGHT_STOP + rightInc);
		LongDelay(0.25);
	}
    
    SetLeft(LEFT_START);
	SetRight(RIGHT_START);
}

void SlowStop(void)
{
	uns8 leftInterval, rightInterval, leftInc, rightInc;
	char i;

	leftInterval = LEFT_STOP - LEFT_START; 
	leftInterval = leftInterval / 5; 
	rightInterval = RIGHT_START - RIGHT_STOP;
	rightInterval = rightInterval / 5;

	for (i = 1; i < 6; i++)
	{
		leftInc = i * leftInterval; 
		rightInc = i * rightInterval;
		SetLeft(LEFT_START + leftInc); 
		SetRight(RIGHT_START - rightInc);
		LongDelay(1);
	}

    SetLeft(LEFT_STOP);
	SetRight(RIGHT_STOP);
}

void main(void)
{
	// Initialize 
	Initialization();
    uns8 irValue, hallValue;  

    // Wait for button press, debounce, then turn the motors on
	WaitForButton();
	LongDelay(4);
    UseServos         
    SlowStart();

    while (1)
    {
    	// Set values to ADC ports
        irValue = AnalogConvert(ADC_IR_SENSOR); // AN0
		hallValue = AnalogConvert(ADC_HALL_EFFECT); // AN2

		// MAGNET CASE 1
		if ( hallValue < HALL_LOW ) // 0x3E
		{
			SlowStop();
			Blink();

			while ( hallValue < LOW_THRESH ) 
			{
				hallValue = AnalogConvert(ADC_HALL_EFFECT);
				LineFollow();
			}

			SlowStart();
		}

		// MAGNET CASE 2
		if ( hallValue > HALL_HIGH ) // 0xAB
		{
			SlowStop();

			// Turn LED on for 7 seconds
		    OnLED
			LongDelay(56);
			OffLED

			while ( hallValue > HIGH_THRESH )
			{
				hallValue = AnalogConvert(ADC_HALL_EFFECT);
				LineFollow();
			}

			SlowStart();
		}

		LineFollow();
    }
}