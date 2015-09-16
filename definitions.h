#ifndef definitions_h
#define definitions_h

// Frequency modes for TIMER1
#define PWM62k   1   //62500 Hz
#define PWM8k    2   // 7812 Hz
#define PWM1k    3   //  976 Hz
#define PWM244   4   //  244 Hz
#define PWM61    5   //   61 Hz
//////
///////adjustment values////////
#define debounceTime 10000
#define num_slices 90
#define num_leds 30
#define num_pixels num_leds*num_slices
#define redGamma 2.8
#define blueGamma 2.8
#define greenGamma 2.8
#define black_adj 24
/////pins/////
#define redPin 16
#define hallPin 0
#define bluePin 14
#define greenPin 15
const int ledPins[num_leds] = {8,9,10,13,12,11,A7,A5,A4,A2,A1,7,6,19,A6,A3,A0,18,21,24,5,2,20,22,23,25,26,4,3,1};
//////////////
//#define image_source pikachu


#endif