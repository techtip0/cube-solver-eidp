//AccelStepper Library inculdieren
#include <AccelStepper.h>

#define RXD2 16
#define TXD2 17

// Defnieren der Motoren-Pinne

const int gruendirPin = 14;
const int gruenstepPin = 27;

const int weissdirPin = 18;
const int weissstepPin = 5;

const int rotdirPin = 13;
const int rotstepPin = 12;

const int orangedirPin = 2;
const int orangestepPin = 15;

const int blaudirPin = 33;
const int blaustepPin = 32;

const int gelbdirPin = 26;
const int gelbstepPin = 25;


// Motor interface typ definieren
#define motorInterfaceType 1

// Motoren als Instancen erstellen
AccelStepper gruen(motorInterfaceType, gruenstepPin, gruendirPin);
AccelStepper weiss(motorInterfaceType, weissstepPin, weissdirPin);
AccelStepper rot(motorInterfaceType, rotstepPin, rotdirPin);
AccelStepper orange(motorInterfaceType, orangestepPin, orangedirPin);
AccelStepper blau(motorInterfaceType, blaustepPin, blaudirPin);
AccelStepper gelb(motorInterfaceType, gelbstepPin, gelbdirPin);


// 90-Grad drehungen aller Seiten in beide Richungen als Funktionen definieren
//D bedeutet im Uhrzeigersinn
//DD bedeutet gegen den Uhrzeigersinn
void DD() {
  weiss.move(800);
  weiss.runToPosition();
}

void D() {
  weiss.move(-800);
  weiss.runToPosition();
}

void U() {
  gelb.move(800);
  gelb.runToPosition();
}

void UU() {
  gelb.move(-800);
  gelb.runToPosition();
}

void LL() {
  gruen.move(800);
  gruen.runToPosition();
}

void L() {
  gruen.move(-800);
  gruen.runToPosition();
}

void BB() {
  rot.move(800);
  rot.runToPosition();
}

void B() {
  rot.move(-800);
  rot.runToPosition();
}

void FF() {
  orange.move(800);
  orange.runToPosition();
}

void FFFF() {
  orange.move(-800);
  orange.runToPosition();
}

void RR() {
  blau.move(800);
  blau.runToPosition();
}

void R() {
  blau.move(-800);
  blau.runToPosition();
}


String RPiEmpfangen(){
  while (Serial2.available() == 0){}
  String received = Serial2.readString();
  received.trim();
  return received;
}




void Verdrehen()
{
  //string wird von Rasberry Pi empfangen


  // Definiere String
  String strVerdreh = RPiEmpfangen();


  for(int i = 0; i <= strVerdreh.length(); i++){
    if (strVerdreh[i] == 'D')
    {
      D();
    }

    else if (strVerdreh[i] == 'U')
    {
      U();
    }

    else if (strVerdreh[i] == 'L')
    {
      L();
    }

    else if (strVerdreh[i] == 'B')
    {
      B();
    }

    else if (strVerdreh[i] == 'F')
    {
      FFFF();
    }

    else if (strVerdreh[i] == 'R')
    {
      R();
    }  
  }
  strVerdreh = "";
}



void setup() {
	// Festsetzen der Maximalgeschwinigkeit und Beschleunigungsfaktoren der Motoren
	// initial speed and the target position
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);


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



void loop ()
{
  Verdrehen();
};