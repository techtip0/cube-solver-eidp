//AccelStepper Library inculdieren
#include <AccelStepper.h>
#include <Wire.h>


//Pins für serielle Verbindung definieren
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
//D1 bedeutet einmal im Uhrzeigersinn, D2 zweimal
//D3 einmal rückwärts
void D3() {
  weiss.move(800);
  weiss.runToPosition();
}
void D2() {
  weiss.move(1600);
  weiss.runToPosition();
}
void D1() {
  weiss.move(-800);
  weiss.runToPosition();
}

void U1() {
  gelb.move(800);
  gelb.runToPosition();
}
void U2() {
  gelb.move(1600);
  gelb.runToPosition();
}
void U3() {
  gelb.move(-800);
  gelb.runToPosition();
}

void L3() {
  gruen.move(800);
  gruen.runToPosition();
}
void L2() {
  gruen.move(1600);
  gruen.runToPosition();
}
void L1() {
  gruen.move(-800);
  gruen.runToPosition();
}

void B3() {
  rot.move(800);
  rot.runToPosition();
}
void B2() {
  rot.move(1600);
  rot.runToPosition();
}
void B1() {
  rot.move(-800);
  rot.runToPosition();
}

void F3() {
  orange.move(800);
  orange.runToPosition();
}
void F2() {
  orange.move(1600);
  orange.runToPosition();
}
void F1() {
  orange.move(-800);
  orange.runToPosition();
}

void R3() {
  blau.move(800);
  blau.runToPosition();
}
void R2() {
  blau.move(1600);
  blau.runToPosition();
}
void R1() {
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

  //String durchgehen und drehen
  for(int i = 0; i <= strVerdreh.length(); i++){
    if (strVerdreh[i] == 'D')
    {
      D1();
    }

    else if (strVerdreh[i] == 'U')
    {
      U1();
    }

    else if (strVerdreh[i] == 'L')
    {
      L1();
    }

    else if (strVerdreh[i] == 'B')
    {
      B1();
    }

    else if (strVerdreh[i] == 'F')
    {
      F1();
    }

    else if (strVerdreh[i] == 'R')
    {
      R1();
    }  
  }
  strVerdreh = "";
}



void setup() {

  //Serielle und I2C Verbindung öffnen
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Wire.begin();

	// Festsetzen der Maximalgeschwinigkeit und Beschleunigungsfaktoren der Motoren
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



void loop ()
{
  Verdrehen();
};