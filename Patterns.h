#ifndef Patterns_h
#define Patterns_h


//////***********//////
/////  patterns  //////
//////***********//////

/*void randomStripes()
{
  int i;
  for (i=0; i<num_slices; i++)
  {
    int red_lev = random(255);
    int blue_lev = random(255);
    int green_lev = random(255);

    int q;
    for (q=0; q<num_leds; q++)
    {
      def.dataRed[i][q] = red_lev;
      def.dataBlue[i][q] = blue_lev;
      def.dataGreen[i][q] = green_lev;

    }
  }
}*/
/*void image_polar(const byte b[])
{
int i; 
int f;
int currByte=0;
for (i = 0; i < num_leds; i++)
{
  for (f = 0; f < num_slices; f++)
  {
    def.dataRed[f][i] = pgm_read_byte_near(b+currByte);
    currByte++;
    def.dataGreen[f][i] = pgm_read_byte_near(b+currByte);
    currByte++;
    def.dataBlue[f][i] = pgm_read_byte_near(b+currByte);
    currByte++;
  }
}
}*/
/*void roundToBoolean()
{
int r=0;
int t=0;
 for (r=0; r<num_leds; r++)
{
  for (t=0; t<num_slices; t++)
  {    
     def.dataRed[t][r] = (def.dataRed[t][r]<128)?LOW:HIGH;
     def.dataBlue[t][r] = (def.dataBlue[t][r]<128)?LOW:HIGH;
     def.dataGreen[t][r] = (def.dataGreen[t][r]<128)?LOW:HIGH;

  }
}
}*/
/*void image_rectangular_inverse(const byte b[], int dimension)
{
int r=0;
int t=0;

for (r=internal_radius_offset; r<(internal_radius_offset+num_leds); r++)
{
  for (t=0; t<num_slices; t++)
  {
  int x = ceil(r*cos(degToRad(t*(360/num_slices)))+30);
  int y = ceil(r*sin(degToRad(t*(360/num_slices)))+30);

//    Serial.println("-----");
//    Serial.println(x);
//    Serial.println(y);

    def.dataRed[t][r-internal_radius_offset] = pgm_read_byte_near(b+(dimension*3)*(y-1)+3*(x-1));
    def.dataGreen[t][r-internal_radius_offset] = pgm_read_byte_near(b+(dimension*3)*(y-1)+3*(x-1)+1);
    def.dataBlue[t][r-internal_radius_offset] = pgm_read_byte_near(b+(dimension*3)*(y-1)+3*(x-1)+2);

  }
}
}*/

/*void tricolor(uint8_t red[3], uint8_t green[3], uint8_t blue[3], boolean analog)
{
  int i;
  int q;
  if (analog)
  {
    for (q=0; q<num_leds; q++)
    {
      for (i=0; i<30; i++)
      {
        
        def.dataBlue[i][q] = blue[0];
        def.dataRed[i][q] = red[0];
        def.dataGreen[i][q] = green[0];

      }
      for (i=30; i<60; i++)
      {

        def.dataBlue[i][q] = blue[1];
        def.dataRed[i][q] = red[1];
        def.dataGreen[i][q] = green[1];

      }
      for (i=60; i<90; i++)
      {

        def.dataBlue[i][q] = blue[2];
        def.dataRed[i][q] = red[2];
        def.dataGreen[i][q] = green[2];

      }
    }
  }
  else {
    for (q=0; q<num_leds; q++)
    {
      for (i=0; i<30; i++)
      {

        def.dataBlue[i][q] = !blue[0];
        def.dataRed[i][q] = !red[0];
        def.dataGreen[i][q] = !green[0];

      }
      for (i=30; i<60; i++)
      {

        def.dataBlue[i][q] = !blue[1];
        def.dataRed[i][q] = !red[1];
        def.dataGreen[i][q] = !green[1];

      }
      for (i=60; i<90; i++)
      {

        def.dataBlue[i][q] = !blue[2];
        def.dataRed[i][q] = !red[2];
        def.dataGreen[i][q] = !green[2];

      }
    }
  }
}
*/
#endif