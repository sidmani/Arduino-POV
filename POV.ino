#include <TimerOne.h>
#include <avr/pgmspace.h>
#include "Images.h"
#include "PWMCTRL.h"
#include "Patterns.h"
/////pins/////
#define redPin 16
#define hallPin 0
#define bluePin 14
#define greenPin 15
const int ledPins[num_leds] = {8,9,10,11,12,13,A7,A5,A4,A2,A1,7,6,19,A6,A3,A0,18,21,24,5,2,20,22,23,25,26,4,3,1};
//////////////
//#define image_source pikachu
///////adjustment values////////
#define offset_slice 40
#define internal_radius_offset 1
#define debounceTime 10000
////////////////////////////////
///constants///


volatile uint8_t prevLED;
volatile uint8_t currLED;
volatile uint8_t nextSlice;
volatile int debounce=0;
volatile long strt=0;
volatile uint8_t slice;
volatile int microsPerLED;

void setup()
{ 
  pwmConfigure(1);
  Timer1.initialize(1000);
  Timer1.start();
  Timer1.attachInterrupt(rev);
  attachInterrupt(hallPin, hallInt, RISING);
  int i;
  for (i=0; i<num_leds; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}
void loop()
{
//update();
//free time (~86% of processor time is in this loop)
}



//Adjust colors with gamma values and black correction, and compensate for common-cathode LEDs

//Calculate gamma values

//////***********//////
/////   timing  //////
//////***********//////
void rev() {
	//interrupts();
//		long test = micros();

  prevLED = currLED;
  currLED = (currLED < (num_leds-1))?(currLED+1):0;
  //nextLED = (currLED < (num_leds-1))?(currLED+1):0;
  if (slice < num_slices-1 && currLED == num_leds-1)
  {
    slice++;
   // nextSlice = (slice<(num_slices-1))?(slice+1):0;
  }
  else if (currLED == num_leds-1)
  {
    slice = 0;
  }
  write_data(true, getPixel(pikachu[slice], currLED));
//  Serial.println(micros() - test);

}

void hallInt()
{
  if (micros() - strt >= debounceTime)
  {
    microsPerLED = ((micros() - strt)/num_slices)/num_leds;
    strt = micros();
    slice = offset_slice;
  	Timer1.setPeriod(microsPerLED);
  }

}
////////////////////////////
////////////////////////////
void write_data(boolean analog_out, Pixel p)
{
  if (analog_out)
  {
      digitalWrite(ledPins[prevLED], LOW);
      digitalWrite(ledPins[currLED], HIGH);
      pwmSet14(p.blue);
      pwmSet16(p.red);
      pwmSet15(p.green);
  }
  else 
  {      
  	  digitalWrite(ledPins[prevLED], LOW);
      digitalWrite(ledPins[currLED], HIGH);
      digitalWrite(bluePin, p.blue);
      digitalWrite(redPin, p.red);
      digitalWrite(greenPin, p.green);    
  }
}




Pixel getPixel(Pixel(*f)(int,int), int led, int slice)
{

return (*f)(led,slice);

//buf = adjustColor(buf);
}

Pixel getPixel(Pixel s[num_leds], int led)
{
	Pixel p ={pgm_read_byte_near(&(s[led].red)), pgm_read_byte_near(&(s[led].green)), pgm_read_byte_near(&(s[led].red))};
	p = adjustColor(p);
	return p;
}
