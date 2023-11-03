//Bibliotheken einbinden
#include <AccelStepper.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"


//Pins für serielle Verbindung definieren
#define RXD2 16 
#define TXD2 17

//initialisierung beider Farbsensoren
Adafruit_TCS34725 tcsKante = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_TCS34725 tcsEcke = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

//Definieren der Motoren-Pins

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

// Motoren als Instanzen erstellen
AccelStepper gruen(motorInterfaceType, gruenstepPin, gruendirPin);
AccelStepper weiss(motorInterfaceType, weissstepPin, weissdirPin);
AccelStepper rot(motorInterfaceType, rotstepPin, rotdirPin);
AccelStepper orange(motorInterfaceType, orangestepPin, orangedirPin);
AccelStepper blau(motorInterfaceType, blaustepPin, blaudirPin);
AccelStepper gelb(motorInterfaceType, gelbstepPin, gelbdirPin);

//90-Grad drehungen aller Seiten in beide Richungen als Funktionen definieren
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
  gelb.move(-800);
  gelb.runToPosition();
}
void U2() {
  gelb.move(-1600);
  gelb.runToPosition();
}
void U3() {
  gelb.move(800);
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

//Funktion zur Auswahl des Multiplexerkanals
void PCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  //I²C Verbindung starten. PCA9548A Addresse ist 0x70
  Wire.write(1 << bus);          //Byte senden zur Auswahl des Kanals
  Wire.endTransmission();
}

//Funktion zum warten via Millis(), da delay() ESP32 blockiert
void warten(long intervall){
  unsigned long currentMillis = millis();   //Vergangene Millisekunden zum Zeitpunkt des Aufrufens der Funktion
  unsigned long previousMillis = millis();  
  while(currentMillis - previousMillis < intervall){    //Prüfen, ob übergebenes Intervall abgelaufen ist
    currentMillis = millis();
  }
}

//2Dimensionale Arrays, in denen die Vergleichswerte beim Kalibrieren gespeichert werden. Jeweils einen für jeden Sensor
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

//Funktion nimmt sich jeweils 2 Werte einer Farbe pro Sensor und speichert diese Werte in die Arrays zum Vergleichen. 
void Kalibrieren(uint16_t (&SamplesKante)[6][5], uint16_t (&SamplesEcke)[6][5]) 
{

  U2();
  warten(1000);                                   //Wartefunktionen geben den Sensoren Zeit, dass der Würfel gut verdreht ist und noch nicht wieder dreht, wenn gescannt wird
  static uint16_t KR1, KG1, KB1, KC1;

  PCA9548A(0);                                    //Korrespondierender Kanal zum Sensor muss ausgewählt werden
  tcsKante.getRawData(&KR1, &KG1, &KB1, &KC1);    //Funktion gibt die Werte des Sensors an die uint16_t

  warten(1000);
  static uint16_t ER1, EG1, EB1, EC1;
  PCA9548A(1);
  tcsEcke.getRawData(&ER1, &EG1, &EB1, &EC1);

  U1();
  warten(1000);

  static uint16_t KR2, KG2, KB2, KC2;
  PCA9548A(0);
  tcsKante.getRawData(&KR2, &KG2, &KB2, &KC2);

  warten(1000);
  static uint16_t ER2, EG2, EB2, EC2;
  PCA9548A(1);
  tcsEcke.getRawData(&ER2, &EG2, &EB2, &EC2);

  SamplesKante[0][0]= (KR1 + KR2) / 2;    //Eingabe in Array über arithmetisches Mittel der 2 Farben 
  SamplesKante[0][1]= (KG1 + KG2) / 2;
  SamplesKante[0][2]= (KB1 + KB2) / 2;
  SamplesKante[0][3]= (KC1 + KC2) / 2;

  SamplesEcke[0][0]= (ER1 + ER2) / 2;
  SamplesEcke[0][1]= (EG1 + EG2) / 2;
  SamplesEcke[0][2]= (EB1 + EB2) / 2;
  SamplesEcke[0][3]= (EC1 + EC2) / 2;  


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


  SamplesKante[5][0]= (KR1 + KR2) / 2;
  SamplesKante[5][1]= (KG1 + KG2) / 2;
  SamplesKante[5][2]= (KB1 + KB2) / 2;
  SamplesKante[5][3]= (KC1 + KC2) / 2;

  SamplesEcke[5][0]= (ER1 + ER2) / 2;
  SamplesEcke[5][1]= (EG1 + EG2) / 2;
  SamplesEcke[5][2]= (EB1 + EB2) / 2;
  SamplesEcke[5][3]= (EC1 + EC2) / 2;


  R2();
  L2();
  warten(1000);
  Serial2.flush();
  warten(1000);


  Serial2.print("feddisch");  //Signalisiert dem RPi, dass Kalibrierung fertig ist

}



