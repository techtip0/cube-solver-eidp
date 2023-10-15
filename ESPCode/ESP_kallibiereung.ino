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



void Kalibrieren() 
{


const int Wertetabelle[][5] = {
  { 0,  0,  0,  0,  1},
  { 0,  0,  0,  0,  2},
  { 0,  0,  0,  0,  3},
  { 0,  0,  0,  0,  4},
  { 0,  0,  0,  0,  5},
  { 0,  0,  0,  0,  6},
};



U2();

uint16_t gelbR1, gelbG1, gelbB1, gelbC1;
  PCA9548A(0);
  tcsKante.getRawData(&r, &g, &b, &c);

U1();

uint16_t gelbR2, gelbG2, gelbB2, gelbC2;
  PCA9548A(0);
  tcsKante.getRawData(&r, &g, &b, &c);

Wertetabelle [1][1]= (gelbR1 + gelbR2) / 2;
Wertetabelle [2][1]= (gelbG1 + gelbG2) / 2;
Wertetabelle [3][1]= (gelbB1 + gelbB2) / 2;
Wertetabelle [4][1]= (gelbC1 + gelbC2) / 2;

U1();
F3();
Bone();
U1();

uint16_t blauR1, blauG1, blauB1, blauC1;
  PCA9548A(0);
  tcsKante.getRawData(&r, &g, &b, &c);

B2();

uint16_t blauR2, blauG2, blauB2, blauC2;
  PCA9548A(0);
  tcsKante.getRawData(&r, &g, &b, &c);

Wertetabelle [1][2]= (blauR1 + blauR2) / 2;
Wertetabelle [2][2]= (blauG1 + blauG2) / 2;
Wertetabelle [3][2]= (blauB1 + blauB2) / 2;
Wertetabelle [4][2]= (blauC1 + blauC2) / 2;

U1();
F2();
B2();
U1();

uint16_t gruenR1, gruenG1, gruenB1, gruenC1;
  PCA9548A(0);
  tcsKante.getRawData(&r, &g, &b, &c);

U2();

uint16_t gruenR2, gruenG2, gruenB2, gruenC2;
  PCA9548A(0);
  tcsKante.getRawData(&r, &g, &b, &c);

Wertetabelle [1][3]= (gruenR1 + gruenR2) / 2;
Wertetabelle [2][3]= (gruenG1 + gruenG2) / 2;
Wertetabelle [3][3]= (gruenB1 + gruenB2) / 2;
Wertetabelle [4][3]= (gruenC1 + gruenC2) / 2;

U1();
F3();
B1();
R1();
L3();
U2();

uint16_t orangeR1, orangeG1, orangeB1, orangeC1;
  PCA9548A(0);
  tcsKante.getRawData(&r, &g, &b, &c);

U2();

uint16_t orangeR2, orangeG2, orangeB2, orangeC2;
  PCA9548A(0);
  tcsKante.getRawData(&r, &g, &b, &c);

Wertetabelle [1][4]= (orangeR1 + orangeR2) / 2;
Wertetabelle [2][4]= (orangeG1 + orangeG2) / 2;
Wertetabelle [3][4]= (orangeB1 + ornageB2) / 2;
Wertetabelle [4][4]= (orangeC1 + orangeC2) / 2;

L2();
R2();
U2();

uint16_t rotR1, rotG1, rotB1, rotC1;
  PCA9548A(0);
  tcsKante.getRawData(&r, &g, &b, &c);

U2();

uint16_t rotR2, rotG2, rotB2, rotC2;
  PCA9548A(0);
  tcsKante.getRawData(&r, &g, &b, &c);

Wertetabelle [1][5]= (rotR1 + rotR2) / 2;
Wertetabelle [2][5]= (rotG1 + rotG2) / 2;
Wertetabelle [3][5]= (rotB1 + rotB2) / 2;
Wertetabelle [4][5]= (rotC1 + rotC2) / 2;

U2();
R3();
L1();
U2();

uint16_t weissR1, weissG1, weissB1, weissC1;
  PCA9548A(0);
  tcsKante.getRawData(&r, &g, &b, &c);

U2();

uint16_t weissR2, weissG2, weissB2, weissC2;
  PCA9548A(0);
  tcsKante.getRawData(&r, &g, &b, &c);

Wertetabelle [1][6]= (weissR1 + weissR2) / 2;
Wertetabelle [2][6]= (weissG1 + weissG2) / 2;
Wertetabelle [3][6]= (weissB1 + weissB2) / 2;
Wertetabelle [4][6]= (weissC1 + weissC2) / 2;

R2();
L2();









}


 