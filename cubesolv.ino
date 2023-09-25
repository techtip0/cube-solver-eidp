// Include the AccelStepper Library
#include <AccelStepper.h>

// Define pin connections

const int gruendirPin = 14;
const int gruenstepPin = 27;

const int weissdirPin = 5;
const int weissstepPin = 17;

const int rotdirPin = 13;
const int rotstepPin = 12;

const int orangedirPin = 2;
const int orangestepPin = 15;

const int blaudirPin = 33;
const int blaustepPin = 32;

const int gelbdirPin = 26;
const int gelbstepPin = 25;


// Define motor interface type
#define motorInterfaceType 1

// Creates an instance
AccelStepper gruen(motorInterfaceType, gruenstepPin, gruendirPin);
AccelStepper weiss(motorInterfaceType, weissstepPin, weissdirPin);
AccelStepper rot(motorInterfaceType, rotstepPin, rotdirPin);
AccelStepper orange(motorInterfaceType, orangestepPin, orangedirPin);
AccelStepper blau(motorInterfaceType, blaustepPin, blaudirPin);
AccelStepper gelb(motorInterfaceType, gelbstepPin, gelbdirPin);

void weissL() {
  weiss.move(800);
  weiss.runToPosition();
}

void weissR() {
  weiss.move(-800);
  weiss.runToPosition();
}

void gelbL() {
  gelb.move(800);
  gelb.runToPosition();
}

void gelbR() {
  gelb.move(-800);
  gelb.runToPosition();
}

void gruenL() {
  gruen.move(800);
  gruen.runToPosition();
}

void gruenR() {
  gruen.move(-800);
  gruen.runToPosition();
}

void rotL() {
  rot.move(800);
  rot.runToPosition();
}

void rotR() {
  rot.move(-800);
  rot.runToPosition();
}

void orangeL() {
  orange.move(800);
  orange.runToPosition();
}

void orangeR() {
  orange.move(-800);
  orange.runToPosition();
}

void blauL() {
  blau.move(800);
  blau.runToPosition();
}

void blauR() {
  blau.move(-800);
  blau.runToPosition();
}

void setup() {
	// set the maximum speed, acceleration factor,
	// initial speed and the target position
	gruen.setMaxSpeed(20000);
	gruen.setAcceleration(10000);
	gruen.setSpeed(20000);
	

  weiss.setMaxSpeed(20000);
	weiss.setAcceleration(10000);
	weiss.setSpeed(20000);

  rot.setMaxSpeed(20000);
	rot.setAcceleration(10000);
	rot.setSpeed(20000);


  orange.setMaxSpeed(20000);
	orange.setAcceleration(10000);
	orange.setSpeed(20000);


  blau.setMaxSpeed(20000);
	blau.setAcceleration(10000);
	blau.setSpeed(20000);


  gelb.setMaxSpeed(20000);
	gelb.setAcceleration(10000);
	gelb.setSpeed(20000);




}

void loop() {

  weissL();
  gruenR();
  weissL();
  blauR();
  rotL();
  rotL();
  weissR();
  orangeR();
  gelbL();
  gruenL();
  gelbR();

  gelbL();
  gruenR();
  gelbR();
  orangeL();
  weissL();
  rotR();
  rotR();
  blauL();
  weissR();
  gruenL();
  weissR();
 
}