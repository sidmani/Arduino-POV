#include <TimerOne.h>
#include <avr/pgmspace.h>
#include "Images.h"
#include "PWMCTRL.h"
#include "Patterns.h"
#include "definitions.h"

/////pins/////
//////////////
//#define image_source pikachu
///////adjustment values////////
////////////////////////////////
///constants///

//Pixel *source_func;
//Pixel **source_img;
int source_img;
boolean pixel_source_type; //0 = image, 1 = function
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
  setSource((int)pikachu[0]);
}
void loop()
{
//free time (~86% of processor time is in this loop)

}



//Adjust colors with gamma values and black correction, and compensate for common-cathode LEDs

//Calculate gamma values

//////***********//////
/////   timing  //////
//////***********//////
void rev() {
//		long test = micros();

  prevLED = currLED;
  currLED = (currLED < (num_leds-1))?(currLED+1):0;
  //nextLED = (currLED < (num_leds-1))?(currLED+1):0;
  if (slice < num_slices-1 && currLED == num_leds-1)
  {
    slice++;
      }
  else if (currLED == num_leds-1)
  {
    slice = 0;
  }
  if (pixel_source_type == 0)
  {
  write_data(true, getPixel(source_img, currLED, slice));
  }
  else
  {
   // write_data(true, getPixel(source_img[slice], currLED));

  }
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

}

Pixel getPixel(int s, int led, int currSlice)
{
	int offset = currSlice*num_leds*3+led*3;	
	Pixel p ={pgm_read_byte_near(s+offset), pgm_read_byte_near(s+offset+1), pgm_read_byte_near(s+offset+2)};
	return adjustColor(p);
}
void setSource(Pixel(*f)(int,int))
{
//source_func = *f;
pixel_source_type = 1;
}

void setSource(int p)
{
source_img = p;
}