
#include <Encoder.h>
#include <Servo.h>

#define BASESERVOPIN A0
#define ARM1SERVOPIN A1
#define ARM2SERVOPIN A2
#define GRIPSERVOPIN A3

#define GRIPBUTTONPIN 9
#define BASEBUTTONPIN 10
#define ARM1BUTTONPIN 11
#define ARM2BUTTONPIN 12

Encoder myEnc(A6, A7);
Servo arm1servo;
Servo arm2servo;
Servo baseservo;
Servo gripservo;

void setup() {
  // put your setup code here, to run once:
  
  baseservo.attach(BASESERVOPIN,440 ,2400);
  arm1servo.attach(ARM1SERVOPIN,440 ,2400);
  arm2servo.attach(ARM2SERVOPIN,440 ,2400);
  gripservo.attach(GRIPSERVOPIN,440 ,2400);
  
  pinMode(BASEBUTTONPIN,INPUT);
  pinMode(ARM1BUTTONPIN,INPUT);
  pinMode(ARM2BUTTONPIN,INPUT);
  pinMode(GRIPBUTTONPIN,INPUT);
  
  Serial.begin(9600);
}

int arm1Angle  = 90;
int arm2Angle  = 90;
int baseAngle  = 90;
int gripAngle  = 90;

long oldPosition=0;

void writePosSerial() {
  Serial.println((String)baseAngle + "," + arm1Angle + "," + arm2Angle + "," + gripAngle);
}

void loop() {

  int amount=0;
  long newPosition = myEnc.read();
  
  if (newPosition != oldPosition) {
    amount=newPosition-oldPosition;
    oldPosition = newPosition;
  }
   
  if (digitalRead(BASEBUTTONPIN) == HIGH && amount!=0) {
    baseAngle+=amount;
    baseservo.write(baseAngle);
    writePosSerial();
  }

  if (digitalRead(ARM1BUTTONPIN) == HIGH && amount!=0) {
    arm1Angle+=amount;
    arm1servo.write(arm1Angle);
    writePosSerial();
  }

  if (digitalRead(ARM2BUTTONPIN) == HIGH && amount!=0) {
    arm2Angle+=amount;
    arm2servo.write(arm2Angle);
    writePosSerial();
  }
  
  if (digitalRead(GRIPBUTTONPIN) == HIGH && amount!=0) {
    gripAngle+=amount;
    gripservo.write(gripAngle);
    writePosSerial();
  }

}
