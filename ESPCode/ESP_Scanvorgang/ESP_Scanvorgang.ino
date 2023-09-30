//AccelStepper Library inculdieren
#include <AccelStepper.h>

#define RXD2 16
#define TXD2 17

char KanteScan();
char EckeScan();

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


//Funktion zum warten via Millis(), da delay() ESP32 blockiert
void warten(long intervall){
  unsigned long currentMillis = millis();
  unsigned long previousMillis = millis();
  while(currentMillis - previousMillis < intervall){
    currentMillis = millis();
  }
}


// 90-Grad drehungen aller Seiten in beide Richungen als Funktionen definieren
//D bedeutet im Uhrzeigersinn
//DD bedeutet gegen den Uhrzeigersinn
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
void Bone() {
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

void Scan()
{

  String CubeDefinitionString = "XXXXUXXXXXXXXRXXXXXXXXFXXXXXXXXDXXXXXXXXLXXXXXXXXBXXXX";   //Erstellen eines Cube Strings im Richtigen Format; dieser wird als Input für den Lösealgorythmus genutzt
                                                                                            //X als Platzhalter für eingelsenen Werte

  CubeDefinitionString.setCharAt(5, KanteScan());        //Austauschen der Platzhalter an den richtigen Stellen im String gegen die eingescannten Werte
  warten(1000);                                           //Kurzer Delay, um Multiplexer und Farbsensor Zeit zu geben
  CubeDefinitionString.setCharAt(0, EckeScan());         //Das Austauschen und das Drehen erfolgt nach einer vorher festgelegten Sequenz und Prositionen

  U1();                                                 //Drehen des Würfels damit alle Sticker eingescannt werden
  warten(1000);

  CubeDefinitionString.setCharAt(1, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(6, EckeScan());

  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(3, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(8, EckeScan());

  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(7, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(2, EckeScan());

  U1();
  R1();
  L3();
  warten(1000);

  CubeDefinitionString.setCharAt(23, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(18, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(21, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(26, EckeScan());

  U2();
  R3();
  L1();
  F1();
  R1();
  L3();
  warten(1000);

  CubeDefinitionString.setCharAt(19, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(24, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(25, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(20, EckeScan());

  U2();
  R3();
  L1();
  F3();
  R2();
  L2();
  warten(1000);

  CubeDefinitionString.setCharAt(32, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(27, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(30, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(35, EckeScan());

  U2();
  R1();
  L2();
  D1();
  R2();
  L2();
  warten(1000);

  CubeDefinitionString.setCharAt(28, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(33, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(34, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(29, EckeScan());

  U2();
  R2();
  L2();
  D3();
  R3();
  L1();
  warten(1000);

  CubeDefinitionString.setCharAt(48, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(53, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(50, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(45, EckeScan());

  U2();
  R1();
  L3();
  Bone();
  R3();
  L1();
  warten(1000);

  CubeDefinitionString.setCharAt(52, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(47, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(46, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(51, EckeScan());

  U2();
  R1();
  L3();
  B3();
  B3();
  F1();
  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(39, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(44, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(41, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(36, EckeScan());

  U1();
  F3();
  Bone();
  L1();
  F1();
  B3();
  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(43, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(38, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(37, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(42, EckeScan());

  U1();
  F3();
  Bone();
  L3();
  F3();
  Bone();
  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(14, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(9, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(12, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(17, EckeScan());

  U1();
  F1();
  B3();
  R1();
  F3();
  Bone();
  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(10, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(15, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(16, KanteScan());
  CubeDefinitionString.setCharAt(11, EckeScan());

  U1();
  F1();
  B3();
  R3();

  Serial2.print(CubeDefinitionString + "\n");


}

void setup(){

}

void loop(){

}