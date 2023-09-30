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

void Scan()
{

string CubeDefinitionString = "XXXXUXXXXXXXXRXXXXXXXXFXXXXXXXXDXXXXXXXXLXXXXXXXXBXXXX";   //Erstellen eines Cube Strings im Richtigen Format; dieser wird als Input für den Lösealgorythmus genutzt
                                                                                          //X als Platzhalter für eingelsenen Werte

CubeDefinitionString.setCharAt(5, 'ScanKante');        //Austauschen der Platzhalter an den richtigen Stellen im String gegen die eingescannten Werte
CubeDefinitionString.setCharAt(0, 'ScanEcke');         //Das Austauschen und das Drehen erfolgt nach einer vorher festgelegten Sequenz und Prositionen

U();                                                  //Drehen des Würfels damit alle Sticker eingescannt werden

CubeDefinitionString.setCharAt(1, 'ScanKante');
CubeDefinitionString.setCharAt(6, 'ScanEcke');

U();

CubeDefinitionString.setCharAt(3, 'ScanKante');
CubeDefinitionString.setCharAt(8, 'ScanEcke');

U();

CubeDefinitionString.setCharAt(7, 'ScanKante');
CubeDefinitionString.setCharAt(2, 'ScanEcke');

U();
R();
LL();

CubeDefinitionString.setCharAt(23, 'ScanKante');
CubeDefinitionString.setCharAt(18, 'ScanEcke');

U();
U();

CubeDefinitionString.setCharAt(21, 'ScanKante');
CubeDefinitionString.setCharAt(26, 'ScanEcke');

U();
U();
RR();
L();
FFFF();
R();
LL();

CubeDefinitionString.setCharAt(19, 'ScanKante');
CubeDefinitionString.setCharAt(24, 'ScanEcke');

U();
U();

CubeDefinitionString.setCharAt(25, 'ScanKante');
CubeDefinitionString.setCharAt(20, 'ScanEcke');

U();
U();
RR();
L(),
FF();
R();
R();
L();
L();

CubeDefinitionString.setCharAt(32, 'ScanKante');
CubeDefinitionString.setCharAt(27, 'ScanEcke');

U();
U();

CubeDefinitionString.setCharAt(30, 'ScanKante');
CubeDefinitionString.setCharAt(35, 'ScanEcke');

U();
U();
R();
R();
L();
L();
D();
R();
R();
L();
L();

CubeDefinitionString.setCharAt(28, 'ScanKante');
CubeDefinitionString.setCharAt(33, 'ScanEcke');

U();
U();

CubeDefinitionString.setCharAt(34, 'ScanKante');
CubeDefinitionString.setCharAt(29, 'ScanEcke');

U();
U();
R();
R();
L();
L();
DD();
RR();
L();

CubeDefinitionString.setCharAt(48, 'ScanKante');
CubeDefinitionString.setCharAt(53, 'ScanEcke');

U();
U();

CubeDefinitionString.setCharAt(50, 'ScanKante');
CubeDefinitionString.setCharAt(45, 'ScanEcke');

U();
U();
R();
LL();
B();
RR();
L();

CubeDefinitionString.setCharAt(52, 'ScanKante');
CubeDefinitionString.setCharAt(47, 'ScanEcke');

U();
U();

CubeDefinitionString.setCharAt(46, 'ScanKante');
CubeDefinitionString.setCharAt(51, 'ScanEcke');

U();
U();
R();
LL();
BB();
BB();
FFFF();
U();

CubeDefinitionString.setCharAt(39, 'ScanKante');
CubeDefinitionString.setCharAt(44, 'ScanEcke');

U();
U();

CubeDefinitionString.setCharAt(41, 'ScanKante');
CubeDefinitionString.setCharAt(36, 'ScanEcke');

U();
FF();
B();
L();
FFFF();
BB();
U();

CubeDefinitionString.setCharAt(43, 'ScanKante');
CubeDefinitionString.setCharAt(38, 'ScanEcke');

U();
U();

CubeDefinitionString.setCharAt(37, 'ScanKante');
CubeDefinitionString.setCharAt(42, 'ScanEcke');

U();
FF();
B();
LL();
FF();
B();
U();

CubeDefinitionString.setCharAt(14, 'ScanKante');
CubeDefinitionString.setCharAt(9, 'ScanEcke');

U();
U();

CubeDefinitionString.setCharAt(12, 'ScanKante');
CubeDefinitionString.setCharAt(17, 'ScanEcke');

U();
FFFF();
BB();
R();
FF();
B();
U();

CubeDefinitionString.setCharAt(10, 'ScanKante');
CubeDefinitionString.setCharAt(24, 'ScanEcke');

U();
U();

CubeDefinitionString.setCharAt(16, 'ScanKante');
CubeDefinitionString.setCharAt(11, 'ScanEcke');

U();
FFFF();
BB();
RR();

}