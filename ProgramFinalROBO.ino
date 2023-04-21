#include <AFMotor.h>
#include <IRremote.h>
#include <Servo.h>

Servo myservo; 
int i=0;

const int TRIGGER_PIN1 = A0;
const int ECHO_PIN1 = A1;

const int TRIGGER_PIN2 = A2;
const int ECHO_PIN2 = A3;

const int TRIGGER_PIN3 = A4;
const int ECHO_PIN3 = A5;

AF_DCMotor motor1(3);
AF_DCMotor motor2(4);

int Speed = 250;
int Speedjaloane = 150;
int Speedviraj = 130;

void setup(){
  Serial.begin(9600);
   motor1.setSpeed(Speed);
  motor2.setSpeed(Speed);
   pinMode (TRIGGER_PIN1, OUTPUT);
  pinMode (ECHO_PIN1, INPUT);
   pinMode (TRIGGER_PIN2, OUTPUT);
  pinMode (ECHO_PIN2, INPUT);
   pinMode (TRIGGER_PIN3, OUTPUT);
   IrReceiver.begin(9);
  myservo.attach(10);
  pinMode (ECHO_PIN3, INPUT);
   myservo.write(65);
}

void loop(){
   if (IrReceiver.decode()) {
    IrReceiver.resume();
    int command = IrReceiver.decodedIRData.command;
    Serial.println(command);
    switch (command) {
        
         case 24:            //  FORWARD Button
            Inainte(Speed);
            break;
 
         case 8:            //  LEFT Button
            Stanga(Speed);
            break;   
 
         case 90:            //  RIGHT Button
            Dreapta(Speed);
            break;
 
         case 82:            //  BACK Button
            Inapoi(Speed);
            break;
        
         case 28:            // STOP Button
            Stop();
            break;

          case 69:
          Jaloane();
          command=0;
          break;

          case 70:
          Jaloane2();
          command=0;
          break;

          case 71:
          Ocolire();
          command=0;
          break;

    } 
   }
  }

