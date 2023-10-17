//AccelStepper Library inculdieren
#include <AccelStepper.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"


//Pins für serielle Verbindung definieren
#define RXD2 16 
#define TXD2 17
#define CONFIG_ESP_IPC_TASK_STACK_SIZE 2048

//initialisierung beider Farbsensoren
Adafruit_TCS34725 tcsKante = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_TCS34725 tcsEcke = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

//Funktion zur Auswahl des Multiplexerkanals
void PCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // PCA9548A addresse ist 0x70
  Wire.write(1 << bus);          //Byte senden zur Auswahl des Kanals
  Wire.endTransmission();
}



uint16_t SamplesKante[6][5] = {
  { 0,  0,  0,  0,  1},
  { 0,  0,  0,  0,  2},
  { 0,  0,  0,  0,  3},
  { 0,  0,  0,  0,  4},
  { 0,  0,  0,  0,  5},
  { 0,  0,  0,  0,  6},
};

uint16_t SamplesEcke[6][5] = {
  { 0,  0,  0,  0,  1},
  { 0,  0,  0,  0,  2},
  { 0,  0,  0,  0,  3},
  { 0,  0,  0,  0,  4},
  { 0,  0,  0,  0,  5},
  { 0,  0,  0,  0,  6},
};

void Kalibrieren(uint16_t (&SamplesKante)[6][5], uint16_t (&SamplesEcke)[6][5]) 
{



  U2();
  warten(1000);
  static uint16_t KR1, KG1, KB1, KC1;

  PCA9548A(0);
  tcsKante.getRawData(&KR1, &KG1, &KB1, &KC1);

  warten(1000);
  static uint16_t ER1, EG1, EB1, EC1;
  PCA9548A(1);
  tcsEcke.getRawData(&ER1, &EG1, &EB1, &EC1);

  U1();
  warten(1000);
  Serial.println("Test");

  static uint16_t KR2, KG2, KB2, KC2;
  PCA9548A(0);
  tcsKante.getRawData(&KR2, &KG2, &KB2, &KC2);

  warten(1000);
  static uint16_t ER2, EG2, EB2, EC2;
  PCA9548A(1);
  tcsEcke.getRawData(&ER2, &EG2, &EB2, &EC2);

  SamplesKante[0][0]= (KR1 + KR2) / 2;
  SamplesKante[0][1]= (KG1 + KG2) / 2;
  SamplesKante[0][2]= (KB1 + KB2) / 2;
  SamplesKante[0][3]= (KC1 + KC2) / 2;

  SamplesEcke[0][0]= (ER1 + ER2) / 2;
  SamplesEcke[0][1]= (EG1 + EG2) / 2;
  SamplesEcke[0][2]= (EB1 + EB2) / 2;
  SamplesEcke[0][3]= (EC1 + EC2) / 2;  

  Serial.println("Test2");

  U1();
  F3();
  Bone();
  U1();
  warten(1000);


  PCA9548A(0);
  tcsKante.getRawData(&KR1, &KG1, &KB1, &KC1);
  warten(1000);

  PCA9548A(1);
  tcsEcke.getRawData(&ER1, &EG1, &EB1, &EC1);


  U2();


  PCA9548A(0);
  tcsKante.getRawData(&KR2, &KG2, &KB2, &KC2);

  warten(1000);


  PCA9548A(1);
  tcsEcke.getRawData(&ER2, &EG2, &EB2, &EC2);

  SamplesKante[1][0]= (KR1 + KR2) / 2;
  SamplesKante[1][1]= (KG1 + KG2) / 2;
  SamplesKante[1][2]= (KB1 + KB2) / 2;
  SamplesKante[1][3]= (KC1 + KC2) / 2;

  SamplesEcke[1][0]= (ER1 + ER2) / 2;
  SamplesEcke[1][1]= (EG1 + EG2) / 2;
  SamplesEcke[1][2]= (EB1 + EB2) / 2;
  SamplesEcke[1][3]= (EC1 + EC2) / 2;

  U1();
  F2();
  B2();
  U1();
  warten(1000);


  PCA9548A(0);
  tcsKante.getRawData(&KR1, &KG1, &KB1, &KC1);

  warten(1000);


  PCA9548A(1);
  tcsEcke.getRawData(&ER1, &EG1, &EB1, &EC1);

  U2();
  warten(1000);


  PCA9548A(0);
  tcsKante.getRawData(&KR2, &KG2, &KB2, &KC2);
  warten(1000);

  PCA9548A(1);
  tcsEcke.getRawData(&ER2, &EG2, &EB2, &EC2);

  SamplesKante[2][0]= (KR1 + KR2) / 2;
  SamplesKante[2][1]= (KG1 + KG2) / 2;
  SamplesKante[2][2]= (KB1 + KB2) / 2;
  SamplesKante[2][3]= (KC1 + KC2) / 2;

  SamplesEcke[2][0]= (ER1 + ER2) / 2;
  SamplesEcke[2][1]= (EG1 + EG2) / 2;
  SamplesEcke[2][2]= (EB1 + EB2) / 2;
  SamplesEcke[2][3]= (EC1 + EC2) / 2;

  U1();
  F3();
  Bone();
  R1();
  L3();
  U2();
  warten(1000);


  PCA9548A(0);
  tcsKante.getRawData(&KR1, &KG1, &KB1, &KC1);

  warten(1000);


  PCA9548A(1);
  tcsEcke.getRawData(&ER1, &EG1, &EB1, &EC1);

  U2();
  warten(1000);


  PCA9548A(0);
  tcsKante.getRawData(&KR2, &KG2, &KB2, &KC2);

  warten(1000);


  PCA9548A(1);
  tcsEcke.getRawData(&ER2, &EG2, &EB2, &EC2);

  SamplesKante[3][0]= (KR1 + KR2) / 2;
  SamplesKante[3][1]= (KG1 + KG2) / 2;
  SamplesKante[3][2]= (KB1 + KB2) / 2;
  SamplesKante[3][3]= (KC1 + KC2) / 2;

  SamplesEcke[3][0]= (ER1 + ER2) / 2;
  SamplesEcke[3][1]= (EG1 + EG2) / 2;
  SamplesEcke[3][2]= (EB1 + EB2) / 2;
  SamplesEcke[3][3]= (EC1 + EC2) / 2;

  L2();
  R2();
  U2();
  warten(1000);


  PCA9548A(0);
  tcsKante.getRawData(&KR1, &KG1, &KB1, &KC1);

  warten(1000);


  PCA9548A(1);
  tcsEcke.getRawData(&ER1, &EG1, &EB1, &EC1);

  U2();
  warten(1000);


  PCA9548A(0);
  tcsKante.getRawData(&KR2, &KG2, &KB2, &KC2);

  warten(1000);
  Serial.println("test3");

  PCA9548A(1);
  tcsEcke.getRawData(&ER2, &EG2, &EB2, &EC2);

  SamplesKante[4][0]= (KR1 + KR2) / 2;
  SamplesKante[4][1]= (KG1 + KG2) / 2;
  SamplesKante[4][2]= (KB1 + KB2) / 2;
  SamplesKante[4][3]= (KC1 + KC2) / 2;

  SamplesEcke[4][0]= (ER1 + ER2) / 2;
  SamplesEcke[4][1]= (EG1 + EG2) / 2;
  SamplesEcke[4][2]= (EB1 + EB2) / 2;
  SamplesEcke[4][3]= (EC1 + EC2) / 2;  


  R3();
  L1();
  U2();
  warten(1000);


  PCA9548A(0);
  tcsKante.getRawData(&KR1, &KG1, &KB1, &KC1);

  warten(1000);


  PCA9548A(1);
  tcsEcke.getRawData(&ER1, &EG1, &EB1, &EC1);

  U2();
  warten(1000);


  PCA9548A(0);
  tcsKante.getRawData(&KR2, &KG2, &KB2, &KC2);

  warten(1000);


  PCA9548A(1);
  tcsEcke.getRawData(&ER2, &EG2, &EB2, &EC2);

  Serial.println("Test4");

  SamplesKante[5][0]= (KR1 + KR2) / 2;
  SamplesKante[5][1]= (KG1 + KG2) / 2;
  SamplesKante[5][2]= (KB1 + KB2) / 2;
  SamplesKante[5][3]= (KC1 + KC2) / 2;

  SamplesEcke[5][0]= (ER1 + ER2) / 2;
  SamplesEcke[5][1]= (EG1 + EG2) / 2;
  SamplesEcke[5][2]= (EB1 + EB2) / 2;
  SamplesEcke[5][3]= (EC1 + EC2) / 2;

  warten(3000);

  Serial.println("Test5");

  R2();
  L2();
  Serial.println("EndeTest");
  warten(5000);
  Serial2.flush();
  warten(10000);


  Serial2.print("feddisch");

  Serial.print(SamplesEcke[0][0]);
  Serial.println("");

  for(int a = 0; a < 6; a++)
  {
    for(int b = 0; b < 5; b++)
    {
      Serial.print(SamplesEcke[a][b]);
      Serial.print(" ");
    }
    Serial.print("\n");
  }  
  Serial.println("");
  for(int a = 0; a < 6; a++)
  {
    for(int b = 0; b < 5; b++)
    {
      Serial.print(SamplesKante[a][b]);
      Serial.print(" ");
    }
    Serial.print("\n");
  }  

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

char EckeScan(uint16_t SamplesEcke[][5])
{

  char ErgebnisEcke;
  uint16_t redSensor, greenSensor, blueSensor, clearSensor;
  int colourDistance;
  int Farbe;
  PCA9548A(1);
  tcsEcke.getRawData(&redSensor, &greenSensor, &blueSensor, &clearSensor);

  // Iterate through the array to find a matching colour sample
  for (int i = 0; i < 6; i++)
  {
    colourDistance = getColourDistance(redSensor, greenSensor, blueSensor, SamplesEcke[i][0], SamplesEcke[i][1], SamplesEcke[i][2]);

    if (colourDistance < 120)
    {
      Farbe = SamplesEcke[i][4];
      switch(Farbe){
        case 1: //gelb
          Serial.println("Gelb an Ecke!");
          ErgebnisEcke = 'U';
          break;        
        case 2: 
          Serial.println("Blau an Ecke!");
          ErgebnisEcke = 'R';
          break;
        case 3: 
          Serial.println("Gruen an Ecke!");
          ErgebnisEcke = 'L';
          break;
        case 4: 
          Serial.println("Orange an Ecke!");
          ErgebnisEcke = 'F';
          break;
        case 5: 
          Serial.println("Rot an Ecke!");
          ErgebnisEcke = 'B';
          break;
        case 6: 
          Serial.println("Weiss an Ecke!");
          ErgebnisEcke = 'D';
          break;
      }
      return ErgebnisEcke;
    }
  }
  Serial.println("ACHTUNG Fehler bei Erkennung an Ecke!");
  return 'X';
}

char KanteScan(uint16_t SamplesKante[][5])
{
  char ErgebnisKante;
  uint16_t redSensor, greenSensor, blueSensor, clearSensor;
  int colourDistance;
  int Farbe;
  PCA9548A(0);
  tcsKante.getRawData(&redSensor, &greenSensor, &blueSensor, &clearSensor);
  // Iterate through the array to find a matching colour sample
  for (int i = 0; i < 6; i++)
  {
    colourDistance = getColourDistance(redSensor, greenSensor, blueSensor, SamplesKante[i][0], SamplesKante[i][1], SamplesKante[i][2]);

    if (colourDistance < 120)
    {
      Farbe = SamplesKante[i][4];
      switch(Farbe){
        case 1: 
          Serial.println("Gelb an Kante!");
          ErgebnisKante = 'U'; 
          break;      
        case 2:
          Serial.println("Blau an Kante!");
          ErgebnisKante = 'R';
          break;
        case 3: 
          Serial.println("Gruen an Kante!");
          ErgebnisKante = 'L';
          break;
        case 4: 
          Serial.println("Orange an Kante!");
          ErgebnisKante = 'F';
          break;
        case 5: 
          Serial.println("Rot an Kante!");
          ErgebnisKante = 'B';
          break;
        case 6: 
          Serial.println("Weiss an Kante!");
          ErgebnisKante = 'D';
          break;
      }
      return ErgebnisKante;
    }
  }
  Serial.println("ACHTUNG Fehler bei Erkennung an Kante!");
  return 'X';
}


void Scan()
{

  String CubeDefinitionString = "XXXXUXXXXXXXXRXXXXXXXXFXXXXXXXXDXXXXXXXXLXXXXXXXXBXXXX";   //Erstellen eines Cube Strings im Richtigen Format; dieser wird als Input für den Lösealgorythmus genutzt
                                                                                            //X als Platzhalter für eingelsenen Werte
  U4();
  warten(1000);
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


void Loesen(String CubeSolveString) 
{


  String Speicherstrg[30];

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
  String start = "";
  Serial.print("Start des Loops!");
  start = RPiEmpfangen();
  warten(1000);
  if (start == "calib"){
    Kalibrieren(SamplesKante, SamplesEcke);
  }
  start = "";
  Verdrehen();
  String weiter = RPiEmpfangen();
  while (weiter != "GO"){
    weiter = RPiEmpfangen();
  }
  weiter = "";
  Serial2.flush();
  Scan();
  String CubeString = RPiEmpfangen();
  warten(1000);
  Serial.print(CubeString);
  Loesen(CubeString);

  Serial.print("Ende des Loops erreicht");
};