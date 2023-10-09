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




void LoesenVorbereiten() 
{

String CubeSolveString = //hier wird lösungstring emfangen
String Speicherstrg[CubeSolveString.length];
int StringCount = 0;

//Aufteilen den CubeSolveStrings in substrings
while (CubeSolveString.length() > 0)
  {
    int index = CubeSolveString.indexOf(' ');
    if (index == -1)  // Keine Leertaste gefunden
    {
      StringCount++;
      Speicherstrg[StringCount] = CubeSolveString;
      break;
    }
    else
    {
      StringCount++;
      Speicherstrg[StringCount] = CubeSolveString.substring(0, index);
      CubeSolveString = CubeSolveString.substring(index+1);
    }
}

void Loesen()
{

for (int i = 0; i <= StringCount; i++)
{

if (SpeicherString[i] == 'D1')
{
  D1();
}

if (SpeicherString[i] == 'D2')
{
  D2();
}

if (SpeicherString[i] == 'D3')
{
  D3();
}

if (SpeicherString[i] == 'U1')
{
  U1();
}

if (SpeicherString[i] == 'U2')
{
  U2();
}

if (SpeicherString[i] == 'U3')
{
  U3();
}

if (SpeicherString[i] == 'L1')
{
  L1();
}

if (SpeicherString[i] == 'L2')
{
  L2();
}

if (SpeicherString[i] == 'L3')
{
  L3();
}

if (SpeicherString[i] == 'B1')
{
  Bone();
}

if (SpeicherString[i] == 'B2')
{
  B2();
}

if (SpeicherString[i] == 'B3')
{
  B3();
}

if (SpeicherString[i] == 'F1')
{
  F1();
}

if (SpeicherString[i] == 'F2')
{
  F2();
}

if (SpeicherString[i] == 'F3')
{
  F3();
}

if (SpeicherString[i] == 'R1')
{
  R1();
}

if (SpeicherString[i] == 'R2')
{
  R2();
}

if (SpeicherString[i] == 'R3')
{
  R3();
}

}