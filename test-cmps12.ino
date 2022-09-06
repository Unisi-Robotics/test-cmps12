/*******************************
 * DUE - Master Program
 *******************************/

#define USE_USBCON // USE THIS LINE FOR DUE ONLY

#define CMPS12_ADDRESS 0x60
#define ANGLE_8 1
#define pinProxy 53

#include <Wire.h>

// cmps 12
unsigned int angle16;
unsigned char high_byte, low_byte;
float compass = 0;
float compass_ori = 0;
float compass_point = -1000;


void setup()
{
  Serial.begin(9600);
  Wire.begin();
}

void loop()
{

  getCompass();

  delay(10);
}

// cmps
float getCompass()
{
  Wire.beginTransmission(CMPS12_ADDRESS);
  Wire.write(ANGLE_8);
  Wire.endTransmission();
  Wire.requestFrom(CMPS12_ADDRESS, 5);

  if (Wire.available() == 5)
  {

    Wire.read();
    high_byte = Wire.read();
    low_byte = Wire.read();
    Wire.read();
    Wire.read();

    angle16 = high_byte;
    angle16 <<= 8;
    angle16 += low_byte;

    // set compass range to 0-180
    float cps = angle16 / 10.0 + (float(angle16 % 10)) / 10.0;

    compass_ori = cps;

    if (compass_point == -1000)
    {
      compass_point = cps;
    }
    else
    {
      cps = compass_point - cps;
      if (cps < 0.0)
      {
        cps = 359.9 + cps;
      }
    }

    if (cps > 180)
    {
      cps = cps - 360.0;
    }

    compass = -cps;

    Serial.println(compass);
  }
}
