#include <Servo.h>
#include <Ramp.h>

#define BASESERVOPIN A0
#define ARM1SERVOPIN A1
#define ARM2SERVOPIN A2
#define GRIPSERVOPIN A3

Servo arm1servo;
Servo arm2servo;
Servo baseservo;
Servo gripservo;

rampDouble arm1ramp;
rampDouble arm2ramp;
rampDouble baseramp;
rampDouble gripramp;
 
void moveToAngle(double b, double a1, double a2, double g) {
  arm1servo.write(a1);
  arm2servo.write(a2);
  baseservo.write(b);
  gripservo.write(g);
}

void rampToAngle(double b, double a1, double a2, double g, unsigned long t) {
  arm1ramp.go(a1,t, LINEAR, ONCEFORWARD);
  arm2ramp.go(a2,t, LINEAR, ONCEFORWARD);
  baseramp.go(b,t, LINEAR, ONCEFORWARD);
  gripramp.go(g,t, LINEAR, ONCEFORWARD);
  
  while (baseramp.isRunning()) {
    moveToAngle(baseramp.update(),arm1ramp.update(),arm2ramp.update(),gripramp.update());
  }
}


void setup() {
  baseservo.attach(BASESERVOPIN,440 ,2400);
  arm1servo.attach(ARM1SERVOPIN,440 ,2400);
  arm2servo.attach(ARM2SERVOPIN,440 ,2400);
  gripservo.attach(GRIPSERVOPIN,440 ,2400);
  
}

void loop() {
  // you will need to change the coordinates in each of the lines below to ones which work for your arm
  // please use the encoder_arm sketch and serial console to find these out
  
  //move above ball
  rampToAngle(105,129,56,90,3000);
  //lower onto ball
  rampToAngle(105,132,50,90,500);
  //close hand
  rampToAngle(107,133,47,72,500);
  //middle-ish
  rampToAngle(121,101,113,72,500);
  //move over hopper
  rampToAngle(169,127,121,72,1000);
  //move down
  rampToAngle(169,128,113,72,500);
  //open hand
  rampToAngle(169,128,113,90,500);
  //move over hopper
  rampToAngle(169,128,113,90,500);
  //middle-ish
  rampToAngle(121,101,113,90,1000);
  
}
