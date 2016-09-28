// BigNumber test: factorials
#include "Arduino.h"
#include "BigNumber.h"

void setup ()
{
  Serial.begin (115200);
  while (!Serial) ;
  delay(500);
  Serial.println ();
  BigNumber::begin ();  // initialize library

}  // end of setup

void loop ()
{
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
