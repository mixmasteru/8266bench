#include "Arduino.h"
#include "BigNumber.h"
#include "AES.h"

AES aes;
byte plain[] = "Add NodeAdd NodeAdd NodeAdd NodeAdd Node";
byte *key = (unsigned char*)"0123456789010123";
unsigned long long int my_iv = 36753562;

void printArray(byte b[],bool p_pad)
{
    uint8_t i,j;
    uint8_t loops = aes.get_size()/N_BLOCK;
    uint8_t outp = N_BLOCK;
    for (j = 0; j < loops; j += 1){
      if (p_pad && (j == (loops  - 1)) ) { outp = N_BLOCK - aes.get_pad(); }
      for (i = 0; i < outp; i++)
      {
        Serial.print((char)b[j*N_BLOCK + i]);
      }
    }
  }

void prekey (int bits)
{
  aes.iv_inc();
  byte iv [N_BLOCK] ;
  byte plain_p[48];
  byte cipher [48] ;
  byte check [48] ;
  unsigned long ms = micros ();
  aes.set_IV(my_iv);
  aes.get_IV(iv);
  aes.do_aes_encrypt(plain,41,cipher,key,bits,iv);
  Serial.print("Encryption took: ");
  Serial.println(micros() - ms);
  ms = micros ();
  aes.set_IV(my_iv);
  aes.get_IV(iv);
  aes.do_aes_decrypt(cipher,48,check,key,bits,iv);
  Serial.print("Decryption took: ");
  Serial.println(micros() - ms);
  Serial.print("\n\nPLAIN :");
  printArray(plain,true);
  Serial.print("\nCIPHER:");
  printArray(cipher,false);
  Serial.print("\nCHECK :");
  printArray(check,true);
  Serial.print("\nIV    :");
  aes.printArray(iv,16);
  Serial.print("\n============================================================\n");
}



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

  //calcE(283);


}  // end of setup

void loop ()
{
  prekey (128) ;
  delay(2000);
}
