//AccelStepper Library inculdieren
#include <AccelStepper.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"


//Pins für serielle Verbindung definieren
#define RXD2 16 
#define TXD2 17

//initialisierung beider Farbsensoren
Adafruit_TCS34725 tcsKante = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_TCS34725 tcsEcke = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

//Funktion zur Auswahl des Multiplexerkanals
void PCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // PCA9548A addresse ist 0x70
  Wire.write(1 << bus);          //Byte senden zur Auswahl des Kanals
  Wire.endTransmission();
}



int SamplesKante[6][5] = {
  { 0,  0,  0,  0,  1},
  { 0,  0,  0,  0,  2},
  { 0,  0,  0,  0,  3},
  { 0,  0,  0,  0,  4},
  { 0,  0,  0,  0,  5},
  { 0,  0,  0,  0,  6},
};

int SamplesEcke[6][5] = {
  { 0,  0,  0,  0,  1},
  { 0,  0,  0,  0,  2},
  { 0,  0,  0,  0,  3},
  { 0,  0,  0,  0,  4},
  { 0,  0,  0,  0,  5},
  { 0,  0,  0,  0,  6},
};

void Kalibrieren(int (*SamplesKante)[6][5], int (*SamplesEcke)[6][5]) 
{



  U2();
  warten(1000);
  uint16_t gelbR1, gelbG1, gelbB1, gelbC1;

  PCA9548A(0);
  tcsKante.getRawData(&gelbR1, &gelbG1, &gelbB1, &gelbC1);

  warten(1000);
  uint16_t EgelbR1, EgelbG1, EgelbB1, EgelbC1;
  PCA9548A(1);
  tcsEcke.getRawData(&EgelbR1, &EgelbG1, &EgelbB1, &EgelbC1);

  U1();

  uint16_t gelbR2, gelbG2, gelbB2, gelbC2;
  PCA9548A(0);
  tcsKante.getRawData(&gelbR2, &gelbG2, &gelbB2, &gelbC2);

  warten(1000);
  uint16_t EgelbR2, EgelbG2, EgelbB2, EgelbC2;
  PCA9548A(1);
  tcsEcke.getRawData(&EgelbR2, &EgelbG2, &EgelbB2, &EgelbC2);

  *SamplesKante[0][0]= (gelbR1 + gelbR2) / 2;
  *SamplesKante[0][1]= (gelbG1 + gelbG2) / 2;
  *SamplesKante[0][2]= (gelbB1 + gelbB2) / 2;
  *SamplesKante[0][3]= (gelbC1 + gelbC2) / 2;

  *SamplesEcke[0][0]= (EgelbR1 + EgelbR2) / 2;
  *SamplesEcke[0][1]= (EgelbG1 + EgelbG2) / 2;
  *SamplesEcke[0][2]= (EgelbB1 + EgelbB2) / 2;
  *SamplesEcke[0][3]= (EgelbC1 + EgelbC2) / 2;  



  U1();
  F3();
  Bone();
  U1();
  warten(1000);

  uint16_t blauR1, blauG1, blauB1, blauC1;
  PCA9548A(0);
  tcsKante.getRawData(&blauR1, &blauG1, &blauB1, &blauC1);
  warten(1000);

  uint16_t EblauR1, EblauG1, EblauB1, EblauC1;
  PCA9548A(1);
  tcsEcke.getRawData(&EblauR1, &EblauG1, &EblauB1, &EblauC1);


  B2();

  uint16_t blauR2, blauG2, blauB2, blauC2;
  PCA9548A(0);
  tcsKante.getRawData(&blauR2, &blauG2, &blauB2, &blauC2);

  uint16_t EblauR2, EblauG2, EblauB2, EblauC2;
  PCA9548A(1);
  tcsEcke.getRawData(&EblauR2, &EblauG2, &EblauB2, &EblauC2);

  *SamplesKante[1][0]= (blauR1 + blauR2) / 2;
  *SamplesKante[1][1]= (blauG1 + blauG2) / 2;
  *SamplesKante[1][2]= (blauB1 + blauB2) / 2;
  *SamplesKante[1][3]= (blauC1 + blauC2) / 2;

  *SamplesEcke[1][0]= (EblauR1 + EblauR2) / 2;
  *SamplesEcke[1][1]= (EblauG1 + EblauG2) / 2;
  *SamplesEcke[1][2]= (EblauB1 + EblauB2) / 2;
  *SamplesEcke[1][3]= (EblauC1 + EblauC2) / 2;

  U1();
  F2();
  B2();
  U1();
  warten(1000);

  uint16_t gruenR1, gruenG1, gruenB1, gruenC1;
  PCA9548A(0);
  tcsKante.getRawData(&gruenR1, &gruenG1, &gruenB1, &gruenC1);

  warten(1000);

  uint16_t EgruenR1, EgruenG1, EgruenB1, EgruenC1;
  PCA9548A(1);
  tcsEcke.getRawData(&EgruenR1, &EgruenG1, &EgruenB1, &EgruenC1);

  U2();
  warten(1000);

  uint16_t gruenR2, gruenG2, gruenB2, gruenC2;
  PCA9548A(0);
  tcsKante.getRawData(&gruenR2, &gruenG2, &gruenB2, &gruenC2);
  warten(1000);

  uint16_t EgruenR2, EgruenG2, EgruenB2, EgruenC2;
  PCA9548A(1);
  tcsEcke.getRawData(&EgruenR2, &EgruenG2, &EgruenB2, &EgruenC2);

  *SamplesKante[2][0]= (gruenR1 + gruenR2) / 2;
  *SamplesKante[2][1]= (gruenG1 + gruenG2) / 2;
  *SamplesKante[2][2]= (gruenB1 + gruenB2) / 2;
  *SamplesKante[2][3]= (gruenC1 + gruenC2) / 2;

  *SamplesEcke[2][0]= (EgruenR1 + EgruenR2) / 2;
  *SamplesEcke[2][1]= (EgruenG1 + EgruenG2) / 2;
  *SamplesEcke[2][2]= (EgruenB1 + EgruenB2) / 2;
  *SamplesEcke[2][3]= (EgruenC1 + EgruenC2) / 2;

  U1();
  F3();
  Bone();
  R1();
  L3();
  U2();
  warten(1000);

  uint16_t orangeR1, orangeG1, orangeB1, orangeC1;
  PCA9548A(0);
  tcsKante.getRawData(&orangeR1, &orangeG1, &orangeB1, &orangeC1);

  warten(1000);

  uint16_t EorangeR1, EorangeG1, EorangeB1, EorangeC1;
  PCA9548A(1);
  tcsEcke.getRawData(&EorangeR1, &EorangeG1, &EorangeB1, &EorangeC1);

  U2();
  warten(1000);

  uint16_t orangeR2, orangeG2, orangeB2, orangeC2;
  PCA9548A(0);
  tcsKante.getRawData(&orangeR2, &orangeG2, &orangeB2, &orangeC2);

  warten(1000);

  uint16_t EorangeR2, EorangeG2, EorangeB2, EorangeC2;
  PCA9548A(1);
  tcsEcke.getRawData(&EorangeR2, &EorangeG2, &EorangeB2, &EorangeC2);

  *SamplesKante[3][0]= (orangeR1 + orangeR2) / 2;
  *SamplesKante[3][1]= (orangeG1 + orangeG2) / 2;
  *SamplesKante[3][2]= (orangeB1 + orangeB2) / 2;
  *SamplesKante[3][3]= (orangeC1 + orangeC2) / 2;

  *SamplesEcke[3][0]= (EorangeR1 + EorangeR2) / 2;
  *SamplesEcke[3][1]= (EorangeG1 + EorangeG2) / 2;
  *SamplesEcke[3][2]= (EorangeB1 + EorangeB2) / 2;
  *SamplesEcke[3][3]= (EorangeC1 + EorangeC2) / 2;

  L2();
  R2();
  U2();
  warten(1000);

  uint16_t rotR1, rotG1, rotB1, rotC1;
  PCA9548A(0);
  tcsKante.getRawData(&rotR1, &rotG1, &rotB1, &rotC1);

  warten(1000);

  uint16_t ErotR1, ErotG1, ErotB1, ErotC1;
  PCA9548A(1);
  tcsEcke.getRawData(&ErotR1, &ErotG1, &ErotB1, &ErotC1);

  U2();
  warten(1000);

  uint16_t rotR2, rotG2, rotB2, rotC2;
  PCA9548A(0);
  tcsKante.getRawData(&rotR2, &rotG2, &rotB2, &rotC2);

  warten(1000);

  uint16_t ErotR2, ErotG2, ErotB2, ErotC2;
  PCA9548A(1);
  tcsEcke.getRawData(&ErotR2, &ErotG2, &ErotB2, &ErotC2);

  *SamplesKante[4][0]= (rotR1 + rotR2) / 2;
  *SamplesKante[4][1]= (rotG1 + rotG2) / 2;
  *SamplesKante[4][2]= (rotB1 + rotB2) / 2;
  *SamplesKante[4][3]= (rotC1 + rotC2) / 2;

  *SamplesEcke[4][0]= (ErotR1 + ErotR2) / 2;
  *SamplesEcke[4][1]= (ErotG1 + ErotG2) / 2;
  *SamplesEcke[4][2]= (ErotB1 + ErotB2) / 2;
  *SamplesEcke[4][3]= (ErotC1 + ErotC2) / 2;  

  U2();
  R3();
  L1();
  U2();
  warten(1000);

  uint16_t weissR1, weissG1, weissB1, weissC1;
  PCA9548A(0);
  tcsKante.getRawData(&weissR1, &weissG1, &weissB1, &weissC1);

  warten(1000);

  uint16_t EweissR1, EweissG1, EweissB1, EweissC1;
  PCA9548A(1);
  tcsEcke.getRawData(&EweissR1, &EweissG1, &EweissB1, &EweissC1);

  U2();
  warten(1000);

  uint16_t weissR2, weissG2, weissB2, weissC2;
  PCA9548A(0);
  tcsKante.getRawData(&weissR2, &weissG2, &weissB2, &weissC2);

  warten(1000);

  uint16_t EweissR2, EweissG2, EweissB2, EweissC2;
  PCA9548A(1);
  tcsEcke.getRawData(&EweissR2, &EweissG2, &EweissB2, &EweissC2);

  *SamplesKante[5][0]= (weissR1 + weissR2) / 2;
  *SamplesKante[5][1]= (weissG1 + weissG2) / 2;
  *SamplesKante[5][2]= (weissB1 + weissB2) / 2;
  *SamplesKante[5][3]= (weissC1 + weissC2) / 2;

  *SamplesEcke[5][0]= (EweissR1 + EweissR2) / 2;
  *SamplesEcke[5][1]= (EweissG1 + EweissG2) / 2;
  *SamplesEcke[5][2]= (EweissB1 + EweissB2) / 2;
  *SamplesEcke[5][3]= (EweissC1 + EweissC2) / 2;

  R2();
  L2();

  Serial2.println("feddisch");

}





