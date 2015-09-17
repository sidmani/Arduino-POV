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
void setSourceFunc(Pixel(*f)(uint8_t,uint8_t));
void setSource(int p);
Pixel getPixelFunc(uint8_t led, uint8_t slice);

Pixel (*source_func)(uint8_t,uint8_t);
//Pixel **source_img;
int source_img;
boolean pixel_source_type; //0 = image, 1 = function
volatile uint8_t prevLED;
volatile uint8_t currLED;
volatile int debounce=0;
volatile long strt=0;
volatile uint8_t slice;
volatile int microsPerLED;
long pattern_start=0;
const int offset_slice = 30;
uint8_t currImage = 0;
int images[2] = {(int)pikachu[0], (int)SFLogo[0]};
void setup()
{ 
  pwmConfigure(1);
  Timer1.initialize(1000);
  Timer1.start();
  Timer1.attachInterrupt(rev);
  attachInterrupt(hallPin, hallInt, RISING);
  uint8_t i;
  for (i=0; i<num_leds; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  setSource(images[0]);
  pattern_start = millis();

}
void loop()
{
if (millis()-pattern_start > 5000) 
{
if (currImage == 0)
{
setSource(images[currImage]);
currImage = 1;
}
else if (currImage == 1)
{
setSource(images[currImage]);
currImage = 2;
}
else
{
setSourceFunc(&hexacolor);
currImage = 0;
}
pattern_start = millis();

}
}




//////***********//////
/////   timing  //////
//////***********//////
void rev() {
//		long test = micros();
  interrupts();
  prevLED = currLED;
  currLED = (currLED < (num_leds-1))?(currLED+1):0;
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
   write_data(true, getPixelFunc(currLED, slice));

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




Pixel getPixelFunc(uint8_t led, uint8_t slice)
{

return (source_func)(slice,led);

}

Pixel getPixel(int s, uint8_t led, uint8_t currSlice)
{
	//int offset = currSlice*num_leds*3+led*3;	
	Pixel p ={pgm_read_byte_near(s+currSlice*num_leds*3+led*3), pgm_read_byte_near(s+currSlice*num_leds*3+led*3+1), pgm_read_byte_near(s+currSlice*num_leds*3+led*3+2)};
	return adjustColor(p);
}
void setSourceFunc(Pixel(*f)(uint8_t,uint8_t))
{
source_func = f;
pixel_source_type = 1;
}

void setSource(int p)
{
source_img = p;
pixel_source_type = 0;
}