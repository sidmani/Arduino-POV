#ifndef PWMCTRL_h
#define PWMCTRL_h
// Frequency modes for TIMER1
#define PWM62k   1   //62500 Hz
#define PWM8k    2   // 7812 Hz
#define PWM1k    3   //  976 Hz
#define PWM244   4   //  244 Hz
#define PWM61    5   //   61 Hz

// Direct PWM change variables

// Configure the PWM clock
// The argument is one of the 5 previously defined modes
void pwmConfigure(int mode)
{
  // TCCR1A configuration
  //  00 : Channel A disabled D9
  //  00 : Channel B disabled D10
  //  00 : Channel C disabled D11
  //  01 : Fast PWM 8 bit
  TCCR3A=1;

  // TCCR1B configuration
  // Clock mode and Fast PWM 8 bit
  TCCR3B=mode|0x08;  

  // TCCR1C configuration
  TCCR3C=0;
}

// Set PWM to D9
// Argument is PWM between 0 and 255
void pwmSet14(int value)
{
  OCR3C=value;   // Set PWM value
  //DDRB|=1<<5;    // Set Output Mode B5
  TCCR3A|=0x80;  // Activate channel
}

// Set PWM to D10
// Argument is PWM between 0 and 255
void pwmSet15(int value)
{
  OCR3B=value;   // Set PWM value
  //DDRB|=1<<6;    // Set Output Mode B6
  TCCR3A|=0x20;  // Set PWM value
}

// Set PWM to D11
// Argument is PWM between 0 and 255
void pwmSet16(int value)
{
  OCR3A=value;   // Set PWM value
  //DDRB|=1<<7;    // Set Output Mode B7
  TCCR3A|=0x08;  // Set PWM value
}
#endif