//Funktion zum warten via Millis(), da delay() ESP32 blockiert
void warten(long intervall){
  unsigned long currentMillis = millis();
  unsigned long previousMillis = millis();
  while(currentMillis - previousMillis < intervall){
    currentMillis = millis();
  }
}

int getColourDistance(int redSensor, int greenSensor, int blueSensor, int redSample, int greenSample, int blueSample)
{
  // Calculates the Euclidean distance between two RGB colours
  // https://en.wikipedia.org/wiki/Color_difference
  return sqrt(pow(redSensor - redSample, 2) + pow(greenSensor - greenSample, 2) + pow(blueSensor - blueSample, 2));
}

char EckeScan(int SamplesEcke[][5])
{
  char ErgebnisEcke;
  uint16_t redSensor, greenSensor, blueSensor, clearSensor;
  int colourDistance;
  int Farbe;
  PCA9548A(1);
  tcsEcke.getRawData(&redSensor, &greenSensor, &blueSensor, &clearSensor);

  // Iterate through the array to find a matching colour sample
  for (byte i = 0; i < 6; i++)
  {
    colourDistance = getColourDistance(redSensor, greenSensor, blueSensor, SamplesEcke[i][0], SamplesEcke[i][1], SamplesEcke[i][2]);

    if (colourDistance < 50)
    {
      Farbe = SamplesEcke[i][5];
      switch(Farbe){
        case 1: //gelb
          ErgebnisEcke = 'U';        
        case 2: 
          ErgebnisEcke = 'R';
        case 3: 
          ErgebnisEcke = 'L';
        case 4: 
          ErgebnisEcke = 'F';
        case 5: 
          ErgebnisEcke = 'B';
        case 6: 
          ErgebnisEcke = 'D';
      }
      return ErgebnisEcke;
    }
  }
}

