// BigNumber test: factorials
#include "Arduino.h"
#include "BigNumber.h"

void calcE(int ini)
{
    Serial.println ("--- calcE " +(String) ini+ " ---");
    BigNumber::begin (ini);
    // some big numbers
    BigNumber n = 1, e = 1, one = 1;

    int i = 1;
    BigNumber E;  // previous result

    unsigned long start = millis ();
    do
    {
      E = e;
      n *= i++;  // n is i factorial
      e += one / n;
    }  while (e != E);
    unsigned long time = millis () - start;
    Serial.println (e);
    Serial.print (time);
    Serial.println (" mS");

    BigNumber::finish();
}

void power()
{
  BigNumber::begin ();  // initialize library
  Serial.println ("--- powers of 2 ---");

  BigNumber a = 2;

  for (int i = 1; i <= 600; i++)
  {
    Serial.print ("2^");
    Serial.print (i);
    Serial.print (" = ");
    BigNumber p = a.pow (i);
    Serial.println (p);
  }  // end of for loop

  Serial.println ("--- powers of 3 ---");

  a = 3;

  for (int i = 1; i <= 300; i++)
  {
    Serial.print ("3^");
    Serial.print (i);
    Serial.print (" = ");
    BigNumber p = a.pow (i);
    Serial.println (p);
  }  // end of for loop
}

void setup ()
{
  Serial.begin (115200);
  while (!Serial) ;
  delay(500);
  Serial.println ();
  delay(5000);

  calcE(283);


}  // end of setup

void loop ()
{

}
