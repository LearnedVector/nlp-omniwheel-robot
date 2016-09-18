#include <Wire.h>

unsigned char DeAd, MoAd, SSd, Update, c ;
unsigned char Temp, M0, M1, M2, M3, SPD;
void MotorControl(unsigned char Motion, unsigned char Spd);
void Movement(unsigned char Vx, unsigned char Vy, unsigned char Om);


void setup()
{
  Serial.begin(9600);
  //Trig=0;
  //Data1=0;
  //Data2=0;
  Update=0;
  Wire.begin();
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  delay(50);
}

void loop()
{ 
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  delay(1);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  if (Serial.available()>0)
  {
    if (c==4)
    {
     c=0; 
    }
    c=c+1;
    Update=1;
    Temp=Serial.read();
    Serial.print("Temp: ");
    Serial.println(Temp, HEX);
    switch (Temp)
    {
    case 0x01: //Motor 0 - Forwawrd
      M0=0x01;
      break;
    case 0x02: //Motir 0 - Backward
      M0=0x02;
      break;

    case 0x05: //Motor 1 - Forwawrd
      M1=0x05;
      break;
    case 0x06: //Motir 1 - Backward
      M1=0x06;
      break;

    case 0x09: //Motor 2 - Forwawrd
      M2=0x09;
      break;
    case 0x0A: //Motir 2 - Backward
      M2=0x0A;
      break;

    case 0x0D: //Motor 3 - Forwawrd
      M3=0x0D;
      break;
    case 0x0E: //Motir 3 - Backward
      M3=0x0E;
      break;   
    }
  }
  else
  {
    SPD=Temp;
  }

  if ((Update==1)  && (c==4))
  {
    Update=0;
    Serial.print("M0: ");
    Serial.println(M0, HEX);
    Serial.print("M1: ");
    Serial.println(M1, HEX);
    Serial.print("M2: ");
    Serial.println(M2, HEX);
    Serial.print("M3: ");
    Serial.println(M3, HEX);

  }

    for (unsigned char i=0; i<=50; i++)
    {
      MotorControl(M0, SPD);
      MotorControl(M1, SPD);
      MotorControl(M2, SPD);
      MotorControl(M3, SPD);
    }

}


void MotorControl(unsigned char Motion, unsigned char Spd)
{
  unsigned char Dir;
  switch (Motion)
  {
  case 0x01: //Motor 0 - Forwawrd
    DeAd = 0x0F; //Device 1
    MoAd = 0xA1; //Motor selection
    Dir = 0b01;
    break;
  case 0x02: //Motir 0 - Backward
    DeAd = 0x0F; //Device 1
    MoAd = 0xA1; //Motor selection
    Dir = 0b10;
    break;

  case 0x05: //Motor 1 - Forwawrd
    DeAd = 0x0F; //Device 1
    MoAd = 0xA5; //Motor selection
    Dir = 0b01;
    break;
  case 0x06: //Motir 1 - Backward
    DeAd = 0x0F; //Device 1
    MoAd = 0xA5; //Motor selection
    Dir = 0b10;
    break;

  case 0x09: //Motor 2 - Forwawrd
    DeAd = 0x0E; //Device 2
    MoAd = 0xA1; //Motor selection
    Dir = 0b01;
    break;
  case 0x0A: //Motir 2 - Backward
    DeAd = 0x0E; //Device 2
    MoAd = 0xA1; //Motor selection
    Dir = 0b10;
    break;

  case 0x0D: //Motor 3 - Forwawrd
    DeAd = 0x0E; //Device 2
    MoAd = 0xA5; //Motor selection
    Dir = 0b01;
    break;
  case 0x0E: //Motir 3 - Backward
    DeAd = 0x0E; //Device 2
    MoAd = 0xA5; //Motor selection
    Dir = 0b10;
    break;
  }

  Wire.beginTransmission(DeAd); // Device address
  Wire.write(MoAd);   // which motor? M1= M2=
  Wire.write(Dir);    // motor direction, forward=0b01, reverse=0b10
  Wire.write(Spd);      // speed 0->0xFF
  Wire.endTransmission(); //
}