char KanteScan(int SamplesKante[][5])
{
  char ErgebnisKante;
  uint16_t redSensor, greenSensor, blueSensor, clearSensor;
  int colourDistance;
  int Farbe;
  PCA9548A(1);
  tcsKante.getRawData(&redSensor, &greenSensor, &blueSensor, &clearSensor);

  // Iterate through the array to find a matching colour sample
  for (byte i = 0; i < 6; i++)
  {
    colourDistance = getColourDistance(redSensor, greenSensor, blueSensor, SamplesKante[i][0], SamplesKante[i][1], SamplesKante[i][2]);

    if (colourDistance < 50)
    {
      Farbe = SamplesKante[i][5];
      switch(Farbe){
        case 1: 
          ErgebnisKante = 'U';        
        case 2:
          ErgebnisKante = 'R';
        case 3: 
          ErgebnisKante = 'L';
        case 4: 
          ErgebnisKante = 'F';
        case 5: 
          ErgebnisKante = 'B';
        case 6: 
          ErgebnisKante = 'D';
      }
      return ErgebnisKante;
    }
  }
}


void Scan()
{

  String CubeDefinitionString = "XXXXUXXXXXXXXRXXXXXXXXFXXXXXXXXDXXXXXXXXLXXXXXXXXBXXXX";   //Erstellen eines Cube Strings im Richtigen Format; dieser wird als Input für den Lösealgorythmus genutzt
                                                                                            //X als Platzhalter für eingelsenen Werte

  CubeDefinitionString.setCharAt(5, KanteScan(SamplesKante));        //Austauschen der Platzhalter an den richtigen Stellen im String gegen die eingescannten Werte
  warten(1000);                                           //Kurzer Delay, um Multiplexer und Farbsensor Zeit zu geben
  CubeDefinitionString.setCharAt(0, EckeScan(SamplesEcke));         //Das Austauschen und das Drehen erfolgt nach einer vorher festgelegten Sequenz und Prositionen

  U1();                                                 //Drehen des Würfels damit alle Sticker eingescannt werden
  warten(1000);

  CubeDefinitionString.setCharAt(1, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(6, EckeScan(SamplesEcke));

  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(3, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(8, EckeScan(SamplesEcke));

  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(7, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(2, EckeScan(SamplesEcke));

  U1();
  R1();
  L3();
  U4();
  warten(1000);

  CubeDefinitionString.setCharAt(23, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(18, EckeScan(SamplesEcke));

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(21, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(26, EckeScan(SamplesEcke));

  U2();
  R3();
  L1();
  F1();
  R1();
  L3();
  U4();
  warten(1000);

  CubeDefinitionString.setCharAt(19, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(24, EckeScan(SamplesEcke));

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(25, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(20, EckeScan(SamplesEcke));

  U2();
  R3();
  L1();
  F3();
  R2();
  L2();
  U4();
  warten(1000);

  CubeDefinitionString.setCharAt(32, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(27, EckeScan(SamplesEcke));

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(30, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(35, EckeScan(SamplesEcke));

  U2();
  R2();
  L2();
  D1();
  R2();
  L2();
  U4();
  warten(1000);

  CubeDefinitionString.setCharAt(28, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(33, EckeScan(SamplesEcke));

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(34, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(29, EckeScan(SamplesEcke));

  U2();
  R2();
  L2();
  D3();
  R3();
  L1();
  U4();
  warten(1000);

  CubeDefinitionString.setCharAt(48, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(53, EckeScan(SamplesEcke));

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(50, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(45, EckeScan(SamplesEcke));

  U2();
  R1();
  L3();
  Bone();
  R3();
  L1();
  U4();
  warten(1000);

  CubeDefinitionString.setCharAt(52, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(47, EckeScan(SamplesEcke));

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(46, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(51, EckeScan(SamplesEcke));

  U2();
  R1();
  L3();
  B3();
  B3();
  F1();
  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(39, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(44, EckeScan(SamplesEcke));

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(41, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(36, EckeScan(SamplesEcke));

  U1();
  F3();
  Bone();
  L1();
  F1();
  B3();
  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(43, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(38, EckeScan(SamplesEcke));

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(37, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(42, EckeScan(SamplesEcke));

  U1();
  F3();
  Bone();
  L3();
  F3();
  Bone();
  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(14, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(9, EckeScan(SamplesEcke));

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(12, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(17, EckeScan(SamplesEcke));

  U1();
  F1();
  B3();
  R1();
  F3();
  Bone();
  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(10, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(15, EckeScan(SamplesEcke));

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(16, KanteScan(SamplesKante));
  warten(1000);
  CubeDefinitionString.setCharAt(11, EckeScan(SamplesEcke));

  U1();
  F1();
  B3();
  R3();
  CubeDefinitionString = CubeDefinitionString + "\n";
  
  Serial2.print(CubeDefinitionString);
  Serial.print(CubeDefinitionString);
  Serial.print("CubeString versandt");
  //warten(10000);

}

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
void U4() {
  gelb.move(3200);
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


String RPiEmpfangen(){
  while (Serial2.available() == 0){}
  warten(1000);
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
      Bone();
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

  Serial2.print('Fertig');
  warten(1000);
  Serial2.flush();


}


String Loesen(String CubeSolveString) 
{


  String Speicherstrg[60];

  int StringCount = 0;

  //Aufteilen den CubeSolveStrings in substrings
  while (CubeSolveString.length() > 0)
    {
      int index = CubeSolveString.indexOf(' ');
      if (index == -1)  // Keine Leertaste gefunden
      {
        Speicherstrg[StringCount++] = CubeSolveString;
        break;
      }
      else
      {
        Speicherstrg[StringCount++] = CubeSolveString.substring(0, index);
        CubeSolveString = CubeSolveString.substring(index+1);
      }
    }
    for (int i = 0; i <= StringCount; i++)
  {

    if (Speicherstrg[i] == "D1")
    {
      D1();
    }

    else if (Speicherstrg[i] == "D2")
    {
      D2();
    }

    else if (Speicherstrg[i] == "D3")
    {
      D3();
    }

    else if (Speicherstrg[i] == "U1")
    {
      U1();
    }

    else if (Speicherstrg[i] == "U2")
    {
      U2();
    }

    else if (Speicherstrg[i] == "U3")
    {
      U3();
    }

    else if (Speicherstrg[i] == "L1")
    {
      L1();
    }

    else if (Speicherstrg[i] == "L2")
    {
      L2();
    }

    else if (Speicherstrg[i] == "L3")
    {
      L3();
    }

    else if (Speicherstrg[i] == "B1")
    {
      Bone();
    }

    else if (Speicherstrg[i] == "B2")
    {
      B2();
    }

    else if (Speicherstrg[i] == "B3")
    {
      B3();
    }

    else if (Speicherstrg[i] == "F1")
    {
      F1();
    }

    else if (Speicherstrg[i] == "F2")
    {
      F2();
    }

    else if (Speicherstrg[i] == "F3")
    {
      F3();
    }

    else if (Speicherstrg[i] == "R1")
    {
      R1();
    }

    else if (Speicherstrg[i] == "R2")
    {
      R2();
    }

    else if (Speicherstrg[i] == "R3")
    {
      R3();
    }
  }
  Serial2.println("Fertig gelöst!");
}


void setup() {

  //Serielle und I2C Verbindung öffnen
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Wire.begin();

	// Festsetzen der Maximalgeschwinigkeit und Beschleunigungsfaktoren der Motoren
	// initial speed and the target position
	gruen.setMaxSpeed(20000);
	gruen.setAcceleration(10000);
	gruen.setSpeed(10000);
	

  weiss.setMaxSpeed(20000);
	weiss.setAcceleration(10000);
	weiss.setSpeed(10000);

  rot.setMaxSpeed(20000);
	rot.setAcceleration(10000);
	rot.setSpeed(10000);


  orange.setMaxSpeed(20000);
	orange.setAcceleration(10000);
	orange.setSpeed(10000);


  blau.setMaxSpeed(20000);
	blau.setAcceleration(10000);
	blau.setSpeed(10000);


  gelb.setMaxSpeed(20000);
	gelb.setAcceleration(10000);
	gelb.setSpeed(10000);

}



void loop ()
{
  Serial.print("Start des Loops!");
  String start = RPiEmpfangen();
  warten(1000);
  if (start = "calib"){
    Kalibrieren(&SamplesKante, &SamplesEcke);
  }
  Verdrehen();
  String weiter = RPiEmpfangen();
  while (weiter != "GO"){
    weiter = RPiEmpfangen();
  }
  weiter = "";
  Serial2.flush();
  Scan();
  String CubeString = RPiEmpfangen();
  Loesen(CubeString);

  Serial.print("Ende des Loops erreicht");
};