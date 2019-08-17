#include <SPI.h>
#include<Thread.h>
Thread u1=Thread();
Thread u2=Thread();
Thread u12=Thread();
Thread up1=Thread();
Thread up2=Thread();
//Thread u22=Thread();
Thread up12=Thread();
#include <PCM.h>
#include "SD.h"
#define SD_ChipSelectPin 4
#include "TMRpcm.h"
#include "SPI.h"
TMRpcm tmrpcm;


const int trigPin = 6;
const int echoPin = 7;
const int trigPin1 = 9;
const int echoPin1 = 10;
//int ledPir = 5;                // choose the pin for the LED
int pirOut = 5; 
int val = 0,f1=0,f2=0,f12=0,fp1=0,fp2=0,fp12=0; 
int pirState = LOW;            // we start, assuming no motion detected
//int ledUlt1 = 5;
long int z=0,m1=0,m2=0,m12=0,mp1=0,mp2=0,mp12=0;
// defines variables
long duration, duration1;
int distance,distance1;
void setup() {
tmrpcm.speakerPin = 8;
tmrpcm.setVolume(5);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); 
pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin1, INPUT);// Sets the echoPin as an Input
//pinMode(ledPir, OUTPUT);      // declare LED as output
//pinMode(pirOut, INPUT);
//pinMode(ledUlt1, OUTPUT);
//startPlayback(sample, sizeof(sample));
u1.onRun(right1);
u2.onRun(left1);
u12.onRun(slow1);
up1.onRun(right2);
up2.onRun(left2);
up12.onRun(slow2);
Serial.begin(9600);
if (!SD.begin(SD_ChipSelectPin)) {
Serial.println("SD fail");
return;
}
 // Starts the serial communication
}

void loop() {
  // Clears the trigPin
digitalWrite(trigPin, LOW);

delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);

delayMicroseconds(10);
digitalWrite(trigPin, LOW);


// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

distance= duration*0.034/2;

digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
duration1 = pulseIn(echoPin1, HIGH);

// Calculating the distance
distance1= duration1*0.034/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
Serial.print("Distance1: ");
Serial.println(distance1);

  val = digitalRead(pirOut); 

   Serial.println(z);
   Serial.print("v ");
   Serial.println(val);
val=LOW;

  if (val == HIGH )
  {
    if(pirState==LOW)
    {              
    if( distance <80 && distance1<80)
    {
      if(fp12==0)
      {
      up12.run();
      fp12=1;
      mp12=z;
      }
      else
      {
        if( up12.enabled!=true)
        {
        up12.run();
        mp12=z;
        }
      }  
    }
    else if(distance<80)
    {
      if(fp1==0&&u1.enabled==false)
      {
      up1.run();
      fp1=1;
      mp1=z;
      }
      else
      {
        if( up1.enabled!=true&&u1.enabled==false)
        {
        up1.run();
        mp1=z;
        }
      }  
    }
      else if(distance1<80)
      {
        if(fp2==0 &&u2.enabled==false)
      {
      up2.run();
      fp2=1;
      mp2=z;
      }
      else
      {
        if( up2.enabled!=true&&u2.enabled==false)
        {
        up2.run();
        mp2=z;
        }
      }  
      }
      else
            Serial.println(" ");

      pirState = HIGH;
    }
    }
   
  else 
  {

  
   // digitalWrite(ledPir, LOW); // turn LED OFF
    if (pirState == HIGH)
    {
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }

if(!(distance < 80 && distance1 < 80))
{ 
    if(distance < 80  )
    {
      if(f1==0 && up1.enabled==false&&m12==0)
      {
      u1.run();
      f1=1;
      m1=z;
      }
      else
      {
        if( u1.enabled!=true && up1.enabled==false&&m12==0)
        {
        u1.run();
        m1=z;
        }
      }
      }

    

    if(distance1 < 80 )
    {
    if(f2==0 && mp2==0&&m12==0)
      {
      u2.run();
      f2=1;
      m2=z;
      }
      else
      {
        if( u2.enabled!=true && mp2==0&&m12==0)
        {
        u2.run();
        m2=z;
        }
      }
    }
}
     else if(distance < 80 && distance1 < 80 )
     {
      if(f12==0)
      {
      u12.run();
      f12=1;
      m12=z;
      }
      else
      {
        if( u12.enabled!=true)
        {
        u12.run();
        m12=z;
        }
      }
     }
  }
if((z-m1)==60)
{
u1.enabled=false;
m1=0;
}
if((z-m2)==60)
{
u2.enabled=false;
m2=0;
}
   
 if((z-m12)==60)
{
u12.enabled=false;
m12=0;
}




if((z-mp1)==60)
{
up1.enabled=false;
mp1=0;
}
if((z-mp2)==60)
{
up2.enabled=false;
mp2=0;
}
   
 if((z-mp12)==60)
{
up12.enabled=false;
mp12=0;
}
           // u12.run();

 // }
  delay(2);
z= z+1;
}

void right1()
{
 
  u2.enabled=false;
  u12.enabled=false;
  up2.enabled=false;
  up12.enabled=false;
  up1.enabled=false;
  u1.enabled=true;
     Serial.println("helooooooooooo ");

  tmrpcm.play("right.wav");
 // delay(1000);
  long int d=0;
  while(u1.enabled)
        d=d+1;
  
}

void left1()
{
   u2.enabled=true;
  u12.enabled=false;
  up2.enabled=false;
  up12.enabled=false;
  up1.enabled=false;
  u1.enabled=false;
       Serial.println("kjdfgoashpijhdaslJLSD ");

  tmrpcm.play("left.wav");
 // delay(1000);
  long int d=0;
  while(u2.enabled)
    d=d+1;
   
}
void slow1()
{
  u2.enabled=false;
  u12.enabled=true;
  up2.enabled=false;
  up12.enabled=false;
  up1.enabled=false;
  u1.enabled=false;
  tmrpcm.play("slow.wav");
  long int d=0;
  while(u12.enabled)
    d=d+1;
  }

void right2()
{
   u2.enabled=false;
  u12.enabled=false;
  up2.enabled=false;
  up12.enabled=false;
  up1.enabled=true;
  u1.enabled=false;
  tmrpcm.play("right.wav");
  long int d=0;
  while(up1.enabled)
    d=d+1;

}
void left2()
{
   u2.enabled=false;
  u12.enabled=false;
  up2.enabled=true;
  up12.enabled=false;
  up1.enabled=false;
  u1.enabled=false;
  tmrpcm.play("left.wav");
  long int d=0;
  while(up2.enabled)
    d=d+1;
}

void slow2()
{
  u2.enabled=false;
  u12.enabled=false;
  up2.enabled=false;
  up12.enabled=true;
  up1.enabled=false;
  u1.enabled=false;
  tmrpcm.play("slow.wav");
  long int d=0;
  while(up12.enabled)
    d=d+1;

  }

