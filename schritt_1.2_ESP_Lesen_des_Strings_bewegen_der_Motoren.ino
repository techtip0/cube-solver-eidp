//AccelStepper Library inculdieren
#include <AccelStepper.h>

// Defnieren der Motoren-Pinne

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


// Motor interface typ definieren
#define motorInterfaceType 1

// Motoren als Instancen erstellen
AccelStepper gruen(motorInterfaceType, gruenstepPin, gruendirPin);
AccelStepper weiss(motorInterfaceType, weissstepPin, weissdirPin);
AccelStepper rot(motorInterfaceType, rotstepPin, rotdirPin);
AccelStepper orange(motorInterfaceType, orangestepPin, orangedirPin);
AccelStepper blau(motorInterfaceType, blaustepPin, blaudirPin);
AccelStepper gelb(motorInterfaceType, gelbstepPin, gelbdirPin);


// 90-Grad drehungen aller Seiten in beide richungen als Funktionen definieren
//D bedeutet im Uhrzeigersinn
//DD bedeutet gegen den Uhrzeigersinn
void D() {
  weiss.move(800);
  weiss.runToPosition();
}

void DD() {
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

void L() {
  gruen.move(800);
  gruen.runToPosition();
}

void LL() {
  gruen.move(-800);
  gruen.runToPosition();
}

void B() {
  rot.move(800);
  rot.runToPosition();
}

void BB() {
  rot.move(-800);
  rot.runToPosition();
}

void F() {
  orange.move(800);
  orange.runToPosition();
}

void FF() {
  orange.move(-800);
  orange.runToPosition();
}

void R() {
  blau.move(800);
  blau.runToPosition();
}

void RR() {
  blau.move(-800);
  blau.runToPosition();
}


void setup() {
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


//string wird von Rasberry Pi empfangen

// Definiere
String str = //emfangerner String 

// Lämge des Strings mit einem extraplatz für die 0 definieren 
int str_len = str.length() + 1; 

// Array für Buchstaben erstellen
char char_array[str_len];

// Kopieren des Stings ins array
str.toCharArray(char_array, str_len);

//Durchgegehn aller Buchstaben im array und bewergen des entsprechden Motors 
void loop ()
{
int i = 0;

if (serial.print(char_array[i])= D)
{
  D();
}

else if (serial.print(char_array[i])= U)
{
  U();
}

else if (serial.print(char_array[i])= L)
{
  L();
}

else if (serial.print(char_array[i])= B)
{
  B();
}

else if (serial.print(char_array[i])= F)
{
  F();
}

else if (serial.print(char_array[i])= R)
{
  R();
}

else if (serial.print(char_array[i])= 0)
{
  exit(0)
}

i++;

};