//Funktion berechnet den Abstand des gemessenen RGB-Wertes mit der Euklidischen Vektornorm
int getColourDistance(int redSensor, int greenSensor, int blueSensor, int redSample, int greenSample, int blueSample)
{
  return sqrt(pow(redSensor - redSample, 2) + pow(greenSensor - greenSample, 2) + pow(blueSensor - blueSample, 2));
}


//Wenn diese Funktion aufgerufen wird, scannt der Farbsensor die momentanen RGB-Werte. Diese werden Verglichen mit den Werten aus der Kalibrierung
char EckeScan(uint16_t SamplesEcke[][5])  //Übergabe der Vergleichswerte
{

  char ErgebnisEcke;
  uint16_t redSensor, greenSensor, blueSensor, clearSensor;
  int colourDistance;
  int Farbe;
  PCA9548A(1);
  tcsEcke.getRawData(&redSensor, &greenSensor, &blueSensor, &clearSensor);  //Scannt momentane RGB-Werte

  // Durch den Array iterieren, um die passende Farbe zu finden.
  for (int i = 0; i < 6; i++)
  {
    colourDistance = getColourDistance(redSensor, greenSensor, blueSensor, SamplesEcke[i][0], SamplesEcke[i][1], SamplesEcke[i][2]);  //Berechnet den Abstand zum gerade ausgewählten Vergleichswert des Arrays

    if (colourDistance < 150)   //Intervalle können angepasst werden, um zuverlässige Ergebnisse zu erzielen
    {
      Farbe = SamplesEcke[i][4];
      switch(Farbe){
        case 1: //gelb
          ErgebnisEcke = 'U';
          break;        
        case 2: 
          ErgebnisEcke = 'R';
          break;
        case 3: 
          ErgebnisEcke = 'L';
          break;
        case 4: 
          ErgebnisEcke = 'F';
          break;
        case 5: 
          ErgebnisEcke = 'B';
          break;
        case 6: 
          ErgebnisEcke = 'D';
          break;
      }
      return ErgebnisEcke;
    }
  }
  return 'X'; //Bei keiner gefundenen Farbe wird ein "X" als Fehler zurückgegeben
}

char KanteScan(uint16_t SamplesKante[][5])
{
  char ErgebnisKante;
  uint16_t redSensor, greenSensor, blueSensor, clearSensor;
  int colourDistance;
  int Farbe;
  PCA9548A(0);
  tcsKante.getRawData(&redSensor, &greenSensor, &blueSensor, &clearSensor);
  for (int i = 0; i < 6; i++)
  {
    colourDistance = getColourDistance(redSensor, greenSensor, blueSensor, SamplesKante[i][0], SamplesKante[i][1], SamplesKante[i][2]);

    if (colourDistance < 150)
    {
      Farbe = SamplesKante[i][4];
      switch(Farbe){
        case 1: 
          ErgebnisKante = 'U'; 
          break;      
        case 2:
          ErgebnisKante = 'R';
          break;
        case 3: 
          ErgebnisKante = 'L';
          break;
        case 4: 
          ErgebnisKante = 'F';
          break;
        case 5: 
          ErgebnisKante = 'B';
          break;
        case 6: 
          ErgebnisKante = 'D';
          break;
      }
      return ErgebnisKante;
    }
  }
  return 'X';
}

//Funktion empfängt den zu verdrehenden String und führt diese Sequenz aus
void Verdrehen()
{
 
  String strVerdreh = RPiEmpfangen(); //Zu verdrehender String wird Empfangen und zum ausführen gespeichertz

  //String wird nach einzelnen Charakteren durchlaufen. Zugehörige Verdrehung wird ausgeführt
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

  Serial2.print('Fertig');
  warten(1000);
  Serial2.flush();        //Stellt zuverlässige serielle Übertragung da, durch löschen des Buffers

}

//Analog zur Verdrehen Funktion, anstelle z.B: bei "D" D1, wird ein D3 verwendet, um die Verdrehung Rückgängig zu machen
//String wurde bereits am RPi umgedreht
void Zurueckdrehen()
{

  String strVerdreh = RPiEmpfangen();

  for(int i = 0; i <= strVerdreh.length(); i++){
    if (strVerdreh[i] == 'D')
    {
      D3();
    }

    else if (strVerdreh[i] == 'U')
    {
      U3();
    }

    else if (strVerdreh[i] == 'L')
    {
      L3();
    }

    else if (strVerdreh[i] == 'B')
    {
      B3();
    }

    else if (strVerdreh[i] == 'F')
    {
      F3();
    }

    else if (strVerdreh[i] == 'R')
    {
      R3();
    }  
  }


}