void Inainte(int Speed)
{
  motor1.setSpeed(Speed);
  motor2.setSpeed(Speed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}
void Inapoi(int Speed)
{
  motor1.setSpeed(Speed);
  motor2.setSpeed(Speed);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
}
void Stanga(int Speed)
{
  motor1.setSpeed(Speed);
  motor2.setSpeed(Speed);
  motor1.run(FORWARD);
  motor2.run(RELEASE);
}
void Dreapta(int Speed)
{
  motor1.setSpeed(Speed);
  motor2.setSpeed(Speed);
  motor1.run(RELEASE);
  motor2.run(FORWARD);
}

void Stop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

float DistantaS1()
{
   unsigned long duration;
  float distance;
  digitalWrite(TRIGGER_PIN1, HIGH);
  delayMicroseconds(1000);
  digitalWrite(TRIGGER_PIN1, LOW);
  duration = pulseIn (ECHO_PIN1, HIGH);
  distance = (duration / 2.0) / 29.0;
  //Serial.print("d1 = ");
  //Serial.print(distance);
  //Serial.println(" cm");
  return distance;
}

float DistantaS3()
{
  unsigned long duration;
  float distance;
  digitalWrite(TRIGGER_PIN2, HIGH);
  delayMicroseconds(1000);
  digitalWrite(TRIGGER_PIN2, LOW);
  duration = pulseIn (ECHO_PIN2, HIGH);
  distance = (duration / 2.0) / 29.0;
 //Serial.print("d2 = ");
 //Serial.print(distance);
 //Serial.println(" cm");
  return distance;
}

float DistantaS2()
{
  unsigned long duration;
  float distance;
  digitalWrite(TRIGGER_PIN3, HIGH);
  delayMicroseconds(1000);
  digitalWrite(TRIGGER_PIN3, LOW);
  duration = pulseIn (ECHO_PIN3, HIGH);
  distance = (duration / 2.0) / 29.0;
  //Serial.print("d3 = ");
  //Serial.print(distance);
  //Serial.println(" cm");
  return distance;
}

void Jaloane()
{  
  Apropiere();
  OcolireDreapta();
  OcolireStanga();
}

void Jaloane2()
{
    delay(2000);   
    while(DistantaS1() >= 30)
    Inainte(Speedjaloane);
    Stop();
    delay(2000);
    while(DistantaS1()<=50)
    Dreapta(Speedviraj);
    Stop();
    delay(2000);
    while(DistantaS2()>=30)
    Inainte(Speedjaloane);
    Stop();
    delay(2000);
    while(DistantaS2()<=20) 
    Inainte(Speedjaloane);
    Stop();
    delay(2000);   
    while(DistantaS1()>=50)
    Stanga(Speedviraj);
    Stop();
    delay(2000);
    while(DistantaS1()<=90)
    Stanga(Speedviraj);
    Stop();
    delay(2000);
    while(DistantaS3()>=30)
    Inainte(Speedjaloane);
    Stop();
    delay(2000);
    while(DistantaS3()<=30)
    Inainte(Speedjaloane);
    Stop();
    delay(2000);
    while(DistantaS1()>=50)
    Dreapta(Speedviraj);
    Stop();
    delay(2000);
    while(DistantaS3()<=30)
    Inainte(Speedjaloane);
    Stop();
    delay(2000);
}

void Ocolire()
{
  while(DistantaS1()>=30)
  Inainte(Speedjaloane);
  Stop();
  delay(1000);
  while(DistantaS2()>=30)
  Dreapta(Speedviraj);
  Stop();
  delay(1000);
   while(DistantaS2() <=40)
        Inainte(Speedjaloane);
        delay(1000);
        Stop();
        delay(1000);
        myservo.write(130);
        while (DistantaS1() >=30)
        Stanga(Speedviraj);
        Stop();
        delay(1000);
        while(DistantaS2() >=30)
        Inainte(Speedjaloane);
        Stop();
        delay(1000);
        while(DistantaS2() <=30)
        Inainte(Speedjaloane);
        Stop();
        delay(1000);
        while(DistantaS1() >=30)
        Stanga(Speedviraj);
        Stop();
        while(DistantaS2() >=50)
        Inainte(Speedjaloane);
        Stop();
}

void Apropiere()
{
  while(DistantaS1()>=30)
  Inainte(Speedjaloane);
  Stop();
  delay(1000);
  while(DistantaS2()>=30)
  Dreapta(Speedviraj);
  Stop();
  delay(1000);
}

void OcolireDreapta()
{
        while(DistantaS2() <=40)
        Inainte(Speedjaloane);
        delay(1000);
        Stop();
        delay(1000);
        myservo.write(130);
        while (DistantaS1() >=30)
        Stanga(Speedviraj);
        Stop();
        delay(1000);
        while(DistantaS2() >=30)
        Inainte(Speedjaloane);
        Stop();
        delay(1000);
        while(DistantaS2() <=30)
        Inainte(Speedjaloane);
        Stop();
        delay(1000);
        while(DistantaS1() >=30)
        Stanga(Speedviraj);
        Stop();
        while(DistantaS2() >=50)
        Inainte(Speedjaloane);
        Stop();
}

void OcolireStanga()
{
     while(DistantaS3() <=40)
        Inainte(Speedjaloane);
        delay(1000);
        Stop();
        delay(1000);
        myservo.write(20);
        while (DistantaS1() >=30)
        Dreapta(Speedviraj);
        Stop();
        delay(1000);
        while(DistantaS3() >=30)
        Inainte(Speedjaloane);
        Stop();
        delay(1000);
        while(DistantaS3() <=30)
        Inainte(Speedjaloane);
        Stop();
        delay(1000);
        while(DistantaS1() >=30)
        Dreapta(Speedviraj);
        Stop();
        while(DistantaS3() >=50)
        Inainte(Speedjaloane);
        Stop();
}