//Funktion scannt über eine festgelegte Sequenz den Würfel über die Sensoren ab. Speichert diese Ergebnisse in den CubeDefinitionString
void Scan()
{

  String CubeDefinitionString = "XXXXUXXXXXXXXRXXXXXXXXFXXXXXXXXDXXXXXXXXLXXXXXXXXBXXXX";   //Erstellen eines Cube Strings im Richtigen Format; dieser wird als Input für den Lösealgorythmus genutzt
                                                                                            //X als Platzhalter für eingelsenen Werte
  U3(); 	    //U3-U1 wird benutzt um ein zuverlässiges Scanergebnis zu erzielen. Die obere Fläche wird "platt gedreht"
  U1();
  warten(1000);
  CubeDefinitionString.setCharAt(5, KanteScan(SamplesKante));         //Austauschen der Platzhalter an den richtigen Stellen im String gegen die eingescannten Werte
  warten(1000);                                                       //Kurzer Delay, um Multiplexer und Farbsensor Zeit zu geben
  CubeDefinitionString.setCharAt(0, EckeScan(SamplesEcke));           //Das Austauschen und das Drehen erfolgt nach einer vorher festgelegten Sequenz und Prositionen

  U1();                                                               //Drehen des Würfels damit alle Sticker eingescannt werden
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
  U3();
  U1();
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
  U3();
  U1();
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
  U3();
  U1();
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
  U3();
  U1();
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
  U3();
  U1();
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
  U3();
  U1();
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
  CubeDefinitionString = CubeDefinitionString + "\n";   //\n wird als Signal dass der String vorbei ist benutzt
  
  Serial2.print(CubeDefinitionString);      //Überträgt den String an den RPi zum lösen

}



//Funktionen zum Empfangen von Daten des RPi
String RPiEmpfangen(){
  while (Serial2.available() == 0){}    //Prüft, ob Daten vorhanden sind. Bleibt bis dahin in der Schleife
  warten(1000);
  String received = Serial2.readString(); //Liest eingehende serielle Daten
  received.trim();  //kürzt Signale wie \n aus dem String
  return received;
}

//Funktioniert analog, wartet nur auf ein "P" als Signal, dass der String vorbei ist
String RPiEmpfangenLine(){
  while (Serial2.available() == 0){}
  String received = Serial2.readStringUntil('P');
  warten(1000);
  received.trim();
  return received;
}



//Funktion löst den Würfel auf Basis der empfangenen Lösung des RPi
void Loesen(String CubeSolveString) 
{


  String Speicherstrg[30];  //Größe gewählt, um immer über Länge der Lösung zu liegen

  int StringCount = 0;

  //Aufteilen den CubeSolveStrings in substrings, um die einzelnen Lösungsschritte abfragen zu können
  while (CubeSolveString.length() > 0)
    {
      int index = CubeSolveString.indexOf(' ');
      if (index == -1)  // Kein Leerzeichen gefunden, Ende des Teilens
      {
        Speicherstrg[StringCount++] = CubeSolveString;
        break;
      }
      else
      {
        //Speichert die Teile als Substring
        Speicherstrg[StringCount++] = CubeSolveString.substring(0, index);
        CubeSolveString = CubeSolveString.substring(index+1);
      }
    }
    //Schleife geht den geteilten Speicherstrg durch und führt die Lösung aus
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

//setup Code wird einmalig durchgeführt beim Programmstart
void setup() {

  //Serielle und I2C Verbindung öffnen
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial2.setRxBufferSize(1024);  //Buffer vergrößert, um Probleme mit langen Strings zu vermeiden
  Wire.begin();

	// Festsetzen der Maximalgeschwinigkeit und Beschleunigungsfaktoren der Motoren
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


//Schleife wird durchgehend durchlaufen
void loop ()
{
  start = RPiEmpfangen(); //wartet auf Startsignal des Benutzers am RPi
  warten(1000);
  if (start == "calib"){                    //Beim Empfangen des calib Signals wird kalibriert
    Kalibrieren(SamplesKante, SamplesEcke);
  }
  Verdrehen();                              
  String weiter = RPiEmpfangen();           //Wartet auf weitersignal des Benutzers am RPi
  while (weiter != "GO"){
    weiter = RPiEmpfangen();
  }
  Serial2.flush();                          //Flush um zuverlässige serielle Verbindung zu gewährleisten
  Scan();
  String scanPruefung = RPiEmpfangen();     //Erhält das Signal, ob der gescannte Würfel lösbar ist und fortgeführt werden kann
  warten(1000);
  if (scanPruefung == "OK"){                //OK -- führt mit Lösung fort
    String CubeSolveString = RPiEmpfangenLine();
    warten(1000);
    Loesen(CubeSolveString);
  }
  else if(scanPruefung == "NOK"){           //Nicht OK -- Dreht die Verdrehung zurück
    Zurueckdrehen();
  }



};